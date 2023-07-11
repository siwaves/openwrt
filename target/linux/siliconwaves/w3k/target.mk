ARCH:=riscv64
SUBTARGET:=w3k
BOARDNAME:=wave3000
CPU_TYPE:=w3k
DEFAULT_PACKAGES += 
KERNELNAME:=Image dtbs

define Target/Description
	Build firmware images for siliconwaves w3k  based boards.
endef

