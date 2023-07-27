#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <linux/netlink.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>

#define NETLINK_LED_LIGHTUP 30
#define MAX_PLOAD 8
#define USER_PORT   100

void print_help(char **argv)
{
    printf("Usage:%s [-hnv] [-n gpio-num 0-3][-v on-off 0/1]\n", argv[0]);
}

int led_getopt(int argc, char **argv)
{
    int ch;
    unsigned char value = 0;
    int tmp;
    int result = -1;
    int flag = 0;
    /*[hn:v:],-h help,  -n gpionum, -v on or off */
    char *string = "hn:v:";
    
    if(argc <= 1)
        goto out;

    while((ch = getopt(argc, argv, string)) != -1){
        switch(ch){
            case 'n':
                tmp = atoi(optarg);
                if(tmp >= 4 || tmp < 0)
                    goto out;
                value |= (tmp << 1);
                flag |= 0x1;
            break;
            case 'v':
                tmp = atoi(optarg);
                if(tmp != 0)
                    value |= 0x1;
                flag |= 0x2;
            break;
            case 'h':
                goto out;
            default:
                printf("other option :%c\n",ch);
        }
    }
    if(flag != 0x3)
        goto out;

    result = value;
out:
    if(result < 0)
        print_help(argv);
    return result;
}

int main(int argc, char **argv)
{
    int skfd, ret;
    unsigned char value;
    socklen_t len;
    struct nlmsghdr *nlh = NULL;
    struct sockaddr_nl saddr, daddr;

    ret = led_getopt(argc, argv);
    if(ret < 0)
        return -1;
    value = ret & 0xff;

    skfd = socket(AF_NETLINK, SOCK_RAW, NETLINK_LED_LIGHTUP);
    if (skfd == -1){
        perror("create socket error\n");
        return -1;
    }

    memset(&saddr, 0, sizeof(saddr));
    saddr.nl_family = AF_NETLINK;
    saddr.nl_pid = USER_PORT;
    saddr.nl_groups = 0;
    if (bind(skfd, (struct sockaddr *)&saddr, sizeof(saddr)) != 0)
    {
        perror("bind() error\n");
        close(skfd);
        return -1;
    }

    memset(&daddr, 0, sizeof(daddr));
    daddr.nl_family = AF_NETLINK;
    daddr.nl_pid = 0; // to kernel
    daddr.nl_groups = 0;

    nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_PLOAD));
    memset(nlh, 0, sizeof(struct nlmsghdr));
    nlh->nlmsg_len = NLMSG_SPACE(MAX_PLOAD);
    nlh->nlmsg_flags = 0;
    nlh->nlmsg_type = 0;
    nlh->nlmsg_seq = 0;
    nlh->nlmsg_pid = saddr.nl_pid; // self port

    memcpy(NLMSG_DATA(nlh), &value, 1);
    ret = sendto(skfd, nlh, nlh->nlmsg_len, 0, (struct sockaddr *)&daddr, sizeof(struct sockaddr_nl));
    if (!ret)
    {
        perror("sendto error\n");
        close(skfd);
        exit(-1);
    }
    
    close(skfd);
    free((void *)nlh);
    return 0;
}
