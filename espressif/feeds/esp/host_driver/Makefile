include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG:=esp-hosted-fg-driver
PKG_NAME:=$(PKG)
PKG_SOURCE_PROTO:=git
PKG_BRANCH:=master
PKG_RELEASE:=1

ESP_SOFTWARE_CATEGORY:=ESP Hosted

LOCAL_SRC ?= $(TOPDIR)/espressif/src/hosted_fg

ifeq (exists, $(shell [ -d $(LOCAL_SRC) ] && echo exists))
PKG_REV=$(shell cd $(LOCAL_SRC)/; git describe --dirty --long --always --abbrev=7| sed 's/.*-g//g')
PKG_VERSION:=g$(PKG_REV)
PKG_SOURCE_URL:=
PKG_UNPACK=mkdir -p $(PKG_BUILD_DIR); $(CP) $(LOCAL_SRC)/* $(PKG_BUILD_DIR)/
endif

ifeq ($(DUMP)$(PKG_VERSION),)
  PKG_REV:=$(shell git ls-remote $(PKG_SOURCE_URL) $(PKG_BRANCH) | cut -b -7)
  PKG_VERSION:=g$(PKG_REV)
endif

CUSTOM_DIRECTORY?=0
ifeq ($(CUSTOM_DIRECTORY),1)
  PKG_BUILD_DIR:=$(KERNEL_BUILD_DIR)/$(PKG_NAME)
else
  PKG_BUILD_DIR:=$(KERNEL_BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
endif

ESP_TARGET_IF:=spi
ESP_CHIP_SERS:=ESP32-c6

include $(INCLUDE_DIR)/package.mk

define KernelPackage/$(PKG_NAME)
    SECTION:=Espressif
    CATEGORY:=$(ESP_SOFTWARE_CATEGORY)
    URL:=http://www.espressif.com
    MAINTAINER:=Espressif IOT 
    TITLE:=Espressif Wireless LAN Driver
    DEPENDS:=@TARGET_siliconwaves +kmod-bluetooth
    FILES:=$(PKG_BUILD_DIR)/host/linux/host_driver/esp32/esp32_$(ESP_TARGET_IF).ko
    AUTOLOAD:=$(call AutoLoad,33,esp32_$(ESP_TARGET_IF))
endef

define KernelPackage/$(PKG_NAME)/Description
    host kenrel driver support for Espressif (ESP32-c6) with SPI/SDIO interface
endef

define Build/Prepare
	rm -rf $(PKG_BUILD_DIR)
	mkdir -p $(PKG_BUILD_DIR); $(CP) $(LOCAL_SRC)/* $(PKG_BUILD_DIR)/
endef

#NOSTDINC_FLAGS := \
#	$(KERNEL_NOSTDINC_FLAGS) \
#	-I$(PKG_BUILD_DIR)/common/include \
#	-I$(PKG_BUILD_DIR)/host/linux/host_driver/esp32 \
#	-I$(PKG_BUILD_DIR)/host/linux/host_driver/esp32/spi \
#	-I$(PKG_BUILD_DIR)/host/linux/host_driver/esp32/sdio
	
	
define Build/Compile
	@echo "[DEON] --- compile, debug info"
	export MAKE="$(MAKE)"; \
	export LINUX_VERSION="$(LINUX_VERSION)"; \
	export LINUX_DIR="$(LINUX_DIR)"; \
	export ARCH="$(LINUX_KARCH)"; \
	export TARGET_CROSS="$(TARGET_CROSS)"; \
	export TARGET_CFLAGS="$(TARGET_CFLAGS)"; \
	export TARGET_LDFLAGS="$(TARGET_LDFLAGS)"; \
	export CONFIG_64BIT="$(CONFIG_64BIT)"; \
	export platform=w3k; \
	export target="$(ESP_TARGET_IF)";\
	export chip="$(ESP_CHIP_SERS)"; \
	$(MAKE) -C "$(PKG_BUILD_DIR)/host/linux/host_driver/esp32" all
#	$(KERNEL_MAKE) M="$(PKG_BUILD_DIR)/host/linux/host_driver/esp32" modules target=spi
#	+$(KERNEL_MAKE) $(PKG_JOBS) \
#		M="$(PKG_BUILD_DIR)/host/linux/host_driver/esp32" \
#		NOSTDINC_FLAGS="$(NOSTDINC_FLAGS)" \
#		modules target=spi
endef

#########################################################
################# VARIANTS DEFINITION ###################
#########################################################
#subtarget:=$(CONFIG_TARGET_BOARD)

$(eval $(call KernelPackage,$(PKG_NAME)))


