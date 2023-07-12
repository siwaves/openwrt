siliconwaves-w3k openwrt release note

# 2023-07

1. opensbi
   * 支持w3k uart。

2. u-boot

   * 支持w3k uart，w3k mmc。
   * 支持从sd卡启动openwrt。

3. openwrt

   * 支持siliconwave-fpga board，Taget System选择Siliconwaves RISCV即可。

   * 支持烧录到sd卡的image。烧录时会将spl、uboot、opensbi、openwrt同时烧录到sd卡上。