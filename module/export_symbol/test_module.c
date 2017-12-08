#include <linux/init.h>
#include <linux/module.h>

extern int calculate_add(int x, int y);
extern int calculate_sub(int x, int y);

static int __init mod_init(void)
{
        printk(KERN_INFO "[%s][%d] 10 - 5 = %d\n", __func__, __LINE__, calculate_add(10, 5));
        printk(KERN_INFO "[%s][%d] 10 - 5 = %d\n", __func__, __LINE__, calculate_sub(10, 5));
        printk(KERN_INFO "test module init ok!\n");
        return 0;
}

static void __exit mod_exit(void)
{
        printk(KERN_INFO "test module exit ok!\n");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
