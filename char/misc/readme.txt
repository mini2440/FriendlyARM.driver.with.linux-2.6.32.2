驱动介绍：
        杂项方式注册字符设备驱动。

[root@FriendlyARM /mnt]# insmod misc_module.ko 
mod_init ok

[root@FriendlyARM /mnt]# ./app 
misc open ok
misc read ok
misc write ok
misc release ok

