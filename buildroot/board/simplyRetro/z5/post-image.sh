#!/bin/bash

set -e

BOARD_DIR="$(dirname $0)"
BOARD_NAME="$(basename ${BOARD_DIR})"
GENIMAGE_CFG="${BOARD_DIR}/genimage/genimage-${BOARD_NAME}.cfg"
GENIMAGE_TMP="${BUILD_DIR}/genimage.tmp"

cp board/simplyRetro/${BOARD_NAME}/genimage/config.txt ${BINARIES_DIR}/config.txt
cp board/simplyRetro/${BOARD_NAME}/genimage/cmdline.txt ${BINARIES_DIR}/cmdline.txt
cp board/simplyRetro/${BOARD_NAME}/genimage/retrogame.cfg ${BINARIES_DIR}/retrogame.cfg
cp board/simplyRetro/${BOARD_NAME}/genimage/wpa_supplicant.conf ${BINARIES_DIR}/wpa_supplicant.conf

rm -rf "${GENIMAGE_TMP}"

genimage                           \
	--rootpath "${TARGET_DIR}"     \
	--tmppath "${GENIMAGE_TMP}"    \
	--inputpath "${BINARIES_DIR}"  \
	--outputpath "${BINARIES_DIR}" \
	--config "${GENIMAGE_CFG}"

exit $?
