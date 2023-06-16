- Deadlock characteristics (and prevention)
    - Mutual Exclusion (Critical section)
    - Hold and wait (Grab all resources or release before grabbing)
    - No preemption (steal)
    - Circular wait (Integer ordering)
- Livelock (hallway)
- Resource Allocation Graph
    - Dining philosiphers problem
- Methods for handling deadlocks
    - ignore (OS)
    - avoid (Developer)
    - allow and recover (algorithm and detection)
- Deadlock prevention
    - Exclude a deadlock characterisation
- Deadlock avoidance
    - safe and unsafe state
    - bankers (use example, remove need calculate on whiteboard)
$$
\begin{array}{cccccc}
& Allocation & Max & Available & Need \\
& A B C & A B C & A B C \\
T_0 & 010 & 753 & 332 & 743 \\
T_1 & 200 & 322 & & 122 \\
T_2 & 302 & 902 & & 600 \\
T_3 & 211 & 222 & & 011 \\
T_4 & 002 & 433 & & 431 \\ 
\end{array}
$$ 
    - Resource Allocation Algorithm (claim edge)
- Deadlock detection
    - Single instance of each resource type (collapse edges, $O(n^2)$, wait for graph)
    - Variant of bankers algorithm (Request, allocation, available)
- Deadlock recovery
    - Thread termination
        - kill all in deadlock (lose of processing time)
        - one-by-one (run deadlock algorithm each time)
    - Resource preemption (Victim selection, Roll back to safe, Starvation)