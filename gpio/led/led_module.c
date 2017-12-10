#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/uaccess.h>        /* copy_to_user ... */
#include <asm/io.h>             /* ioremap ... */

#include <linux/gpio.h>
#include <mach/regs-gpio.h>

/* simple log */
#define log(fmt, arg...)\
        printk(KERN_INFO "[Paul][%s][%d] "fmt"\n", __func__, __LINE__, ##arg);

#define err(fmt, arg...)\
        printk(KERN_ERR "[Paul][%s][%d] ERROR!!! "fmt"\n", __func__, __LINE__, ##arg);

/* detail log */
#define dbg(fmt, arg...)\
        printk(KERN_INFO "%s:\n[Paul][%s][%d] "fmt"\n", __FILE__, __func__, __LINE__, ##arg);

static volatile unsigned int *GPBCON = NULL;
static volatile unsigned int *GPBDAT = NULL;

static int mini2440_led_open(struct inode *my_indoe, struct file *my_file)
{
        gpio_free(S3C2410_GPB(5));
        log("hello");
        /* 设置 GPIOB5 为输出模式 */
        /* GPBCON = 0000 0000 0000 0000 0000 0100 0000 0000 */
        *GPBCON = 0x00000400;
        return 0;
}

static int mini2440_led_release(struct inode *my_indoe, struct file *my_file)
{
        log("bye");
        return 0;
}

static ssize_t mini2440_led_read(struct file *my_file, char __user *buff, size_t cnt, loff_t *loff)
{
        return 0;
}

static ssize_t mini2440_led_write(struct file *my_file, const char __user *buff, size_t cnt, loff_t *loff)
{
        int state = -1;
        copy_from_user(&state, buff, cnt);

        if(1 == state)
        {
                log("led on");
                /* GPBDAT = 1111 1111 1111 1111 1111 1111 1101 1111 */
                *GPBDAT = 0xffffffdf;
        }
        else if(2 == state)
        {
                log("led off");
                /* GPBDAT = 1111 1111 1111 1111 1111 1111 1111 1111 */
                *GPBDAT = 0xffffffff;
        }
        else
        {
                log("led off");
                /* GPBDAT = 1111 1111 1111 1111 1111 1110 0001 1111 */
                *GPBDAT = 0xffffffff;
        }

        return cnt;
}

static struct file_operations mini2440_led_fops =
{
        .open    = mini2440_led_open,
        .release = mini2440_led_release,
        .read    = mini2440_led_read,
        .write   = mini2440_led_write,
};

static int mini2440_led_major;
static int mini2440_led_minor;
static dev_t mini2440_led_devno;

struct cdev * mini2440_led;
static struct class * mini2440_led_class;

static int __init mod_init(void)
{
        int ret = -1;

        GPBCON = ioremap(0x56000010, 4);
        GPBDAT = ioremap(0x56000014, 4);

        ret = alloc_chrdev_region(&mini2440_led_devno, mini2440_led_minor, 1, "cdev_name");
        mini2440_led_major = MAJOR(mini2440_led_devno);
        if (ret < 0)
        {
                err("cannot get led_major %d", mini2440_led_major);
                return -1;
        }

        mini2440_led = cdev_alloc();
        if (mini2440_led != NULL)
        {
                cdev_init(mini2440_led, &mini2440_led_fops);
                mini2440_led->owner = THIS_MODULE;
                if (cdev_add(mini2440_led, mini2440_led_devno, 1) != 0)
                {
                        err("add cdev error!");
                        goto error;
                }
        }
        else
        {
                err("cdev_alloc error!");
                return -1;
        }

        mini2440_led_class = class_create(THIS_MODULE, "s3c2440a");
        if (IS_ERR(mini2440_led_class))
        {
                err("create class error");
                return -1;
        }
        device_create(mini2440_led_class, NULL, mini2440_led_devno, NULL, "led1");

        log("successful!");

        return 0;

error:
        unregister_chrdev_region(mini2440_led_devno, 1);
        return ret;
}

static void __exit mod_exit(void)
{
        cdev_del(mini2440_led);
        unregister_chrdev_region(mini2440_led_devno, 1);
        device_destroy(mini2440_led_class, mini2440_led_devno);
        class_destroy(mini2440_led_class);

        iounmap(GPBCON);
        iounmap(GPBDAT);

        log("successful!");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");

