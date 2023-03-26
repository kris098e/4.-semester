![[ch03_linux_modules.pdf]]

* Major and minor numbers when issuing `(cd /dev/; ls -l)`, major identifies the driver associated with the device, such that the linux kernel knows which driver we have to pass to when a device does something. The driver _controls_ the device
	* These can be shared
* The minor number is used by the kernel to determine exactly which device is being referred to, which can then be passed to the driver (major number) that controls the device.
* driver numbers has `12 bits`, devices has `20 bits`
* The driver should get major and minor numbers from
	* `MAJOR(dev_t dev);
	* `MINOR(dev_t dev);`
		* defined in `<linux/kdev_t.h`
	* These methods are used since we cannot just assume which minor and major number the driver should get
* The driver needs to get device numbers such that we can use that many devices for the driver. this is done via
	* `int register_chrdev_region(dev_t first, unsigned int count, char *name);`
		* first is the first device number, count is how many.
		* name is the name associated with the number range
* `int alloc_chrdev_region(dev_t *dev, unsigned int firstminor, unsigned int count, char *name);` to allocate on the fly, if we dont know how many devices are needed. `dev` is output only.
* freeing device numbers: `void unregister_chrdev_region(dev_t first, unsigned int count);`
	* call in the cleanup
* use `alloc_chrdev_region()` to get major number for device driver. This way we dynamicly get the number, instead of staticly putting it somewhere, and we are less likely to run into risks.
* can use script to load devices see here [[ch03_linux_modules.pdf#page=6]]

Can provide default values for the major and minor numbers with this, if we read an input. or `else` is just dynamic
```c
if (scull_major) {
 dev = MKDEV(scull_major, scull_minor);
 result = register_chrdev_region(dev, scull_nr_devs, "scull");
} else {
 result = alloc_chrdev_region(&dev, scull_minor, scull_nr_devs,"scull"); 
 scull_major = MAJOR(dev); 
} 
if (result < 0) { 
  printk(KERN_WARNING "scull: can't get major %d\n", scull_major); 
  return result; 
}
```


# data structures
## file_operations
* `<linux/fs.h>`
The methods the driver can implement for the`file_operations struct` are listed here.  [[ch03_linux_modules.pdf#page=9]]
an example for the SCULL-driver:
```c
struct file_operations scull_fops = {
 .owner = THIS_MODULE,
 .llseek = scull_llseek,
 .read = scull_read,
 .write = scull_write,
 .ioctl = scull_ioctl,
 .open = scull_open,
 .release = scull_release,
};
```
## file
represents an _open_ file descriptor
_The inode structure is used by the kernel internally to represent files. Therefore, it is different from the file structure that represents an open file descriptor. There can be numerous file structures representing multiple open descriptors on a single file, but they all point to a single inode structure._

* `<linux/fs.h>`
_We’ll consistently call the pointer filp to prevent ambiguities with the structure itself. Thus, file refers to the structure and filp to a pointer to the structure._
The filp is passed to every function that operates on the opened file

examples of fields in the `file struct` are listed here [[ch03_linux_modules.pdf#page=12]]

## inode
used by kernel to represent files
The fiels are listen here [[ch03_linux_modules.pdf#page=14]]

From a `struct inode` retrieve the `major` and `minor` number by the methods here
```c
unsigned int iminor(struct inode *inode);
unsigned int imajor(struct inode *inode);
```

# Char driver registration
`include <linux/cdev.h>`
at runtime get the `cdev` struct if you have not already gotten it inside the _device specific structure_
```c
struct cdev *my_cdev = cdev_alloc( );
my_cdev->ops = &my_fops;
```

If already have a `struct cdev` within the device specific structure, initialize it
```c
void cdev_init(struct cdev *cdev, struct file_operations *fops);
```

Either way, there is one other struct cdev field that you need to initialize. Like the file_operations structure, struct cdev has an owner field that should be set to THIS_MODULE. Once the cdev structure is set up, the final step is to tell the kernel about it with a call to: 
`int cdev_add(struct cdev *dev, dev_t num, unsigned int count);`

once `cdev_add` returns the device is _live_. and its operations can be called by the kernel. Therefore this should not be called before the driver is ready to handle operations on the device.

to remove it:
`void cdev_del(struct cdev *dev);`

structure of scull:
```c
struct scull_dev {
 struct scull_qset *data; /* Pointer to first quantum set */
 int quantum; /* the current quantum size */
 int qset; /* the current array size */
 unsigned long size; /* amount of data stored here */
 unsigned int access_key; /* used by sculluid and scullpriv */
 struct semaphore sem; /* mutual exclusion semaphore */
 struct cdev cdev; /* Char device structure */
};
```

init cdev:
```c
static void scull_setup_cdev(struct scull_dev *dev, int index)
{
 int err, devno = MKDEV(scull_major, scull_minor + index);
 cdev_init(&dev->cdev, &scull_fops);
 dev->cdev.owner = THIS_MODULE;
 dev->cdev.ops = &scull_fops; // search for this in the text. Pointer to all operations
 err = cdev_add (&dev->cdev, devno, 1);
 /* Fail gracefully if need be */
 if (err)
	 printk(KERN_NOTICE "Error %d adding scull%d", err, index);
}
```
Since the cdev structure is embedded within struct scull_dev, cdev_init must be called to perform the initialization of that structure.

# open
The open method is provided for a driver to do any initialization in preparation for later operations
open: [[ch03_linux_modules.pdf#page=17]]

```c
// OPEN simplified
int scull_open(struct inode *inode, struct file *filp)
{
 struct scull_dev *dev; /* device information */
 dev = container_of(inode->i_cdev, struct scull_dev, cdev); // retrieve the information for the char driver
 filp->private_data = dev; /* for other methods */
 /* now trim to 0 the length of the device if open was write-only */
 if ( (filp->f_flags & O_ACCMODE) == O_WRONLY) {
	 scull_trim(dev); /* ignore errors */
 }
 return 0; /* success */
}
```
# release
The role of the release method is the reverse of open. Sometimes you’ll find that the method implementation is called device_close instead of device_release.

[[ch03_linux_modules.pdf#page=18]]

# Memory
uses paging.
![[Pasted image 20230323155714.png]]
The chosen numbers are such that writing a single byte in scull consumes 8000 or
12,000 thousand bytes of memory: 4000 for the quantum and 4000 or 8000 for the
quantum set (according to whether a pointer is represented in 32 bits or 64 bits on
the target platform). If, instead, you write a huge amount of data, the overhead of the
linked list is not too bad. There is only one list element for every four megabytes of
data, and the maximum size of the device is limited by the computer’s memory size.

**see** the code for trim at [[ch03_linux_modules.pdf#page=21]] which will free all quantums and qsets


# Write and read
[[ch03_linux_modules.pdf#page=22]]
dont ever access memory from user-space directly, as this is paged. If we try to access it, we will generate a page fault, as this does not share the same page table. This will then bring down the calling process.

```c
unsigned long copy_to_user(void __user *to,
const void *from,
unsigned long count);

unsigned long copy_from_user(void *to,
const void __user *from,
unsigned long count);
```
When reading and writing to the `filp` we can then also choose to update the offset and other attributes in the structure of `struct file` , to match what we have written and read

read code is here [[ch03_linux_modules.pdf#page=26]]
write code is here [[ch03_linux_modules.pdf#page=27]]

# RECAP
[[ch03_linux_modules.pdf#page=29]] at the bottom
The PDF file titled "Chapter 3: Char Drivers" is a chapter from the book "Linux Device Drivers, Third Edition" written by Jonathan Corbet, Alessandro Rubini, and Greg Kroah-Hartman.

The chapter begins by introducing the concept of character devices, which are one of the three types of devices in Linux, and explains how to create a character device driver. It then discusses the different data structures that are used to manage character devices, including file operations, inode operations, and file structures.

Next, the chapter goes into detail about the functions that are required to implement the file operations and inode operations for a character device driver. It covers the open, release, read, write, ioctl, and poll functions, explaining their purpose and how they are implemented.

The chapter also provides information about how to handle errors that may occur during operation and how to debug a character device driver using printk statements.

Finally, the chapter explains how to register a character device driver with the kernel and provides an example of a simple character device driver.

Overall, this chapter provides a comprehensive introduction to writing a character device driver in Linux, covering the necessary data structures, functions, and techniques needed for implementation.