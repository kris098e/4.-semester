#include "../include/asm/dm510_msgbox.h"
#include "linux/kernel.h"
#include "linux/unistd.h"
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/errno.h>

typedef struct _msg_t msg_t;

struct _msg_t{
  msg_t* previous;
  int length;
  char* message;
};

static msg_t *bottom;
static msg_t *top;

unsigned long flags;

asmlinkage
int sys_dm510_msgbox_put( char *buffer, int length ) {
  msg_t* msg;
  int bytesNotWritten;
  
  if(length < 0) return -EINVAL; // error code for invalid function argument.
  if(access_ok(buffer, length) == 0) return -EFAULT; // error code for bad address

  // Create new message ( not critical, as we are just creating, not updating shared struct )
  msg = kmalloc(sizeof(msg_t), GFP_KERNEL); // allocate mem for the kernel
  if(!msg) return -ENOMEM; // couldn't allocate memory
  msg->previous = NULL;
  msg->length = length;
  msg->message = kmalloc(length, GFP_KERNEL); 
  if(!msg->message) return -ENOMEM; // couldn't allocate memory

  bytesNotWritten = copy_from_user(msg->message, buffer, length); // returns number of bytes not written, defined on length
  if(bytesNotWritten != 0) {
    // write to log-file such that it is possible to debug how many bytes were not written
    printk(KERN_WARNING "%d bytes were not written into memory from the buffer, %d were padded as 0-bytes\n", bytesNotWritten, bytesNotWritten);
    
    /* free the allocated memory as we are to try again */
    kfree(msg->message);
    kfree(msg);

    return -EAGAIN;
  }

  /**
   * Begin the updating of the entire shared data structure
   * Updates on shared data structures are critical.
  */
  local_irq_save(flags);
  if (!bottom) {
    // empty stack
    bottom = msg;
    top = msg;
  } else {
    /* not empty stack */
    msg->previous = top;
    top = msg;
  }
  local_irq_restore(flags);

  return 0;
}

asmlinkage
int sys_dm510_msgbox_get( char* buffer ) {
  /**
   * entering critical region where we are taking action if the structure
   * has a top, checks on the shared structure is critical. 
   * Updating the shared structure is critical.
  */
  local_irq_save(flags);
  if (top) {
    int numberOfBytesNotCopied;
    
    msg_t* msg = top;
    top = msg->previous;
    local_irq_restore(flags);
    int mlength = msg->length;
    
    if(access_ok(buffer, mlength) == 0) return -EFAULT; // error code for bad address

    /* copy message */
    numberOfBytesNotCopied = copy_to_user(buffer, msg->message, mlength); // returns number of bytes not copied, defined on length

    if(numberOfBytesNotCopied != 0) { 
      // write to log-file such that it is possible to debug how many bytes were not written
      printk(KERN_WARNING "%d bytes were not copied to the buffer from the original message\n", mlength); 

      top = msg;      // restore top, as we return try again.
      return -EAGAIN; // error code for try again 
    }

    /* free memory */
    kfree(msg->message);
    kfree(msg);

    return mlength; // return how many bytes copied
  }
  
  return -1;
}
