#
# Copyright (C) 2007-2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

# Note: host depend on libpopt-dev

include $(TOPDIR)/rules.mk

PKG_NAME:=gptfdisk
PKG_REV:=1.0.9
PKG_VERSION:=1.0.9

PKG_SOURCE:=$(PKG_NAME)-$(PKG_REV).tar.gz
PKG_SOURCE_URL:=@SF/gptfdisk
PKG_HASH:=dafead2693faeb8e8b97832b23407f6ed5b3219bc1784f482dd855774e2d50c2

PKG_LICENSE:=BSD-4-Clause
PKG_LICENSE_FILES:=LICENSE

HOST_BUILD_DIR:=$(BUILD_DIR_HOST)/$(PKG_NAME)-$(PKG_VERSION)/$(PKG_NAME)-$(PKG_REV)
HOST_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/host-build.mk

define Host/Compile
	+$(HOST_MAKE_VARS) $(MAKE) $(HOST_JOBS) -C $(HOST_BUILD_DIR) 
endef

define Host/Install
	$(INSTALL_DIR) $(STAGING_DIR_HOST)/bin/
	$(INSTALL_BIN) $(HOST_BUILD_DIR)/sgdisk $(STAGING_DIR_HOST)/bin/
endef

define Host/Clean
	rm -rf $(STAGING_DIR_HOST)/bin/sgdisk
endef

$(eval $(call HostBuild))
