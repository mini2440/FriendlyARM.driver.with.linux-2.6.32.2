驱动介绍：
        介绍了 Linux 内核 sys 节点的创建方式。

[root@FriendlyARM /mnt]# insmod sys_module.ko 
[root@FriendlyARM /mnt]# cd /sys/kernel/
[root@FriendlyARM kernel]# ls
config           mm               uevent_helper
kobject_example  slab             uevent_seqnum

[root@FriendlyARM kernel]# cd kobject_example/
[root@FriendlyARM kobject_example]# ls
bar  baz  foo

[root@FriendlyARM kobject_example]# cat bar
0
[root@FriendlyARM kobject_example]# cat baz
0
[root@FriendlyARM kobject_example]# cat foo
0

[root@FriendlyARM kobject_example]# echo 1 > foo 
[root@FriendlyARM kobject_example]# cat foo
1