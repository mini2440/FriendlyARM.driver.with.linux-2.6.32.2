#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>        /* copy_to_user ... */

/* simple log */
#define log(fmt, arg...)\
        printk(KERN_INFO "[Paul][%s][%d] "fmt"\n", __func__, __LINE__, ##arg);

#define err(fmt, arg...)\
        printk(KERN_ERR "[Paul][%s][%d] ERROR!!! "fmt"\n", __func__, __LINE__, ##arg);

/* detail log */
#define dbg(fmt, arg...)\
        printk(KERN_INFO "%s:\n[Paul][%s][%d] "fmt"\n", __FILE__, __func__, __LINE__, ##arg);

static struct proc_dir_entry* proc_dir = NULL;
static struct proc_dir_entry* proc_node = NULL;

static ssize_t mstar_proc_read(struct file * fd, char __user * buff, size_t len, loff_t * lof)
{
        char * ptr = buff;
        char * str = "hello I am proc node";
        if (*lof)
                return 0;
        ptr += sprintf(ptr, "%s\n", str);
        *lof += ptr - buff;
        return (ptr - buff);
}

static ssize_t mstar_proc_write(struct file * fd, const char __user * buff, size_t len, loff_t * lof)
{
        char str[len + 1];
        str[len] = '\0';
        copy_from_user(str, buff, len);
        log("rec = %s", str);

        /* 必须返回写进的字节数，返回 0 的话，会不断的打印 */
        return len;
}

static const struct file_operations mstar_proc_fops = 
{
        .owner = THIS_MODULE,
        .read = mstar_proc_read,
        .write = mstar_proc_write,
};

static int __init mod_init(void)
{
        proc_dir = proc_mkdir("mstar", NULL);
        if(!proc_dir)
        {
                remove_proc_entry("mstar", NULL);
                return -ENOMEM;
        }

        proc_node = proc_create("gesture", 0666, proc_dir, &mstar_proc_fops);
        if(!proc_node)
        {
                remove_proc_entry("mstar", NULL);
                return -ENOMEM;
        }

        log("module init add the /proc/mstar/gesture node");

        return 0;
}

static void __exit mod_exit(void)
{
        remove_proc_entry("gesture", proc_dir);
        remove_proc_entry("mstar", NULL);

        log("module exit remove all proc node");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
