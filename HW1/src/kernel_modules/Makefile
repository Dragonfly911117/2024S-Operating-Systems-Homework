obj-m += jiffies.o
obj-m += seconds.o
obj-m += task_info.o

all: clean
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	mv *.ko ../../bin/kernel_modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f ../../bin/kernel_modules/*.ko