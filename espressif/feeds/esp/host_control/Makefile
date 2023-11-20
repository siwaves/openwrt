include $(TOPDIR)/rules.mk

PKG:=esp-hosted-fg-control
PKG_NAME:=$(PKG)
PKG_SOURCE_PROTO:=git
PKG_BRANCH:=master
PKG_RELEASE:=1

# legacy and hawkeye header files.
PKG_BUILD_ID:=1

ESP_SOFTWARE_CATEGORY:=ESP Hosted

LOCAL_SRC ?= $(TOPDIR)/espressif/src/hosted_fg

ifeq (exists, $(shell [ -d $(LOCAL_SRC) ] && echo exists))
PKG_REV=$(shell cd $(LOCAL_SRC)/; git describe --dirty --long --always --abbrev=7| sed 's/.*-g//g')
PKG_VERSION:=g$(PKG_REV)
PKG_SOURCE_URL:=
PKG_UNPACK=mkdir -p $(PKG_BUILD_DIR); $(CP) $(LOCAL_SRC)/* $(PKG_BUILD_DIR)/
endif

include $(INCLUDE_DIR)/package.mk

define Package/c_support
  SECTION:=Espressif
  CATEGORY:=$(ESP_SOFTWARE_CATEGORY)
  TITLE:=esp hosted control for c_support
  DEPENDS:=+librt +libnl-tiny
  URL:=http://www.espressif.com
  VARIANT:=c_support
endef

define Package/c_support/description
  c command support for esp hosted fg
endef

define Package/python_support
  SECTION:=Espressif
  CATEGORY:=$(ESP_SOFTWARE_CATEGORY)
  TITLE:=esp hosted control for python_support
  DEPENDS:=+librt +libnl-tiny
  URL:=http://www.espressif.com
  VARIANT:=python_support
endef

define Package/python_support/description
  python command support for esp hosted fg
endef

define Build/Compile/c_support
	CFLAGS="$(TARGET_CPPFLAGS) $(TARGET_CFLAGS)" \
	LDFLAGS="$(TARGET_LDFLAGS)" \
	$(MAKE) -C $(PKG_BUILD_DIR)/host/linux/host_control/c_support all \
	TOOLPREFIX="$(TARGET_CROSS)" \
	LIBS="$(TARGET_LDFLAGS)" \
    VARIANT:=c_support
endef

define Build/Compile/python_support
	CFLAGS="$(TARGET_CPPFLAGS) $(TARGET_CFLAGS)" \
	LDFLAGS="$(TARGET_LDFLAGS)" \
	$(MAKE) -C $(PKG_BUILD_DIR)/host/linux/host_control/python_support all  \
	TOOLPREFIX="$(TARGET_CROSS)" \
	LIBS="$(TARGET_LDFLAGS)" \
    VARIANT:=python_support
endef

define Build/Compile
	$(Build/Compile/$(BUILD_VARIANT))
endef

define Package/c_support/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/host/linux/host_control/c_support/esp-test $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/host/linux/host_control/c_support/esp-stress $(1)/usr/sbin
	$(INSTALL_BIN) ./files/run_esp $(1)/etc/init.d/run_esp
	$(INSTALL_BIN) ./files/esptools $(1)/bin/
endef

define Package/python_support/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_DIR) $(1)/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/host/linux/host_control/python_support/test.py $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/host/linux/host_control/python_support/stress.py $(1)/usr/sbin
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/host/linux/host_control/python_support/*.so $(1)/lib
endef

$(eval $(call BuildPackage,c_support))
$(eval $(call BuildPackage,python_support))


