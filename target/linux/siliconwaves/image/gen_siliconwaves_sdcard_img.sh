#!/bin/sh

set -x
[ $# -eq 7 ] || {
    echo "SYNTAX: $0 <file> <bootfs image> <rootfs image> <bootfs size> <rootfs size> <uboot file> <uboot-spl file>"
    exit 1
}

OUTPUT="$1"
BOOTFS="$2"
ROOTFS="$3"
BOOTFSSIZE="$4"
ROOTFSSIZE="$5"
UBOOTITB="$6"
UBOOTSPL="$7"

HOLE_SIZE=1
UBOOTSPLSIZE=1
UBOOTITBSIZE=4

UBOOTSPLOFFSET=34 # u-bool-spl start sector 

UBOOTITBOFFSET=$(( $UBOOTSPLSIZE * 1024 * 1024 / 512 + $UBOOTSPLOFFSET ))
BOOTFSOFFSET=$(( $UBOOTITBSIZE * 1024 * 1024 / 512 + $UBOOTITBOFFSET ))
ROOTFSOFFSET=$(( ($BOOTFSSIZE) * 1024 * 1024 / 512 + $BOOTFSOFFSET ))


TOTAL_SIZE=$(( $HOLE_SIZE + $UBOOTSPLSIZE + $UBOOTITBSIZE + $BOOTFSSIZE + $ROOTFSSIZE ))
TOTAL_SECTORS=$(( $TOTAL_SIZE * 1024 * 1024 / 512 + $UBOOTSPLOFFSET))

dd if=/dev/zero of=$OUTPUT bs=512 count=$TOTAL_SECTORS

sgdisk -g --clear --set-alignment=1 \
	--new=1:${UBOOTSPLOFFSET}:+${UBOOTSPLSIZE}M: --change-name=1:'u-boot-spl' --typecode=1:5b193300-fc78-40cd-8002-e86c45580b47 \
	--new=2:${UBOOTITBOFFSET}:+${UBOOTITBSIZE}M: --change-name=2:'uboot-itb' --typecode=2:2e54b353-1271-4842-806f-e436d6af6985 \
	--new=3:${BOOTFSOFFSET}:+${BOOTFSSIZE}M: --change-name=3:'boot' --typecode=3:ebd0a0a2-b9e5-4433-87c0-68b6b72699c7 \
	--new=4:${ROOTFSOFFSET}:-0 --change-name=4:'rootfs' --attributes=3:set:2 \
        $OUTPUT

dd bs=512 if="$UBOOTSPL" of="$OUTPUT" seek="$UBOOTSPLOFFSET" conv=notrunc
dd bs=512 if="$UBOOTITB" of="$OUTPUT" seek="$UBOOTITBOFFSET" conv=notrunc
dd bs=512 if="$BOOTFS" of="$OUTPUT" seek="$BOOTFSOFFSET" conv=notrunc
dd bs=512 if="$ROOTFS" of="$OUTPUT" seek="$ROOTFSOFFSET" conv=notrunc

