

//Mon Dec 05 19:41:57 BDT 2011 
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>

#ifndef P_DRIVER_H
#define P_DRIVER_H

struct q_set
{
	void **data;
	struct q_set *next;
};

struct p_dev
{
	struct q_set *data;
	int quantum;		/* the current quantum size */
	int qset;		/* the current array size */
	unsigned long size;
	//devfs_handle_t handle; 	/* only used if devfs is there */
	unsigned int access_key;/* used by sculluid and scullpriv */
	struct semaphore sem; 	/* mutual exclusion semaphore */
	struct cdev cdev;
	
};



typedef struct p_driver
{
	dev_t dev;
	dev_t driver_major_number; //unsigned int -> __u32 in 32bit OS maybe
	dev_t driver_first_number;
	dev_t driver_minor_number;
	char *driver_name;
	struct file_operations pfops;
	int limit;
	struct p_dev *p_dev;
	

}p_driver;





//int p_trim(dev_info *);

int p_driver_open(struct inode *, struct file *);
struct q_set *p_follow(struct p_dev *, int );
int p_trim(struct p_dev *);


int p_init_driver(struct p_driver *);
void p_rel_driver(struct p_driver *);

static void p_setup_cdev(struct p_driver *);
//static int p_release(struct inode *, struct file *);



int p_fop_open(struct inode *, struct file *);
int p_fop_release(struct inode *, struct file *);
ssize_t p_fop_read(struct file *, char __user *, size_t , loff_t *);
ssize_t p_fop_write(struct file *, const char __user *, size_t , loff_t *);

#include "char_driver_load.c"
#include "file_operations_func.c"



#endif

