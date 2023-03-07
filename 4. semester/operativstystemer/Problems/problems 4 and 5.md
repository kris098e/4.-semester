1.  Provide three programming examples in which multithreading provides better performance than a single-threaded solution.
- summing up a big array
- some sorting algorithms (fx mergesort)
- video games (multitasking)
- itteratin through a directory doing something to each file
- networking (server requests)
- multiple I/O (one thread running each IO-device)
- Matrix-matrix multiplication
all programs which has parts that can be executed in parallel.

2.  Using Amdahl’s Law, calculate the speedup gain of an application that has a 60 percent parallel component for
    -   two processing cores and
    -   four processing cores.
upperbound of the speedup we can achieve when using multiple cors
$$amdahls\ law \ = speedup \leq\frac{1}{S+\frac{1-s}{N}}$$
where
`s=%serial computing`
`N=%processing cores`

**answer**1: $speedup \leq \frac{1}{0.4+\frac{1-0.4}{2}}=1.43$
**answer**2: $speedup \leq \frac{1}{0.4+\frac{1-0.4}{4}}=1.82$


3.  Does the multithreaded web server described in Section 4.1 exhibit task or data parallelism?
`data parrallelism:` multiple threads working on the same **code** (**not necessarily same data**)
`task parralellism:` multiple threads working on different tasks/code

The websever server does data parralellism if it executes the same code for all requests
it can then also do task parralellism if it does different code for other requests.

4. What are two differences between user-level threads and kernel-level threads? Under what circumstances is one type better than the other?

Kernel-threads interract with the hardware, and user-level thread is doing software without hardware, the user-level thread is mapped to a kernel-thread. The user-level thread does requests to the kernel-threads, for which it is mapped to by a **lightweight process**, which will then be doing the computations on the CPU and other hardware.

If we dont have several kernel threads, fx only one kernel thread, then parrallelism cannot be done, as this single kernel thread has to do everything. We can then still be doing **concurrency** but not parrallelism. 

**cannot map multiple user-level threads** to a kernel-level thread, but over time when switching around, it can be seen as **many-to-one**

The lightweight process maps user-level threads to kernel-threads, so the kernel does only know about the kernel-level threads.

it does not make sense to have more kernel-threads than user-space threads, because user-level threads are mapped to kernel-threads. It does however make sense the other way around

5. Describe the actions taken by a kernel to context-switch between kernellevel threads.
save fx. the program counter, such that the other thread knows where to start

6. What resources are used when a thread is created? How do they differ from those used when a process is created?
More lightweight to make a new thread, as a process needs its own memory and more, the thread needs only to create a new stack for this. The threads **controll block** is much smaller. This is the major part

7. Assume that an operating system maps user-level threads to the kernel using the many-to-many model and that the mapping is done through LWPs. Furthermore, the system allows developers to create real-time threads for use in real-time systems. Is it necessary to bind a real-time thread to an LWP? Explain.

No it does not, it only needs to change the priority of the existing threads. But this is only if the schedualer cares about priority. **Else it has to map into real-time-threads**

**LWPs** does the mapping of the user-level-thread to kernel/real time threads.

8. Under what circumstances does a multithreaded solution using multiple kernel threads provide better performance than a single-threaded solution on a single-processor system?
if we have I/O heavy process, then one thread can be the one to wait for I/O and then another process can keep executing

9.  Which of the following components of program state are shared across threads in a multithreaded process?
    -   Register values
    -   Heap memory
    -   Global variables
    -   Stack memory
global variables (through the prcoess control block), heap memory.


10.  Using Amdahl’s Law, calculate the speedup gain for the following applications:
    -   40 percent parallel with (a) eight processing cores and (b) sixteen processing cores
    -   67 percent parallel with (a) two processing cores and (b) four processing cores
    -   90 percent parallel with (a) four processing cores and (b) eight processing cores
just insert into the formulla

11.  Determine if the following problems exhibit task or data parallelism:
    -   Using a separate thread to generate a thumbnail for each photo in a collection
    -   Transposing a matrix in parallel
    -   A networked application where one thread reads from the network
    -   The fork-join array summation application described in Section 4.5.2
    -   The Grand Central Dispatch system

1. data parallelism
2. data parallelism (shares code)
3. task parallelism (1 task reading, other threads doing something else)
4. data parallelism (exact same code being ran to sum up)
5. task parallelism (creates threads for different programs, as a dispatcher)

12. Consider the following code segment:
```c
    pid t pid;
    pid = fork(); 
    if (pid == 0) { /* child process */
        fork(); 
        thread create( . . .); 
    }
    fork(); 
```
-   How many unique processes are created?
parents forks twice
first fork forks and createas a thread which forks
the fork from the children forks once and creates a thread that also forks

7 processes are created (that is, parent is not included)
![[Pasted image 20230302114129.png]]

-   How many unique threads are created?
2 threads are created.

13. The following program uses the Pthreads API. What would be the output from the program at LINE C and LINE P?
```c
#include <pthread.h>
#include <stdio.h>
int value = 0;
void *runner(void *param); /* the thread */
int main(int argc, char *argv[])
{
    pid t pid;
    pthread t tid;
    pthread attr t attr;

    pid = fork();

    if (pid == 0) { /* child process */
        pthread attr init(&attr);
        pthread create(&tid,&attr,runner,NULL);
        pthread join(tid,NULL);
        printf("CHILD: value = %d",value); /* LINE C */
    } else if (pid > 0) { /* parent process */
        wait(NULL);
        printf("PARENT: value = %d",value); /* LINE P */
    }
}

void *runner(void *param) {
    value = 5;
    pthread exit(0);
}
```
as `value` is a global variable in the process which creates a thread, i.e the child process, the thread program modifies the shared variable
**value for parent** = 0 because it does not share the stack with the child process it creates

14.  Consider a multicore system and a multithreaded program written using the many-to-many threading model. Let the number of user-level threads in the program be greater than the number of processing cores in the system. Discuss the performance implications of the following scenarios.
	    -   The number of kernel threads allocated to the program is less than the number of processing cores.
	    -   The number of kernel threads allocated to the program is equal to the number of processing cores.
	    -   The number of kernel threads allocated to the program is greater than the number of processing cores but less than the number of user-level threads.
1. underperform, as we cannot use all cors that is given
2. underperform?, as all threads can use a core but some threads may be waiting for an I/O-device, or are just blocking
3. Faster, because if some kernel-level threads blocks/waits for I/O, then we can switch to another kernel-level thread which can start executing.

