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

static int led_open(struct inode *my_indoe, struct file *my_file)
{
        gpio_free(S3C2410_GPB(4));
        gpio_free(S3C2410_GPB(5));
        gpio_free(S3C2410_GPB(6));
        gpio_free(S3C2410_GPB(7));
        // 设置 GPIOB4 GPIOB5 GPIOB6 GPIOB7 输出模式
        // GPBCON = 0000 0000 0000 0001 0101 0100 0000 0000
        *GPBCON = 0x00015400;
        return 0;
}

static int led_release(struct inode *my_indoe, struct file *my_file)
{
        return 0;
}

static ssize_t led_read(struct file *my_file, char __user *buff, size_t cnt, loff_t *loff)
{
        return 0;
}

static ssize_t led_write(struct file *my_file, const char __user *buff, size_t cnt, loff_t *loff)
{
        int state = -1;
        copy_from_user(&state, buff, cnt);

        if(1 == state)
        {
                log("led on");
                // GPBDAT = 1111 1111 1111 1111 1111 1111 1101 1111
                *GPBDAT = 0xfffffe1f;
        }
        else if(2 == state)
        {
                log("led off");
                // GPBDAT = 1111 1111 1111 1111 1111 1111 1111 1111
                *GPBDAT = 0xffffffff;
        }
        else
        {
                log("led on");
                // GPBDAT = 1111 1111 1111 1111 1111 1110 0001 1111
                *GPBDAT = 0xfffffe1f;
        }

        return 0;
}

static struct file_operations led_fops =
{
        .open    = led_open,
        .release = led_release,
        .read    = led_read,
        .write   = led_write,
};

static int led_major;
static int led_minor;
static dev_t led_devno;

struct cdev * led;
static struct class * led_class;

static int __init mod_init(void)
{
        int ret = -1;

        GPBCON = ioremap(0x56000010, 4);
        GPBDAT = ioremap(0x56000014, 4);

        ret = alloc_chrdev_region(&led_devno, led_minor, 1, "standard_device");
        led_major = MAJOR(led_devno);
        if (ret < 0)
        {
                err("cannot get led_major %d", led_major);
                return -1;
        }

        led = cdev_alloc();
        if (led != NULL)
        {
                cdev_init(led, &led_fops);
                led->owner = THIS_MODULE;
                if (cdev_add(led, led_devno, 1) != 0)
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

        led_class = class_create(THIS_MODULE, "led_class");
        if (IS_ERR(led_class))
        {
                err("create class error");
                return -1;
        }
        device_create(led_class, NULL, led_devno, NULL, "standard_device");
        return 0;

error:
        unregister_chrdev_region(led_devno, 1);
        return ret;
}

static void __exit mod_exit(void)
{
        cdev_del(led);
        unregister_chrdev_region(led_devno, 1);
        device_destroy(led_class, led_devno);
        class_destroy(led_class);

        iounmap(GPBCON);
        iounmap(GPBDAT);
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");

