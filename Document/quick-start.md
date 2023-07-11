# 1. 编译环境

服务器版本：ubuntu 22.04

```
Linux super 5.19.0-44-generic #45~22.04.1-Ubuntu SMP PREEMPT_DYNAMIC Tue May 30 20:00:11 UTC 2 x86_64 x86_64 x86_64 GNU/Linux
```

ubuntu 22.04 安装必须的软件

```shell
sudo apt install cmake autoconf automake autotools-dev curl libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf patchutils bc zlib1g-dev  python-dev-is-python3 libtool pkg-config mingw-w64 mingw-w64-tools texlive zip gettext libglib2.0-dev libpixman-1-dev swig ninja-build python3 python3-pip libelf-dev quilt libpopt-dev
```

python安装

```
pip3 install swig
pip3 install pylibfdt
```



# 2. 克隆代码

```
git clone https://github.com/siwaves/openwrt
cd openwrt
git checkout openwrt-22.03-linux-5.10.168 
```



# 3. 编译代码

```
./scripts/feeds update -a
./scripts/feeds install  -a
```

> update的时候确保packages、luci、routing、telephony都更新成功。然后再install。

选择执行make menuconfig选择平台

```
make menuconfig

1. Target System (Siliconwaves RISC-V)  ---> 
2. Subtarget (wave3000)  --->  
3. Target Profile (SiliconWaves w3k-fpga (64bit))  ---> 
```

选择如上。选择好之后，退出保存。



最后编译：

```
make V=s -j72
```

如果编译错误，则执行make V=s 单线程编译，查看哪里编译有问题。



编译成功后，在bin/targets/siliconwaves/w3k/目录下会生成openwrt-siliconwaves-w3k-siliconwaves-w3k-fpga-ext4-factory.img.gz 软件。