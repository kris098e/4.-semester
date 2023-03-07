Prepare for the Tutorial Session in Week 08 from Chapter 3 the following exercises,

1.  Using the program shown below, explain what the output will be at `LINE A`.
    
    ```C
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

	The value will be 5 and it will be the parent process that uses the else if - statement
	The child has it's own value

2.  Including the initial parent process, how many processes are created by the program shown below?
    
    ```C
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

	8 processes are created. When a process is forked, the child process will keep on from the same state. 1 -> 2 -> 4 -> 8
	$2^{3}$ 

3.  Original versions of Apple’s mobile iOS operating system provided no means of concurrent processing. Discuss three major complications that concurrent processing adds to an operating system.

	- Race conditions
	- Deadlocks
	- Synchronization and communication overhead
	- Content switches
	- Memory handling - Not overwriting memory it shouldn't
	- Process scheduling
	- Generally complexity increases
    
4.  Some computer systems provide multiple register sets. Describe what happens when a context switch occurs if the new context is already loaded into one of the register sets. What happens if the new context is in memory rather than in a register set and all the register sets are in use?

	- First Q
		- The pointer for the register has to change for the CPU to point to the correct register

	- Second Q
		1. Choose a register to change
		2. Move old process content into main memory
		3. Move new process into register
		4. Change the pointer
	
	-Chat
	If the new context is already loaded into one of the register sets when a context switch occurs, the processor can simply switch to that register set, without the need to fetch the context from memory. This can save a significant amount of time and improve system performance.

	However, if the new context is in memory rather than in a register set, and all the register sets are in use, the processor must perform a more complex context switch. In this case, the processor saves the current state of the process in a register or in memory, and loads the new context from memory into a register set. This process can take much longer than a simple register set switch, because the processor must fetch the context from memory, which is slower than accessing registers.
	
	To manage this situation, some computer systems provide a priority scheme to determine which process gets assigned to a register set when all sets are in use. For example, the operating system may give priority to processes with higher levels of urgency or importance, or it may use a round-robin scheduling scheme to distribute the register sets among the processes that need them.

5.  When a process creates a new process using the `fork()` operation, which of the following states is shared between the parent process and the child process?
    -   Stack
    -   Heap
    -   Shared memory segments

	The following is shared:
	- Shared memory segments
		- Message passing
		- Message box

	The following is not shared:
	- Stack
	- Heap

6.  Consider the “exactly once”-semantic with respect to the RPC mechanism. Does the algorithm for implementing this semantic execute correctly even if the ACK message sent back to the client is lost due to a network problem? Describe the sequence of messages, and discuss whether “exactly once” is still preserved.

	“exactly once”: When the server gets a message from a client, it wants to execute only once but it's ACK knowledge might be lost. We want to promise execution on the server side only once.
	The client has a timeout, and resends if it doesn't get an answer in time.

	- Use the same timestamp (In case the same message comes along, send the same answer as earlier)

	-Chat
	The "exactly once" semantic in RPC (Remote Procedure Call) refers to the guarantee that an RPC will only be executed once, even if the client or server fails, or if the network experiences delays, losses or reordering of messages.

	If the ACK message is lost due to a network problem, the client will not receive it and may retransmit the request, believing that the server did not receive it. This can lead to the RPC being executed more than once, violating the "exactly once" semantic.

	To avoid this problem, some RPC implementations use a technique called "idempotent processing", which ensures that multiple invocations of the same RPC have the same effect as a single invocation. For example, if the RPC is a read operation that returns a value, the server can cache the result and return it again if it receives a duplicate request with the same identifier. This way, the client can safely retry the RPC without causing any harm.

7.  Assume that a distributed system is susceptible to server failure. What mechanisms would be required to guarantee the “exactly once” semantic for execution of RPCs?

	- If we use non volatile memory it can keep up from where it left off when it comes back on.

	- Message idempotency
	- Duplicate request detection
	- Timeout and retransmission
	- State replication and consistency
	- Transaction management

9.  Describe the actions taken by a kernel to context-switch between processes.

	1. Save the current process context into memory
	2. Update process state
	3. Choose the next process
	4. Restore the next process context into register

10. Including the initial parent process, how many processes are created by the program shown below.
    
```C
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

It creates 16 processes : 1 -> 2 (after it 1) -> 4 (after it 2) -> 8 (after it 3) -> 16 (after it 4)
$2^4$

10.  Using the program below, identify the values of pid at lines A , B , C , and D . (Assume that the actual pids of the parent and child are 2600 and 2603, respectively.)

```C
#include <sys/types.h>
    #include <stdio.h>
    #include <unistd.h>
    int main()
    {
      pid_t pid, pid1;
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

- At line A, the value of `pid` in the child process will be 0, since `pid` is set to 0 in the child process after the `fork()` call.
- At line B, the value of `pid1` in the child process will be the pid of the child process, which is 2603.
- At line C, the value of `pid` in the parent process will be the pid of the child process, which is 2603.
- At line D, the value of `pid1` in the parent process will be the pid of the parent process, which is 2600.

11.  Give an example of a situation in which ordinary pipes are more suitable than named pipes and an example of a situation in which named pipes are more suitable than ordinary pipes. 

Ordinary pipe:  Write end and read end. Unidirectional. After use it dies
When fork an ordinary pipe is good. We get a parent -> child communication line

Named pipe: Bidirectional
Server <-> client communication

-Chat
Ordinary pipes, also known as anonymous pipes, are suitable when communication is required between two related processes. For example, when a parent process creates a child process and wants to communicate with it. Ordinary pipes allow communication between two related processes only.

On the other hand, named pipes, also known as FIFOs, are suitable when communication is required between two unrelated processes. Named pipes allow communication between any two processes, as long as they know the name of the pipe.

12.  Using the program shown below, explain what the output will be at lines X and Y.

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

X: Negative i times i
Y: Printing the list

When we go to the parent process it has it's own stack and so on

Chat
The output at `LINE X` will be the values of the `nums` array multiplied by negative values of `i`, since it is being executed by the child process. The output at `LINE Y` will be the original values of the `nums` array, since it is being executed by the parent process after the child process has finished modifying the array. Therefore, the output of the program will be:

CHILD: 0 CHILD: -1 CHILD: -4 CHILD: -9 CHILD: -16 
PARENT: 0 PARENT: 1 PARENT: 2 PARENT: 3 PARENT: 4

13.  What are the benefits and the disadvantages of each of the following? Consider both the system level and the programmer level.
    -   Synchronous and asynchronous communication - Synchronous: Waiting for the other process to finish before keeping on (Waiting command). Asynchronous: Both goes on
	    - Pro 
		    - Synchronous:
			    - It provides a reliable way to transfer data as a sender waits for the receiver to acknowledge the message.
			    - No race conditions
		    - Asynchronous
			    - It can increase performance as senders and receivers can perform other operations while waiting for a response.
	    - Con:
		    - Synchronous
			    - It can be slow as it waits for a response from the receiver.
		    - Asynchronous
			    - It can be more error-prone as it requires careful handling of messages that arrive out of order.
    -   Automatic and explicit buffering - Automatic: Automatic allocation. Explicit: Have to manually allocate
	    - Pro:
		    - Automatic
			    - It simplifies programming, as the system manages the buffer automatically.
			    - It can increase performance by optimizing the use of network bandwidth.
		    - Explicit
			    - It can provide better performance in certain situations where buffer size is known in advance.
	    - Con:
		    - Automatic
			    - It can increase memory usage, as buffers are allocated automatically.
			    - It can lead to unexpected behavior, as buffers can be flushed at any time by the system.
		    - Explicit
			    - It can increase programming complexity, as the programmer has to manage buffers explicitly.
			    - It can lead to inefficient use of network bandwidth if buffer sizes are not optimized.
    -   Send by copy and send by reference. Reference: Copy: Copies the data. Sends a pointer
	    - Pro:
		    - Send by copy 
			    - It provides greater data integrity, as data cannot be modified by the receiver.
			    - Ease of use
		    - Send by reference
			    - It can be more efficient, as it avoids copying data.
			    - It can provide greater flexibility, as data can be modified by the receiver.
	    - Con:
		    - Send by copy 
			    - It can be inefficient, as it requires copying data from one process to another.
			    - It can be wasteful of memory if large amounts of data need to be transferred.
		    - Send by reference
			    - It can lead to data integrity issues, as data can be modified by the receiver.
			    - It can be more difficult to understand and debug, as data sharing can be complex.
    -   Fixed-sized and variable-sized messages. 
	    - Pro:
		    - Fixed-sized 
			    - They can be faster to process, as their size is known in advance.
			    - They can be simpler to manage, as they do not require dynamic allocation of memory.
		    - variable-sized
			    - They can be more flexible, as the message size can be changed at runtime.
			    - They can be more efficient in certain situations where message size is not known in advance.
	    - Con:
		    - Fixed-sized 
			    - They can be wasteful of network bandwidth if the message size is not optimized.
			    - They can be less flexible, as the message size cannot be changed at runtime.
		    - variable-sized
			    - They can be slower to process, as their size is not known in advance and requires additional processing.
			    - They can be more difficult to manage, as they require dynamic allocation of memory.

14.  What is the following bpftrace one-liner doing? What is the output you would expect?
    
```
bpftrace -e 'tracepoint:raw_syscalls:sys_enter { @ = count(); } interval:s:1 { print(@); clear(@); }'
```

The bpftrace one-liner is tracing the `sys_enter` event of the `raw_syscalls` tracepoint and counting the number of occurrences using the `count()` aggregation function. It then prints the count every 1 second (`interval:s:1`). The `clear(@)` function is used to reset the count after it has been printed.

The output would be a continuously updating count of the number of times the `sys_enter` event is triggered, printed every second.

15.  Discuss the following code of a bpftrace (resp. DTrace) script. `interval:s:1` (resp. `profile:::tick-1sec`) tells bpftrace (resp. DTrace) to create a new probe which fires once per second. What are the probes, what are the filters, and what are the actions of the bpftrace script? What happens on execution and what is the output of the program? wrt DTrace: the function `trace()` indicates that DTrace should record the specific argument and print it out.

The begin part is the probe
Conditions is the / part

Each have a filter and do an action
Print value of i and decrement
    
```C
	BEGIN { @i = 10; }
    interval:s:1
    /@i > 0/
    {
       @i--;
       printf("Tick %d\n",@i);
    }
    
    interval:s:1
    /@i == 0/
    {
       printf("blastoff!");
       exit();
    }
```
    

It does the same thing

```C
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

# C Programming

Analyse the following C program(s), and discuss the code given below wrt. correctness, readability and efficiency of the code. Is the first version more efficient than the naïve recursive approach (2nd version) to compute the power of a number?

\\>> is logical right shift -> Same as deviding by 2 (and rounding down -> Heltalsdivition)
& is to binary

if (exp & 1) -> Checks if it is uneven... Is checked because the power part can only compute equal numbers

takes log(n) time

```C
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

  if (exp & 1)
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

This happens n-times 

```C
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

