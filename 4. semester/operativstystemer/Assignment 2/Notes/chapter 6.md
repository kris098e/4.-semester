[[ch06_linux_modules.pdf]]

IOCTL is used to interract with the module and set some control. I.e can set the amount of memory, i.e change a variable in the data structure kept in the module
# Summary
The PDF is a chapter from the book "Linux Device Drivers, Third Edition" titled "Advanced Char Driver Operations." The chapter focuses on advanced techniques for writing character device drivers in the Linux operating system.

The chapter begins by discussing asynchronous notification techniques, which allow user-level processes to receive notifications when events occur in the device driver. The chapter then discusses how to handle hardware interrupts in the kernel, including interrupt handlers and tasklets.

The next section of the chapter covers advanced memory management techniques, including using DMA and scatter/gather I/O to improve performance. The chapter also covers the use of kernel threads for background processing in device drivers.

The final section of the chapter discusses some miscellaneous topics, including the use of spinlocks and semaphores for synchronization, implementing IOCTL commands, and handling power management in device drivers.

Throughout the chapter, the author provides code examples and explanations of the relevant Linux kernel APIs and data structures. The chapter assumes a basic knowledge of Linux kernel programming and is aimed at intermediate to advanced device driver developers.


# IOCTL
## User space:
```c
int ioctl(int fd, unsigned long cmd, ...);
```
The prototype stands out in the list of Unix system calls because of the dots, which usually mark the function as having a variable number of arguments. In a real system, however, a system call can’t actually have a variable number of arguments. System calls must have a well-defined prototype, because user programs can access them only through hardware “gates.” Therefore, the dots in the prototype represent not a variable number of arguments but a single optional argument, traditionally identified as char \*argp. The dots are simply there to prevent type checking during compilation. The actual nature of the third argument depends on the specific control command being issued (the second argument). Some commands take no arguments, some take an integer value, and some take a pointer to other data. Using a pointer is the way to pass arbitrary data to the ioctl call; the device is then able to exchange any amount of data with user space.

## Driver method
```c
int (*ioctl) (struct inode *inode, struct file *filp,
 unsigned int cmd, unsigned long arg);
```

The inode and filp pointers are the values corresponding to the file descriptor fd passed on by the application and are the same parameters passed to the open method. The cmd argument is passed from the user unchanged, and the optional arg argument is passed in the form of an unsigned long, regardless of whether it was given by the user as an integer or a pointer. If the invoking program doesn’t pass a third argument, the arg value received by the driver operation is undefined. Because type checking is disabled on the extra argument, the compiler can’t warn you if an invalid argument is passed to ioctl, and any associated bug would be difficult to spot.

### The arg argument? or the cmd?
To choose ioctl numbers for your driver according to the Linux kernel convention, you should first check `include/asm/ioctl.h` and `Documentation/ioctl-number.txt`. The header defines the bitfields you will be using: type (magic number), ordinal number, direction of transfer, and size of argument. The ioctl-number.txt file lists the magic numbers used throughout the kernel,* so you’ll be able to choose your own magic number and avoid overlaps. The text file also lists the reasons why the convention should be used.

### For list of ioctl command numbers
see bottom of [[ch06_linux_modules.pdf#page=3]]

### Defining the numbers for the cmd argument
This is done with 16 bits. We have to use the convention of the `ioctl`. This is done via the ways shown here [[ch06_linux_modules.pdf#page=5]]. Define a magic number (used as the upper 8 bits to make the device unique), give it a sequential argument to tell the commands apart in this specific device and if need be, the return type. see 
`./dm510/linux-6.1.9/Documentation/userspace-api/ioctl/ioctl-number.rst`.

## The return value
The implementation of ioctl is usually a switch statement based on the command number. But what should the default selection be when the command number doesn’t match a valid operation? The question is controversial. Several kernel functions return -EINVAL (“Invalid argument”), which makes sense because the command argument is indeed not a valid one. The POSIX standard, however, states that if an inappropriate ioctl command has been issued, then -ENOTTY should be returned. This error code is interpreted by the C library as “inappropriate ioctl for device,” which is usually exactly what the programmer needs to hear. It’s still pretty common, though, to return -EINVAL in response to an invalid ioctl command.

## accessing the arg

`#include <asm/uaccess.h>`
the driver should use `acess_ok()`  to test if we should or can access the argument provided.
```c
int access_ok(int type, const void *addr, unsigned long size);
```

## example of ioctl
```c
int err = 0, tmp;
int retval = 0;
/*
 * extract the type and number bitfields, and don't decode
 * wrong cmds: return ENOTTY (inappropriate ioctl) before access_ok( )
 */
 if (_IOC_TYPE(cmd) != SCULL_IOC_MAGIC) return -ENOTTY;
 if (_IOC_NR(cmd) > SCULL_IOC_MAXNR) return -ENOTTY;
/*
 * the direction is a bitmask, and VERIFY_WRITE catches R/W
 * transfers. `Type' is user-oriented, while
 * * access_ok is kernel-oriented, so the concept of "read" and
 * "write" is reversed
 */
if (_IOC_DIR(cmd) & _IOC_READ)
 err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
else if (_IOC_DIR(cmd) & _IOC_WRITE)
 err = !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
if (err) return -EFAULT;
```

## Capabilities and Restricted Operations
`#include <linux/capability.h>`
[[ch06_linux_modules.pdf#page=10]]

Be able to set restrictions on who can use the driver. Many options. See the linked page.

The driver can check the capabilities with
`#include <linux/sched.h>`

```c
int capable(int capability);
```
As an example, only some should be able to change the memory usage of the _scull-driver_
```c
if (! capable (CAP_SYS_ADMIN)) 
	return -EPERM;
```

## Implementation of IOCTL command
see [[ch06_linux_modules.pdf#page=11]]

# BLocking IO
A process that calls a blocking request (i.e the driver we are to write) must be put to sleep. If however the process holds a lock it becomes more tricky. Also when the process is waken up again, it does not know how long it slept for, and has to do checks if neccessay that the conditions before, are also true now.

We implement the sleeping with a **wait_que_head_t** defined in 
`#include <linux/wait.h>`
This is a sleeping que of processes.

static: 
```c
DECLARE_WAIT_QUEUE_HEAD(name);
```

dynamic:
```c
wait_queue_head_t my_queue;
init_waitqueue_head(&my_queue);
```

```c
wait_event(queue, condition)
wait_event_interruptible(queue, condition)
wait_event_timeout(queue, condition, timeout)
wait_event_interruptible_timeout(queue, condition, timeout)
```
all of the above forms, queue is the wait queue head to use. Notice that it is passed “by value.” The condition is an arbitrary boolean expression that is evaluated by the macro before and after sleeping; until condition evaluates to a true value, the process continues to sleep. Note that condition may be evaluated an arbitrary number of times, so it should not have any side effects.

If you use wait_event, your process is put into an uninterruptible sleep which, as we have mentioned before, is usually not what you want. The preferred alternative is wait_event_interruptible, which can be interrupted by signals. This version returns an integer value that you should check; a nonzero value means your sleep was interrupted by some sort of signal, and your driver should probably return -ERESTARTSYS. The final versions (wait_event_timeout and wait_event_interruptible_timeout) wait for a limited time; after that time period (expressed in jiffies, which we will discuss in Chapter 7) expires, the macros return with a value of 0 regardless of how condition evaluates.

**wake-up**
```c
void wake_up(wait_queue_head_t *queue);
void wake_up_interruptible(wait_queue_head_t *queue);
```
wake_up wakes up all processes waiting on the given queue (though the situation is a
little more complicated than that, as we will see later). The other form (wake_up_
interruptible) restricts itself to processes performing an interruptible sleep. In general, the two are indistinguishable (if you are using interruptible sleeps); in practice,
the convention is to use wake_up if you are using wait_event and wake_up_interruptible if you use wait_event_interruptible

# KOMMET TIL SIDE 16 EKSEMPEL