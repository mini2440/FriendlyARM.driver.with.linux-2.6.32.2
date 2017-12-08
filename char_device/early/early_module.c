#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

static int mini2440_open(struct inode *my_indoe, struct file *my_file)
{
        printk(KERN_INFO "early open ok\n");
        return 0;
}

static int mini2440_release(struct inode *my_indoe, struct file *my_file)
{
        printk(KERN_INFO "early release ok\n");
        return 0;
}

static ssize_t mini2440_read(struct file *my_file, char __user *buff, size_t cnt, loff_t *loff)
{
        printk(KERN_INFO "early read ok\n");
        return 0;
}

static ssize_t mini2440_write(struct file *my_file, const char __user *buff, size_t cnt, loff_t *loff)
{
        printk(KERN_INFO "early write ok\n");
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
static struct class *mini2440_class;

static int __init mod_init(void)
{
        mini2440_major = register_chrdev(0, "mini2440_module", &mini2440_fops);
        printk(KERN_INFO "mini2440_major = %d\n", mini2440_major);
        
        mini2440_class = class_create(THIS_MODULE, "mini2440_class");
        if (IS_ERR(mini2440_class))
        {
                printk(KERN_ERR "create class error\n");
                return -1;
        }
        device_create(mini2440_class, NULL, MKDEV(mini2440_major, 0), NULL, "early_device");
      
        printk(KERN_INFO "mod_init ok\n");
        return 0;
}

static void __exit mod_exit(void)
{
        unregister_chrdev(mini2440_major, "mini2440_module");
        printk(KERN_INFO "mod_exit ok\n");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
