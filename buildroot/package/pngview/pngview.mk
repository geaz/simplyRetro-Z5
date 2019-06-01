################################################################################
#
# PNGVIEW
#
################################################################################

PNGVIEW_VERSION = c28061521fc84e97f5ae28c92d57130520614014
PNGVIEW_SITE = $(call github,AndrewFromMelbourne,raspidmx,$(PNGVIEW_VERSION))
PNGVIEW_DEPENDENCIES = libpng rpi-userland
PNGVIEW_CFLAGS = -I../common
PNGVIEW_COMMON_LDFLAGS = -L$(STAGING_DIR)/usr/lib -lbcm_host -lpng -lm -lvchostif
PNGVIEW_LDFLAGS = -L$(STAGING_DIR)/usr/lib -lbcm_host -lpng -lm -lvchostif -L../lib -lraspidmx
PNGVIEW_INCLUDES = -I$(STAGING_DIR)/usr/include/ -I$(STAGING_DIR)/usr/include/interface/vcos/pthreads -I$(STAGING_DIR)/usr/include/interface/vmcs_host/linux

define PNGVIEW_BUILD_CMDS
	CFLAGS="$(TARGET_CFLAGS) $(PNGVIEW_CFLAGS)" CXXFLAGS="$(TARGET_CXXFLAGS)" \
		$(MAKE) CXX="$(TARGET_CXX)" CC="$(TARGET_CC)" LDFLAGS="$(PNGVIEW_COMMON_LDFLAGS)" INCLUDES="$(PNGVIEW_INCLUDES)" -C $(@D)/lib all

	CFLAGS="$(TARGET_CFLAGS) $(PNGVIEW_CFLAGS)" CXXFLAGS="$(TARGET_CXXFLAGS)" \
		$(MAKE) CXX="$(TARGET_CXX)" CC="$(TARGET_CC)" LDFLAGS="$(PNGVIEW_LDFLAGS)" INCLUDES="$(PNGVIEW_INCLUDES)" -C $(@D)/pngview all

endef

define PNGVIEW_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/pngview/pngview \
		$(TARGET_DIR)/usr/bin/pngview

	$(INSTALL) -D $(@D)/lib/libraspidmx.so.1 \
		$(TARGET_DIR)/usr/lib/libraspidmx.so.1
endef

$(eval $(generic-package))
