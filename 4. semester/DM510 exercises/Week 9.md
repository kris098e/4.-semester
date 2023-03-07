Prepare for the Tutorial Session in Week 09 all the exercises not discussed so far, and in addition, the following exercises from Chapter 4.

1.  Provide three programming examples in which multithreading provides better performance than a single-threaded solution.

 - Data processing
 - Image processing
 - Some sorting algorithms (ms)
 - Video games (multitasking, physics, image)
 - Multiple I/O
 - Networking (server request)
    
2.  Using Amdahl’s Law, calculate the speedup gain of an application that has a 60 percent parallel component for
    -   two processing cores and
    -   four processing cores.
		
		S is serial portion (decimal notation)
		N processing cores
		As N approaches infinity, speedup approaches 1 / S
		$$
		\text { speedup } \leq \frac{1}{S+\frac{(1-S)}{N}}
		$$
		
		Speedup 2 cores
		```mathpad
		1/((0.4) + (1-0.4)/2) =~?
		```
		
		Speedup 4 cores
		```mathpad
		1/((0.4) + (1-0.4)/4) =~?
		```

3.  Does the multithreaded web server described in Section 4.1 exhibit task or data parallelism?

	Data parallelism -> same code working on distributed data
	Task parallelism -> A set of independent tasks running in parallel

	 - Depending on the implementation.
		 - If the request handler is the same then it is data 
		 - else it is task

4.  What are two differences between user-level threads and kernel-level threads? Under what circumstances is one type better than the other?

	user-level threads
	- Managed by user-level libraries
	- User-level thread management involves thread creation, scheduling, and synchronization through user-level libraries such as pthreads
	  
	Kernel-level threads
	- managed by the operating system kernel
	- kernel-level thread management is handled by the operating system kernel through system calls.

	-   User-level threads are often preferred for applications that require fine-grained control over thread scheduling and synchronization, such as multimedia applications or real-time systems. Since user-level thread libraries are written in higher-level languages like C or Java, they offer more flexibility and can be customized to meet the specific needs of an application.
	-   Kernel-level threads are often preferred for applications that require direct access to system resources, such as device drivers or file system operations. Since kernel-level threads run in kernel space, they have direct access to system resources and can execute more efficiently for certain types of operations.
	-   In some cases, a combination of user-level and kernel-level threads may be used to take advantage of the benefits of both approaches. For example, an application might use user-level threads for scheduling and synchronization, while relying on kernel-level threads for I/O operations.

5.  Describe the actions taken by a kernel to context-switch between kernel level threads.

	1. Save the current state -> Program counter
	2. Select the new thread

	Chat:
   A context switch is a process in which the operating system switches the processor from running one thread or process to another. In the case of kernel-level threads, a context switch involves saving the current thread's state and restoring the state of the next thread that will be executed. Here are the actions taken by a kernel to context-switch between kernel-level threads:
	`
	1. Saving the current thread's context: Before the context switch can occur, the kernel must save the state of the current thread, including its registers, program counter, and stack pointer. This information is typically saved in a data structure known as a thread control block (TCB)
	2. Selecting the next thread to execute: Once the current thread's context has been saved, the kernel must select the next thread to execute. This is typically done using a scheduling algorithm that takes into account factors such as thread priority, CPU utilization, and waiting time.
	3. Restoring the next thread's context: Once the next thread has been selected, the kernel must restore its context from its TCB. This involves loading the thread's saved registers, program counter, and stack pointer.
	4. Updating kernel data structures: After the context switch is complete, the kernel must update its data structures to reflect the new state of the system. This may involve updating the thread's status, adjusting the scheduling algorithm's parameters, or updating other system resources.
	`
	Overall, a context switch is a complex operation that involves a significant amount of overhead.	
    
6.  What resources are used when a thread is created? How do they differ from those used when a process is created?
   
   It is more lightweight to create a thread than a process due to memory allocation compared to stack pointer
	
   Threads share the resources of their parent process, while processes have their own set of resources. This means that creating a thread is typically faster and requires fewer resources than creating a new process, but threads are more lightweight and have less isolation than processes.
    
7.  Assume that an operating system maps user-level threads to the kernel using the many-to-many model and that the mapping is done through LWPs. Furthermore, the system allows developers to create real-time threads for use in real-time systems. Is it necessary to bind a real-time thread to an LWP? Explain.
   
   LWP -> Light weight process
	`
	(Depends if the scheduler care about it.)
	Yes, otherwise it will just wait and it's not sure that it won't loss its connection to another process.

   In the many-to-many threading model where user-level threads are mapped to kernel-level threads through LWPs, it is not strictly necessary to bind a real-time thread to an LWP. This is because LWPs are typically used to manage the scheduling and execution of user-level threads, while real-time threads are typically managed by the kernel's scheduler.
   
   However, binding a real-time thread to an LWP can provide some benefits in terms of control and predictability. By binding a real-time thread to a specific LWP, the developer can ensure that the thread always runs on the same processor core, which can improve cache locality and reduce the overhead of thread migration. Additionally, binding a real-time thread to an LWP can help to isolate it from other threads and processes that may be running on the same system, which can help to ensure that the thread meets its real-time requirements.
   
   In summary, while it is not strictly necessary to bind a real-time thread to an LWP in a many-to-many threading model, doing so can provide some benefits in terms of control, predictability, and performance. The decision to bind a real-time thread to an LWP will depend on the specific requirements of the real-time system and the tradeoffs between performance and isolation.
    
8.  Under what circumstances does a multithreaded solution using multiple kernel threads provide better performance than a single-threaded solution on a single-processor system?
   
   It is possible to have threads waiting (F.x. while waiting for an I/O process to finish) and do other other processes in the mean time.
   
   Multithreaded solution can provide better performance than a single-threaded solution on a single-processor system when the program is designed to take advantage of concurrency, and when the workload includes a mix of CPU-bound and I/O-bound tasks. However, designing a multithreaded program requires careful consideration of synchronization, communication, and resource management to avoid problems such as deadlocks, race conditions, and resource contention.
	
9.  Which of the following components of program state are shared across threads in a multithreaded process?
    -   Register values - Not shared
    -   Heap memory - Shared
    -   Global variables - Shared
    -   Stack memory - Not shared

	In a multithreaded process, heap memory and global variables are shared across threads, while register values and stack memory are not shared.
      
10.  Using Amdahl’s Law, calculate the speedup gain for the following applications:
    -   40 percent parallel with (a) eight processing cores and (b) sixteen processing cores
    -   67 percent parallel with (a) two processing cores and (b) four processing cores
    -   90 percent parallel with (a) four processing cores and (b) eight processing cores
		
		S is serial portion 
		N processing cores
		As N approaches infinity, speedup approaches 1 / S
		$$
		\text { speedup } \leq \frac{1}{S+\frac{(1-S)}{N}}
		$$
		
		40 percent parallel with (a) eight processing cores and (b) sixteen processing cores
		a)
		```mathpad
		1/((0.6) + (1-0.6)/8) =~?
		```
		
		b)
		```mathpad
		1/((0.6) + (1 - 0.6)/16) =~?
		```
		
		67 percent parallel with (a) two processing cores and (b) four processing cores
		a)
		```mathpad
		1/((0.33) + (1- 0.33)/2) =~?
		```
		
		b)
		```mathpad
		1/((0.33) + (1 - 0.33)/4) =~?
		```
		
		90 percent parallel with (a) four processing cores and (b) eight processing cores
		a)
		```mathpad
		1/((0.1) + (1-0.1)/4) =~?
		```
		
		b)
		```mathpad
		1/((0.1) + (1 - 0.1)/8) =~?
		```
		  
11.  Determine if the following problems exhibit task or data parallelism:
    -   Using a separate thread to generate a thumbnail for each photo in a collection
    -   Transposing a matrix in parallel
    -   A networked application where one thread reads from the network
    -   The fork-join array summation application described in Section 4.5.2
    -   The Grand Central Dispatch system
      `
    -   Using a separate thread to generate a thumbnail for each photo in a collection: This exhibits data parallelism because each thread processes a separate photo independently. The same task is performed.
	-   Transposing a matrix in parallel: This exhibits data parallelism because each element of the matrix can be transposed independently. Same code different data.
	-   A networked application where one thread reads from the network: This exhibits task parallelism because the thread reading from the network performs a single task, and multiple threads could be performing this task in parallel.
	-   The fork-join array summation application described in Section 4.5.2: This exhibits data parallelism because the array can be divided into smaller sub-arrays that can be summed up independently. Though it might be task parallelism due to the arrays are split up -> potentially seen as different data but the same tasks.
	-   The Grand Central Dispatch system: This exhibits task parallelism because it can manage multiple concurrent tasks that can be executed in parallel on a multi-core processor.
    
12.  Consider the following code segment:
		
		```C
		pid t pid;
		pid = fork();
		if (pid == 0) { /* child process */
			fork();
			thread create( . . .); // -> Created by two threads
		}
		fork();
		```
		`
	-   How many unique processes are created?
	-   How many unique threads are created?
	`
		Processes created: 6 
		Threads created: 2
		
		[[forkTree.jpg]]

13.  The following program uses the Pthreads API. What would be the output from the program at LINE C and LINE P?

  ```C
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
		
		Line C: 5
		Line P: 0
	    
14.  Consider a multicore system and a multithreaded program written using the many-to-many threading model. Let the number of user-level threads in the program be greater than the number of processing cores in the system. Discuss the performance implications of the following scenarios.
    -   The number of kernel threads allocated to the program is less than the number of processing cores.
	    - If the number of kernel threads allocated to the program is less than the number of processing cores, some of the cores will be idle while waiting for user-level threads to be mapped to available kernel threads. This can result in poor performance and underutilization of processing cores.
	    - Underperform -> not utilizing all processing cores
    -   The number of kernel threads allocated to the program is equal to the number of processing cores.
	    - If the number of kernel threads allocated to the program is equal to the number of processing cores, all processing cores will be utilized, and the performance will be optimal as long as the number of user-level threads is not too large.
	    - We are satisfied. Performing what it can perform.
    -   The number of kernel threads allocated to the program is greater than the number of processing cores but less than the number of user-level threads.
	    - If the number of kernel threads allocated to the program is greater than the number of processing cores but less than the number of user-level threads, some of the user-level threads will have to wait for kernel threads to become available. This can result in decreased performance due to increased context switching and overhead from mapping user-level threads to kernel threads.
	    - Content switching
	    - Faster than the previous question due to content switching but kernel threads are still kept busy so it is stil using its capacity.
      
      