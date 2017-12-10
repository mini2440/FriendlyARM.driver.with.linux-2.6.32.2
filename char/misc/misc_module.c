#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>

static int mini2440_open(struct inode *my_indoe, struct file *my_file)
{
        printk(KERN_INFO "misc open ok\n");
        return 0;
}

static int mini2440_release(struct inode *my_indoe, struct file *my_file)
{
        printk(KERN_INFO "misc release ok\n");
        return 0;
}

static ssize_t mini2440_read(struct file *my_file, char __user *buff, size_t cnt, loff_t *loff)
{
        printk(KERN_INFO "misc read ok\n");
        return 0;
}

static ssize_t mini2440_write(struct file *my_file, const char __user *buff, size_t cnt, loff_t *loff)
{
        printk(KERN_INFO "misc write ok\n");
        return 0;
}

static struct file_operations mini2440_fops =
{
        .open    = mini2440_open,
        .release = mini2440_release,
        .read    = mini2440_read,
        .write   = mini2440_write,
};

static struct miscdevice misc =
{
        .minor   = 255,
        .name    = "misc_device",
        .fops    = &mini2440_fops,
};

static int __init mod_init(void)
{
        misc_register(&misc);
        printk(KERN_INFO "mod_init ok\n");
        return 0;
}

static void __exit mod_exit(void)
{
        misc_deregister(&misc);
        printk(KERN_INFO "mod_exit ok\n");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
