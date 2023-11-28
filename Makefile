ccflags-y := -I$(PWD)/inc  # -I - флаг, що вказує компілятору GCC де шукати header hello1.h
ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m := hello1.o hello2.o
else
# normal makefile
KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR) M=$$PWD
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
endif
