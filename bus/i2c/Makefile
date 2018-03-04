obj-m += i2c_device.o
obj-m += i2c_driver.o

KERNEL = /home/user/workspace/mini2440/linux-2.6.32.2
SHARE = /home/user/board

all:
	make -C $(KERNEL) M=`pwd` modules
	arm-linux-gcc -o app i2c_app.c
	rm -rf $(SHARE)/*
	cp -f *.ko $(SHARE)/
	cp -f app $(SHARE)/
	make clean
	@echo "\033[31m >>>>>> make all successful <<<<<< \033[0m"
clean:
	make -C $(KERNEL) M=`pwd` modules clean
	rm -rf app
