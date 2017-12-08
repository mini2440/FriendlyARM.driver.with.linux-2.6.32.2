驱动介绍：
        早期方式注册字符设备驱动。

[root@FriendlyARM /mnt]# insmod early_module.ko 
mini2440_major = 253
mod_init ok

[root@FriendlyARM /mnt]# ./app 
early open ok
early read ok
early write ok
early release ok


