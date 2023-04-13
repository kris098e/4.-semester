/* Prototype module for second mandatory DM510 assignment */
#ifndef __KERNEL__
#define __KERNEL__
#endif
#ifndef MODULE
#define MODULE
#endif

#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/wait.h>
#include <linux/cdev.h>
/* #include <asm/uaccess.h> */
#include <linux/uaccess.h>
#include <linux/semaphore.h>
/* #include <asm/system.h> */
#include <asm/switch_to.h>
#include "dm510_ioctl_numbers.h"
/* Prototypes - this would normally go in a .h file */
static int dm510_open(struct inode *, struct file *);
static int dm510_release(struct inode *, struct file *);
static ssize_t dm510_read(struct file *, char *, size_t, loff_t *);
static ssize_t dm510_write(struct file *, const char *, size_t, loff_t *);
long dm510_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);

#define DEVICE_NAME "dm510_dev" /* Dev name as it appears in /proc/devices */
#define MAJOR_NUMBER 255
#define MIN_MINOR_NUMBER 0
#define MAX_MINOR_NUMBER 1

#define DEVICE_COUNT 2
/* end of what really should have been in a .h file */

struct dm510_dev
{
    int minor_number;
    struct cdev cdev;
    wait_queue_head_t read_q, write_q, open_q;
    struct mutex mutex; // lock for opening and closing the pipes, and updating this dev.
    char *wp, *rp;
    int nreaders, nwriters;
};

struct dm510_buffer
{
    struct mutex mutex; // lock for writing and reading to/from this buffer
    char *end, *head; // head just points to the buffer, end ofc points to end of it
    int size;
};

/* file operations struct */
static struct file_operations dm510_fops = {
    .owner = THIS_MODULE,
    .read = dm510_read,
    .write = dm510_write,
    .open = dm510_open,
    .release = dm510_release,
    .unlocked_ioctl = dm510_ioctl
};

static struct dm510_dev *devices;
static struct dm510_buffer *buffers; // The buffers
/* parameters */
int dm510_buffer_size = 4; // defaults to 1022
int dm510_nreaders = 2;

module_param(dm510_buffer_size, int, 0);


static void dm510_setup_cdev(struct dm510_dev *dev, int index);

/*
 * Set up a cdev entry.
 */
static void dm510_setup_cdev(struct dm510_dev *dev, int index) {
    int err, devno = MKDEV(MAJOR_NUMBER, index);

    cdev_init(&dev->cdev, &dm510_fops);
    dev->cdev.owner = THIS_MODULE;
    err = cdev_add(&dev->cdev, devno, 1);
    if(err)
        printk(KERN_NOTICE "Error %d adding dm510_dev%d", err, index);
}

/* called when module is loaded */
int dm510_init_module(void)
{
    int result;
    dev_t dev = MKDEV(MAJOR_NUMBER, 0);

    /* register how many devices we want */
    result = register_chrdev_region(dev, DEVICE_COUNT, DEVICE_NAME);
    if (result < 0)
    {
        printk(KERN_NOTICE "Unable to get dm510_dev region, error %d\n", result);
        return 0;
    }

    /* pointer to the devices we create */
    devices = kmalloc(DEVICE_COUNT * sizeof(struct dm510_dev), GFP_KERNEL);
    if (!devices) {
        unregister_chrdev_region(dev, DEVICE_COUNT); // fail, unregister again
        return 0;
    }

    /* make buffers, initialize to 0 bits */
    buffers = kzalloc(2 * sizeof(struct dm510_buffer), GFP_KERNEL);

    /* initialize buffers */
    for(int i = 0; i < DEVICE_COUNT; i++) {
        buffers[i].head = kmalloc(dm510_buffer_size * sizeof(char), GFP_KERNEL);
        buffers[i].size = dm510_buffer_size;
        buffers[i].end = buffers[i].head + buffers[i].size; // point at the end
    }

    for(int i = 0; i < DEVICE_COUNT; i++) {
        init_waitqueue_head(&(devices[i].read_q));
        init_waitqueue_head(&(devices[i].write_q));
        init_waitqueue_head(&(devices[i].open_q));
        mutex_init(&buffers[i].mutex);
        mutex_init(&devices[i].mutex);
        dm510_setup_cdev(&devices[i], i);
        buffers[i].size = dm510_buffer_size;
        devices[i].minor_number = i;
        devices[i].nreaders = 0;
        devices[i].nwriters = 0;
    }

    /* point to the correct buffer */
    devices[0].wp = buffers[1].head;
    devices[0].rp = buffers[0].head;

    devices[1].wp = buffers[0].head;
    devices[1].rp = buffers[1].head;
    
    printk(KERN_INFO "DM510: Hello from your device!\n");
    return 0;
}

/* Called when module is unloaded */
void dm510_cleanup_module(void)
{
    int i;

    if(!devices) {
        return;
    }

    for(i = 0; i < DEVICE_COUNT; i++) {
        cdev_del(&devices[i].cdev);
    }
    kfree(buffers);
    kfree(devices);
    /* clean up code belongs here */

    unregister_chrdev_region(MKDEV (MAJOR_NUMBER, 0), DEVICE_COUNT);
    devices = NULL;

    printk(KERN_INFO "DM510: Module unloaded.\n");
}

/* Called when a process tries to open the device file */
static int dm510_open(struct inode *inode, struct file *filp)
{
    struct dm510_dev *dev;
    
    dev = container_of(inode->i_cdev, struct dm510_dev, cdev);
    
    printk(KERN_INFO "DM510: dm510 has been opened with minor number %d.\n", dev->minor_number);
    
    filp->private_data = dev;

    if (mutex_lock_interruptible(&dev->mutex))
        return -ERESTARTSYS;
    
    /* loop until we may open the devices, release() will wake this up */
    while (dev->nreaders == dm510_nreaders) {
        mutex_unlock (&dev->mutex);
        if (filp->f_flags & O_NONBLOCK) return -EAGAIN;

        printk("\"%s\" reading: going to sleep\n", current->comm);
		if (wait_event_interruptible(dev->open_q, (dev->nreaders != dm510_nreaders)))
        	return -ERESTARTSYS; /* signal: tell the fs layer to handle it */
        
        /* otherwise loop, but first reacquire the lock */
		if (mutex_lock_interruptible(&dev->mutex))
			return -ERESTARTSYS;
    }

    if (filp->f_mode & O_ACCMODE)
        dev->nreaders++;
    if (filp->f_mode & FMODE_WRITE)
        dev->nwriters++;
    mutex_unlock(&dev->mutex);

    return nonseekable_open(inode, filp);
}

/* Called when a process closes the device file. */
static int dm510_release(struct inode *inode, struct file *filp)
{
	struct dm510_dev *dev = filp->private_data;

    printk("readers and writers before:\n writers: %d, readers %d\n", dev->nwriters, dev->nreaders);
	mutex_lock(&dev->mutex);
	if (filp->f_mode & FMODE_READ)
		dev->nreaders--;
	if (filp->f_mode & FMODE_WRITE)
		dev->nwriters--;

    /**
    printk("closed minor number %d\n", dev->minor_number);
    printk("there are currently %d readers and %d writers \n", dev->nreaders, dev->nwriters);
    */
    wake_up_interruptible(&dev->open_q);
	mutex_unlock(&dev->mutex);
    return 0;
}

/* Called when a process, which already opened the dev file, attempts to read from it. */
static ssize_t dm510_read(struct file *filp,
                          char *buf,     /* The buffer to fill with data     */
                          size_t count,  /* The max number of bytes to read  */
                          loff_t *f_pos) /* The offset in the file           */
{
    int opposite_minor_number; // used to wake up the writers to the buffer
    struct dm510_buffer *read_buffer; 
    struct dm510_dev *dev = filp->private_data;
    
    if (dev->minor_number == 1) {
        read_buffer = &buffers[1];
        opposite_minor_number = 0;
    } else {
        read_buffer = &buffers[0];
        opposite_minor_number = 1;
    }

    if (mutex_lock_interruptible(&read_buffer->mutex))
        return -ERESTARTSYS;

    while (dev->rp == devices[opposite_minor_number].wp) { // Noting to read
        mutex_unlock (&read_buffer->mutex);
        if (filp->f_flags & O_NONBLOCK) return -EAGAIN;

        printk("\"%s\" reading: going to sleep\n", current->comm);
		if (wait_event_interruptible(dev->read_q, (dev->rp != devices[opposite_minor_number].wp)))
        	return -ERESTARTSYS; /* signal: tell the fs layer to handle it */
        
        /* otherwise loop, but first reacquire the lock */
		if (mutex_lock_interruptible(&read_buffer->mutex))
			return -ERESTARTSYS;
    }
    // Data is there, begin read
    if (devices[opposite_minor_number].wp > dev->rp) {
        count = min(count, (size_t)(devices[opposite_minor_number].wp - dev->rp));
        printk("count is: %ld\n", count);
    }
	else /* the write pointer has wrapped, return data up to dev->end */
		count = min(count, (size_t)(read_buffer->end - dev->rp));

	if (copy_to_user(buf, dev->rp, count)) { 
		mutex_unlock (&read_buffer->mutex);
		return -EFAULT;
	}

    dev->rp += count;
	if (dev->rp == read_buffer->end) {
		dev->rp = read_buffer->head; /* wrapped */
    }
	mutex_unlock (&read_buffer->mutex);

    /* finally, awake any writers to this buffer and return */
	wake_up_interruptible(&devices[opposite_minor_number].write_q);
	printk("\"%s\" did read %li bytes\n",current->comm, (long)count);
    
    return count; // return number of bytes read
}

/* How much space is free? */
static int spacefree(struct dm510_dev *dev)
{
    int opposite_minor_number; // used to wake up the readers to the buffer
    struct dm510_buffer *write_buffer; 
    
    if (dev->minor_number == 1) {
        write_buffer = &buffers[0];
        opposite_minor_number = 0;
    } else {
        write_buffer = &buffers[1];
        opposite_minor_number = 1;
    }

    if (dev->wp == devices[opposite_minor_number].rp) {
		// printk("write pointer equal read pointer\n");
        return write_buffer->size - 1;
    }
	return ((devices[opposite_minor_number].rp + write_buffer->size - dev->wp) % write_buffer->size) - 1;
}

/* Wait for space for writing; caller must hold device semaphore.  On
 * error the semaphore will be released before returning. */
static int getwritespace(struct dm510_dev *dev, struct file *filp, struct mutex *mutex)
{
	while (spacefree(dev) == 0) { /* full */
		DEFINE_WAIT(wait);
		
		mutex_unlock(mutex);
		if (filp->f_flags & O_NONBLOCK)
			return -EAGAIN;
		printk("\"%s\" writing: going to sleep\n",current->comm);
		prepare_to_wait(&dev->write_q, &wait, TASK_INTERRUPTIBLE);
		if (spacefree(dev) == 0)
			schedule();
		finish_wait(&dev->write_q, &wait);
		if (signal_pending(current))
			return -ERESTARTSYS; /* signal: tell the fs layer to handle it */
		if (mutex_lock_interruptible(mutex))
			return -ERESTARTSYS;
	}
	return 0;
}	

/* Called when a process writes to dev file */
static ssize_t dm510_write(struct file *filp,
                           const char *buf, /* The buffer to get data from      */
                           size_t count,    /* The max number of bytes to write */
                           loff_t *f_pos)   /* The offset in the file           */
{
	int result;

    int opposite_minor_number; // used to wake up the readers to the buffer
    struct dm510_buffer *write_buffer; 
    struct dm510_dev *dev = filp->private_data;
    
    if (dev->minor_number == 1) {
        write_buffer = &buffers[0];
        opposite_minor_number = 0;
    } else {
        write_buffer = &buffers[1];
        opposite_minor_number = 1;
    }

	if (mutex_lock_interruptible(&write_buffer->mutex))
		return -ERESTARTSYS;

	/* Make sure there's space to write */
	result = getwritespace(dev, filp, &write_buffer->mutex);
	if (result)
		return result; /* getwritespace called mutex_unlock(&dev->mutex) */

	/* ok, space is there, accept something */
	count = min(count, (size_t)spacefree(dev));
	if (dev->wp >= devices[opposite_minor_number].rp)
		count = min(count, (size_t)(write_buffer->end - dev->wp)); /* to end-of-buf */
	else /* the write pointer has wrapped, fill up to rp-1 */
		count = min(count, (size_t)(devices[opposite_minor_number].rp - dev->wp - 1));

	printk("Going to accept %li bytes to %p from %p\n", (long)count, dev->wp, buf);
    
	if (copy_from_user(dev->wp, buf, count)) {
		mutex_unlock (&write_buffer->mutex);
		return -EFAULT;
	}

	dev->wp += count;
	if (dev->wp == write_buffer->end) {
		dev->wp = write_buffer->head; /* wrapped */
        printk("did update the write pointer\n");
    }
	mutex_unlock(&write_buffer->mutex);

	/* finally, awake any reader */
    printk("waking up readers\n");
	wake_up_interruptible(&devices[opposite_minor_number].read_q);  /* blocked in read() */

	printk("\"%s\" did write %li bytes\n",current->comm, (long)count);

	return count;
}

static void update_buffers(void) {
    for(int i = 0; i < DEVICE_COUNT; i++) {
        kfree(buffers[i].head);

        buffers[i].head = kmalloc(dm510_buffer_size * sizeof(char), GFP_KERNEL);
        buffers[i].size = dm510_buffer_size;
        buffers[i].end = buffers[i].head + buffers[i].size; // point at the end
        mutex_init(&buffers[i].mutex);
    }

    /* point to the correct buffer */
    devices[0].wp = buffers[1].head;
    devices[0].rp = buffers[0].head;

    devices[1].wp = buffers[0].head;
    devices[1].rp = buffers[1].head;
}

/* called by system call icotl */
long dm510_ioctl(
    struct file *filp,
    unsigned int cmd,  /* command passed from the user */
    unsigned long arg /* argument of the command */
    )
{
    int err = 0;
    int retval = 0;

    if(_IOC_TYPE(cmd) != DM510_MAGIC_NUMBER) return -ENOTTY;
    if(_IOC_NR(cmd) > DM510_IOC_MAXNR) return -ENOTTY;

    if (_IOC_DIR(cmd) & _IOC_READ)
        err = !access_ok((void __user *)arg, _IOC_SIZE(cmd));
    else if (_IOC_DIR(cmd) & _IOC_WRITE)
        err = !access_ok((void __user *)arg, _IOC_SIZE(cmd));
    if (err) return -EFAULT;

    switch (cmd)
    {
    case DM510_IOR_BUFFER_SIZE:
        retval = __put_user(dm510_buffer_size, (int __user *) arg);
        break;
    case DM510_IOR_READERS:
        retval = __put_user(dm510_nreaders, (int __user *) arg);
        break;
    case DM510_IOS_BUFFER_SIZE: // Must be called before starting to write/read, or may lead to invalid state
        retval = __get_user(dm510_buffer_size, (int __user *) arg);
        update_buffers();
        break;
    case DM510_IOS_READERS:
        retval = __get_user(dm510_nreaders, (int __user *) arg);
        break;
    default:  /* does not match any commands defined */
        return -ENOTTY;
    }

    return retval;
}

module_init(dm510_init_module);
module_exit(dm510_cleanup_module);

MODULE_AUTHOR("...Kristian Degn Abrahamsen.");
MODULE_LICENSE("GPL");

