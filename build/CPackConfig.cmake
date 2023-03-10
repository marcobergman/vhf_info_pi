# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BUILD_SOURCE_DIRS "/home/marcb/vhf_info_pi;/home/marcb/vhf_info_pi/build")
set(CPACK_CMAKE_GENERATOR "Ninja")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEBIAN_COMPRESSION_TYPE "xz")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "x86_64")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6, libwxgtk3.0-0, wx3.0-i18n, libglu1-mesa (>= 7.0.0), libgl1-mesa-glx (>= 7.0.0), zlib1g, bzip2, libportaudio2,opencpn, bzip2, gzip")
set(CPACK_DEBIAN_PACKAGE_NAME "vhf_info_pi-0.4.8.0-ubuntu-22.10")
set(CPACK_DEBIAN_PACKAGE_RECOMMENDS "xcalib,xdg-utils")
set(CPACK_DEBIAN_PACKAGE_SECTION "misc")
set(CPACK_DEBIAN_PACKAGE_VERSION "0.4.8.0-ov50")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "/usr/share/cmake-3.24/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "vhf_info_pi built using CMake")
set(CPACK_DMG_SLA_USE_RESOURCE_FILE_LICENSE "ON")
set(CPACK_GENERATOR "DEB;TGZ")
set(CPACK_INSTALL_CMAKE_PROJECTS "/home/marcb/vhf_info_pi/build;vhf_info_pi;ALL;/")
set(CPACK_INSTALL_PREFIX "/usr/local")
set(CPACK_MODULE_PATH "/home/marcb/vhf_info_pi/cmake;/home/marcb/vhf_info_pi/cmake")
set(CPACK_NSIS_DISPLAY_NAME "vhf_info_pi")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "vhf_info_pi")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OUTPUT_CONFIG_FILE "/home/marcb/vhf_info_pi/build/CPackConfig.cmake")
set(CPACK_PACKAGE_CONTACT "Marco Bergman")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION "vhf_info_pi PlugIn for OpenCPN")
set(CPACK_PACKAGE_DESCRIPTION_FILE "/home/marcb/vhf_info_pi/README")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "vhf_info_pi PlugIn for OpenCPN")
set(CPACK_PACKAGE_FILE_NAME "vhf_info_pi-0.4.8.0-ubuntu-x86_64-22.10")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "vhf_info_pi")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "vhf_info_pi")
set(CPACK_PACKAGE_NAME "vhf_info_pi")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "opencpn.org")
set(CPACK_PACKAGE_VERSION "0.4.8.0-ov50")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "4")
set(CPACK_PACKAGE_VERSION_PATCH "8")
set(CPACK_PROJECT_CONFIG_FILE "/home/marcb/vhf_info_pi/build/PluginCPackOptions.cmake")
set(CPACK_RESOURCE_FILE_LICENSE "/home/marcb/vhf_info_pi/cmake/gpl.txt")
set(CPACK_RESOURCE_FILE_README "/home/marcb/vhf_info_pi/README")
set(CPACK_RESOURCE_FILE_WELCOME "/usr/share/cmake-3.24/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "ON")
set(CPACK_SOURCE_GENERATOR "TBZ2;TGZ;TXZ;TZ")
set(CPACK_SOURCE_IGNORE_FILES "^/home/marcb/vhf_info_pi/.git/*;^/home/marcb/vhf_info_pi/build*;^vhf_info_pi/*")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/home/marcb/vhf_info_pi/build/CPackSourceConfig.cmake")
set(CPACK_SOURCE_RPM "OFF")
set(CPACK_SOURCE_TBZ2 "ON")
set(CPACK_SOURCE_TGZ "ON")
set(CPACK_SOURCE_TXZ "ON")
set(CPACK_SOURCE_TZ "ON")
set(CPACK_SOURCE_ZIP "OFF")
set(CPACK_STRIP_FILES "TRUE")
set(CPACK_SYSTEM_NAME "Linux")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "Linux")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/home/marcb/vhf_info_pi/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
