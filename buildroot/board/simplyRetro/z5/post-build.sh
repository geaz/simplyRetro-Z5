#!/bin/sh

set -u
set -e

# Add a console on tty1
if [ -e ${TARGET_DIR}/etc/inittab ]; then
    grep -qE '^tty1::' ${TARGET_DIR}/etc/inittab || \
	sed -i '/GENERIC_SERIAL/a\
tty1::respawn:/sbin/getty -L  tty1 0 vt100 # HDMI console' ${TARGET_DIR}/etc/inittab
fi

# Set custom init scripts to executable
chmod +x ${TARGET_DIR}/etc/init.d/S40network
chmod +x ${TARGET_DIR}/etc/init.d/S80RetroPower
chmod +x ${TARGET_DIR}/etc/init.d/S85RetroGame

# Disabled Network, SSH and FTP per Default
if [ -e ${TARGET_DIR}/etc/init.d/S40network ]
then 
	mv ${TARGET_DIR}/etc/init.d/S40network ${TARGET_DIR}/etc/init.d/disabled.S40network
fi

if [ -e ${TARGET_DIR}/etc/init.d/S50dropbear ]
then 
	mv ${TARGET_DIR}/etc/init.d/S50dropbear ${TARGET_DIR}/etc/init.d/disabled.S50dropbear
fi

if [ -e ${TARGET_DIR}/etc/init.d/S70vsftpd ]
then
	mv ${TARGET_DIR}/etc/init.d/S70vsftpd ${TARGET_DIR}/etc/init.d/disabled.S70vsftpd
fi
