1. In Section 6.4, we mentioned that disabling interrupts frequently can affect the system’s clock. Explain why this can occur and how such effects can be minimized.
The system clock figure out the time by counting interrupts

2. What is the meaning of the term busy waiting? What other kinds of waiting are there in an operating system? Can busy waiting be avoided altogether? Explain your answer.
Sleeping and waking up

3. Explain why spinlocks are not appropriate for single-processor systems yet are often used in multiprocessor systems.
spinlocks will hold the CPU until a check passes. If the check can only be updated by another process, then we spin forever. If we fx use round-robin, it will just be put to sleep only to be waken up to check again. Rather give the CPU to the process that can change this condition

4.  Show that, if the `wait()` and `signal()` semaphore operations are not executed atomically, then mutual exclusion may be violated.
if context switch right after the while loop finished, then it doesnt get to `--` on the semaphore

5. Illustrate how a binary semaphore can be used to implement mutual exclusion among n processes.
dont have to ensure mutual exclusion, so just have a semaphore initialized to being 1, and then one process graps the lock, the other then wait until signal, and one will then grap it again and so on...

6. Race conditions are possible in many computer systems. Consider a banking system that maintains an account balance with two functions: deposit(amount) and withdraw(amount). These two functions are passed the amount that is to be deposited or withdrawn from the bank account balance. Assume that a husband and wife share a bank account. Concurrently, the husband calls the withdraw() function, and the wife calls deposit(). Describe how a race condition is possible and what might be done to prevent the race condition from occurring.
Aquire a lock before updating the shared bank account balance.


7. The pseudocode below illustrates the basic push() and pop() operations of an array-based stack. Assuming that this algorithm could be used in a concurrent environment, answer the following questions:
* What data have a race condition?
* How could the race condition be fixed?
```c
 push(item) {
     acquire();
     if (top < SIZE) {
         stack[top] = item;
         top++;
     }
     else
         ERROR
             release();
 }
 pop() {
     acquire();
     if (!is empty()) {
         top--;
         item = stack[top];
         release();
         return item;
     }
     else
         ERROR
             release();
 }
 is empty() {
     if (top == 0)
         return true;
     else
         return false;
 }
```

8. The following program example can be used to sum the array values of size N elements in parallel on a system containing N computing cores (there is a separate processor for each array element):
```c
 for j = 1 to log 2(N) {
     for k = 1 to N {
         if ((k + 1) % pow(2,j) == 0) {
           values[k] += values[k - pow(2,(j-1))]
         }
     }
 }
```
This has the effect of summing the elements in the array as a series of partial sums, as shown in the figure below.
![[Pasted image 20230316090248.png]]
After the code has executed, the sum of all elements in the array is stored in the last array location. Are there any race conditions in the above code example? If so, identify where they occur and illustrate with an example. If not, demonstrate why this algorithm is free from race conditions.

There are race conditions, since if one processor goes to the next layer before the previous layer was done.


9. One approach for using compare_and_swap() for implementing a spinlock is as follows:
```c
 void lock spinlock(int *lock) {
     while (compare_and_swap(lock, 0, 1) != 0)
         ; /* spin */
 }
```
A suggested alternative approach is to use the “compare and compareand-swap” idiom, which checks the status of the lock before invoking the compare_and_swap() operation. (The rationale behind this approach is to invoke compare_and_swap() only if the lock is currently available.)
This strategy is shown below:

```c
 void lock_spinlock(int *lock) {
     while (true) {
         if (*lock == 0) {
             /* lock appears to be available */

             if (!compare_and_swap(lock, 0, 1))
                 break;
         }
     }
 }
```
Does this “compare and compare-and-swap” idiom work appropriately for implementing spinlocks? If so, explain. If not, illustrate how the integrity of the lock is compromised.

it is valid, check fewer times. since `compare_and_swap` is atomicly in the end


10. The first known correct software solution to the critical-section problem for two processes was developed by Dekker. The two processes, P0 and p1 , share the following variables:
```c
boolean flag[2]; /* initially false */
 int turn;
```
The structure of process Pi (i == 0 or 1) in Dekker’s algorithm is shown below. The other process is Pj (j == 1 or 0).
```c
 while (true) {
     flag[i] = true;

     while (flag[j]) {
         if (turn == j) {
             flag[i] = false;
             while (turn == j)
                 ; /* do nothing */
             flag[i] = true;
         }
     }

     /* critical section */

     turn = j;
     flag[i] = false;

     /* remainder section */
  }
```
Prove that the algorithm satisfies all three requirements for the critical-section problem.

1. mutual exclusion
2. progress (a process enters the critical section at some point)
	1. if no processes are to enter the seciton, then mutual exclusion is done. This is dumb
3. bounded waiting (all processes that wants to enter the critical seciton gets in at some point)

Just follows the same principal as **Petersons solution**


11. Consider how to implement a mutex lock using the compare_and_swap() instruction. Assume that the following structure defining the mutex lock is available:
```c
 typedef struct {
     int available;
 } lock;
```

The value (`available == 0`) indicates that the lock is available, and a value of 1 indicates that the lock is unavailable. Using this struct, illustrate how the following functions can be implemented using the `compare_and_swap()` instruction:

-   void acquire(lock *mutex)
    
-   void release(lock *mutex)
    
Be sure to include any initialization that may be necessary.

There is an example in the slides for synchronization tools, but we implement it with `compare_and_swap()` given the lock, and we wait for it to become available.

12. Assume that a system has multiple processing cores. For each of the following scenarios, describe which is a better locking mechanism—a spinlock or a mutex lock where waiting processes sleep while waiting for the lock to become available:

* The lock is to be held for a short duration.
if short is less than 2 context switches, then spinlock. 1 for sleep and 1 for wake up
* The lock is to be held for a long duration.
sleep
* A thread may be put to sleep while holding the lock.
go to sleep, since we know the other process will also need to do atleast 2 context-switches before we can get the lock


13. A multithreaded web server wishes to keep track of the number of requests it services (known as hits). Consider the two following strategies to prevent a race condition on the variable hits. The first strategy is to use a basic mutex lock when updating hits:

```c
 int hits;
 mutex lock hit lock;
 hit lock.acquire();
 hits++;
 hit lock.release();
```
A second strategy is to use an atomic integer:

```c
 atomic t hits;
 atomic inc(&hits);
```
Explain which of these two strategies is more efficient.

**Merkle** explained that if we are using semaphores instead of atomic built in features, then we should use the features as they should be faster. We dont have to worry about the semaphores.
So we assume the _atomic  integer is faster_

14. Servers can be designed to limit the number of open connections. For example, a server may wish to have only N socket connections at any point in time. As soon as N connections are made, the server will not accept another incoming connection until an existing connection is released. Illustrate how semaphores can be used by a server to limit the number of concurrent connections.

Bounded buffer problem
```c
#done once
Sem s = N;

# infinite loop
wait(s);
open();
...
...
close();
signal(s)
```

15. Describe how the signal() operation associated with monitors differs from the corresponding operation defined for semaphores.
This uses `conditional variables`, which are just binary simaphores
When signaling you see if some processes are in the que for this lock, if no one is there, you just do nothing. In an ordinary semaphore we increment and decrement a semaphore
