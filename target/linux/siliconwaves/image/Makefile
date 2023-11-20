#
# Copyright (C) 2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/image.mk

FAT32_BLOCK_SIZE=1024
FAT32_BLOCKS=$(shell echo $$(($(CONFIG_SILICONWAVES_SD_BOOT_PARTSIZE)*1024*1024/$(FAT32_BLOCK_SIZE))))

KERNEL_LOADADDR := 0x80200000

define Build/Compile
   $(CP) $(LINUX_DIR)/COPYING $(KDIR)/COPYING.linux
endef

define Device/FitImage
  KERNEL_SUFFIX := -fit-uImage.itb
  KERNEL = kernel-bin | gzip | fit gzip $$(KDIR)/image-$$(DEVICE_DTS).dtb
  KERNEL_NAME := Image
endef

define Device/FitImageLzma
  KERNEL_SUFFIX := -fit-uImage.itb
  KERNEL = kernel-bin | lzma | fit lzma $$(KDIR)/image-$$(DEVICE_DTS).dtb
  KERNEL_NAME := Image
endef

### Image scripts ###
define Build/riscv-sdcard
  rm -f $@.boot
  mkfs.fat -n boot -C $@.boot $(FAT32_BLOCKS)
  mcopy -i $@.boot extlinux-fpga ::extlinux
  mcopy -i $@.boot $(IMAGE_KERNEL) ::$(KERNEL_IMG)
  mcopy -i $@.boot $(KDIR)/image-$(firstword $(DEVICE_DTS)).dtb ::$(firstword $(DEVICE_DTS)).dtb
  ./gen_siliconwaves_sdcard_img.sh $@ $@.boot $(IMAGE_ROOTFS) \
    $(CONFIG_SILICONWAVES_SD_BOOT_PARTSIZE) $(CONFIG_TARGET_ROOTFS_PARTSIZE) \
    $(STAGING_DIR_IMAGE)/$(UBOOT_NAME)-u-boot.itb \
    $(STAGING_DIR_IMAGE)/$(UBOOT_NAME)-u-boot.itb-spl
endef

### Devices ###
define Device/Default
  PROFILES := Default
  DEVICE_DTS_DIR := ../dts
endef

define Device/fpga-board-nor
  $(call Device/FitImageLzma)
  DEVICE_VENDOR := SiliconWaves
  DEVICE_DTS_CONFIG := config@1
  DEVICE_MODEL := FPGA(nor)
  DEVICE_DTS := siliconwaves-fpga
  IMAGES := sysupgrade.bin
  FILESYSTEMS := squashfs
  BLOCKSIZE := 64k
  IMAGE_SIZE := 16384k
  IMAGE/sysupgrade.bin := append-kernel | append-rootfs | pad-rootfs | check-size | append-metadata
  DEVICE_PACKAGES := kmod-led-driver-demo led-user-demo kmod-shortcut-fe-cm iperf3
endef
TARGET_DEVICES += fpga-board-nor

define Device/fpga-board
  DEVICE_VENDOR := SiliconWaves
  DEVICE_MODEL := FPGA(sdcard)
  DEVICE_DTS := siliconwaves-fpga
  KERNEL := kernel-bin | gzip
  KERNEL_IMG := siliconwaves-fpga-kernel.bin
  IMAGES := sdcard.img.gz
  UBOOT_NAME := siliconwaves_fpga
  FILESYSTEMS := ext4
  IMAGE/sdcard.img.gz := riscv-sdcard | append-metadata | gzip
  DEVICE_PACKAGES := kmod-led-driver-demo led-user-demo kmod-shortcut-fe-cm iperf3 \
		     u-boot-siliconwaves_fpga
endef
TARGET_DEVICES += fpga-board

$(eval $(call BuildImage))
