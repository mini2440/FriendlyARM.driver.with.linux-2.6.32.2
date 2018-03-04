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

static int demo_probe(struct platform_device * tiny4412_led_device)
{
        log("enter the probe");
        return 0;
}

static int demo_remove(struct platform_device *plat_dev)
{
        log("enter the remove");
        return 0;
}

static struct platform_driver demo_driver =
{
        .probe  = demo_probe,
        .remove = demo_remove,
        .driver =
        {
                .name = "demo",
        }
};

static int __init mod_init(void)
{
        platform_driver_register(&demo_driver);
        log("platform device init");
        return 0;
}

static void __exit mod_exit(void)
{
        platform_driver_unregister(&demo_driver);
        log("platform device exit");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");