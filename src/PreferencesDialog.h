/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  autopilot_route Plugin
 * Author:   Sean D'Epagnier
 *
 ***************************************************************************
 *   Copyright (C) 2018 by Sean D'Epagnier                                 *
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

#include "vhf_info_pi.h"
#include "VhfInfoUI.h"

class PreferencesDialog : public PreferencesDialogBase
{
public:
    PreferencesDialog(wxWindow *parent, vhf_info_pi &pi )
        : PreferencesDialogBase(parent), m_pi(pi) {}

    bool Show( bool show = true );
private:
    void OnMode( wxChoicebookEvent& event );
    void OnInformation( wxCommandEvent& event );
    void OnCancel( wxCommandEvent& event );
    void OnOk( wxCommandEvent& event );

    vhf_info_pi &m_pi;
};
