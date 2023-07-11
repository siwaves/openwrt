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
PKG_SOURCE_URL:=https://github.com/siwaves/u-boot
PKG_SOURCE_VERSION:=e702f8843b9e90fac07d6ae728d1bc1a520126c4
PKG_MIRROR_HASH:=ba9c699a97cbe92c67a415032dd8453bb1f516b219ac9c8959115c547e646063

OPENSBI:=$(STAGING_DIR_IMAGE)/fw_dynamic.bin

include $(INCLUDE_DIR)/u-boot.mk
include $(INCLUDE_DIR)/package.mk

define U-Boot/Default
  BUILD_TARGET:=siliconwaves
  BUILD_SUBTARGET:=generic
  UBOOT_IMAGE:=u-boot.itb spl/u-boot-spl.bin
endef

define U-Boot/siliconwaves_fpga
  NAME:=w3k-fpga
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
