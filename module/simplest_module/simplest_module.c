#include <linux/init.h>
#include <linux/module.h>

static int __init mod_init(void)
{
        printk(KERN_INFO "simplest module init ok!\n");
        return 0;
}

static void __exit mod_exit(void)
{
        printk(KERN_INFO "simplest module exit ok!\n");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
