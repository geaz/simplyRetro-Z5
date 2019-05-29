################################################################################
#
# retroarch
#
################################################################################

RETROARCH_VERSION = 741198ed483dd7489112b0f8dfe4181148991ed7
RETROARCH_SITE = git://github.com/libretro/RetroArch.git
RETROARCH_SITE_METHOD = git
RETROARCH_LICENSE = GPLv3+
RETROARCH_CONF_OPTS += --disable-opengl1
RETROARCH_DEPENDENCIES = host-pkgconf

ifeq ($(BR2_PACKAGE_SDL2),y)
RETROARCH_CONF_OPTS += --enable-sdl2
RETROARCH_DEPENDENCIES += sdl2
else
RETROARCH_CONF_OPTS += --disable-sdl2
ifeq ($(BR2_PACKAGE_SDL),y)
RETROARCH_CONF_OPTS += --enable-sdl
RETROARCH_DEPENDENCIES += sdl
else
RETROARCH_CONF_OPTS += --disable-sdl
endif
endif

# RPI 0 and 1
ifeq ($(BR2_arm1176jzf_s),y)
RETROARCH_CONF_OPTS += --enable-floathard
endif

# RPI 2 and 3
ifeq ($(BR2_cortex_a7),y)
RETROARCH_CONF_OPTS += --enable-floathard
endif
ifeq ($(BR2_arm)$(BR2_cortex_a53),yy)
RETROARCH_CONF_OPTS += --enable-floathard
endif

ifeq ($(BR2_ARM_CPU_HAS_NEON),y)
RETROARCH_CONF_OPTS += --enable-neon
endif

# Add dispamnx renderer and no opengl1.1 for Pi
ifeq ($(BR2_PACKAGE_RPI_FIRMWARE),y)
RETROARCH_CONF_OPTS += --enable-dispmanx
endif

# odroid xu4
ifeq ($(BR2_PACKAGE_RECALBOX_TARGET_XU4),y)
RETROARCH_CONF_OPTS += --enable-floathard
endif

# x86 : SSE
ifeq ($(BR2_X86_CPU_HAS_SSE),y)
RETROARCH_CONF_OPTS += --enable-sse
endif

# Common
RETROARCH_CONF_OPTS += --enable-rgui --enable-xmb --enable-ozone
RETROARCH_CONF_OPTS += --enable-threads --enable-dylib
RETROARCH_CONF_OPTS += --enable-lua
RETROARCH_CONF_OPTS += --enable-networking

# Package dependant

ifeq ($(BR2_PACKAGE_PYTHON3),y)
RETROARCH_CONF_OPTS += --enable-python
RETROARCH_DEPENDENCIES += python
else
RETROARCH_CONF_OPTS += --disable-python
endif

ifeq ($(BR2_PACKAGE_XORG7),y)
RETROARCH_CONF_OPTS += --enable-x11
RETROARCH_DEPENDENCIES += xserver_xorg-server
else
RETROARCH_CONF_OPTS += --disable-x11
endif

ifeq ($(BR2_PACKAGE_ALSA_LIB),y)
RETROARCH_CONF_OPTS += --enable-alsa
RETROARCH_DEPENDENCIES += alsa-lib
else
RETROARCH_CONF_OPTS += --disable-alsa
endif

ifeq ($(BR2_PACKAGE_PULSEAUDIO),y)
RETROARCH_CONF_OPTS += --enable-pulse
RETROARCH_DEPENDENCIES += pulseaudio
else
RETROARCH_CONF_OPTS += --disable-pulse
endif

ifeq ($(BR2_PACKAGE_HAS_LIBGLES),y)
RETROARCH_CONF_OPTS += --enable-opengles
RETROARCH_DEPENDENCIES += libgles
else
RETROARCH_CONF_OPTS += --disable-opengles
endif

ifeq ($(BR2_PACKAGE_HAS_LIBEGL),y)
RETROARCH_CONF_OPTS += --enable-egl
RETROARCH_DEPENDENCIES += libegl
else
RETROARCH_CONF_OPTS += --disable-egl
endif

ifeq ($(BR2_PACKAGE_HAS_LIBOPENVG),y)
RETROARCH_DEPENDENCIES += libopenvg
endif

ifeq ($(BR2_PACKAGE_LIBUSB=y),y)
RETROARCH_CONF_OPTS += --enable-libusb
RETROARCH_DEPENDENCIES += libusb
else
RETROARCH_CONF_OPTS += --disable-libusb
endif

ifeq ($(BR2_PACKAGE_ZLIB),y)
RETROARCH_CONF_OPTS += --enable-zlib
RETROARCH_DEPENDENCIES += zlib
else
RETROARCH_CONF_OPTS += --disable-zlib
endif

ifeq ($(BR2_PACKAGE_HAS_UDEV),y)
RETROARCH_DEPENDENCIES += udev
RETROARCH_CONF_OPTS += --enable-udev
else
RETROARCH_CONF_OPTS += --disable-udev
endif

ifeq ($(BR2_PACKAGE_FREETYPE),y)
RETROARCH_CONF_OPTS += --enable-freetype
RETROARCH_DEPENDENCIES += freetype
else
RETROARCH_CONF_OPTS += --disable-freetype
endif

define RETROARCH_MALI_FIXUP
	# the type changed with the recent sdk
	$(SED) 's|mali_native_window|fbdev_window|g' $(@D)/gfx/drivers_context/mali_fbdev_ctx.c
endef

ifeq ($(BR2_PACKAGE_MALI_OPENGLES_SDK),y)
RETROARCH_PRE_CONFIGURE_HOOKS += RETROARCH_MALI_FIXUP
RETROARCH_CONF_OPTS += --enable-opengles --enable-mali_fbdev
endif

ifeq ($(BR2_i386),y)
RETROARCH_COMPILER_COMMONS_CFLAGS = $(COMPILER_COMMONS_CFLAGS_NOLTO)
RETROARCH_COMPILER_COMMONS_CXXFLAGS = $(COMPILER_COMMONS_CXXFLAGS_NOLTO)
RETROARCH_COMPILER_COMMONS_LDFLAGS = $(COMPILER_COMMONS_LDFLAGS_NOLTO)
else
RETROARCH_COMPILER_COMMONS_CFLAGS = $(COMPILER_COMMONS_CFLAGS_SO)
RETROARCH_COMPILER_COMMONS_CXXFLAGS = $(COMPILER_COMMONS_CXXFLAGS_SO)
RETROARCH_COMPILER_COMMONS_LDFLAGS = $(COMPILER_COMMONS_LDFLAGS_SO)
endif

define RETROARCH_CONFIGURE_CMDS
	(cd $(@D); rm -rf config.cache; \
		$(TARGET_CONFIGURE_ARGS) \
		$(TARGET_CONFIGURE_OPTS) \
		CFLAGS="$(TARGET_CFLAGS) $(RETROARCH_COMPILER_COMMONS_CFLAGS)" \
		CXXFLAGS="$(TARGET_CXXFLAGS) $(RETROARCH_COMPILER_COMMONS_CXXFLAGS)" \
		LDFLAGS="$(TARGET_LDFLAGS) $(RETROARCH_COMPILER_COMMONS_LDFLAGS) -lc" \
		CROSS_COMPILE="$(HOST_DIR)/bin/" \
		PKG_CONFIG_PATH="$(STAGING_DIR)/usr/lib/pkgconfig/" \
		./configure \
		--prefix=/usr \
		$(RETROARCH_CONF_OPTS) \
	)
endef

define RETROARCH_FIX_LIBS
	$(SED) "s|-\([IL]\)/usr|-\1$(STAGING_DIR)/usr|g" $(@D)/config.mk
endef

RETROARCH_POST_CONFIGURE_HOOKS += RETROARCH_FIX_LIBS

define RETROARCH_BUILD_CMDS
	$(MAKE) CXX="$(TARGET_CXX)" CC="$(TARGET_CC)" LD="$(TARGET_LD)" -C $(@D) all
endef

define RETROARCH_INSTALL_TARGET_CMDS
	$(MAKE) CXX="$(TARGET_CXX)" -C $(@D) DESTDIR=$(TARGET_DIR) install
endef

$(eval $(generic-package))

# DEFINITION OF LIBRETRO PLATFORM
RETROARCH_LIBRETRO_PLATFORM =
ifeq ($(BR2_ARM_CPU_ARMV6),y)
RETROARCH_LIBRETRO_PLATFORM += armv6
endif

ifeq ($(BR2_cortex_a7),y)
RETROARCH_LIBRETRO_PLATFORM += armv7
endif

ifeq ($(BR2_cortex_a8),y)
RETROARCH_LIBRETRO_PLATFORM += armv8 cortexa8
endif

ifeq ($(BR2_i386),y)
RETROARCH_LIBRETRO_PLATFORM = unix
endif

ifeq ($(BR2_x86_64),y)
RETROARCH_LIBRETRO_PLATFORM = unix
endif

ifeq ($(BR2_cortex_a15)$(BR2_cortex_a15_a7),y)
RETROARCH_LIBRETRO_PLATFORM += armv7 odroidxu4
endif

ifeq ($(BR2_aarch64)$(BR2_cortex_a53),yy)
RETROARCH_LIBRETRO_PLATFORM += unix
endif

ifeq ($(BR2_arm)$(BR2_cortex_a53),yy)
RETROARCH_LIBRETRO_PLATFORM += armv8
endif

ifeq ($(BR2_ARM_CPU_HAS_NEON),y)
RETROARCH_LIBRETRO_PLATFORM += neon
endif

# SPECIFIC PLATFORM
# Will be equal to rpi1, rpi2, rpi3 if we are on rpi.
# Will be equal to RETROARCH_LIBRETRO_PLATFORM otherwise
RETROARCH_LIBRETRO_BOARD=$(RETROARCH_LIBRETRO_PLATFORM)
#ifeq ($(BR2_PACKAGE_RETROARCH_TARGET_RPI0)),y)
#RETROARCH_LIBRETRO_BOARD=rpi1
#endif
#ifeq ($(BR2_PACKAGE_RETROARCH_TARGET_RPI1)),y)
#RETROARCH_LIBRETRO_BOARD=rpi1
#endif
ifeq ($(BR2_PACKAGE_RETROARCH_TARGET_RPI2)),y)
RETROARCH_LIBRETRO_BOARD=rpi2
endif
ifeq ($(BR2_PACKAGE_RETROARCH_TARGET_RPI3)),y)
RETROARCH_LIBRETRO_BOARD=rpi3
endif