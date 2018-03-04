#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>

/* simple log */
#define log(fmt, arg...)\
        printk(KERN_INFO "[Paul][%s][%d] "fmt"\n", __func__, __LINE__, ##arg);

#define err(fmt, arg...)\
        printk(KERN_ERR "[Paul][%s][%d] ERROR!!! "fmt"\n", __func__, __LINE__, ##arg);

/* detail log */
#define dbg(fmt, arg...)\
        printk(KERN_INFO "%s:\n[Paul][%s][%d] "fmt"\n", __FILE__, __func__, __LINE__, ##arg);

struct platform_device demo_device =
{
        .name   ="demo",        // 设备名称, 由于和平台驱动匹配
        .id     = 1,            // 设备 id
};

static int __init mod_init(void)
{
        platform_device_register(&demo_device);
        log("platform device init");
        return 0;
}

static void __exit mod_exit(void)
{
        platform_device_unregister(&demo_device);
        log("platform device exit");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
