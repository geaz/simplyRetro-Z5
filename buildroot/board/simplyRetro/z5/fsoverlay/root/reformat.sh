#!/bin/sh

echo "Reformating ..."
cat << _EOF_ | fdisk /dev/mmcblk0
p
d
2
n
p
2
$(parted /dev/mmcblk0 -ms unit s p | grep ':ext4::;' | sed 's/:/ /g' | sed 's/s//g' | awk '{ print $2 }')

p
w

_EOF_

reboot