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
PKG_MIRROR_HASH:=bd622a5f3546ff0524c9eb03cf4974c9c8c10ed04ec866ce3b3399f595dba654
MAKE_PATH:=$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/opensbi
    SECTION:=boot
    CATEGORY:=Boot Loaders
    DEPENDS:=@TARGET_siliconwaves
    URL:=https://github.com/riscv/opensbi/blob/master/README.md
    VARIANT:=$(subst _,/,$(subst opensbi_,,$(1)))
    TITLE:=OpenSBI generic
    OPENSBI_IMAGE:=
    PLAT:=
endef

define Package/$(PKG_NAME)
  $(Package/opensbi)
  TITLE:=OpenSBI for Siliconwaves w3k
  OPENSBI_IMAGE:=fw_dynamic.bin
  PLAT:=generic
endef

#define Build/Prepare
#endef

export GCC_HONOUR_COPTS=s

MAKE_VARS = \
	CROSS_COMPILE="$(TARGET_CROSS)"

define Build/Compile
	$(eval $(Package/opensbi_$(BUILD_VARIANT))) \
		+$(MAKE_VARS) $(MAKE) -C $(PKG_BUILD_DIR) \
		PLATFORM=$(PLAT)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(STAGING_DIR_IMAGE)
	$(CP) $(PKG_BUILD_DIR)/build/platform/$(PLAT)/firmware/fw_dynamic.bin \
		$(STAGING_DIR_IMAGE)/fw_dynamic-${BUILD_VARIANT}.bin
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
