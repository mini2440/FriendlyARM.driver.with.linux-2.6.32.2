驱动介绍：
        led 字符设备驱动。

[root@FriendlyARM /mnt]# insmod led_module.ko 
[Paul][mod_init][129] successful!

[root@FriendlyARM /mnt]# ./app 
[Paul][mini2440_led_open][29] hello
[Paul][mini2440_led_write][54] led on
[Paul][mini2440_led_write][60] led off
[Paul][mini2440_led_write][54] led on
[Paul][mini2440_led_write][60] led off
[Paul][mini2440_led_write][54] led on
[Paul][mini2440_led_write][60] led off
[Paul][mini2440_led_release][38] bye

