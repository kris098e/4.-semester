-   Prepare for the Tutorial Session in Week 06 from Chapter 1 the following exercises

1.  What are the three main purposes of an operating system?
		A program that acts as an intermediary between a user of a computer and the computer hardware
	
	- Execute user programs and make solving user problems easier 
	- Make the computer system convenient to use 
	- Use the computer hardware in an efficient manner
	- Resource allocation

2.  What is the main difficulty that a programmer must overcome in writing an operating system for a real-time environment?

	Real-time invironment: Somethings happens in real time with strict deadlines. 
    
3.  Keeping in mind the various definitions of operating system, consider whether the operating system should include applications such as web browsers and mail programs. Argue both that it should and that it should not, and support your answers.

	- Pro: 
		- Web browsers and mail programs are a basic use of computers and wil typically be installed anyways -> convenience
		- Programs and software can be specifik be made compatible with the hardware
	
	- Con: 
		- It's not easy to seperate and keep the software small if it has to consist of other bloatware.
    
4.  How does the distinction between kernel mode and user mode function as a rudimentary form of protection (security)?

	User mode makes it possible to use a system within a certain frame while the user is unable to control basic functions of the system. This means that the user cannot by mistake make a horrible mistake for the system to shut down or run incorrectly. Another point is that if the user gets hacked, the hacker doesn't neither have acces to viable functionality.
    
5.  Which of the following instructions should be privileged?
    -   Set value of timer.                                       X
    -   Read the clock.
    -   Clear memory.                                             X
    -   Issue a trap instruction.                               (Making system calls cannot be done if priviledge)
    -   Turn off interrupts.                                      X
    -   Modify entries in device-status table.         X
    -   Switch from user to kernel mode.               X
    -   Access I/O device.                                       X

6.  Some CPUs provide for more than two modes of operation. What are two possible uses of these multiple modes?

	User mode and kernel mode are the typical.
	
	- Virtual machine kernal mode
	- More users (different privilege users)

7.  Give two reasons why caches are useful. What problems do they solve? What problems do they cause? If a cache can be made as large as the device for which it is caching (for instance, a cache as large as a disk), why not make it that large and eliminate the device?

	Reasons:
	They reduce latency roughly by 1/10 and they often store what was recently used, so they quickly can reach it. It stores temporary values which does not need to be written in the long term memory,

	Problem: 
	If it does not exist, it has to fetch from further out aka. it can only store limited data. 

	Making it the main device:
	It is expensive. Volitary memory isn't good as secondary memory. It will take more size and the distance will be larger to travel when communicating.

8.  How do clustered systems differ from multiprocessor systems? What is required for two machines belonging to a cluster to cooperate to provide a highly available service?

	Cluster system: notes can have independent hardware
	Multi processor: In the same space and share space and variables

	They should be able to communicate. If something goes down the service sould be able to continue.
    
9.  (**important**) What is the purpose of interrupts? How does an interrupt differ from a trap? Can traps be generated intentionally by a user program? If so, for what purpose?

	Interrups helps keep the system seemingly fluently running, switching from task to task in micro seconds. Tasks can run simutaniusly.

	There are two ways to enter kernel mode:
	- Interrupt
	- Exception
	When either occurs, the processor dispatches to the appropriate handler in its interrupt dispatch table (or similar mechanism). This table is defined by the operating system.
	A trap is an exception where the instruction cannot be restarted. In contrast, a fault is an exception where the instruction can be restarted.

	Traps: Traps are for applications to make interrups

10.  Direct memory access is used for high-speed I/O devices in order to avoid increasing the CPU’s execution load.
    -   How does the CPU interface with the device to coordinate the transfer?
    -   How does the CPU know when the memory operations are complete?
    -   The CPU is allowed to execute other programs while the DMA controller is transferring data. Does this process interfere with the execution of the user programs? If so, describe what forms of interference are caused.

		Direct memory access: It would take a lot of time if the cpu should be a middle man
	- They signal to each other via DMA controller
	- The DMA controller interrups
	- DMA and cpu competes for memory access which might make it slower

11.  (**important**) Rank the following storage systems from slowest to fastest:
    -   Hard-disk drives
    -   Registers
    -   Optical disk
    -   Main memory
    -   Nonvolatile memory
    -   Magnetic tapes
    -   Cache

[[ch01.pdf#page=50]]
[[ch01.pdf#page=28]]
	1. Registers (5,000 - 10,000 MB/sec)
	2. Cache (5,000 - 10,000 MB/sec)
	3. Main memory (1,000 - 5,000 MB/sec)
	4. Nonvolatile memory (fx. main memory, memory that isn't deleted when shutting down)
	5. HDD ( MB/sec) SSD (MB/sec)
	6. Optical disk
	7. Magnetic tapes

12.  Describe some of the challenges of designing operating systems for mobile devices compared with designing operating systems for traditional PCs.
		
		Interrups might be different. More programs running in the background - battery savings
		Different interface (no programs -> apps)
		

# C Programming (refresh)

-   Which of the following is the proper declaration of a pointer?
    -   int x;
    -   int &x;
    -   ptr x;
    -   int $*$x;        X
-   Which of the following gives the memory address of integer variable a?
    -   $*$a;
    -   a;
    -   &a;           X
    -   address(a);
-   Which of the following gives the memory address of a variable pointed to by pointer a?
    -   a;             X
    -   $*$a;
    -   &a;
    -   address(a);
-   Which of the following gives the value stored at the address pointed to by pointer a?
    -   a;
    -   val(a);
    -   $*$a;          X
    -   &a;
-   Which of the following is the proper keyword or function to allocate memory in C?
    -   new
    -   malloc    X
    -   create
    -   value
-   Which of the following is the proper keyword or function to deallocate memory?
    -   free        X
    -   delete
    -   clear
    -   remove
-   Repeat the discussion of the four following examples to swap the content of two variables. Which of the examples are correct, which are wrong?
    -   [Swap Version 1](http://pythontutor.com/visualize.html#code=static%20inline%20void%20swap%28int%20*m,%20int%20*n%29%0A%7B%0A%20%20int%20temp%20%3D%20*m%3B%0A%20%20*m%20%3D%20*n%3B%0A%20%20*n%20%3D%20temp%3B%0A%7D%0A%0Aint%20main%28int%20argc,%20char%20**argv%29%0A%7B%0A%20%20int%20x,y%3B%0A%0A%20%20x%3D42%3B%0A%20%20y%3D100%3B%0A%20%20%0A%20%20swap%28%26x,%20%26y%29%3B%0A%7D&cumulative=false&curInstr=0&heapPrimitives=nevernest&mode=display&origin=opt-frontend.js&py=c&rawInputLstJSON=%5B%5D&textReferences=false)
		It works correctly

    -   [Swap Version 2](http://pythontutor.com/visualize.html#code=%23include%20%3Cstdlib.h%3E%0A%0Astatic%20inline%20void%20swap%28int%20*m,%20int%20*n%29%0A%7B%0A%20%20int%20temp%20%3D%20*m%3B%0A%20%20*m%20%3D%20*n%3B%0A%20%20*n%20%3D%20temp%3B%0A%7D%0A%0Aint%20main%28int%20argc,%20char%20**argv%29%0A%7B%0A%20%20int%20*%20x%3B%0A%20%20int%20*%20y%3B%0A%0A%20%20x%20%3D%20calloc%281,sizeof%28int%29%29%3B%0A%20%20y%20%3D%20calloc%281,sizeof%28int%29%29%3B%0A%0A%20%20*x%20%3D%2042%3B%0A%20%20*y%20%3D%20100%3B%0A%20%20%0A%20%20swap%28x,%20y%29%3B%0A%7D%0A&cumulative=false&curInstr=0&heapPrimitives=nevernest&mode=display&origin=opt-frontend.js&py=c&rawInputLstJSON=%5B%5D&textReferences=false)
		It works correctly

    -   [Swap Version 3](http://pythontutor.com/visualize.html#code=%23include%20%3Cstdlib.h%3E%0A%0Astatic%20inline%20void%20swap%28int%20*m,%20int%20*n%29%0A%7B%0A%20%20int%20*%20temp%20%3D%20m%3B%0A%20%20m%20%3D%20n%3B%0A%20%20n%20%3D%20temp%3B%0A%7D%0A%0Aint%20main%28int%20argc,%20char%20**argv%29%0A%7B%0A%20%20int%20*%20x%3B%0A%20%20int%20*%20y%3B%0A%0A%20%20x%20%3D%20calloc%281,sizeof%28int%29%29%3B%0A%20%20y%20%3D%20calloc%281,sizeof%28int%29%29%3B%0A%0A%20%20*x%20%3D%2042%3B%0A%20%20*y%20%3D%20100%3B%0A%20%20%0A%20%20swap%28x,%20y%29%3B%0A%7D%0A&cumulative=false&curInstr=0&heapPrimitives=nevernest&mode=display&origin=opt-frontend.js&py=c&rawInputLstJSON=%5B%5D&textReferences=false)
        Didn't work (Copies but values doesn't change)
        
    -   [Swap Version 4](http://pythontutor.com/visualize.html#code=%23include%20%3Cstdlib.h%3E%0A%0Astatic%20inline%20void%20swap%28int%20**m,%20int%20**n%29%0A%7B%0A%20%20int%20*%20temp%20%3D%20*m%3B%0A%20%20*m%20%3D%20*n%3B%0A%20%20*n%20%3D%20temp%3B%0A%7D%0A%0Aint%20main%28int%20argc,%20char%20**argv%29%0A%7B%0A%20%20int%20*%20x%3B%0A%20%20int%20*%20y%3B%0A%0A%20%20x%20%3D%20calloc%281,sizeof%28int%29%29%3B%0A%20%20y%20%3D%20calloc%281,sizeof%28int%29%29%3B%0A%0A%20%20*x%20%3D%2042%3B%0A%20%20*y%20%3D%20100%3B%0A%20%20%0A%20%20swap%28%26x,%20%26y%29%3B%0A%7D%0A&cumulative=false&curInstr=0&heapPrimitives=nevernest&mode=display&origin=opt-frontend.js&py=c&rawInputLstJSON=%5B%5D&textReferences=false)
        It works correctly
        
-   Analyse the following C source code. Discuss what it does (this prepares you for the 1st mandatory assignment).

	Suppose to work like a message box. Stack of messages to put in and return.

```C
#include "dm510_msgbox.h"
#include <stdlib.h>
#include <string.h>
typedef struct _msg_t msg_t;

struct _msg_t{
  msg_t* previous;
  int length;
  char* message;
};

static msg_t *bottom = NULL;
static msg_t *top = NULL;

int dm510_msgbox_put( char *buffer, int length ) {
  msg_t* msg = malloc(sizeof(msg_t));
  msg->previous = NULL;
  msg->length = length;
  msg->message = malloc(length);
  memcpy(msg->message, buffer, length);

  if (bottom == NULL) {
	bottom = msg;
	top = msg;
  } else {
	/* not empty stack */
	msg->previous = top;
	top = msg;
  }
  return 0;
}

int dm510_msgbox_get( char* buffer, int length ) {
  if (top != NULL) {
	msg_t* msg = top;
	int mlength = msg->length;
	top = msg->previous;

	/* copy message */
	memcpy(buffer, msg->message, mlength);

	/* free memory */
	free(msg->message);
	free(msg);

	return mlength;
  }
  return -1;
}

int main(int argc, char** argv) {
  char *in = "This is a stupid message.";
  char msg[50];
  int msglen;
 
  /* Send a message containing 'in' */
  dm510_msgbox_put(in, strlen(in)+1);
 
  /* Read a message */
  msglen = dm510_msgbox_get(msg, 50);

  return 0;
}
```