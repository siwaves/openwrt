#
# Copyright (C) 2012-2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk


PKG_VERSION:=2023.01

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/u-boot/u-boot
PKG_SOURCE_VERSION:=62e2ad1ceafbfdf2c44d3dc1b6efc81e768a96b9
PKG_MIRROR_HASH:=be7454f322cac97fbe6613fcde6ff7d20560dd6dae2a2e55ccc0d179129a5195

OPENSBI:=$(STAGING_DIR_IMAGE)/fw_dynamic.bin

include $(INCLUDE_DIR)/u-boot.mk
include $(INCLUDE_DIR)/package.mk

define U-Boot/Default
  BUILD_TARGET:=siliconwaves
  BUILD_SUBTARGET:=generic
  UBOOT_IMAGE:=u-boot.itb spl/u-boot-spl.bin
endef

define U-Boot/siliconwaves_fpga
  NAME:=siliconwaves-fpga
  BUILD_SUBTARGET:=w3k
  BUILD_DEVICES:=siliconwaves-w3k-fpga
  DEPENDS:= +opensbi-siliconwaves
endef

UBOOT_TARGETS:=siliconwaves_fpga

define Build/InstallDev
	$(foreach device,$(BUILD_DEVICES), \
		$(INSTALL_DIR) $(STAGING_DIR_IMAGE)/$(device)
	)
	$(foreach device,$(BUILD_DEVICES), \
		$(CP) $(patsubst %,$(PKG_BUILD_DIR)/%,$(UBOOT_IMAGE)) $(STAGING_DIR_IMAGE)/$(device)/
	)
endef

$(eval $(call BuildPackage/U-Boot))
