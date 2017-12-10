驱动介绍：
        介绍了 Linux 内核 sys 节点的创建方式。

[root@FriendlyARM /mnt]# insmod kset_example.ko
[root@FriendlyARM /mnt]# cd /sys/kernel/
[root@FriendlyARM kernel]# ls
config         mm             uevent_helper
kset_example   slab           uevent_seqnum

[root@FriendlyARM kernel]# cd kset_example/
[root@FriendlyARM kset_example]# ls -l
drwxr-xr-x    2 root     root            0 Jan  1 10:29 bar
drwxr-xr-x    2 root     root            0 Jan  1 10:29 baz
drwxr-xr-x    2 root     root            0 Jan  1 10:29 foo

[root@FriendlyARM kset_example]# cd foo
[root@FriendlyARM foo]# ls
bar  baz  foo
[root@FriendlyARM foo]# cat foo
0

[root@FriendlyARM foo]# echo 7 > foo 
[root@FriendlyARM foo]# cat foo
7
