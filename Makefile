
obj-m := chrdev_scrull.o


NATIVE ?= true


ifeq ($(NATIVE), false)
	KERNEL_DIR = /home/sun/Documents/imx6ull_source/ebf-buster-linux  
else
	KERNEL_DIR = /home/sun/Documents/imx6ull_source/ebf-buster-linux 
endif

all:modules
modules clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(shell pwd) $@
