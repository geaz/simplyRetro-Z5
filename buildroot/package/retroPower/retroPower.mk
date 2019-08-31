################################################################################
#
# RETROPOWER
#
################################################################################

RETROPOWER_VERSION = 7bda933af2956f6e08b172a6a8e2ea882869fc3b
RETROPOWER_SITE = git://github.com/geaz/simplyRetro-z5
RETROPOWER_SITE_METHOD = git
RETROPOWER_DEPENDENCIES = wiringpi

define RETROPOWER_BUILD_CMDS
	$(MAKE) CXX="$(TARGET_CXX) -lm" CC="$(TARGET_CC) -lm" LD="$(TARGET_LD) -lm" -C $(@D) all
endef

define RETROPOWER_INSTALL_TARGET_CMDS
	$(MAKE) CXX="$(TARGET_CXX)" -C $(@D) DESTDIR=$(TARGET_DIR) install
endef

$(eval $(generic-package))
