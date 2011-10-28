CC=gcc -Wall

KERNEL_DIR?=/lib/modules/$(shell uname -r)/build
.PHONY: clean modules modules_install
obj-m=xtime_module.o

syscall_test:
	$(CC) use_xtime.c -o syscall_test

module_test:
	$(CC) use_time_module.c -o module_test

modules:
	$(MAKE) -C $(KERNEL_DIR) M=$(shell pwd) modules

modules_install:
	$(MAKE) -C $(KERNEL_DIR) M=$(shell pwd) modules_install

clean:
	rm -rf syscall_test *.o *.ko *.mod.c .tmp_versions *.symvers .*.cmd *.order
