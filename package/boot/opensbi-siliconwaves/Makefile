#
# Copyright (C) 2020 Tobias Maedel <openwrt@tbspace.de>
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=opensbi-siliconwaves
PKG_VERSION:=v1.0

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/riscv-software-src/opensbi
PKG_SOURCE_VERSION:=48f91ee9c960f048c4a7d1da4447d31e04931e38
PKG_MIRROR_HASH:=f560cbf2104f9326514d6a3eabf7ea1a3aa30ef858a7e5f747e9c0b387ce5e31
MAKE_PATH:=$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
    SECTION:=boot
    CATEGORY:=Boot Loaders
    TITLE:=OpenSBI for siliconWaves w3k Soc
    DEPENDS:=@TARGET_siliconwaves
endef

#define Build/Prepare
#endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) CROSS_COMPILE=$(TARGET_CROSS)  \
		PLATFORM=generic  INSTALL_LIB_PATH=lib FW_PIC=n
endef

define Build/InstallDev
	$(INSTALL_DIR) -p $(STAGING_DIR_IMAGE)
	$(CP) $(PKG_BUILD_DIR)/build/platform/generic/firmware/fw_dynamic.bin  \
	       $(STAGING_DIR_IMAGE)/
endef

define Package/$(PKG_NAME)/install
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
