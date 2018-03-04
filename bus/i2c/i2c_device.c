#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/i2c.h>

/* simple log */
#define log(fmt, arg...)\
        printk(KERN_INFO "[Paul][%s][%d] "fmt"\n", __func__, __LINE__, ##arg);

#define err(fmt, arg...)\
        printk(KERN_ERR "[Paul][%s][%d] ERROR!!! "fmt"\n", __func__, __LINE__, ##arg);

/* detail log */
#define dbg(fmt, arg...)\
        printk(KERN_INFO "%s:\n[Paul][%s][%d] "fmt"\n", __FILE__, __func__, __LINE__, ##arg);

/* i2c 设备结构体 */
static struct i2c_client *at24cxx_client;

/* 这个 addr list 表示当前 device 支持的设备地址，创建 i2c_client 的时候会使用它和设备通信一次，判断设备是否真实存在总线上 */
static const unsigned short addr_list[] = { 0x50, I2C_CLIENT_END };

static int __init mod_init(void)
{
        struct i2c_adapter *i2c_adap;
        struct i2c_board_info at24cxx_info;
        memset(&at24cxx_info, 0, sizeof(struct i2c_board_info));

        log("start");

        /* 这里的 type 属性就是 device 的 name 属性 */
        /* 和驱动匹配就是靠这个 type 属性 */
        strlcpy(at24cxx_info.type, "at24c08", I2C_NAME_SIZE);

        /* 获取 i2c 控制器，适配器 */
        i2c_adap = i2c_get_adapter(0);
        
        /* 
        此函数有干了以下这几件事：
           1. 创建了一个 i2c_client。
           2. 根据 addr_list 中提供的 i2c 地址，主机发 i2c 地址，看设备是否真实存在在总线上
        */
        at24cxx_client = i2c_new_probed_device(i2c_adap, &at24cxx_info, addr_list);
        i2c_put_adapter(i2c_adap);

        log("done");

        if (at24cxx_client)
                return 0;
        else
                return -ENODEV;
        
}

static void __exit mod_exit(void)
{
        log("start");
        i2c_unregister_device(at24cxx_client);
        log("done");
        log("platform device exit");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
