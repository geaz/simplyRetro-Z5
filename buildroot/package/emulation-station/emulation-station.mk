################################################################################
#
# Emulation Station
#
################################################################################

EMULATION_STATION_VERSION = v2.7.1
EMULATION_STATION_SITE = git://github.com/RetroPie/EmulationStation
EMULATION_STATION_SITE_METHOD = git
EMULATION_STATION_GIT_SUBMODULES = YES
EMULATION_STATION_LICENSE = MIT
EMULATION_STATION_DEPENDENCIES = sdl2 freeimage boost freetype alsa-lib libgles libcurl vlc

define EMULATION_STATION_RPI_FIXUP
	$(SED) 's|/opt/vc/include|$(STAGING_DIR)/usr/include|g' $(@D)/CMakeLists.txt
	$(SED) 's|/opt/vc/lib|$(STAGING_DIR)/usr/lib|g' $(@D)/CMakeLists.txt
	$(SED) 's|/usr/lib|$(STAGING_DIR)/usr/lib|g' $(@D)/CMakeLists.txt
endef

EMULATION_STATION_PRE_CONFIGURE_HOOKS += EMULATION_STATION_RPI_FIXUP

$(eval $(cmake-package))
