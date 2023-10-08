#
# Copyright (C) 2016-2023 GitHub 
#
# This is free software, licensed under the GNU General Public License v3.
# See /LICENSE for more information.

include $(TOPDIR)/rules.mk

PKG_NAME:=default-settings-siliconwaves
PKG_VERSION:=1
PKG_RELEASE:=1
PKG_LICENSE:=GPLv3
PKG_LICENSE_FILES:=LICENSE

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  SECTION:=base
  CATEGORY:=siliconwaves
  TITLE:=Default Settings Siliconwaves
  PKGARCH:=all
  DEPENDS:=
endef

define Package/$(PKG_NAME)/description
siliconwaves default settings
endef

define Build/Compile
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/etc/uci-defaults
	$(INSTALL_BIN) ./files/default-settings $(1)/etc/uci-defaults/99-default-settings
endef

$(eval $(call BuildPackage,$(PKG_NAME)))

