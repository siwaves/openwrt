#
# Copyright (C) 2010-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# Copyright (c) 2015 OpenWrt.org
#
include $(TOPDIR)/rules.mk

ARCH:=riscv64
BOARD:=siliconwaves
BOARDNAME:=SIWAVES U-based RISC-V boards 
SUBTARGETS:=generic
FEATURES:= ext4 squashfs
KERNELNAME:= Image dtbs

KERNEL_PATCHVER:=5.10

include $(INCLUDE_DIR)/target.mk
define Target/Description
        Build firmware image for SilionWaves SoC devices.
        Currently produces SD Card image for siliconwaves test.
endef

DEFAULT_PACKAGES += e2fsprogs perf ethtool-full minicom default-settings-siliconwaves

$(eval $(call BuildTarget))
