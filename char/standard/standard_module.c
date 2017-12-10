#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/uaccess.h>        /* copy_to_user ... */

/* simple log */
#define log(fmt, arg...)\
        printk(KERN_INFO "[Paul][%s][%d] "fmt"\n", __func__, __LINE__, ##arg);

#define err(fmt, arg...)\
        printk(KERN_ERR "[Paul][%s][%d] ERROR!!! "fmt"\n", __func__, __LINE__, ##arg);

/* detail log */
#define dbg(fmt, arg...)\
        printk(KERN_INFO "%s:\n[Paul][%s][%d] "fmt"\n", __FILE__, __func__, __LINE__, ##arg);

static int mini2440_open(struct inode *my_indoe, struct file *my_file)
{
        log("standard open ok");
        return 0;
}

static int mini2440_release(struct inode *my_indoe, struct file *my_file)
{
        log("standard release ok");
        return 0;
}

static ssize_t mini2440_read(struct file *my_file, char __user *buff, size_t cnt, loff_t *loff)
{
        int tmp = 128;
        copy_to_user(buff, &tmp, 4);
        log("standard read ok");
        return 0;
}

static ssize_t mini2440_write(struct file *my_file, const char __user *buff, size_t cnt, loff_t *loff)
{
        int tmp = 0;
        copy_from_user(&tmp, buff, 4);
        log("tmp = %d", tmp);
        log("standard write ok");
        return 0;
}

static struct file_operations mini2440_fops =
{
        .open    = mini2440_open,
        .release = mini2440_release,
        .read    = mini2440_read,
        .write   = mini2440_write,
};

static int mini2440_major;
static int mini2440_minor;
static dev_t mini2440_devno;

struct cdev * standard_device;
static struct class * mini2440_class;

static int __init mod_init(void)
{
        int ret;
        ret = alloc_chrdev_region(&mini2440_devno, mini2440_minor, 1, "standard_device");
        mini2440_major = MAJOR(mini2440_devno);
        if (ret < 0)
        {
                err("cannot get mini2440_major %d", mini2440_major);
                return -1;
        }

        standard_device = cdev_alloc();
        if (standard_device != NULL)
        {
                cdev_init(standard_device, &mini2440_fops);
                standard_device->owner = THIS_MODULE;
                if (cdev_add(standard_device, mini2440_devno, 1) != 0)
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

        mini2440_class = class_create(THIS_MODULE, "mini2440_class");
        if (IS_ERR(mini2440_class))
        {
                err("create class error");
                return -1;
        }
        device_create(mini2440_class, NULL, mini2440_devno, NULL, "standard_device");

        log("mod_init ok");
        return 0;

error:
        unregister_chrdev_region(mini2440_devno, 1);
        return ret;
}

static void __exit mod_exit(void)
{
        cdev_del(standard_device);
        unregister_chrdev_region(mini2440_devno, 1);
        device_destroy(mini2440_class, mini2440_devno);
        class_destroy(mini2440_class);
        log("mod_exit ok");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
