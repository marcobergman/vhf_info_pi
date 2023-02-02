/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  VHF Info Plugin
 * Author:   Marco Bergman
 *
 ***************************************************************************
 *   Copyright (C) 2023 by Marco Bergman                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.         *
 ***************************************************************************
 */

#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/aui/aui.h>

#include "plugingl/pidc.h"

#include "json/json.h"

#include "vhf_info_pi.h"
#include "concanv.h"

#include "PreferencesDialog.h"
#include "icons.h"

double heading_resolve(double degrees, double offset=0)
{
    while(degrees < offset-180)
        degrees += 360;
    while(degrees >= offset+180)
        degrees -= 360;
    return degrees;
}

// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void *ppimgr)
{
    return new vhf_info_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p)
{
    delete p;
}

waypoint::waypoint(double lat, double lon, wxString n, wxString guid,
                   double ar, double ab)
    : wp(lat, lon), name(n), GUID(guid), arrival_radius(ar), arrival_bearing(ab)
{
}


//-----------------------------------------------------------------------------
//
//    VHF_Info PlugIn Implementation
//
//-----------------------------------------------------------------------------

vhf_info_pi::vhf_info_pi(void *ppimgr)
    : opencpn_plugin_116(ppimgr)
{
    // Create the PlugIn icons
    initialize_images();
    m_ConsoleCanvas = NULL;
    m_PreferencesDialog = NULL;
    m_avg_sog=0;
    m_declination = NAN;
	
// Create the PlugIn icons  -from shipdriver
// loads png file for the listing panel icon
    wxFileName fn;
    auto path = GetPluginDataDir("vhf_info_pi");
    fn.SetPath(path);
    fn.AppendDir("data");
    fn.SetFullName("ap_route_panel.png");

    path = fn.GetFullPath();

    wxInitAllImageHandlers();

    wxLogDebug(wxString("Using icon path: ") + path);
    if (!wxImage::CanRead(path)) {
        wxLogDebug("Initiating image handlers.");
        wxInitAllImageHandlers();
    }
    wxImage panelIcon(path);
    if (panelIcon.IsOk())
        m_panelBitmap = wxBitmap(panelIcon);
    else
        wxLogWarning("VHF_Info panel icon has NOT been loaded");
// End of from Shipdriver	
	
}

//---------------------------------------------------------------------------------------------------------
//
//          PlugIn initialization and de-init
//
//---------------------------------------------------------------------------------------------------------

int vhf_info_pi::Init(void)
{
    AddLocaleCatalog( PLUGIN_CATALOG_NAME );

    // Read Config
    wxFileConfig *pConf = GetOCPNConfigObject();
    pConf->SetPath ( _T( "/Settings/VhfInfo" ) );
    preferences &p = prefs;

    // Mode
    p.mode = pConf->Read("Mode", "Route Position Bearing");
    p.xte_multiplier = pConf->Read("XTEP", 1.0);
    p.route_position_bearing_mode = (preferences::RoutePositionBearingMode)
        pConf->Read("RoutePositionBearingMode", 0L);
    p.route_position_bearing_distance = pConf->Read("RoutePositionBearingDistance", 100);
    p.route_position_bearing_time = pConf->Read("RoutePositionBearingTime", 100);
    p.route_position_bearing_max_angle = pConf->Read("RoutePositionBearingMaxAngle", 30);
    
    // Active Route Window
    wxString labels[2] = {pConf->Read("ActiveRouteItems0", "XTE;BRG;RNG;TTG;VMG;Highway;Deactivate;"),
                          pConf->Read("ActiveRouteItems1", "XTE;Route ETA;Route RNG;Route TTG;Highway;")};
    for(int i=0; i<2; i++) {
        while(labels[i].size()) {
            p.active_route_labels[i][labels[i].BeforeFirst(';')] = true;
            labels[i] = labels[i].AfterFirst(';');
        }
    }

    // options
    p.confirm_bearing_change = (bool)pConf->Read("ConfirmBearingChange", 0L);
//    p.intercept_route = (bool)pConf->Read("InterceptRoute", 1L);
    p.computation = pConf->Read("Computation", "Great Circle") == "Mercator" ? preferences::MERCATOR : preferences::GREAT_CIRCLE;

    // Boundary
    p.boundary_guid = pConf->Read("Boundary", "");
    p.boundary_width = pConf->Read("BoundaryWidth", 30);

    // NMEA output
    p.rate = pConf->Read("NMEARate", 1L);
    p.magnetic = (bool)pConf->Read("NMEAMagnetic", 0L);
    wxString sentences = pConf->Read("NMEASentences", "APB;");
    while(sentences.size()) {
        p.nmea_sentences[sentences.BeforeFirst(';')] = true;
        sentences = sentences.AfterFirst(';');
    }

    PlugInHandleVhfInfo(true);
    m_Timer.Connect(wxEVT_TIMER, wxTimerEventHandler
                    ( vhf_info_pi::OnTimer ), NULL, this);

    return (WANTS_OVERLAY_CALLBACK |
            WANTS_OPENGL_OVERLAY_CALLBACK |
            WANTS_CURSOR_LATLON       |
            WANTS_NMEA_SENTENCES      |
            WANTS_NMEA_EVENTS         |
            WANTS_AIS_SENTENCES       |
            WANTS_PLUGIN_MESSAGING    |
            WANTS_PREFERENCES         |
            WANTS_CONFIG);
}

bool vhf_info_pi::DeInit(void)
{    
    PlugInHandleVhfInfo(false);
    delete m_PreferencesDialog;

    m_Timer.Disconnect(wxEVT_TIMER, wxTimerEventHandler( vhf_info_pi::OnTimer ), NULL, this);
    
    RemovePlugInTool(m_leftclick_tool_id);

    // save config
    wxFileConfig *pConf = GetOCPNConfigObject();
    pConf->SetPath ( _T( "/Settings/VhfInfo" ) );

    if(m_ConsoleCanvas) {
        wxPoint p = GetFrameAuiManager()->GetPane(m_ConsoleCanvas).floating_pos;
        pConf->Write("PosX", p.x);
        pConf->Write("PosY", p.y);
    }
    delete m_ConsoleCanvas;
   
    preferences &p = prefs;

    // Mode
    pConf->Write("Mode", p.mode);
    pConf->Write("XTEP", p.xte_multiplier);
    pConf->Write("RoutePositionBearingMode", (int)p.route_position_bearing_mode);
    pConf->Write("RoutePositionBearingDistance", p.route_position_bearing_distance);
    pConf->Write("RoutePositionBearingTime", p.route_position_bearing_time);
    pConf->Write("RoutePositionBearingMaxAngle", p.route_position_bearing_max_angle);
    // Active Route Window
    for(int i=0; i<2; i++) {
        wxString labels;
        for(std::map<wxString, bool>::iterator it = p.active_route_labels[i].begin();
            it != p.active_route_labels[i].end(); it++)
            if(p.active_route_labels[i][it->first])
                labels += it->first + ";";
        pConf->Write("ActiveRouteItems"+wxString::Format("%d", i), labels);
    }
    // Waypoint Arrival
    pConf->Write("ConfirmBearingChange", p.confirm_bearing_change);
    pConf->Write("Computation", p.computation == preferences::MERCATOR ? "Mercator" : "Great Circle");

    // Boundary
    pConf->Write("Boundary", p.boundary_guid);
    pConf->Write("BoundaryWidth", p.boundary_width);

    // NMEA output
    pConf->Write("NMEARate", p.rate);
    pConf->Write("NMEAMagnetic", p.magnetic);
    wxString sentences;
    for(std::map<wxString, bool>::iterator it = p.nmea_sentences.begin();
        it != p.nmea_sentences.end(); it++)
        if(p.nmea_sentences[it->first])
            sentences += it->first + ";";
    pConf->Write("NMEASentences", sentences);

    return true;
}

int vhf_info_pi::GetAPIVersionMajor()
{
    return OCPN_API_VERSION_MAJOR;
}

int vhf_info_pi::GetAPIVersionMinor()
{
    return OCPN_API_VERSION_MINOR;
}

int vhf_info_pi::GetPlugInVersionMajor()
{
    return PLUGIN_VERSION_MAJOR;
}

int vhf_info_pi::GetPlugInVersionMinor()
{
    return PLUGIN_VERSION_MINOR;
}

//  Converts  icon.cpp file to an image. Original process
//wxBitmap *vhf_info_pi::GetPlugInBitmap()
//{
//    return new wxBitmap(_img_vhf_info->ConvertToImage().Copy());
//}

// Shipdriver uses the climatology_panel.png file to make the bitmap.
wxBitmap *vhf_info_pi::GetPlugInBitmap()  { return &m_panelBitmap; }
// End of shipdriver process


wxString vhf_info_pi::GetCommonName()
{
    return _T(PLUGIN_COMMON_NAME);
//    return _("VHF Info");
}

wxString vhf_info_pi::GetShortDescription()
{
    return _(PLUGIN_SHORT_DESCRIPTION);
//    return _("VHF Info PlugIn for OpenCPN");
}

wxString vhf_info_pi::GetLongDescription()
{
    return _(PLUGIN_LONG_DESCRIPTION); 
//    return _("VHF Info PlugIn for OpenCPN Configurable VHF Info following abilities.");
}

void vhf_info_pi::SetColorScheme(PI_ColorScheme cs)
{
    m_colorscheme = cs;
    if( m_ConsoleCanvas )
        m_ConsoleCanvas->SetColorScheme(cs);
}

void vhf_info_pi::ShowPreferencesDialog( wxWindow* parent )
{
    if( NULL == m_PreferencesDialog )
        m_PreferencesDialog = new PreferencesDialog( parent, *this );

    m_PreferencesDialog->ShowModal();
    
    delete m_PreferencesDialog;
    m_PreferencesDialog = NULL;
}

bool vhf_info_pi::RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp)
{
    piDC odc(dc);
    Render(odc, *vp);
    return true;
}

bool vhf_info_pi::RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp)
{
    piDC odc;
    glEnable( GL_BLEND );
    Render(odc, *vp);
    glDisable( GL_BLEND );
    return true;
}

void vhf_info_pi::ShowConsoleCanvas()
{
    if( !m_ConsoleCanvas ) {
        wxFileConfig *pConf = GetOCPNConfigObject();
        pConf->SetPath ( _T( "/Settings/VhfInfo" ) );
        wxPoint pos(pConf->Read("PosX", 0L), pConf->Read("PosY", 50));
        
        m_ConsoleCanvas = new ConsoleCanvas( GetOCPNCanvasWindow(), *this );
        wxSize sz = m_ConsoleCanvas->GetSize();
        wxAuiPaneInfo p = wxAuiPaneInfo().
            Name( "Console Canvas" ).
            Caption( "Console Canvas" ).
            CaptionVisible( false ).
            TopDockable(false).
            BottomDockable(false).
            LeftDockable(true).
            RightDockable(true).
            MinSize(wxSize(20, 20)).
            BestSize(sz).
            FloatingSize(sz).
            FloatingPosition(pos).
            Float().
            Gripper(false);
        wxAuiManager *pauimgr = GetFrameAuiManager();
        pauimgr->AddPane(m_ConsoleCanvas, p);
        pauimgr->Update();
        SetColorScheme(m_colorscheme);
        m_ConsoleCanvas->Show();
    }

    m_ConsoleCanvas->ShowWithFreshFonts();
    GetFrameAuiManager()->GetPane(m_ConsoleCanvas).Show(true);
    GetFrameAuiManager()->Update();
    wxSize sz = GetFrameAuiManager()->GetPane(m_ConsoleCanvas).floating_size;
    sz.y++; // horrible stupid hack to make things look right
    GetFrameAuiManager()->GetPane(m_ConsoleCanvas).FloatingSize(sz);
    GetFrameAuiManager()->Update();

}

void vhf_info_pi::ShowPreferences()
{
    if( !m_PreferencesDialog ) {
        m_PreferencesDialog = new PreferencesDialog( GetOCPNCanvasWindow(), *this );
        wxIcon icon;
        icon.CopyFromBitmap(*_img_vhf_info);
        m_PreferencesDialog->SetIcon(icon);
    }

    m_PreferencesDialog->Show();
}

wxString vhf_info_pi::StandardPath()
{
    wxStandardPathsBase& std_path = wxStandardPathsBase::Get();
    wxString s = wxFileName::GetPathSeparator();

#if defined(__WXMSW__)
    wxString stdPath  = std_path.GetConfigDir();
#elif defined(__WXGTK__) || defined(__WXQT__)
    wxString stdPath  = std_path.GetUserDataDir();
#elif defined(__WXOSX__)
    wxString stdPath  = (std_path.GetUserConfigDir() + s + _T("opencpn"));
#endif

    stdPath += s + _T("plugins");
    if (!wxDirExists(stdPath))
      wxMkdir(stdPath);

    stdPath += s + _T("vhf_info");

#ifdef __WXOSX__
    // Compatibility with pre-OCPN-4.2; move config dir to
    // ~/Library/Preferences/opencpn if it exists
    wxString oldPath = (std_path.GetUserConfigDir() + s + _T("plugins") + s + _T("weatherfax"));
    if (wxDirExists(oldPath) && !wxDirExists(stdPath)) {
	wxLogMessage("weatherfax_pi: moving config dir %s to %s", oldPath, stdPath);
	wxRenameFile(oldPath, stdPath);
    }
#endif

    if (!wxDirExists(stdPath))
      wxMkdir(stdPath);

    stdPath += s; // is this necessary?
    return stdPath;
}

double vhf_info_pi::Declination()
{
    if(prefs.magnetic &&
       (!m_declinationTime.IsValid() || (wxDateTime::Now() - m_declinationTime).GetSeconds() > 1200)) {
        m_declination = NAN;
        SendPluginMessage("WMM_VARIATION_BOAT_REQUEST", "");
    }
    return m_declination;
}

bool vhf_info_pi::GetConsoleInfo(double &sog, double &cog,
                                        double &bearing, double &xte,
                                        double *rng, double *nrng)
{
    sog = m_lastfix.Sog;
    cog = m_lastfix.Cog;
    bearing = m_current_bearing;
    xte = m_current_xte;

    if(rng) {
        double rbrg;
        DistanceBearing(m_lastfix.Lat, m_lastfix.Lon,
                        m_current_wp.lat, m_current_wp.lon, &rbrg, rng);
        *nrng = *rng * acos((rbrg - bearing)*M_PI/180);
    }
    
    return true;
}

void vhf_info_pi::DeactivateRoute()
{
    SendPluginMessage("OCPN_RTE_DEACTIVATED", "");
    m_current_wp.GUID = "";    
}

void vhf_info_pi::Render(piDC &dc, PlugIn_ViewPort &vp)
{
    if(m_active_guid.IsEmpty())
        return;
    
    wxPoint r1, r2;
    GetCanvasPixLL(&vp, &r1, m_current_wp.lat, m_current_wp.lon);
    GetCanvasPixLL(&vp, &r2, m_lastfix.Lat, m_lastfix.Lon);
    dc.SetPen(wxPen(*wxRED, 2));

    #if 1
    double r = hypot(r1.x-r2.x, r1.y-r2.y);
    r1.x = r2.x+r*sin(m_current_bearing*M_PI/180);
    r1.y = r2.y-r*cos(m_current_bearing*M_PI/180);
    #endif
    
    dc.DrawLine(r1.x, r1.y, r2.x, r2.y);
}


void vhf_info_pi::OnTimer( wxTimerEvent & )
{
    if(m_active_guid.IsEmpty())
        return;

    // for now poll active route (not efficient)
    if((wxDateTime::Now() - m_active_request_time).GetSeconds() > 10) {
        if(m_active_guid.IsEmpty())
            return;
    }
    
    if(!m_active_guid.IsEmpty()) {
        m_ConsoleCanvas->UpdateRouteData();
    }
}


void vhf_info_pi::SetCursorLatLon(double lat, double lon)
{
    wxPoint pos = wxGetMouseState().GetPosition();
    if(pos == m_cursor_position)
        return;
    m_cursor_position = pos;
}

void vhf_info_pi::SetNMEASentence(wxString &sentence)
{
    // Check for conflicting autopilot messages
}

void vhf_info_pi::SetPositionFixEx(PlugIn_Position_Fix_Ex &pfix)
{
    m_lastfix = pfix;
    if(pfix.nSats > 3)
        m_avg_sog = m_avg_sog*.9 + pfix.Sog*.1;
}

static bool ParseMessage(wxString &message_body, Json::Value &root)
{
    Json::Reader reader;
    if(reader.parse( std::string(message_body), root ))
        return true;
    
    wxLogMessage(wxString("vhf_info_pi: Error parsing JSON message: ") + reader.getFormattedErrorMessages() );
    return false;
}


void vhf_info_pi::SetPluginMessage(wxString &message_id, wxString &message_body)
{
    // construct the JSON root object
    Json::Value  root;
    // construct a JSON parser
    wxString    out;
    
    if(message_id == wxS("VHF_INFO_PI")) {
        return; // nothing yet
    } else if(message_id == wxS("AIS")) {
    } else if(message_id == _T("WMM_VARIATION_BOAT")) {
        if(ParseMessage( message_body, root )) {
            wxString(root["Decl"].asString()).ToDouble(&m_declination);
            m_declinationTime = wxDateTime::Now();
        }
    } else if(message_id == "OCPN_RTE_ACTIVATED") {
        if(ParseMessage( message_body, root )) {
            // when route is activated, request the route
            ShowConsoleCanvas();
        }
    } else if(message_id == "OCPN_WPT_ACTIVATED") {
        wxString guid = root["GUID"].asString();
        m_last_wpt_activated_guid = guid;
        //ShowConsoleCanvas();
    } else if(message_id == "OCPN_WPT_ARRIVED") {
    } else if(message_id == "OCPN_RTE_DEACTIVATED" || message_id == "OCPN_RTE_ENDED") {
        m_Timer.Stop();
        m_active_guid = "";
        m_active_request_guid = "";
        if( m_ConsoleCanvas ) {
            GetFrameAuiManager()->GetPane(m_ConsoleCanvas).Float();
            GetFrameAuiManager()->GetPane(m_ConsoleCanvas).Show(false);
            GetFrameAuiManager()->Update();
        }
    } else if(message_id == "OCPN_ROUTE_RESPONSE") {
        if(!ParseMessage( message_body, root ))
            return;
        
        if(root["error"].asBool())
            return;
        
        wxString guid = root["GUID"].asString();
        if(guid != m_active_request_guid)
            return;
        
        m_active_request_time = wxDateTime::Now();        
        m_active_guid = guid;
        Json::Value w = root["waypoints"];
        int size = w.size();
        m_route.clear();
        double lat0 = m_lastfix.Lat, lon0 = m_lastfix.Lon;
        for(int i=0; i<size; i++) {
            double lat = w[i]["lat"].asDouble(), lon = w[i]["lon"].asDouble();
            double brg;
            DistanceBearing(lat0, lon0, lat, lon, &brg, 0);
            waypoint wp(lat, lon, w[i]["Name"].asString(), w[i]["GUID"].asString(),
                        w[i]["ArrivalRadius"].asDouble(), brg);
            
            // set arrival bearing to current course for first waypoint
            if(i == 0 && m_avg_sog > 1)
                wp.arrival_bearing = m_lastfix.Cog;
            m_route.push_back(wp);
            lat0 = lat, lon0 = lon;
        }
        
        // add interception points
// Take out to match Sean 098226d
//        if(prefs.intercept_route) {
//            ap_route_iterator it = m_route.begin(), closest;
//            wp p0 = *it;
//            wp boat(m_lastfix.Lat, m_lastfix.Lon);
//            double mindist = INFINITY;
//            // find closest segment
//            for(it++; it!=m_route.end(); it++) {
//                waypoint p1 = *it;
//                wp x = ClosestSeg(boat, p0, p1);
//                double dist = Distance(boat, x);
//                if(dist < mindist) {
//                    mindist = dist;
//                    closest = it;
//                }
//                p0 = p1;
//            }
//            
//            // do we intersect this segment on current course?
//            wp p1 = *closest, w;
//            closest--;
//            p0 = *closest;
//            // insert boat position after p0
//            double brg;
//            DistanceBearing(boat.lat, boat.lon, p0.lat, p0.lon, &brg, 0);
//            waypoint boat_wp(boat.lat, boat.lon, "boat", "", 0, brg);
//            m_route.insert(closest, boat_wp);
//            
//            // if intersect, insert this position
//            if(Intersect(boat, m_lastfix.Cog, p0, p1, w)) {
//                double brg;
//                DistanceBearing(w.lat, w.lon, boat.lat, boat.lon, &brg, 0);                        waypoint i(w.lat, w.lon, "intersection", "",
//                                                                                                              closest->arrival_radius, brg);
//                m_route.insert(closest, i);
//            }
//        }
       
//        m_current_wp.GUID = "";
        Recompute();
        m_Timer.Start(1000/prefs.rate);
    }
}

void vhf_info_pi::RearrangeWindow()
{
    SetColorScheme(PI_ColorScheme());
}

