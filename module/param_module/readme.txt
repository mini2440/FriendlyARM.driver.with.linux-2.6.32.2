驱动介绍：
        实现模块带参数加载。

[root@FriendlyARM /mnt]# insmod param_module.ko
usage: insmod param_module name=<str> age=<int>
insmod: cannot insert 'param_module.ko': Operation not permitted

[root@FriendlyARM /mnt]# insmod param_module.ko name="bean" age=20
hello bean, your age is 20
param module init ok!
[root@FriendlyARM /mnt]# rmmod param_module
param module exit ok!
