obj-m += kset_example.o

KERNEL = /home/user/workspace/mini2440/linux-2.6.32.2
SHARE = /home/user/board

all:
	make -C $(KERNEL) M=`pwd` modules
	rm -rf $(SHARE)/*
	cp -f *.ko $(SHARE)/
	make clean
	@echo "\033[31m >>>>>> make all successful <<<<<< \033[0m"
clean:
	make -C $(KERNEL) M=`pwd` modules clean
	rm -f app
