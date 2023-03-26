[[ch05_linux_modules.pdf]]
# Linux semaphore implementation
[[ch05_linux_modules.pdf#page=5]]
`#include <asm/semaphore.h` 

```c
void sema_init(struct semaphore *sem, int val);

/** these needs pointers to semaphores.*/
void init_MUTEX(struct semaphore *sem);
void init_MUTEX_LOCKED(struct semaphore *sem);

DECLARE_MUTEX(name); // create semaphore with given name
DECLARE_MUTEX_LOCKED(name); // lock semaphore with given name
```
has then some methods to initialize this. Also to wait/down the semaphore. 
```c
void down(struct semaphore *sem);
int down_interruptible(struct semaphore *sem);
int down_trylock(struct semaphore *sem);
```
Best to use the _interruptible_ one, such that user processes can interrupt their programs.  `trylock` tries to get the lock, if not available returns immediately with value other than 0. `down` cannot be interrupted.

# Semaphores in scull drivers
```c
for (i = 0; i < scull_nr_devs; i++) {
 scull_devices[i].quantum = scull_quantum;
 scull_devices[i].qset = scull_qset;
 init_MUTEX(&scull_devices[i].sem);
 scull_setup_cdev(&scull_devices[i], i);
 }
```
Note that the semaphore must be initialized before the scull device is made available to the rest of the system. Therefore, init_MUTEX is called before scull_setup_cdev. Performing these operations in the opposite order would create a race condition where the semaphore could be accessed before it is ready.

```c
if (down_interruptible(&dev->sem))
 return -ERESTARTSYS;
```
Note the checkon the return value of down_interruptible; if it returns nonzero, the operation was interrupted. The usual thing to do in this situation is to return -ERESTARTSYS. Upon seeing this return code, the higher layers of the kernel will either restart the call from the beginning or return the error to the user. If you return -ERESTARTSYS, you must first undo any user-visible changes that might have been made, so that the right thing happens when the system call is retried. If you cannot undo things in this manner, you should return -EINTR instead.

scull_write must release the semaphore whether or not it was able to carry out its other tasks successfully. If all goes well, execution falls into the final few lines of the function:
```c
out:
 up(&dev->sem);
 return retval;
```

## Reader writer semaphores
`#ìnlude <linux/rwsem.h>` 

```c
void init_rwsem(struct rw_semaphore *sem);
```

readers
```c
void init_rwsem(struct rw_semaphore *sem);

void down_read(struct rw_semaphore *sem);
int down_read_trylock(struct rw_semaphore *sem);
void up_read(struct rw_semaphore *sem);
```
again `down_read()` is not uninterruptible

writers
```c
void down_write(struct rw_semaphore *sem);
int down_write_trylock(struct rw_semaphore *sem);
void up_write(struct rw_semaphore *sem);
void downgrade_write(struct rw_semaphore *sem);
```
down_write, down_write_trylock, and up_write all behave just like their reader counterparts, except, of course, that they provide write access. If you have a situation where a writer lockis needed for a quickchange, followed by a longer period of readonly access, you can use downgrade_write to allow other readers in once you have finished making changes

# Completions
`<linux/completion.h>`

`DECLARE_COMPLETION(my_completion);`
```c
struct completion my_completion;
/* ... */
init_completion(&my_completion);
```

```c
void wait_for_completion(struct completion *c);
```

```c
void complete(struct completion *c);
void complete_all(struct completion *c);
```

If using `complete_all()` you must call
```c
INIT_COMPLETION(struct completion c);
```
again to initialize the completion again, before it can be used.

## example
```c
DECLARE_COMPLETION(comp);

ssize_t complete_read (struct file *filp, char __user *buf, size_t count, loff_t *pos)
{
 printk(KERN_DEBUG "process %i (%s) going to sleep\n",
 current->pid, current->comm);
 wait_for_completion(&comp);
 printk(KERN_DEBUG "awoken %i (%s)\n", current->pid, current->comm);
 return 0; /* EOF */
}
ssize_t complete_write (struct file *filp, const char __user *buf, size_t count, loff_t *pos)
{
 printk(KERN_DEBUG "process %i (%s) awakening the readers...\n",
 current->pid, current->comm);
 complete(&comp);
 return count; /* succeed, to avoid retrial */
}
```
This way, if multiple readers calls to `write()` then only one will be woken up, however, it cannot be known which one will be woken up.

# Spinlocking
[[ch05_linux_modules.pdf#page=12]]
`include <linux/spinlock.h>`


```c
spinlock_t my_lock = SPIN_LOCK_UNLOCKED;

void spin_lock_init(spinlock_t *lock);

void spin_lock(spinlock_t *lock);

void spin_unlock(spinlock_t *lock);
```

## Spinlock and Atomic Context
Most readers would agree that this scenario is best avoided. Therefore, the core rule that applies to spinlocks is that any code must, while holding a spinlock, be atomic. It cannot sleep; in fact, it cannot relinquish the processor for any reason except to service interrupts (and sometimes not even then).

**there are some methods in the spin_lock-api that will ensure that the process holding the spin-lock will not sleep.**

The last important rule for spinlockusage is that spinlocks must always be held for the minimum time possible. The longer you hold a lock, the longer another processor may have to spin waiting for you to release it, and the chance of it having to spin at all is greater. Long lockhold times also keep the current processor from scheduling, meaning that a higher priority process—which really should be able to get the CPU—may have to wait. The kernel developers put a great deal of effort into reducing kernel latency (the time a process may have to wait to be scheduled) in the 2.5 development series. A poorly written driver can wipe out all that progress just by holding a lockfor too long. To avoid creating this sort of problem, make a point of keeping your lock-hold times short.

## The spinlock functions
Other than the functions provided above, there are more functions here that can be used. Cannot dive into a lot of details, as we need knowledge of interrupt-handlers aswel.

### Acquire
```c
void spin_lock(spinlock_t *lock);
void spin_lock_irqsave(spinlock_t *lock, unsigned long flags);
void spin_lock_irq(spinlock_t *lock);
void spin_lock_bh(spinlock_t *lock)
```
We have already seen how spin_lock works. spin_lock_irqsave disables interrupts (on the local processor only) before taking the spinlock; the previous interrupt state is stored in flags. If you are absolutely sure nothing else might have already disabled interrupts on your processor (or, in other words, you are sure that you should enable interrupts when you release your spinlock), you can use spin_lock_irq instead and not have to keep track of the flags. Finally, spin_lock_bh disables software interrupts before taking the lock, but leaves hardware interrupts enabled.

### Release
```c
void spin_unlock(spinlock_t *lock);
void spin_unlock_irqrestore(spinlock_t *lock, unsigned long flags);
void spin_unlock_irq(spinlock_t *lock);
void spin_unlock_bh(spinlock_t *lock);
```

## Reader-writer spinlock
### init
```c
rwlock_t my_rwlock = RW_LOCK_UNLOCKED; /* Static way */

rwlock_t my_rwlock;
rwlock_init(&my_rwlock); /* Dynamic way */
```

### locking
```c
void read_lock(rwlock_t *lock);
void read_lock_irqsave(rwlock_t *lock, unsigned long flags);
void read_lock_irq(rwlock_t *lock);
void read_lock_bh(rwlock_t *lock);

void read_unlock(rwlock_t *lock);
void read_unlock_irqrestore(rwlock_t *lock, unsigned long flags);
void read_unlock_irq(rwlock_t *lock);
void read_unlock_bh(rwlock_t *lock);
```

#### write
```c
void write_lock(rwlock_t *lock);
void write_lock_irqsave(rwlock_t *lock, unsigned long flags);
void write_lock_irq(rwlock_t *lock);
void write_lock_bh(rwlock_t *lock);
int write_trylock(rwlock_t *lock);

void write_unlock(rwlock_t *lock);
void write_unlock_irqrestore(rwlock_t *lock, unsigned long flags);
void write_unlock_irq(rwlock_t *lock);
void write_unlock_bh(rwlock_t *lock);
```

# Locking traps (things that typically goes wrong)
## Ambigous rules
As you write your code, you will doubtless encounter several functions that all require access to structures protected by a specific lock. At this point, you must be careful: if one function acquires a lockand then calls another function that also attempts to acquire the lock, your code deadlocks. Neither semaphores nor spinlocks allow a lockholder to acquire the locka second time; should you attempt to do so, things simply hang.

To make your locking work properly, you have to write some functions with the assumption that their caller has already acquired the relevant lock(s). Usually, only your internal, static functions can be written in this way; functions called from outside must handle locking explicitly. When you write internal functions that make assumptions about locking, do yourself (and anybody else who works with your code) a favor and document those assumptions explicitly. It can be very hard to come backmonths later and figure out whether you need to hold a lockto call a particular function or not.

## Lock Ordering rules
Taking multiple locks can be dangerous, however. If you have two locks, called Lock1 and Lock2, and code needs to acquire both at the same time, you have a potential deadlock. Just imagine one thread locking Lock1 while another simultaneously takes Lock2. Then each thread tries to get the one it doesn’t have. Both threads will deadlock.

## Fine- versus Coarse-Grained locking
having multiple locks is harder to manage and debug than one big lock (of course it would be easier if we only had to manage one lock.)

If you do suspect that lockcontention is hurting performance, you may find the lockmeter tool useful. This patch (available at http://oss.sgi.com/projects/lockmeter/) instruments the kernel to measure time spent waiting in locks. By looking at the report, you are able to determine quickly whether lock contention is truly the problem or not.

# Alternatives to locking
## Lock-free algorithms
Circular buffer **only 1 writer** and multiple readers. Have array, with two indexes. Writer is the only one that can update the writer index. If the writer puts an item in before updating the index of the writer-index, there will be no complications. The reader of course has to check for empty buffer. ![[Pasted image 20230326110234.png]]

The kernel has an implementation for this already, see `<linux/kfifo.h>`

## Atomic variables
[[ch05_linux_modules.pdf#page=19]]

## Bit operations
can be performed by one machine instruction

`#include <asm/bitops.h>`


# KOMMET TIL SIDE 22