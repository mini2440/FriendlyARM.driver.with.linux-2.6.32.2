#include <linux/init.h>
#include <linux/module.h>

/* simple log */
#define log(fmt, arg...)\
        printk(KERN_INFO "[Paul][%s][%d] "fmt"\n", __func__, __LINE__, ##arg);

#define err(fmt, arg...)\
        printk(KERN_ERR "[Paul][%s][%d] ERROR!!! "fmt"\n", __func__, __LINE__, ##arg);

/* detail log */
#define dbg(fmt, arg...)\
        printk(KERN_INFO "%s:\n[Paul][%s][%d] "fmt"\n", __FILE__, __func__, __LINE__, ##arg);

static int __init mod_init(void)
{
        log("hello everyone");
        log("my name is %s", "Paul");
        log("my age is %d", 24);
        log("using hex is 0x%02x", 24);
        return 0;
}

static void __exit mod_exit(void)
{
        dbg("goodbye, everyone");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
