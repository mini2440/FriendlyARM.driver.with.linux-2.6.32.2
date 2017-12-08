驱动介绍：
        led 字符设备驱动。

[root@FriendlyARM /mnt]# insmod standard_module.ko 
[Paul][mod_init][99] mod_init ok

[root@FriendlyARM /mnt]# ./app 
[app] O_RDWR = 2
[Paul][mini2440_open][21] standard open ok
[Paul][mini2440_write][43] tmp = 100
[Paul][mini2440_write][44] standard write ok
[Paul][mini2440_read][35] standard read ok
[Paul][mini2440_release][27] standard release ok
[app] read_buf = 128

