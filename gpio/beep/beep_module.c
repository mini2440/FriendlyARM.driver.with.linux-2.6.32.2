#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/uaccess.h>        /* copy_to_user ... */
#include <asm/io.h>             /* ioremap ... */

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

static int beep_open(struct inode *my_indoe, struct file *my_file)
{
        // 设置 GPIOB0   输出模式
        // GPBCON = 0000 0000 0000 0000 0000 0000 0000 0001
        *GPBCON = *GPBCON & 0xfffffffc;
        *GPBCON = *GPBCON | 0x00000001;
        return 0;
}

static int beep_release(struct inode *my_indoe, struct file *my_file)
{
        *GPBDAT = 0xffffffffe;
        return 0;
}

static ssize_t beep_read(struct file *my_file, char __user *buff, size_t cnt, loff_t *loff)
{
        return 0;
}

static ssize_t beep_write(struct file *my_file, const char __user *buff, size_t cnt, loff_t *loff)
{
        int state = -1;
        copy_from_user(&state, buff, cnt);

        if(1 == state)
        {
                log("beep on");
                *GPBDAT = *GPBDAT | 0x00000001;
        }
        else if(2 == state)
        {
                log("beep off");
                *GPBDAT = *GPBDAT & 0xfffffffe;
        }
        else
        {
                log("beep off");
                *GPBDAT = 0xffffffffe;
        }

        return 0;
}

static struct file_operations beep_fops =
{
        .open    = beep_open,
        .release = beep_release,
        .read    = beep_read,
        .write   = beep_write,
};

static int beep_major;
static int beep_minor;
static dev_t beep_devno;

struct cdev * beep;
static struct class * beep_class;

static int __init mod_init(void)
{
        int ret = -1;

        GPBCON = ioremap(0x56000010, 4);
        GPBDAT = ioremap(0x56000014, 4);

        ret = alloc_chrdev_region(&beep_devno, beep_minor, 1, "beep_device");
        beep_major = MAJOR(beep_devno);
        if (ret < 0)
        {
                err("cannot get beep_major %d", beep_major);
                return -1;
        }

        beep = cdev_alloc();
        if (beep != NULL)
        {
                cdev_init(beep, &beep_fops);
                beep->owner = THIS_MODULE;
                if (cdev_add(beep, beep_devno, 1) != 0)
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

        beep_class = class_create(THIS_MODULE, "beep_class");
        if (IS_ERR(beep_class))
        {
                err("create class error");
                return -1;
        }
        device_create(beep_class, NULL, beep_devno, NULL, "paul-beep");
        return 0;

error:
        unregister_chrdev_region(beep_devno, 1);
        return ret;
}

static void __exit mod_exit(void)
{
        cdev_del(beep);
        unregister_chrdev_region(beep_devno, 1);
        device_destroy(beep_class, beep_devno);
        class_destroy(beep_class);

        iounmap(GPBCON);
        iounmap(GPBDAT);
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");

