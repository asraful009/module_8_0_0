
#Sun Dec 04 21:52:20 BDT 2011 

obj-m := driver_open.o

all:
	make -C /usr/src/linux SUBDIRS=$(PWD)/ modules

