驱动介绍：
        平台设备驱动匹配过程。

[root@FriendlyARM /mnt]# ls
platform_device.ko  platform_driver.ko

[root@FriendlyARM /mnt]# insmod platform_device.ko
[Paul][mod_init][26] platform device init
[root@FriendlyARM /mnt]# insmod platform_driver.ko
[Paul][demo_probe][19] enter the probe
[Paul][mod_init][42] platform device init

[root@FriendlyARM /mnt]# rmmod platform_driver
[Paul][demo_remove][25] enter the remove
[Paul][mod_exit][49] platform device exit


