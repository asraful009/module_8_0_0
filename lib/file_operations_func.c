
//Mon Dec 05 09:12:33 BDT 2011 

#include <linux/fs.h>


int p_trim(struct p_dev *dev)
{
	struct q_set *next, *dptr;
	int qset = dev->qset;
	/* "dev" is not-null */
	int i;
	for (dptr = dev->data; dptr; dptr = next)
	{ /* all the list items */
		if (dptr->data)
		{
			for (i = 0; i < qset; i++)
				kfree(dptr->data[i]);
			kfree(dptr->data);
			dptr->data = NULL;
		}
		next = dptr->next;
		kfree(dptr);
	}
	dev->size = 0;
	dev->quantum = p_quantum;
	dev->qset = p_qset;
	dev->data = NULL;
	
	return 0;
}




int p_fop_open(struct inode *inode, struct file *filp)
{
	//struct p_dev *dev;


	
	pcount=0;
	p_strlen=strlen(tmp);
	
	printk
	(
		"<1> driver_open major number %d and minor is %d\nstring length %d\n",
		MAJOR(inode->i_rdev),
		MINOR(inode->i_rdev),
		p_strlen
	);


/*	dev=container_of(inode->i_cdev, struct p_dev, cdev);
	filp->private_data=dev;
	
	if((filp->f_flags & O_ACCMODE)== O_WRONLY)
	{
		p_trim(dev);
	}
*/	
	
	
	return 0;
	
}


int p_fop_release(struct inode *inode, struct file *filp)
{
	//MOD_DEC_USE_COUNT;
	printk
	(
		"<1> driver_open %d %d want to bye \n",
		MAJOR(inode->i_rdev),
		MINOR(inode->i_rdev)
	);
	pcount=0;
	printk("<1>tmp data \"%s\"", tmp);
	return 0;
}


ssize_t p_fop_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{

	
	
	//long long int t1, t2;
	p_strlen=strlen(tmp);
	printk
	(
		"<1> driver_open want to read (%d) strlen %d\n",
		pcount,
		p_strlen
		//MAJOR(inode->i_rdev),
		//MINOR(inode->i_rdev)
	);
	
	
	//a[0]=inb(888);

	//printk
	//(
	//	"<1> driver_open want to inb() = %d\n",
	//	a[0]
	//);
	
	
	//i use //copy_to_user(buf, string , count);
	
	count=1;
	
	
	
	
	copy_to_user(buf, &tmp[pcount], count);
	pcount++;
	//////////////////
	
	/*
	struct p_dev *dev = filp->private_data;
	struct q_set *dptr;
	
	/// the first listitem /
	int quantum = dev->quantum, qset = dev->qset;
	int itemsize = quantum * qset; // how many bytes in the listitem //
	int item, s_pos, q_pos, rest;
	
	ssize_t retval = 0;
	
	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;
	if (*f_pos >= dev->size)
		goto out;
	if (*f_pos + count > dev->size)
		count = dev->size - *f_pos;
	
	// find listitem, qset index, and offset in the quantum //
	item = (long)*f_pos / itemsize;
	rest = (long)*f_pos % itemsize;
	s_pos = rest / quantum; q_pos = rest % quantum;
	
	// follow the list up to the right position (defined elsewhere) //
	dptr = p_follow(dev, item);
	
	if (dptr == NULL || !dptr->data || ! dptr->data[s_pos])
		goto out; // don't fill holes //
	// read only up to the end of this quantum //
	if (count > quantum - q_pos)
		count = quantum - q_pos;
		
	if (copy_to_user(buf, dptr->data[s_pos] + q_pos, count))
	{
		retval = -EFAULT;
		goto out;
	}
	
	*f_pos += count;
	retval = count;
	
	out:
	up(&dev->sem);
	*/
	if(pcount<=p_strlen)
	
		return 1;
		
	return 0;
}

ssize_t p_fop_write(struct file *filp, const char __user *buf, size_t count,loff_t *f_pos)
{
	
	
	

	
	printk
	(
		"<1> driver_open want to write\n"
		//MAJOR(inode->i_rdev),
		//MINOR(inode->i_rdev)
	);
	
	
	

	
  	copy_from_user(tmp, buf, count);
  	
  	tmp[count]='\0';
  	
  	printk("<1>-%s-\n", tmp);
  	
  	//outb(tmp[0], 888);
  	return count;
	
	
	
	/*
	struct p_dev *dev = filp->private_data;
	struct q_set *dptr;
	int quantum = dev->quantum, qset = dev->qset;
	int itemsize = quantum * qset;
	int item, s_pos, q_pos, rest;
	ssize_t retval = -ENOMEM; // value used in "goto out" statements //

	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;
	// find listitem, qset index and offset in the quantum //
	item = (long)*f_pos / itemsize;
	rest = (long)*f_pos % itemsize;
	s_pos = rest / quantum; q_pos = rest % quantum;
	
	// follow the list up to the right position //
	dptr = p_follow(dev, item);
	if (dptr == NULL)
		goto out;
	if (!dptr->data)
	{
		dptr->data = kmalloc(qset * sizeof(char *), GFP_KERNEL);
		if (!dptr->data)
			goto out;
		memset(dptr->data, 0, qset * sizeof(char *));
	}
	
	if (!dptr->data[s_pos])
	{
		dptr->data[s_pos] = kmalloc(quantum, GFP_KERNEL);
		if (!dptr->data[s_pos])
			goto out;
	}

	// write only up to the end of this quantum //
	if (count > quantum - q_pos)
		count = quantum - q_pos;
	if (copy_from_user(dptr->data[s_pos]+q_pos, buf, count))
	{
		retval = -EFAULT;
		goto out;
	}
	
	*f_pos += count;
	retval = count;
	
	// update the size //
	if (dev->size < *f_pos)
		dev->size = *f_pos;
	
	out:

	up(&dev->sem);
*/
	//return 0;//retval;
}




struct q_set *p_follow(struct p_dev *dev, int n)
{

        struct q_set *qs = dev->data;
/*                // Allocate first qset explicitly if need be //
         if (! qs) {
                 qs = dev->data = kmalloc(sizeof(struct q_set), GFP_KERNEL);
                 if (qs == NULL)
                         return NULL;  // Never mind //
                 memset(qs, 0, sizeof(struct q_set));
         }
 
         // Then follow the list //
         while (n--) {
                 if (!qs->next) {
                         qs->next = kmalloc(sizeof(struct q_set), GFP_KERNEL);
                         if (qs->next == NULL)
                                 return NULL;  // Never mind //
                         memset(qs->next, 0, sizeof(struct q_set));
                 }
                 qs = qs->next;
                 continue;
         }
         */
         return qs;
}



