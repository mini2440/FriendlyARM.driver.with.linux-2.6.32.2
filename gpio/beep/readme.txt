驱动介绍：
        beep 字符设备驱动。

[root@FriendlyARM /mnt]# insmod beep_module.ko 
[root@FriendlyARM /mnt]# ./app 
[Paul][beep_write][50] beep on
[Paul][beep_write][55] beep off
[Paul][beep_write][50] beep on
[Paul][beep_write][55] beep off
[Paul][beep_write][50] beep on
[Paul][beep_write][55] beep off

[root@FriendlyARM /mnt]# ls -l /sys/class/beep_class/paul-beep/    
-r--r--r--    1 root     root         4096 Jan  1 08:20 dev
lrwxrwxrwx    1 root     root            0 Jan  1 08:20 subsystem -> ../../../../class/beep_class
-rw-r--r--    1 root     root         4096 Jan  1 08:20 uevent

