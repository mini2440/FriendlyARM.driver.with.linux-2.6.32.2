驱动介绍：
        介绍了 Linux 内核 proc 节点的创建方式。

[root@FriendlyARM /mnt]# insmod proc_module.ko 
[Paul][mod_init][66] module init add the /proc/mstar/gesture node

[root@FriendlyARM /mnt]# cat /proc/mstar/gesture 
hello I am proc node

[root@FriendlyARM /mnt]# echo "1" >> /proc/mstar/gesture 
[Paul][mstar_proc_write][37] rec = 1

