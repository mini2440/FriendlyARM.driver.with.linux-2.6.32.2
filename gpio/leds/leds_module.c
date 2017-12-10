#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/uaccess.h>        /* copy_to_user ... */

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

static unsigned long led_table[] = {
	S3C2410_GPB(5),
	S3C2410_GPB(6),
	S3C2410_GPB(7),
	S3C2410_GPB(8),
};

unsigned int leds_num = 0;

/**
 * cmd = 0, turn off the led
 * cmd = 1, turn on the led
 */
static int mini2440_leds_ioctl(struct inode *inode, struct file *file,
                        unsigned int cmd, unsigned long arg)
{
        int i = 0;
        int minor = MINOR(file->f_dentry->d_inode->i_rdev);
        if(0 == minor)
        {
                for(i = 0; i < leds_num; i++)
                {
                        s3c2410_gpio_setpin(led_table[minor], !cmd);
                }
        }
        else if(minor > 0 && minor <= leds_num)
        {
                s3c2410_gpio_setpin(led_table[minor - 1], !cmd);
        }
        else
        {
                return -EINVAL;
        }
        return 0;
}


static struct file_operations mini2440_leds_fops =
{
        .owner  = THIS_MODULE,
        .ioctl  = mini2440_leds_ioctl,
};

static int mini2440_leds_major;
static int mini2440_leds_minor;
static dev_t mini2440_leds_devno;

struct cdev *mini2440_leds;
static struct class *mini2440_leds_class;

static int __init mod_init(void)
{
        int ret = -1;
        int i = 0;
        leds_num = sizeof(led_table)/sizeof(unsigned long);

        for(i = 0; i < leds_num; i++) {
                gpio_free(led_table[i]);
                gpio_request(led_table[i], "led");
                s3c2410_gpio_cfgpin(led_table[i], S3C2410_GPIO_OUTPUT);
        }

        ret = alloc_chrdev_region(&mini2440_leds_devno, mini2440_leds_minor, leds_num + 1, "driver_name");
        if (ret < 0)
        {
                err("cannot get leds_major");
                return -1;
        }

        mini2440_leds = cdev_alloc();
        if (mini2440_leds != NULL)
        {
                cdev_init(mini2440_leds, &mini2440_leds_fops);
                mini2440_leds->owner = THIS_MODULE;
                if (cdev_add(mini2440_leds, mini2440_leds_devno, 4) != 0)
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

        mini2440_leds_class = class_create(THIS_MODULE, "s3c2440a");
        if (IS_ERR(mini2440_leds_class))
        {
                err("create class error");
                return -1;
        }
        device_create(mini2440_leds_class, NULL, MKDEV(mini2440_leds_major, 0), NULL, "leds");
        for(i = 1; i <= leds_num; i++)
        {
                device_create(mini2440_leds_class, NULL, MKDEV(mini2440_leds_major, i), NULL, "led%d", i);
        }
        log("successful!");

        return 0;

error:
        unregister_chrdev_region(mini2440_leds_devno, 1);
        return ret;
}

static void __exit mod_exit(void)
{
        cdev_del(mini2440_leds);
        unregister_chrdev_region(mini2440_leds_devno, 1);
        device_destroy(mini2440_leds_class, mini2440_leds_devno);
        class_destroy(mini2440_leds_class);

        log("successful!");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");

