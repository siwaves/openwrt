CONFIG_SUPPORT_ESP_SERIAL = y
CONFIG_TEST_RAW_TP := n
CONFIG_ENABLE_MONITOR_PROCESS = n
# In case of SDIO as transport, one of slave chipset used,
# CONFIG_TARGET_ESP32  OR
# CONFIG_TARGET_ESP32C6
# need to be added depending upon slave in use
# rpi_init.sh will add that flag using ESP_SLAVE
ESP_SLAVE := ""


#Default interface is sdio
MODULE_NAME=esp32_sdio

#Targets passed overrrides default value
ifeq ($(target), sdio)
	MODULE_NAME=esp32_sdio
endif

ifeq ($(target), spi)
	MODULE_NAME=esp32_spi
endif

ifeq ($(chip), ESP32-c6)
	EXTRA_CFLAGS += -DCONFIG_TARGET_ESP32C6
endif

ifeq ($(platform), w3k)
	EXTRA_CFLAGS += -DCONFIG_DISABLE_SPIDEV_DTS
endif

ifeq ($(CONFIG_SUPPORT_ESP_SERIAL), y)
	EXTRA_CFLAGS += -DCONFIG_SUPPORT_ESP_SERIAL
endif

ifeq ($(CONFIG_TEST_RAW_TP), y)
	EXTRA_CFLAGS += -DCONFIG_TEST_RAW_TP
endif

ifeq ($(CONFIG_ENABLE_MONITOR_PROCESS), y)
	EXTRA_CFLAGS += -DCONFIG_ENABLE_MONITOR_PROCESS
endif

EXTRA_CFLAGS += -I$(PWD)/../../../../common/include -I$(PWD)

ifeq ($(MODULE_NAME), esp32_sdio)
	EXTRA_CFLAGS += -I$(PWD)/sdio
	module_objects += sdio/esp_sdio.o sdio/esp_sdio_api.o
endif

ifeq ($(MODULE_NAME), esp32_spi)
	EXTRA_CFLAGS += -I$(PWD)/spi
	module_objects += spi/esp_spi.o
endif

ifneq ($(ESP_SLAVE), "")
EXTRA_CFLAGS += -D$(ESP_SLAVE)
endif

PWD := $(shell pwd)

obj-m := $(MODULE_NAME).o
$(MODULE_NAME)-y := esp_bt.o main.o esp_stats.o $(module_objects)

ifeq ($(CONFIG_SUPPORT_ESP_SERIAL), y)
	$(MODULE_NAME)-y += esp_serial.o esp_rb.o
endif

all: clean
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(TARGET_CROSS) -C $(LINUX_DIR) M=$(PWD) modules

clean:
	rm -rf *.o sdio/*.o spi/*.o *.ko
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(TARGET_CROSS) -C $(LINUX_DIR) M=$(PWD) clean