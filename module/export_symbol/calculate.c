#include <linux/init.h>
#include <linux/module.h>

int calculate_add(int x, int y)
{
        printk(KERN_INFO "[%s][%d] is running\n", __func__, __LINE__);
        return x + y;
}
EXPORT_SYMBOL(calculate_add);

int calculate_sub(int x, int y)
{
        printk(KERN_INFO "[%s][%d] is running\n", __func__, __LINE__);
        return x - y;
}
EXPORT_SYMBOL(calculate_sub);

static int __init mod_init(void)
{
        printk(KERN_INFO "calculate module init ok!\n");
        return 0;
}

static void __exit mod_exit(void)
{
        printk(KERN_INFO "calculate module exit ok!\n");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
