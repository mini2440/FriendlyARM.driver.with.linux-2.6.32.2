#include "tp_common.h"

static int __init mod_init(void)
{
        tp_print_support_gesture();
        tp_print_firmware_version();
        printk(KERN_INFO "touch module init ok!\n");
        return 0;
}

static void __exit mod_exit(void)
{
        printk(KERN_INFO "touch module exit ok!\n");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
