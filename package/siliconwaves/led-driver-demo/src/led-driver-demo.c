#include <linux/init.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/types.h>
#include <net/sock.h>
#include <linux/netlink.h>

#define GPIO_INPUT_EN 0x00
#define GPIO_OUTPUT_EN 0x00
#define GPIO_INPUT_BIT 0x02
#define GPIO_OUTPUT_BIT 0x02
#define GPIO_OUT_REG_OFFSET 0x88
#define GPIO_IN_REG_OFFSET 0x8C
#define GPIO_MAX 4
#define GPIO_BASE_ADDR 0x3e204000

#define NETLINK_LED_LIGHTUP 30
#define USER_PORT   100

static void *gpio_base = NULL;
struct sock *nlsk = NULL;
extern struct net init_net;

static int siliconwaves_gpio_direction_output(void *base, u32 gpio);
static int siliconwaves_gpio_set_value(void *base, u32 gpio, int value);

static void netlink_rcv_msg(struct sk_buff *skb)
{
    struct nlmsghdr *nlh = NULL;
    unsigned char *umsg = NULL;
    unsigned char op;

    if(skb->len >= nlmsg_total_size(0)){
        nlh = nlmsg_hdr(skb);
        umsg = NLMSG_DATA(nlh);
        if(umsg){
            op = umsg[0];
            //printk("kernel recv from user: %x\n", op);
            siliconwaves_gpio_direction_output(gpio_base, (op>>1) & 0x7f);
            siliconwaves_gpio_set_value(gpio_base, (op >> 1)& 0x7f, op & 0x1);
        }
    }
}

struct netlink_kernel_cfg cfg = { 
    .input  = netlink_rcv_msg, /* set recv callback */
};  

static int netlink_init(void)
{
    /* create netlink socket */
    nlsk = (struct sock *)netlink_kernel_create(&init_net, NETLINK_LED_LIGHTUP, &cfg);
    if(!nlsk){   
        pr_err("netlink_kernel_create error!\n");
        return -1; 
    }
    return 0;
}

static void siliconwaves_update_gpio_reg(void *bptr, u32 reg_offset,
                                         u32 bit, bool value)
{
    void __iomem *ptr = (void __iomem *)bptr + reg_offset;
    u32 old = readl(ptr);

    if (value)
        writel(old | (1 << bit), ptr);
    else
        writel(old & ~(1 << bit), ptr);
}

static int siliconwaves_gpio_direction_output(void *base, u32 gpio)
{
    if (gpio > GPIO_MAX)
        return -EINVAL;

    /* Configure gpio direction as output */
    siliconwaves_update_gpio_reg(base, GPIO_OUTPUT_EN + gpio * 4,
                                 GPIO_INPUT_BIT, false);

    return 0;
}

static int siliconwaves_gpio_set_value(void *base, u32 gpio, int value)
{
	if (gpio > GPIO_MAX)
		return -EINVAL;
	siliconwaves_update_gpio_reg(base, GPIO_OUT_REG_OFFSET, gpio, value);
	return 0;
}

static int __init led_init(void)
{
    gpio_base = ioremap(GPIO_BASE_ADDR, 0x1000);
    if(!gpio_base){
        pr_err("led ioremap failed\n");
        return -1;
    }
    if(netlink_init() < 0){
        pr_err("led netlink init failed\n");
        iounmap(gpio_base);
        return -1;
    }
    siliconwaves_gpio_direction_output(gpio_base, 4);
    siliconwaves_gpio_set_value(gpio_base, 4, 1);
    pr_info("siliconwaves led driver init done\n");
    return 0;
}

static void __exit led_exit(void)
{
    if(gpio_base)
        iounmap(gpio_base);
    if (nlsk)
        netlink_kernel_release(nlsk);
     pr_info("siliconwaves led driver exit\n");
}

module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Richard Dai");
MODULE_DESCRIPTION("led driver demo");
