console=tty3 quiet logo.nologo loglevel=3 vt.global_cursor_default=0 

boot_delay=0
disable_splash=1
disable_overscan=1
display_rotate=2

hdmi_force_hotplug=1
config_hdmi_boost=7
hdmi_group=2
hdmi_mode=87
hdmi_drive=2
hdmi_cvt=800 480 60 6 0 0 0

dtoverlay=pi3-disable-bt
dtoverlay=gpio-poweroff,gpiopin=7,active_low=1
dtparam=spi=on
dtparam=audio=on



rom start screens: https://retropie.org.uk/forum/topic/4611/runcommand-system-splashscreens

compiling:
gcc main.c -lwiringPi



