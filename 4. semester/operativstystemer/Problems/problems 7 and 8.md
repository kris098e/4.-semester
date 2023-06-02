See also the Weekly Notes from [Week 11](https://imada.sdu.dk/~daniel/DM510-2023/lectures/week-11-2023.html), as there are still important exercises from earlier chapters to be discussed. In addition prepare the following exercises form Chapter 7 and 8:

# Chapter 7

1.  Describe how deadlock is possible with the dining-philosophers problem.
   If all philosophers took the fork to the same side a deadlock would occur. 
**circular wait**

2. .  The Linux kernel has a policy that a process cannot hold a spinlock while attempting to acquire a semaphore. Explain why this policy is in place.
If another process is trying to grab the spinlock, while it is holding the semaphore


# Chapter 8

1.  List three examples of deadlocks that are not related to a computersystem environment.
   
   1. If two construction workers need to use several tools (hammer and nail), and one takes the hammer and the other takes the nails, a deadlock occurs.
   
   2. If four cars comes to an intersection and has to wait for the car to the right, a deadlock occurs.
      
   3. In a negotiation. Suppose each party refuses to compromise or make concessions. In that case, a negotiation deadlock can occur, preventing any progress from being made towards an agreement or resolution.
    
2.  Suppose that a system is in an unsafe state. Show that it is possible for the threads to complete their execution without entering a deadlocked state.
   
   if T1 in the below example does not end up actually requesting $R_{2}$ then it cannot enter a deadlock, since $T_{1}$ will just release $R_{1}$
   ![[ch08-2023.pdf#page=25]]
    
3.  (**important**) Consider the following snapshot of a system:
    ![image](https://imada.sdu.dk/~daniel/DM510-2023/_images/Ex8.3.png)
    Answer the following questions using the banker’s algorithm
    
    -   What is the content of the matrix Need?
      |     | A   | B   | C   | D   |
      | --- | --- | --- | --- | --- |
      | T0  | 0   | 0   | 0   | 0   |
      | T1  | 0   | 7   | 5   | 0   |
      | T2  | 1   | 0   | 0   | 2   |
      | T3  | 0   | 0   | 2   | 0   |
      | T4  | 0   | 6   | 4   | 2   | 
      
    -   Is the system in a safe state?
      Available
      | A   | B   | C   | D   |
      | --- | --- | --- | --- |
      | 1   | 5   | 3   | 2   |
      | 1   | 0   | 0   | 2   |
      | 1   | 0   | 0   | 0   |
      | 0   | 0   | 0   | 0   | 
	yes just run the algorithm.
    
    -   If a request from thread T1 arrives for (0,4,2,0), can the request be granted immediately?
      
      There's more available than needed, so yes, it can be granted immediately. If we do pretend we have allocated the resources, and check if we are still in a safe state. If not (when the resources has been prenteded to given to the process), we will not grant the resources.
  
      
4.  A possible method for preventing deadlocks is to have a single, higher-order resource that must be requested before any other resource. For example, if multiple threads attempt to access the synchronization objects A , …, E, deadlock is possible. (Such synchronization objects may include mutexes, semaphores, condition variables, and the like.) We can prevent deadlock by adding a sixth object F. Whenever a thread wants to acquire the synchronization lock for any object A, …, E, it must first acquire the lock for object F. This solution is known as containment: the locks for objects A, …, E are contained within the lock for object F. Compare this scheme with the circular-wait scheme of Section 8.5.4.
   
   Section 8.5.4 -> To require R(n+1) R(n) needs to be acquired.
   
   Comparison: In the lock example we need only F to get hold of any resource while circular-wait scheme needs to acquire the resource before to get hold of the next resource.
	**however** the prevention technique in in section 8.5.4 may be better since if fx a process wants to acquire locks 1 and 3 and another wants to acquire locks 4 and 5, then it would be unnecessary to acquire a shared lock when they are not dependent on each other 
    
5.  Show that the safety algorithm presented in Section 8.6.3 requires an order of $m * n^2$ operations.
   
   The worst-case scenario is when we need to check each process against all possible resource allocation scenarios. There are n processes, and for each process, we need to simulate resource allocation for all possible resource allocation scenarios. There are n possible resource allocation scenarios, each with m resource types. Therefore, the total number of resource allocation scenarios is $m*n^2$
    
6.  Can a system detect that some of its threads are starving? If you answer “yes,” explain how it can. If you answer “no,” explain how the system can deal with the starvation problem.

	depends on the information. If we know last time on the CPU and IO-device.  But if no information available then we cannot. Or just a single timer
   can look at when was the last time a process has been on the cpu, and the last time the process was an I/O device. If it was a long time a go the process has been on an I/O device and the CPU, the process is being starved.
    
7.  Consider the following resource-allocation policy. Requests for and releases of resources are allowed at any time. If a request for resources cannot be satisfied because the resources are not available, then we check any threads that are blocked waiting for resources. If a blocked thread has the desired resources, then these resources are taken away from it and are given to the requesting thread. The vector of resources for which the blocked thread is waiting is increased to include the resources that were taken away. For example, a system has three resource types, and the vector Available is initialized to (4,2,2). If thread T0 asks for (2,2,1), it gets them. If T1 asks for (1,0,1), it gets them. Then, if T0 asks for (0,0,1), it is blocked (resource not available). If T2 now asks for (2,0,0), it gets the available one (1,0,0), as well as one that was allocated to T0 (since T0 is blocked). T0 ’s Allocation vector goes down to (1,2,1), and its Need vector goes up to (1,0,1).
    
    -   Can deadlock occur? If you answer “yes,” give an example. If you answer “no,” specify which necessary condition cannot occur.
      
      No it can not occur -> Circular wait cannot occur and it is preemptive (Other processes can take resources from another). and preemption allowed. Removed 2 of the 4 conditions for deadlocks.
        
    -   Can indefinite blocking occur? Explain your answer.
      
     Yes, if new processes are constantly being created with a higher priority than the current blocked process. Then it could technically be blocked indefinitely.
	 if u are blocked and other processes continues to come and take your resources, then you may not ever get the hold of the resources you need to run.
        
8.  (**important**) Consider the following snapshot of a system:
    ![image](https://imada.sdu.dk/~daniel/DM510-2023/_images/Ex8.9.png)
    
    Using the banker’s algorithm, determine whether or not each of the following states is unsafe. If the state is safe, illustrate the order in which the threads may complete. Otherwise, illustrate why the state is unsafe.
    
    -   Available = (0, 3, 0, 1)
      T2 finish: available = (3,4,2,2)
      T1 finish: available = (5, 6, 3, 2)
      T3 finish: available = (5, 11, 4, 2)
       
	both T0 and T4 will need maximally 3 of D more, which cannot be provided. Therefore it is an unsafe state.
	
    -   Available = (1, 0, 0, 2)
	T1 finish: available = (3, 2, 1, 2)
	T2 finish: available = (6, 3, 3, 3)
	T0 finish: available = (9, 3, 4, 7)
	can start both T3 and T4 so it is in a safe state.
	
10.  (**important**) Is it possible to have a deadlock involving only one single-threaded process? Explain your answer.
No this is not possible, as only this process can grab any potential locks, so this process does not ever want to synchronize with other processes.

no Circular wait

11.  Draw the resource-allocation graph that illustrates deadlock from the program example shown in Figure 8.1 in Section 8.2.
```c
/* thread one runs in this function */
void *do work one(void *param)
{
	pthread mutex lock(&first mutex);
	pthread mutex lock(&second mutex);
	/**
	* Do some work
	*/
	pthread mutex unlock(&second mutex);
	pthread mutex unlock(&first mutex);
}
pthread exit(0);
/* thread two runs in this function */
void *do work two(void *param)
{
	pthread mutex lock(&second mutex);
	pthread mutex lock(&first mutex);
	/**
	* Do some work
	*/
	pthread mutex unlock(&first mutex);
	pthread mutex unlock(&second mutex);
}
```
T2 has resource 2 request 1, T1 has resource 1 and request 2

12.  Assume that a multithreaded application uses only reader–writer locks for synchronization. Applying the four necessary conditions for deadlock, is deadlock still possible if multiple reader–writer locks are used?
	* mutual exclusion is satisfied since one has to acquire the lock to write.
	* hold and wait is satisfied since if the first reader acquire a reader lock it still may have to wait for a writer lock.
	* No preemption is satisfied.
	* circular wait is staisfied, since if we have two writer locks, 1 writer can wait for the writer lock that 2 has and 2 can wait for the one that 1 has

13.  The program example shown in Figure 8.1 of the book (2 mutex deadlock example) doesn’t always lead to deadlock. Describe what role the CPU scheduler plays and how it can contribute to deadlock in this program.
	if the CPU-schedular decides to preempt a process in `one()` after acquring both locks it is fine if no other process is in `two()`, but if the process running in `one()` has acquired the first lock and then get preempted, deadlock may occur if a process in `two()` starts running.

14.  (**important**) Which of the six resource-allocation graphs shown in Figure below illustrate deadlock? For those situations that are deadlocked, provide the cycle of threads and resources. Where there is not a deadlock situation, illustrate the order in which the threads may complete execution.
	    ![image](https://imada.sdu.dk/~daniel/DM510-2023/_images/Ex8.12.png)
    a. is not deadlocked since T2 is not asking for R1 while holding R2. No circular wait
    b. since  T1 is asking for a resourcethat T3 has, while T3 is asking for the resource T1 has, a deadlock occurs. 
    c.  No deadlock. T3 can finish which will free up R2 and R1 such that T1 can take one and also finish and T2 can also just finish.
    d. Deadlocked since T3 and T4 cannot finish before T1 or T2 finishes while T1 and T2 cannot finish before T3 and T4 finishes.
    e. When T2 finishes, T1 can start, which will ultimately free up one R1 and one R2. The T3 can finish and T4 can finish.
    f. R2 has given more resources than it is allowed to?
    
15.  Consider the version of the dining-philosophers problem in which the chopsticks are placed at the center of the table and any two of them can be used by a philosopher. Assume that requests for chopsticks are made one at a time. Describe a simple rule for determining whether a particular request can be satisfied without causing deadlock given the current allocation of chopsticks to philosophers.
can only take a chopstick if it fullfills your need for your max


16.  Consider the following snapshot of a system:
    
	    ![image](https://imada.sdu.dk/~daniel/DM510-2023/_images/Ex8.18.png)
	    
	    Using the banker’s algorithm, determine whether or not each of the following states is unsafe. If the state is safe, illustrate the order in which the threads may complete. Otherwise, illustrate why the state is unsafe.
	    
	    -   Available = (2, 2, 2, 3)
			safe
	    -   Available = (4, 4, 1, 1)
	    safe
	    -   Available = (3, 0, 1, 4)
			
	    -   Available = (1, 5, 2, 2)
			safe
17.  A single-lane bridge connects the two Vermont villages of North Tunbridge and South Tunbridge. Farmers in the two villages use this bridge to deliver their produce to the neighboring town. The bridge can become deadlocked if a northbound and a southbound farmer get on the bridge at the same time. (Vermont farmers are stubborn and are unable to back up.) Using semaphores and/or mutex locks, design an algorithm in pseudocode that prevents deadlock. Initially, do not be concerned about starvation (the situation in which northbound farmers prevent southbound farmers from using the bridge, or vice versa).
Binary semaphore initialized to 1, call wait when want to cross and signal when crossed

can also just make the street one-way