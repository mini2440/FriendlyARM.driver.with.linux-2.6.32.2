驱动介绍：
        内核打印等级。

[root@FriendlyARM /mnt]# insmod print_level.ko 
hello world! KERN_EMERG   = <0>
hello world! KERN_ALERT   = <1>
hello world! KERN_CRIT    = <2>
hello world! KERN_ERR     = <3>
hello world! KERN_WARNING = <4>
hello world! KERN_NOTICE  = <5>
hello world! KERN_INFO    = <6>
[root@FriendlyARM /mnt]# rmmod print_level    
goodbye world! KERN_EMERG   = <0>
goodbye world! KERN_ALERT   = <1>
goodbye world! KERN_CRIT    = <2>
goodbye world! KERN_ERR     = <3>
goodbye world! KERN_WARNING = <4>
goodbye world! KERN_NOTICE  = <5>
goodbye world! KERN_INFO    = <6>

[root@FriendlyARM /mnt]# dmesg -c > 0
[root@FriendlyARM /mnt]# dmesg
hello world! KERN_EMERG   = <0>
hello world! KERN_ALERT   = <1>
hello world! KERN_CRIT    = <2>
hello world! KERN_ERR     = <3>
hello world! KERN_WARNING = <4>
hello world! KERN_NOTICE  = <5>
hello world! KERN_INFO    = <6>
hello world! KERN_DEBUG   = <7>
goodbye world! KERN_EMERG   = <0>
goodbye world! KERN_ALERT   = <1>
goodbye world! KERN_CRIT    = <2>
goodbye world! KERN_ERR     = <3>
goodbye world! KERN_WARNING = <4>
goodbye world! KERN_NOTICE  = <5>
goodbye world! KERN_INFO    = <6>
goodbye world! KERN_DEBUG   = <7>
