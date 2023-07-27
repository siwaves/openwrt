#
# Copyright (C) 2019-2020 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
PKG_NAME:=led-user-demo
PKG_RELEASE:=1
PKG_BUILD_DIR:=$(BUILD_DIR)/led-user-demo

include $(INCLUDE_DIR)/package.mk

define Package/led-user-demo
  CATEGORY:=siliconwaves
  TITLE:=siliconwaves led light up demo
endef

define Package/led-user-demo/description
siliconwaves led light up test demo
endef
 
define Build/led-user-demo/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) -r ./src/* $(PKG_BUILD_DIR)/
endef

define Package/led-user-demo/install
	echo "Here is Package/install"
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/led-lightup $(1)/bin/
endef

$(eval $(call BuildPackage,led-user-demo))
