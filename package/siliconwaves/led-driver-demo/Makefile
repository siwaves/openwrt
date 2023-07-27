#
# Copyright (C) 2019-2020 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk
 
PKG_NAME:=led-driver-demo
PKG_RELEASE:=1
 
include $(INCLUDE_DIR)/package.mk
 
define KernelPackage/led-driver-demo
  SECTION:=utils
  CATEGORY:=siliconwaves
  TITLE:=Siliconwaves led driver demo
  FILES:=$(PKG_BUILD_DIR)/led-driver-demo.ko
  PROVIDES:=$(PKG_NAME)
  AUTOLOAD:=$(call AutoLoad,50,led-driver-demo,1)
endef
 
define KernelPackage/led-driver-demo/Description
Simple led driver
endef

define Build/Compile
  $(MAKE) -C "$(LINUX_DIR)" \
  $(KERNEL_MAKE_FLAGS) \
  M="$(PKG_BUILD_DIR)" \
  EXTRA_CFLAGS="$(BUILDFLAGS)" \
  modules 
endef
 
$(eval $(call KernelPackage,led-driver-demo))