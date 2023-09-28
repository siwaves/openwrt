// SPDX-License-Identifier: GPL-2.0-only
/*
 * Espressif Systems Wireless LAN device driver
 *
 * Copyright (C) 2015-2021 Espressif Systems (Shanghai) PTE LTD
 *
 * This software file (the "File") is distributed by Espressif Systems (Shanghai)
 * PTE LTD under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modify this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE FILE IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#ifndef __esp__h_
#define __esp__h_

#include <linux/workqueue.h>
#include <linux/interrupt.h>
#include <linux/netdevice.h>
#include <net/bluetooth/bluetooth.h>
#include <net/bluetooth/hci_core.h>
#include "esp_kernel_port.h"
#include "adapter.h"

#define ESP_IF_TYPE_SDIO        1
#define ESP_IF_TYPE_SPI         2

/* Network link status */
#define ESP_LINK_DOWN           0
#define ESP_LINK_UP             1

#define ESP_MAX_INTERFACE       2

#define ESP_PAYLOAD_HEADER      8
struct esp_private;
struct esp_adapter;

#define ACQUIRE_LOCK            1
#define LOCK_ALREADY_ACQUIRED   0

#define SKB_DATA_ADDR_ALIGNMENT 4
#define INTERFACE_HEADER_PADDING (SKB_DATA_ADDR_ALIGNMENT*3)

#ifdef CONFIG_W3K_TARGET
#define GPIO_OUT_BIT 0x01
#define GPIO_OEN_BIT 0x02
#define GPIO_REN_BIT 0x04

#define GPIO_IRQ_BIT 0x02
#define GPIO_IRQ_BIT 0x02

#define GPIO_NUM_MAX 32
#define GPIO_BASE_ADDR 0x3e204000

//output enable register
#define GPIO_N_OEN_REG	0x80
//pull low enable
#define GPIO_N_REN_REG	0x84
//output register
#define GPIO_N_OUT_REG	0x88
//input register
#define GPIO_N_IN_REG	0x8C

//interrupt config0, gpio0~7
#define GPIO_N_ITR_CFG0_REG	0x90
//interrupt config1, gpio8~15
#define GPIO_N_ITR_CFG1_REG	0x94
//interrupt config2, gpio16~23
#define GPIO_N_ITR_CFG2_REG	0x98
//interrupt config3, gpio24~31
#define GPIO_N_ITR_CFG3_REG	0x9C

//interrupt enable register
#define GPIO_N_EINT_REG	0xA0
//interrupt disable register
#define GPIO_N_EINT_FLAG_REG	0xA4

#define GPIO_MODE_INPUT 0
#define GPIO_MODE_OUTPUT 1

#define GPIO_ITR_FLAG_EDGE_RISING	0x00
#define GPIO_ITR_FLAG_EDGE_FAILIG	0x01
#define GPIO_ITR_FLAG_HIGH_LEVEL	0x02
#define GPIO_ITR_FLAG_LOW_LEVEL		0x03
#define GPIO_ITR_FLAG_EDGE_BOTH		0x04
#endif //CONFIG_W3K_TARGET

struct esp_device {
	struct spi_device *spi;
	int handshake; /*SPI Interface GPIO of HandShake PIN*/
	int dataready; /*SPI Interface GPIO of DataReady PIN*/
	int reset; /*GPIO for Reset PIN*/
	#ifdef CONFIG_W3K_TARGET
	int ginterrupt;
	#endif
};

struct esp_adapter {
	u8                      if_type;
	u32                     capabilities;

	/* Possible types:
	 * struct esp_sdio_context */
	void                    *if_context;

	struct esp_if_ops       *if_ops;

	/* Private for each interface */
	struct esp_private      *priv[ESP_MAX_INTERFACE];
	struct hci_dev          *hcidev;

	struct workqueue_struct *if_rx_workqueue;
	struct work_struct       if_rx_work;

	/* Process TX work */
	struct workqueue_struct *tx_workqueue;
	struct work_struct      tx_work;
	struct esp_device		*pdev;
};


struct esp_private {
	struct esp_adapter      *adapter;
	struct net_device       *ndev;
	struct net_device_stats stats;
	u8                      link_state;
	u8                      mac_address[6];
	u8                      if_type;
	u8                      if_num;
};

struct esp_skb_cb {
	struct esp_private      *priv;
};

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 17, 0))
#define do_exit(code)	kthread_complete_and_exit(NULL, code)
#endif

#ifdef CONFIG_W3K_TARGET
extern int siliconwaves_gpio_direction_output(u32 gpio, int value);
extern int siliconwaves_gpio_direction_input(u32 gpio);
extern int siliconwaves_gpio_request_irq(u32 gpio, int irq_flag);
extern int siliconwaves_gpio_is_interrupt_gen(u32 gpio);
extern int siliconwaves_gpio_enable_irq(u32 gpio);
extern int siliconwaves_gpio_disable_irq(u32 gpio);
#endif //CONFIG_W3K_TARGET

#endif
