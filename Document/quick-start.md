

# 0. 代码库

相关代码库已从 Github 开源代码库 Fork 出来，参考下表

| 代码库地址 | 分支 |
|-----------|------|
| [openwrt](https://github.com/siwaves/openwrt/) | [openwrt-22.03-linux-5.10.168](https://github.com/siwaves/openwrt/tree/openwrt-22.03-linux-5.10.168) |
| [luci](https://github.com/siwaves/luci) | [openwrt-22.03](https://github.com/siwaves/luci/tree/openwrt-22.03)  |
| [u-boot](https://github.com/siwaves/u-boot) | [w3k-fpga](https://github.com/siwaves/u-boot/tree/w3k-fpga) |
| [packages](https://github.com/siwaves/packages) | [openwrt-22.03](https://github.com/siwaves/packages/tree/openwrt-22.03) |
| [opensbi](https://github.com/siwaves/opensbi) | [w3k](https://github.com/siwaves/opensbi/tree/w3k) |
| [telephony](https://github.com/siwaves/telephony) | [openwrt-22.03](https://github.com/siwaves/telephony/tree/openwrt-22.03) |
| [routing](https://github.com/siwaves/routing) | [openwrt-22.03](https://github.com/siwaves/routing/tree/openwrt-22.03) |


Note: 以下编译流程需要个人 Github 帐户， 并已设置 [Github SSH Key Access](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent)。

# 1. 编译环境

OpenWRT 22.03 with Linux Kernel 5.10.168 编译流程在以下两个环境下测试过。

## 环境 1

服务器版本：ubuntu 22.04

```
Linux super 5.19.0-44-generic #45~22.04.1-Ubuntu SMP PREEMPT_DYNAMIC Tue May 30 20:00:11 UTC 2 x86_64 x86_64 x86_64 GNU/Linux
```

## 环境 2

Ubuntu 20.04 工作站 with 以下软硬件配置：

![](./pictures/ubuntu_20_sys_info.png)

## 软件依赖

安装必须的软件包

```shell
sudo apt install cmake autoconf automake autotools-dev curl \
	libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison \
	flex texinfo gperf patchutils bc zlib1g-dev  python-dev-is-python3 \
	libtool pkg-config mingw-w64 mingw-w64-tools texlive zip gettext \
	libglib2.0-dev libpixman-1-dev swig ninja-build python3 python3-pip \
	libelf-dev quilt libpopt-dev libncurses-dev
```

python安装

```
pip3 install swig
pip3 install pylibfdt
```

# 2. 克隆代码

```
git clone git@github.com:siwaves/openwrt.git
cd openwrt
git checkout openwrt-22.03-linux-5.10.168 
```



# 3. 编译代码

## 3.1 更新feeds

```
./scripts/feeds update -a
./scripts/feeds install  -a
```

> update的时候确保packages、luci、routing、telephony都更新成功。然后再install。

## 3.2 选择siliconwaves-riscv平台

当执行make menuconfig后，出现默认的配置，Target System 选择回车

![](./pictures/default.png)


然后目录走到Siliconwaves RISC-V，空格选择

![](./pictures/target-system-riscv.png)



选择好**Siliconwaves RISC-V** 之后，选择 Save 回车如下

![](./pictures/select-riscv-siliconwaves.png)



此时所有配置都会自动选择，现在选择Exit。

![exit](./pictures/exit.png)

选择Yes，将生成.config。


确认 Target System 是 Siliconwaves RISC-V 后，选择 Exit 。


## 3.3 提前下载openwrt dl文件

为加速编译过程，部分文件已打包上传到云端，这样一次下载后，无需在每次编译过程中通过网络下载这些文件。

链接：https://share.weiyun.com/Gxg9j4Ud 密码：muj8jr

下载好之后，放到openwrt目录，然后执行命令解压：

```shell
$ tar jxvf dl-linux-5.10.168.tar.bz2 
dl/
dl/fstools-2022-06-02-93369be0.tar.xz
dl/ca-certificates_20230311.tar.xz
dl/ncurses-6.3.tar.gz
.....
```



## 3.4 最后编译：

```
make V=s -j72
```

如果编译错误，则执行make V=s 单线程编译，查看哪里编译有问题。

> 72表示cpu数量，实际改成编译服务器的CPU数量



编译成功后，在 bin/targets/siliconwaves/w3k/ 目录下会生成 openwrt-siliconwaves-w3k-siliconwaves-w3k-fpga-ext4-factory.img.gz 软件。

作为参考，在环境2下，整个编译过程大概花了25分钟。

# 4. 制作w3k-fpga openwrt的启动卡

将sd卡插入读卡器，读卡器连接到ubuntu主机，然后执行命令**ls /dev/sd***, 确认是哪个描述符时sd卡。
制作启动卡的命令如下：
```
zcat openwrt-siliconwaves-w3k-siliconwaves-w3k-fpga-ext4-factory.img.gz | sudo dd of=/dev/sdX bs=512K iflag=fullblock conv=fsync status=progress
```
X替换为实际的磁盘名字即可。
执行完上述命令，启动磁盘就制作好了。
```
$ ls /dev/sdb*
/dev/sdb  /dev/sdb1  /dev/sdb2  /dev/sdb3  /dev/sdb4
```
磁盘有4个分区
| 分区 | 内容 |
|-----------|------|
|1|	u-boot-spl.bin|
|2|	u-boot.itb|
|3|	linux的内核以及设备树|
|4|	ext4格式的openwrt文件系统|

