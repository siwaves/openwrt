#
# Copyright (C) 2020 Tobias Maedel <openwrt@tbspace.de>
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=opensbi-siliconwaves
PKG_VERSION:=1.0

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/siwaves/opensbi
PKG_SOURCE_VERSION:= 2930e03bf088027296f0a67c4a9741c0f50a9edd
PKG_MIRROR_HASH:=f1b9ea5622902bc4e1247044aa57d28c5fd304ca697ce25b7b469cc74409b386
MAKE_PATH:=$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
    SECTION:=boot
    CATEGORY:=Boot Loaders
    TITLE:=RISC-V OpenSBI For SiliconWaves w3k Soc
    DEPENDS:=@TARGET_siliconwaves_w3k
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
