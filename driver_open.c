

//Sun Dec 04 21:41:16 BDT 2011 


#include <linux/kernel.h> 
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h> 	///kmalloc()
#include <linux/fcntl.h>	///O_ACCMODE
#include <asm/uaccess.h>	///copy_to/from_user() function
#include <asm/io.h>		///inb() outb()
#include <linux/ioport.h>
#include <linux/string.h>	///string ... function strlen()


//#include <linux/timer.h>		///ssleep() not find

MODULE_LICENSE("GPL");
MODULE_AUTHOR("pavel");
MODULE_DESCRIPTION("he he he i don't  know what happen when it run");

static int __init p_init(void);
static void __exit p_exit(void);

int p_quantum;
int p_qset;
int pcount=0;
int pport;
char a[10]="hi pavel\n\0";
char tmp[1000];
__kernel_size_t p_strlen=0;


#include "lib/driver.h"

//struct p_dev *pdev=NULL;

struct p_driver pdriver=
{
	driver_major_number: 	0,
	driver_name: 		"driver_open",
	limit:			1,
	driver_first_number: 	0,//both are same driver_first_number 
	driver_minor_number: 	0,//and driver_minor_number
	p_dev:		NULL,
	pfops:
	{
		owner:		THIS_MODULE,
		open:		p_fop_open,
		release:	p_fop_release,
		read:		p_fop_read,
		write:		p_fop_write
			
	}
};




static int __init p_init(void)
{
	
	int i;
	//a={"hi pavel\n\0"};
	tmp[0]='\0'; //first time string length is 0
	printk
	(
		"<1>pavel driver_open: loaded [ok]\n\n%d %d %s\n",
			pdriver.limit,
			pdriver.driver_first_number,
			pdriver.driver_name
	);
	
	//pdriver.p_dev=NULL;
	if(p_init_driver(&pdriver)==0)
	{
		p_setup_cdev(&pdriver);
			
		printk(KERN_ALERT "driver_open create %d %d\n",MAJOR(pdriver.dev), MINOR(pdriver.dev));
	}
	else
		printk(KERN_ALERT "driver_open create error\n");	
	
	//pport=check_region(888, 1);
	//if(pport==0)
	{
	//	request_region(888, 1, pdriver.driver_name);
		
	}

	
	
	//printk("<1>pavel driver_open: loaded [ok]\n");
	return 0;
}

static void __exit p_exit()
{

	p_rel_driver(&pdriver);
	//unregister_chrdev_region(pdriver.dev, pdriver.limit);
	
	//if(pport==0)
	{
	//	release_region(888, 1);
	}
	
	printk("<1>pavel driver_open: exit [ok]\n");
	
	
}

module_init(p_init);
module_exit(p_exit);




