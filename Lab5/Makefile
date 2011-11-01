CC=gcc -Wall

KERNEL_DIR?=/lib/modules/$(shell uname -r)/build
.PHONY: clean modules modules_install
obj-m=hello.o

modules:
	$(MAKE) -C $(KERNEL_DIR) M=$(shell pwd) modules

modules_install:
	$(MAKE) -C $(KERNEL_DIR) M=$(shell pwd) modules_install

clean:
	rm -rf *.o *.ko *.mod.c .tmp_versions *.symvers .*.cmd *.order
