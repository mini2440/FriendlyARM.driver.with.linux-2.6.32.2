obj-m += led_module.o

KERNEL = /home/user/workspace/mini2440/linux-2.6.32.2
SHARE = /home/user/board

all:
	make -C $(KERNEL) M=`pwd` modules
	arm-linux-gcc led_app.c -o app
	rm -rf $(SHARE)/*
	cp -f *.ko $(SHARE)/
	cp -f app $(SHARE)/
	make clean
	@echo "\033[31m >>>>>> make all successful <<<<<< \033[0m"
clean:
	make -C $(KERNEL) M=`pwd` modules clean
	rm -f app
