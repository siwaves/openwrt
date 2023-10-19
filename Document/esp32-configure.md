# 概述
1. FPGA板子上电后，默认ethnet网卡为wan接口
2. 默认未开启wifi

# wifi开启/关闭
esptools命令用于配置wifi的ap和sta模式
在串口中执行
```
# esptools
esptools [ap/sta]
```
## ap模式配置
执行命令`esptools ap`后，会将esp32配置成ap模式，并且设置ethnet网卡为wan口，默认的wifi SSID:`ESPWifi``,密码为:`ESPWifi@123`
## sta模式配置
执行命令`esptools sta`后，会将esp32配置成ap模式，并且设置ethnet网卡为lan口,此时esp32-wifi回去连接SSID:`MyWifi`,密码为:`MyWifiPass@123`的路由器。
