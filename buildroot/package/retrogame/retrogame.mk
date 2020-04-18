################################################################################
#
# Emulation Station
#
################################################################################

RETROGAME_VERSION = e1211cc3b34aadfa405c995aab052b8e82ceba0a
RETROGAME_SITE = git://github.com/adafruit/Adafruit-Retrogame
RETROGAME_SITE_METHOD = git
RETROGAME_LICENSE = MIT

define RETROGAME_BUILD_CMDS
	$(MAKE) CXX="$(TARGET_CXX)" CC="$(TARGET_CC)" LD="$(TARGET_LD)" -C $(@D) all
endef

define RETROGAME_INSTALL_TARGET_CMDS
	$(MAKE) CXX="$(TARGET_CXX)" -C $(@D) DESTDIR=$(TARGET_DIR) install
endef

$(eval $(generic-package))