#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/i2c.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

/* simple log */
#define log(fmt, arg...)\
        printk(KERN_INFO "[Paul][%s][%d] "fmt"\n", __func__, __LINE__, ##arg);

#define err(fmt, arg...)\
        printk(KERN_ERR "[Paul][%s][%d] ERROR!!! "fmt"\n", __func__, __LINE__, ##arg);

/* detail log */
#define dbg(fmt, arg...)\
        printk(KERN_INFO "%s:\n[Paul][%s][%d] "fmt"\n", __FILE__, __func__, __LINE__, ##arg);


static int major;
static struct class *class;
static struct i2c_client *at24cxx_client;

/* 传入: buf[0] : addr
 * 输出: buf[0] : data
 */
static ssize_t at24cxx_read(struct file * file, char __user *buf, size_t count, loff_t *off)
{
        unsigned char addr, data;

        copy_from_user(&addr, buf, 1);
        data = i2c_smbus_read_byte_data(at24cxx_client, addr);
        copy_to_user(buf, &data, 1);
        return 1;
}

/* buf[0] : addr
 * buf[1] : data
 */
static ssize_t at24cxx_write(struct file *file, const char __user *buf, size_t count, loff_t *off)
{
        unsigned char ker_buf[2];
        unsigned char addr, data;

        copy_from_user(ker_buf, buf, 2);
        addr = ker_buf[0];
        data = ker_buf[1];

        printk("addr = 0x%02x, data = 0x%02x\n", addr, data);

        if (!i2c_smbus_write_byte_data(at24cxx_client, addr, data))
                return 2;
        else
                return -EIO;
}

static struct file_operations at24cxx_fops = {
        .owner = THIS_MODULE,
        .read  = at24cxx_read,
        .write = at24cxx_write,
};

static int __devinit at24cxx_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
        at24cxx_client = client;
        major = register_chrdev(0, "at24cxx", &at24cxx_fops);
        class = class_create(THIS_MODULE, "at24cxx");
        device_create(class, NULL, MKDEV(major, 0), NULL, "at24cxx"); /* /dev/at24cxx */
        return 0;
}

static int __devexit at24cxx_remove(struct i2c_client *client)
{
        device_destroy(class, MKDEV(major, 0));
        class_destroy(class);
        unregister_chrdev(major, "at24cxx");
        return 0;
}

static const struct i2c_device_id at24cxx_id_table[] = {
        /* 第一参数是支持的设备名，第二个参数是私有的数据，这里没有私有的数据，随便写了个 0 */
        { "at24c08", 0 },
        {}
};

/* 1. 分配/设置i2c_driver */
static struct i2c_driver at24cxx_driver = {
        .driver	= {
                /* 这个名字不重要 */
                .name   = "100ask",
                .owner  = THIS_MODULE,
        },
        .probe          = at24cxx_probe,
        .remove         = __devexit_p(at24cxx_remove),
        /* 这里指定了本驱动支持的设备的名称列表 */
        .id_table       = at24cxx_id_table,
};

static int __init mod_init(void)
{
        log("start");
        i2c_add_driver(&at24cxx_driver);
        log("done");
        return 0;
}

static void __exit mod_exit(void)
{
        log("start");
        i2c_del_driver(&at24cxx_driver);
        log("done");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");