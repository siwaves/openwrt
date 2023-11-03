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

include $(INCLUDE_DIR)/u-boot.mk
include $(INCLUDE_DIR)/package.mk

define U-Boot/Default
  BUILD_TARGET:=siliconwaves
  BUILD_DEVICES=$(1)
  BUILD_SUBTARGET:=generic
  UBOOT_IMAGE:=u-boot.itb
  DTS_DIR:=arch/riscv/dts
endef

define U-Boot/siliconwaves_fpga
  NAME:=siliconwaves FPGA board
  OPENSBI:=opensbi-siliconwaves
  BUILD_DEVICES:=siliconwaves-w3k-fpga
  UBOOT_DTS:=siliconwaves-fpga.dtb
  DEPENDS:= +opensbi-siliconwaves
endef
UBOOT_MAKE_FLAGS += \
  OPENSBI=$(STAGING_DIR_IMAGE)/fw_dynamic-${OPENSBI}.bin

UBOOT_TARGETS:=siliconwaves_fpga

define Build/InstallDev
	$(INSTALL_DIR) $(STAGING_DIR_IMAGE)
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(UBOOT_IMAGE) $(STAGING_DIR_IMAGE)/$(BUILD_VARIANT)-$(UBOOT_IMAGE)
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/spl/u-boot-spl.bin $(STAGING_DIR_IMAGE)/$(BUILD_VARIANT)-$(UBOOT_IMAGE)-spl
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(DTS_DIR)/$(UBOOT_DTS) $(STAGING_DIR_IMAGE)/$(UBOOT_DTS)
endef

$(eval $(call BuildPackage/U-Boot))
