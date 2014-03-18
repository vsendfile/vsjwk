obj-m := vsend.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	rm -rf vsend.o vsend.ko vsend.mod.c vsend.mod.o modules.order Module.symvers
