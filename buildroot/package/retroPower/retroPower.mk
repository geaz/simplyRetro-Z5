################################################################################
#
# RETROPOWER
#
################################################################################

RETROPOWER_VERSION = 01d3978749e4b9772ba89b8908dabaaa2915843f
RETROPOWER_SITE = $(call github,geaz,simplyRetro-z5,$(RETROPOWER_VERSION))
RETROPOWER_DEPENDENCIES = wiringpi

define RETROPOWER_BUILD_CMDS
	$(MAKE) CXX="$(TARGET_CXX)" CC="$(TARGET_CC)" LD="$(TARGET_LD)" -C $(@D) all
endef

define RETROPOWER_INSTALL_TARGET_CMDS
	$(MAKE) CXX="$(TARGET_CXX)" -C $(@D) DESTDIR=$(TARGET_DIR) install
endef

$(eval $(generic-package))
