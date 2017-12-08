#include <linux/init.h>
#include <linux/module.h>

char* name = "unknow";
int age = -1;

module_param(name, charp, S_IRUGO);
module_param(age, int, S_IRUGO);

static int __init mod_init(void)
{
        if(!strcmp(name, "unknow") || -1 == age)
        {
                printk(KERN_INFO "usage: insmod param_module name=<str> age=<int>\n");
                return -1;
        }

        printk(KERN_INFO "hello %s, your age is %d\n", name, age);
        printk(KERN_INFO "param module init ok!\n");
        return 0;
}

static void __exit mod_exit(void)
{
        printk(KERN_INFO "param module exit ok!\n");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
