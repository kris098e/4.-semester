1.  A CPU-scheduling algorithm determines an order for the execution of its scheduled processes. Given n processes to be scheduled on one processor, how many different schedules are possible? Give a formula in terms of n.
$$n!$$
permutations.

2.  Explain the difference between preemptive and nonpreemptive scheduling.
**preemptive**: processes can be interrupted by the schedular
**nonpreemptive**: processes cannot interrupted unless they call to wait themselves. Otherwise they stay on the core until they finish executing

3.  Suppose that the following processes arrive for execution at the times indicated. Each process will run for the amount of time listed. In answering the questions, use nonpreemptive scheduling, and base all decisions on the information you have at the time the decision must be made.
![[Pasted image 20230307153550.png]]
    -   What is the average turnaround time for these processes with the FCFS scheduling algorithm?
_**Turnaround time**. From the point of view of a particular process, the
important criterion is how long it takes to execute that process. The interval
from the time of submission of a process to the time of completion is the
turnaround time. Turnaround time is the sum of the periods spent waiting
in the ready queue, executing on the CPU , and doing I/O_

**p1 turnaround**=8=8
**p2 turnaround**=8+4-0.4=11.6
**p3 turnaround**=8+4-1+1=12
**average**=$\frac{8+11.6+12}{3}=10.533$

    -   What is the average turnaround time for these processes with the SJF scheduling algorithm?
Shortest job first based on the knowledge we have at the time, forces us to start P1 as we dont know anything about p2 yet. when P1 is done, we know P3 is shorter, and start this one. Then we start P2.
**p1 turnaround**=8
**p3 turnaround**=8+1-1=8
**p2 turnaround**=8+1+4-0.4=12.6
**average**=$\frac{8+8+12.6}{3}=9.533$
        
    -   The SJF algorithm is supposed to improve performance, but notice that we chose to run process P1 at time 0 because we did not know that two shorter processes would arrive soon. Compute what the average turnaround time will be if the CPU is left idle for the first 1 unit and then SJF scheduling is used. Remember that processes P1 and P2 are waiting during this idle time, so their waiting time may increase. This algorithm could be known as future-knowledge scheduling.
we will then execute p3 , then p2 and then p1
**turnaround p3**=1
**turnaround p2**=(1+1-0.4)+4=5.6
**turnaround p1**=1+1+4+8=14
**average=**$\frac{1+5.6+14}{3}=6.867$
        
4.  Consider the following set of processes, with the length of the CPU burst time given in milliseconds:
![[Pasted image 20230307153432.png]]
    
    The processes are assumed to have arrived in the order p1, p2, p3, p4, p5 all at time 0.
    -   Draw four Gantt charts that illustrate the execution of these processes using the following scheduling algorithms: FCFS, SJF, nonpreemptive priority (a larger priority number implies a higher priority), and RR (quantum = 2).
**FCFS**: p1->p2->p3->p4->p5
**SJF**: p2->p1->p4->p5->p3
**nonpreemptive priority**: p3->p5->(p1,p4)->p2
**RR (assume no priority, as FCFS)**:p1(done)->p2(done)->p3(6 left)->p4(2 left)->p5(3 left)->p3(4 left)->p4(2 left)->p5(1 left)->p3(2 left)->p4(done)->p5(done)->p3(done) 

    -   What is the turnaround time of each process for each of the scheduling algorithms in part a?
**RR**:
p1=2=2
p2=2(wait for p1)+1=3
p3=p2+2+2+2+2+2+2+2+2+1+2=22
p4=p2+2+2+2+2+2+2+2+2=19
p5=p2+2+2+2+2+2+2+2+2+1=20

    -   What is the waiting time of each process for each of these scheduling algorithms?
        
    -   Which of the algorithms results in the minimum average waiting time (over all processes)?
        
5.  The following processes are being scheduled using a preemptive, roundrobin scheduling algorithm.
    
    Process
    
    Priority
    
    Burst
    
    Arrival
    
    P1�1
    
    40
    
    20
    
    0
    
    P2�2
    
    30
    
    25
    
    25
    
    P3�3
    
    30
    
    25
    
    30
    
    P4�4
    
    35
    
    15
    
    60
    
    P5�5
    
    5
    
    10
    
    100
    
    P6�6
    
    10
    
    10
    
    105
    
    Each process is assigned a numerical priority, with a higher number indicating a higher relative priority. In addition to the processes listed below, the system also has an idle task (which consumes no CPU resources and is identified as Pidle�����). This task has priority 0 and is scheduled whenever the system has no other available processes to run. The length of a time quantum is 10 units. If a process is preempted by a higher-priority process, the preempted process is placed at the end of the queue.
    
    -   Show the scheduling order of the processes using a Gantt chart.
        
    -   What is the turnaround time for each process?
        
    -   What is the waiting time for each process?
        
    -   What is the CPU utilization rate?
        
6.  What advantage is there in having different time-quantum sizes at different levels of a multilevel queueing system?
    
7.  Many CPU-scheduling algorithms are parameterized. For example, the RR algorithm requires a parameter to indicate the time slice. Multilevel feedback queues require parameters to define the number of queues, the scheduling algorithms for each queue, the criteria used to move processes between queues, and so on. These algorithms are thus really sets of algorithms (for example, the set of RR algorithms for all time slices, and so on). One set of algorithms may include another (for example, the FCFS algorithm is the RR algorithm with an infinite time quantum). What (if any) relation holds between the following pairs of algorithm sets?
    
    -   Priority and SJF
        
    -   Multilevel feedback queues and FCFS
        
    -   Priority and FCFS
        
    -   RR and SJF
        
8.  Suppose that a CPU scheduling algorithm favors those processes that have used the least processor time in the recent past. Why will this algorithm favor I/O-bound programs and yet not permanently starve CPU-bound programs?
    
9.  Distinguish between PCS and SCS scheduling.
    
10.  The traditional UNIX scheduler enforces an inverse relationship between priority numbers and priorities: the higher the number, the lower the priority. The scheduler recalculates process priorities once per second using the following function:
    
    Priority = (recent CPU usage / 2) + base
    
    where base = 60 and recent CPU usage refers to a value indicating how often a process has used the CPU since priorities were last recalculated. Assume that recent CPU usage for process P1�1 is 40, for process P2�2 is 18, and for process P3�3 is 10. What will be the new priorities for these three processes when priorities are recalculated? Based on this information, does the traditional UNIX scheduler raise or lower the relative priority of a CPU-bound process?
    
11.  Of these two types of programs:
    
    -   I/O-bound
    -   CPU-bound
    
    which is more likely to have voluntary context switches, and which is more likely to have nonvoluntary context switches? Explain your answer.
    
12.  One technique for implementing **lottery scheduling** works by assigning processes lottery tickets, which are used for allocating CPU time. Whenever a scheduling decision has to be made, a lottery ticket is chosen at random, and the process holding that ticket gets the CPU. The BTV operating system implements lottery scheduling by holding a lottery 50 times each second, with each lottery winner getting 20 milliseconds of CPU time (20 milliseconds × 50 = 1 second). Describe how the BTV scheduler can ensure that higher-priority threads receive more attention from the CPU than lower-priority threads.
    
13.  Consider the exponential average formula used to predict the length of the next CPU burst. What are the implications of assigning the following values to the parameters used by the algorithm?
    
    -   α = 0 and τ0�0 = 100 milliseconds
        
    -   α = 0.99 and τ0�0 = 10 milliseconds
        
14.  A variation of the round-robin scheduler is the **regressive round-robin scheduler**. This scheduler assigns each process a time quantum and a priority. The initial value of a time quantum is 50 milliseconds. However, every time a process has been allocated the CPU and uses its entire time quantum (does not block for I/O), 10 milliseconds is added to its time quantum, and its priority level is boosted. (The time quantum for a process can be increased to a maximum of 100 milliseconds.) When a process blocks before using its entire time quantum, its time quantum is reduced by 5 milliseconds, but its priority remains the same. What type of process (CPU-bound or I/O-bound) does the regressive round-robin scheduler favor? Explain.
    
15.  The following processes are being scheduled using a preemptive, priority-based, round-robin scheduling algorithm.
    
    Process
    
    Priority
    
    Burst
    
    Arrival
    
    P1�1
    
    8
    
    15
    
    0
    
    P2�2
    
    3
    
    20
    
    0
    
    P3�3
    
    4
    
    20
    
    20
    
    P4�4
    
    4
    
    20
    
    25
    
    P5�5
    
    5
    
    5
    
    45
    
    P6�6
    
    5
    
    15
    
    55
    
    Each process is assigned a numerical priority, with a higher number indicating a higher relative priority. The scheduler will execute the highestpriority process. For processes with the same priority, a round-robin scheduler will be used with a time quantum of 10 units. If a process is preempted by a higher-priority process, the preempted process is placed at the end of the queue.
    
    -   Show the scheduling order of the processes using a Gantt chart.
        
    -   What is the turnaround time for each process?
        
    -   What is the waiting time for each process?
        
16.  Which of the following scheduling algorithms could result in starvation?
    
    -   First-come, first-served
        
    -   Shortest job first
        
    -   Round robin
        
    -   Priority
        
17.  Consider a system running ten I/O-bound tasks and one CPU-bound task. Assume that the I/O-bound tasks issue an I/O operation once for every millisecond of CPU computing and that each I/O operation takes 10 milliseconds to complete. Also assume that the context-switching overhead is 0.1 millisecond and that all processes are long-running tasks. Describe the CPU utilization for a round-robin scheduler when:
    
    -   The time quantum is 1 millisecond
        
    -   The time quantum is 10 milliseconds
        
18.  Explain the how the following scheduling algorithms discriminate either in favor of or against short processes:
    
    -   FCFS
        
    -   RR
        
    -   Multilevel feedback queues
        
19.  Assume that an SMP system has private, per-processor run queues. When a new process is created, it can be placed in either the same queue as the parent process or a separate queue.
    
    -   What are the benefits of placing the new process in the same queue as its parent?
        
    -   What are the benefits of placing the new process in a different queue?
        
20.  Explain why interrupt and dispatch latency times must be bounded in a hard real-time system.