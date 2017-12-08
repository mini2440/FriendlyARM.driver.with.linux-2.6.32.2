驱动介绍：
        最简单的内核模块，相当于 c 语言入门的 hello world 程序。
        介绍了模块 init 和 exit 函数。
        
[root@FriendlyARM /mnt]# insmod simplest_module.ko 
simplest module init ok!
[root@FriendlyARM /mnt]# rmmod simplest_module    
simplest module exit ok!

[root@FriendlyARM /mnt]# insmod simplest_module.ko 
simplest module init ok!
[root@FriendlyARM /mnt]# modprobe -r simplest_module
simplest module exit ok!
