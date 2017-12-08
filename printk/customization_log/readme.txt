驱动介绍：
        封装一个个人专属的打印 log 的函数。

[root@FriendlyARM /mnt]# insmod log_module.ko 
[Paul][mod_init][14] hello everyone
[Paul][mod_init][15] my name is Paul
[Paul][mod_init][16] my age is 24
[Paul][mod_init][17] using hex is 0x18

[root@FriendlyARM /mnt]# rmmod log_module
/home/user/workspace/mini2440/linux_driver/02_printk/02_log/log_module.c:
[Paul][mod_exit][23] goodbye, everyone

