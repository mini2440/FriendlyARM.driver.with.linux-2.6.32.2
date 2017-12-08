驱动介绍：
        模块与模块之前具有依赖关系，一个模块导出符号给另一个模块使用。

[root@FriendlyARM /mnt]# insmod test_module.ko 
test_module: Unknown symbol calculate_add
test_module: Unknown symbol calculate_sub
insmod: cannot insert 'test_module.ko': unknown symbol in module or invalid parameter

[root@FriendlyARM /mnt]# insmod calculate.ko 
calculate module init ok!
[root@FriendlyARM /mnt]# insmod test_module.ko 
[calculate_add][6] is running
[mod_init][9] 10 - 5 = 15
[calculate_sub][13] is running
[mod_init][10] 10 - 5 = 5
test module init ok!

