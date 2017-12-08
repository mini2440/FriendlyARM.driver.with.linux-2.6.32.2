#include <linux/init.h>
#include <linux/module.h>

static int __init mod_init(void)
{
        printk(KERN_EMERG   "hello world! KERN_EMERG   = %s\n", KERN_EMERG  );
        printk(KERN_ALERT   "hello world! KERN_ALERT   = %s\n", KERN_ALERT  );
        printk(KERN_CRIT    "hello world! KERN_CRIT    = %s\n", KERN_CRIT   );
        printk(KERN_ERR     "hello world! KERN_ERR     = %s\n", KERN_ERR    );
        printk(KERN_WARNING "hello world! KERN_WARNING = %s\n", KERN_WARNING);
        printk(KERN_NOTICE  "hello world! KERN_NOTICE  = %s\n", KERN_NOTICE );
        printk(KERN_INFO    "hello world! KERN_INFO    = %s\n", KERN_INFO   );
        printk(KERN_DEBUG   "hello world! KERN_DEBUG   = %s\n", KERN_DEBUG  );
        return 0;
}

static void __exit mod_exit(void)
{
        printk(KERN_EMERG   "goodbye world! KERN_EMERG   = %s\n", KERN_EMERG  );
        printk(KERN_ALERT   "goodbye world! KERN_ALERT   = %s\n", KERN_ALERT  );
        printk(KERN_CRIT    "goodbye world! KERN_CRIT    = %s\n", KERN_CRIT   );
        printk(KERN_ERR     "goodbye world! KERN_ERR     = %s\n", KERN_ERR    );
        printk(KERN_WARNING "goodbye world! KERN_WARNING = %s\n", KERN_WARNING);
        printk(KERN_NOTICE  "goodbye world! KERN_NOTICE  = %s\n", KERN_NOTICE );
        printk(KERN_INFO    "goodbye world! KERN_INFO    = %s\n", KERN_INFO   );
        printk(KERN_DEBUG   "goodbye world! KERN_DEBUG   = %s\n", KERN_DEBUG  );
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
