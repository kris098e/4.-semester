# 1. Using the program shown below, explain what the output will be at `LINE A`

``` c
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
int value = 5;
int main()
{
  pid_t pid;
  pid = fork();
  if (pid == 0) {
    /* child process */
    value += 15;
    return 0;
  }
  else if (pid > 0) {
    /* parent process */
    wait(NULL);
    printf("PARENT: value = %d",value); /* LINE A */
    return 0;
  }
}
```
When executing the fork command, the process will start right after the `fork()` command has been executed. 
-   If **fork()** returns a negative value, the creation of a child process was unsuccessful.
-   **fork()** returns a zero to the newly created child process.
-   **fork()** returns a positive value, the **_process ID_** of the child process, to the parent. The returned process ID is of type **pid_t** defined in **sys/types.h**. Normally, the process ID is an integer. Moreover, a process can use function **getpid()** to retrieve the process ID assigned to this process.

Since they do not share the same address space, the child process will add 15 to its own copy of **value** and will then stop. The parent process does not have the same **value** as the child-process and the value printed will be 5.


# 2. Including the initial parent process, how many processes are created by the program shown below?
``` c
#include <stdio.h>
#include <unistd.h>
int main()
{
  /* fork a child process */
  fork();
  /* fork another child process */
  fork();
  /* and fork another */
  fork();
  return 0;
}
```
the first will do such that we have 2 processes.
the two processes will then call fork, creating 4 processes in total. And lastly the final call will create a process for one each. therefore 8 processes are created including the parent process.

# 3. Original versions of Apple’s mobile iOS operating system provided no means of concurrent processing. Discuss three major complications that concurrent processing adds to an operating system.
* context switches
* race conditions
* memory handling
	* interprocess communication
* process schedualing
* debugging and testing
* overall complexity increases


# 4. Some computer systems provide multiple register sets. Describe what happens when a context switch occurs if the new context is already loaded into one of the register sets. What happens if the new context is in memory rather than in a register set and all the register sets are in use?
In this design the CPU can point to different register sets, but only a finite amount of sets. Therefore we have to switch registersets from time to time

1. the CPU has to Switch the pointer of which register set is pointing to,  to the new register set of the process we want to execute

2. move the contents of the current register set into memory to save it, and load the register set from memory into a register set the CPU can point to



# 5. When a process creates a new process using the `fork()` operation, which of the following states is shared between the parent process and the child process?
-   Stack
-   Heap
-   Shared memory segments
only the shared memory segments are shared. 
The parent process has a shared memory segment, for which all of the child processes can access. It can also create it and give it to the child.


# 6. Consider the “exactly once”-semantic with respect to the RPC mechanism. Does the algorithm for implementing this semantic execute correctly even if the ACK message sent back to the client is lost due to a network problem? Describe the sequence of messages, and discuss whether “exactly once” is still preserved.
**What is exactly-once?:** we have a client side and a server side, we send a RPC request from the client to the server - THEN the server only  wants to execute this **exactly ones**. If the server doesn't ACK that it will do the RPC, the client will send a request again to the server after a **timeout**. How does the server ensure that it doesnt execute this request twice?
**answer**: mark the RPC with a timestamp, the ***first time*** it was sent, and the server can then check this timestamp both times, and it should have stored the timestamp the first time it was sent. 

_RPCs are used if the client doesnt want to execute something on its machine, and rather want the program executed on the server - maybe because the server has better hardware_


# 7. Assume that a distributed system is susceptible to server failure. What mechanisms would be required to guarantee the “exactly once” semantic for execution of RPCs?
Store the request/answer in non-volatile memory. Have a **log** with fx. timestamps, this log can also store a state of the program it was executing, such that it can continue executing the request when rebooting.


# 8. Describe the actions taken by a kernel to context-switch between processes.
Save all the neccessary current state of the process into some data structure (registers, memory, ...), and load the new process. 


# 9. Including the initial parent process, how many processes are created by the program shown below.
``` c
#include <stdio.h>
#include <unistd.h>
int main()
{
  int i;
  for (i = 0; i < 4; i++)
     fork();
  return 0;
}
```
Remember that each process gets their own copy of the variable from the parent process
the parent process will create 1 process resulting in 2 total
	i | # process
	\_\_\_\_\_\______ 
	0 | 2
	1 | 4
	2 | 8
	3 | 16

# 10. Using the program below, identify the values of pid at lines A , B , C , and D . (Assume that the actual pids of the parent and child are 2600 and 2603, respectively.)
``` c
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
  pid t pid, pid1;
  /* fork a child process */
  pid = fork();
  if (pid < 0) {
     /* error occurred */
     fprintf(stderr, "Fork Failed");
     return 1;
  }
  else if (pid == 0) {
     /* child process */
     pid1 = getpid();
     printf("child: pid = %d",pid);   /* A */
     printf("child: pid1 = %d",pid1); /* B */
  }
  else {
     /* parent process */
     pid1 = getpid();
     printf("parent: pid = %d",pid);   /* C */
     printf("parent: pid1 = %d",pid1); /* D */
     wait(NULL);
  }
  return 0;
}
```
$A=0$ as it is the child process
$B=2603$ the actual processID?

$C=2603$ since the call to fork() will in the parent process return the **pid** of the child it just created.
$D=2600$

# 11.  Give an example of a situation in which ordinary pipes are more suitable than named pipes and an example of a situation in which named pipes are more suitable than ordinary pipes.

## ordinary (most of the times only one-directional, so you have to create multiple pipes to read and write both ends. Only alive during the process which created it.)
* Between parent and child, no other processes needs to know about this pipe

## named (caracterized as files, bi-directional)
* Can be used between fx. two parent processes

# 12. Using the program shown below, explain what the output will be at lines X and Y.
```C
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#define SIZE 5
int nums[SIZE] = {0,1,2,3,4};
int main()
{
  int i;
  pid t pid;
  pid = fork();
  if (pid == 0) {
     for (i = 0; i < SIZE; i++) {
       nums[i] *= -i;
       printf("CHILD: %d ",nums[i]); /* LINE X */
     }
  }
  else if (pid > 0) { wait(NULL);
     for (i = 0; i < SIZE; i++)
       printf("PARENT: %d ",nums[i]); /* LINE Y */
  }
  return 0;
}
```
* X: negative multiples of itself of the array
* Y: just prints {0,1,2,3,4}

# 13. What are the benefits and the disadvantages of each of the following? Consider both the system level and the programmer level.
-   Synchronous and asynchronous communication
	- asynchronous is faster, but less reliable
		- easier for the programmer, just call and go on

	* syncrhonous is slower, but more reliable (no race-conditions)
		* hard for the operating system
			* has to sleep the program calling it, and wake it up again when finished?


-   Automatic(operating system handles the buffering) and explicit(manual in the programing) buffering
	* automatic is hard for the operating system, many cases to be handled
	* explicit is done by the programmer

-   Send by copy and send by reference
	* copy is hard for the operating system, as we have to copy it all
	* reference is just passing the pointer, and nothing else

-   Fixed-sized and variable-sized messages
	- fixed-size: always the same size, cannot grow which is annoying for the programmer, but also have to pad the remaining size
	- variable-sized: easier to implement.

# 14. What is the following bpftrace one-liner doing? What is the output you would expect?
```bash
bpftrace -e 'tracepoint:raw_syscalls:sys_enter { @ = count(); } interval:s:1 { print(@); clear(@); }'
```
put a tracepoint on the **sys_enter**, and counts how many sys_enter were made each second - which is just counting all syscalls each second

# 15. Discuss the following code of a bpftrace (resp. DTrace) script. `interval:s:1` (resp. `profile:::tick-1sec`) tells bpftrace (resp. DTrace) to create a new probe which fires once per second. What are the probes, what are the filters, and what are the actions of the bpftrace script? What happens on execution and what is the output of the program? wrt DTrace: the function `trace()` indicates that DTrace should record the specific argument and print it out.
```shell
BEGIN { @i = 10; }  # BEGIN is the prope
interval:s:1 # interval
/@i > 0/  # filter
{
   @i--;
   printf("Tick %d\n",@i);
}

interval:s:1 # interval
/@i == 0/ # condition
{
   printf("blastoff!");
   exit();
}
```


```shell
dtrace:::BEGIN
{
   i = 10;
}

profile:::tick-1sec
/i > 0/
{
   trace(i--);
}

profile:::tick-1sec
/i == 0/
{
   trace("blastoff!");
   exit(0);
}
```
does the same think as the one above

# C. programming
## Analyse the following C program(s), and discuss the code given below wrt. correctness, readability and efficiency of the code. Is the first version more efficient than the naïve recursive approach (2nd version) to compute the power of a number?
```c
/* Version 1 */
#include <stdio.h>
#include <inttypes.h>
float power(float x, uint32_t exp);

float power(float x, uint32_t exp)
{
  float result;
  /* base case */
  if (exp == 0)
    return 1.0;

  result = power(x, exp >> 1); 
  result = result * result;

  if (exp & 1) // check if the number is odd
    result = result * x;
  return result;
}

int main(int argc, char **argv)
{
  float p;
  p = power(10.0, 5);
  printf("p = %f\n", p);
  return 0;
}
```
$O(\log_{2}(n))$

```c
/* Version 2 */
#include <stdio.h>
#include <inttypes.h>


float power(float x, uint32_t exp)
{
  /* base case */
  if (exp == 0) {
    return 1.0;
  }
  /* recursive case */
  return x*power(x, exp - 1);
}

int main(int argc, char **argv)
{
  float p;
  p = power(10.0, 5);
  printf("p = %f\n", p);
  return 0;
}
```
$O(n)$