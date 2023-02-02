# ---------------------------------------------------------------------------
# Author:      Jon Gough Copyright:   2020 License:     GPLv3+
# ---------------------------------------------------------------------------

# This file contains changes needed during the make package process depending on the type of package being created

if(CPACK_GENERATOR MATCHES "DEB")
    set(CPACK_PACKAGE_FILE_NAME "vhf_info_pi-0.4.8.0-ubuntu-22.10")
    if(CPACK_DEBIAN_PACKAGE_ARCHITECTURE MATCHES "x86_64")
        set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE )
    endif()
else()
    set(CPACK_PACKAGE_FILE_NAME "vhf_info_pi-0.4.8.0-ubuntu-x86_64-22.10")
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE x86_64)
endif()
