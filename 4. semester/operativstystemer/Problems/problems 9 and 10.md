#### 1.  (**important**) Name two differences between logical and physical addresses.
1. physical is the location of the actual bits in hardware
2. logical addresses "pointers" to physical memory
	1. Made by the CPU


#### 2. (**important**) Why are page sizes always powers of 2?
Hvis page size ikke er 2 potens vil man spilde nogle offset-bits, da man ikke kan bruge alle alle bytes.

#### 3. Consider a system in which a program can be separated into two parts: code and data. The CPU knows whether it wants an instruction (instruction fetch) or data (data fetch or store). Therefore, two base –limit register pairs are provided: one for instructions and one for data. The instruction base –limit register pair is automatically read-only, so programs can be shared among different users. Discuss the advantages and disadvantages of this scheme.
Waste less memory since we shared memory, and the instructions are read only so no synchronization. Think about the libc also lives one place in memory, and multiple processes page-tables refers to the same frame in memory.

disadvantages: cache thrashing

#### 4. (important) Consider a logical address space of 64 pages of 1,024 words each, mapped onto a physical memory of 32 frames.
-   How many bits are there in the logical address?
need $\log_{2}(1024)=10$ bits for the offset and $\log_{2}(64)=6$  bits for all the 64 possibilities. so **16** in total
-   How many bits are there in the physical address?
offset is the same, and need $\log_{2}(32)=5$ bits for the 32 possibilities. so **15** in total

#### 5. What is the effect of allowing two entries in a page table to point to the same page frame in memory? Explain how this effect could be used to decrease the amount of time needed to copy a large amount of memory from one place to another. What effect would updating some byte on one page have on the other page?
Instead of actually copying memory, we can just create an index in the page table to point to the same page in memory.
If we update 1 byte in the frame using one of the processes, it is updated for both. Then we have to copy, to not update the other processes memory aswel. If we are lucky they do not write and only read, then we dont have to copy the frame

#### 6. (**important**) Given six memory partitions of 300 KB, 600 KB, 350 KB, 200 KB, 750 KB, and 125 KB (in order), how would the first-fit, best-fit, and worst-fit algorithms place processes of size 115 KB, 500 KB, 358 KB, 200 KB, and 375 KB (in order)?

in order: FIFO, BEST FIT, WORST FIT
![[Pasted image 20230330084831.png]]

#### 7. Assuming a 1-KB page size, what are the page numbers and offsets for the following address references (provided as decimal numbers):
* 3085
	* binær: 1100 0000 1101
	* 10 for offset, and 3 for the page number 
		* offset = $13_{10}$
		* page = $3_{10}$
* 42095
	* binær: 1010 0100 0110 1111
		* 10 bits for offset, and 6 for page
			* offset = 111
			* page = 41
* 215201
	* page = 210
	* offset = 161
* 650000 
	* offset = 784
	* page =
* 2000001
	* offset = 129
	* page number = 1953

#### 8. (**important**) The BTV operating system has a 21-bit virtual address, yet on certain embedded devices, it has only a 16-bit physical address. It also has a 2-KB page size. How many entries are there in each of the following?
* A conventional, single-level page table
2 kb page size = 11 bits for offset
then we have page numbers for the rest 21-11 bits = 10 bits for the indexes. Therefore we have 10 bits for the entries, which 1024 indexes

* An inverted page table
Here we base on the physical addresses. **i.e 1 entry per frame** Base the index of the page tabe to the index in the physical table.
Still have 11 bits offset and then we have 16-11 bits for the indexes. I.e 5 bits for the page indexeses, which means $2^5$ indexes

* What is the maximum amount of physical memory in the BTV operating system?
$2^{16}$ Because we have $2^5$ frames holding $2^{11}$ bits.


#### 9. (**important**) Consider a logical address space of 256 pages with a 4-KB page size, mapped onto a physical memory of 64 frames.
-   How many bits are required in the logical address?
12 bits til offset
8 bits til index

20 bits
-   How many bits are required in the physical address? 
12 bits for offset
6 bits for index

18 bits

#### 10. (**important**) Consider a computer system with a 32-bit logical address and 4-KB page size. The system supports up to 512 MB of physical memory. How many entries are there in each of the following?
512MB for the entire memory
32 bits for addresses
* A conventional, single-level page table
12 bits offset
rest of the addressing of the page: 32-12=20 for the page index
2^20 indexes

* An inverted page table
we can calculate how many frames we have: $\frac{512MB}{4K}=128k$

#### 11. (**important**) Explain the difference between internal and external fragmentation.
* Internal
inside the block in the memory. The process we will want to get into the memory may only need 120MB but the block size i 140MB, then we will waste 20MB.
* External
The amount of free memory in the entire memory. But it is fragmented, so we may have 20MB of free memory, but it is not contigues, so we may not be able to allocate a program that needs 20MB, because it is fragmented

#### 12. Given six memory partitions of 100 MB, 170 MB, 40 MB, 205 MB, 300 MB, and 185 MB (in order), how would the first-fit, best-fit, and worst-fit algorithms place processes of size 200 MB, 15 MB, 185 MB, 75 MB, 175 MB, and 80 MB (in order)? Indicate which—if any—requests cannot be satisfied. Comment on how efficiently each of the algorithms manages memory.


#### 13. (**important**) Most systems allow a program to allocate more memory to its address space during execution. Allocation of data in the heap segments of programs is an example of such allocated memory. What is required to support dynamic memory allocation in the following schemes?
-   Contiguous memory allocation
|p1|p2| free |
If p1 wants more  memory, then we will have to be able to move entire processes, since p1 cannot allocate right after its memory addressing space contigously if we do not move p2.

-   Paging
Out logical addresses can still be contigoues, since we just have map other frames into the page right after a page. This means the physical addresses are not contigues, but are mapped into virtual addresses that are contigous

#### 14. Explain why mobile operating systems such as iOS and Android do not support swapping.
Too many processes in main memory, if something then comes, we have to move a process into a swapped memory. 
It is very slow, since we have to move the process onto the disc, which is **very slow** to move from RAM to disc.

we dont do it because it is very slow, and also it may cost some battery.
Mobiles has flash memory, which is only writeable x amount of times, since it wears off, so we rather write as little as possible.

#### 15. (**should be very easy**) Assuming a 1-KB page size, what are the page numbers and offsets for the following address references (provided as decimal numbers)?
write the stuff out in binary, and then use 10 bits ($\log_{2}(1024)=10$bits) for the offset, and the rest for page numbers. 
-   21205
-   164250
-   121357
-   16479315
-   27253187

#### 16. (**hopefully easy, but important**) Consider a logical address space of 2,048 pages with a 4-KB page size, mapped onto a physical memory of 512 frames.
* How many bits are required in the logical address?
12bits for offset  since 4-kb page size
11bits for the pages to index into eveyrthing

so 23 bits logical

* How many bits are required in the physical address?
12bits for offset  since 4-kb page size
9 bits for the number of frames to index into every frame

21 bits physical

#### 17. (**only for repetiition now**) Consider a computer system with a 32-bit logical address and 8-KB page size. The system supports up to 1 GB of physical memory. How many entries are there in each of the following?
-   A conventional, single-level page table
13bits offset
and then 32-13=19 bits for the page numbers

so $2^{19}$ entries in the page table

-   An inverted page table
$\frac{1GB}{8KB}=\frac{1kb}{8kb}\cdot 10^6=125000$ frames


#### 18. (**for specific architecture, only**) Consider the IA-32 address-translation scheme shown in Figure 9.22 or on the lecture slides.
-   Describe all the steps taken by the IA-32 in translating a logical address into a physical address.
**g is a flag if it is in a global or local descriptor table**
**s is an index into the descriptor table**
**p is permissions**

1. use selector to look up in descriptor table. This makes it a 32 bits linear-address. This makes a linear address
2. either the first 10 bits points to a bigger page and use the 10+12 bits to lookup into the 4MB page. If they point to a page table, we use the extra 10 bits to index into the page-table, which points to a 4KB page
	1. this bringes to a physical address

- What are the advantages to the operating system of hardware that provides such complicated memory translation?
advantages
1. logical addresses are smaller
2. dont have to write logic into the software, since the hardware can do it all
	1. hardware is faster than software

distadvantages
1. may be concerned that since it is complex that it may be slow

-   Are there any disadvantages to this address-translation system? If so, what are they? If not, why is this scheme not used by every manufacturer?
May not be implemented by all manufacturers, since it has disadvantages and advantages.

# 10
1.  (**very important**) Under what circumstances do page faults occur? Describe the actions taken by the operating system when a page fault occurs.

Page faults occur when a process attempts to access a page of virtual memory that is not currently in physical memory (RAM). This can happen due to a variety of reasons such as a page being swapped out to disk or being allocated for the first time. When a page fault occurs, the operating system takes the following actions:

1.  The processor generates a page fault exception and transfers control to the operating system's kernel.
2.  The operating system determines the cause of the page fault and checks whether the access was legal or not.
3.  If the access was illegal (e.g., accessing a page that is not owned by the process), the operating system terminates the process with an appropriate error message.
4.  If the access was legal, the operating system determines the location of the page in the virtual memory space and checks whether the page is currently in physical memory (RAM) or not.
5.  If the page is in physical memory, the operating system updates the page table and restarts the instruction that caused the page fault.
6.  If the page is not in physical memory, the operating system selects a victim page to evict from physical memory to make room for the requested page. If the victim page has been modified, it needs to be written back to disk before it can be evicted. The operating system then loads the requested page into physical memory and updates the page table.
7.  Finally, the operating system restarts the instruction that caused the page fault.

Overall, page faults are a common occurrence in modern operating systems and the operating system's ability to handle them efficiently is critical to the performance and stability of the system.

2.  Assume that you have a page-reference string for a process with m frames (initially all empty). The page-reference string has length p, and n distinct page numbers occur in it. Answer these questions for any page-replacement algorithms:
    -   What is a lower bound on the number of page faults?
    -   What is an upper bound on the number of page faults?


3. (**important**) Consider the following page-replacement algorithms. Rank these algorithms on a five-point scale from “bad” to “perfect” according to their page-fault rate. Separate those algorithms that suffer from Belady’s anomaly from those that do not.
    -   LRU replacement
    -   FIFO replacement
    -   Optimal replacement
    -   Second-chance replacement


4.  An operating system supports a paged virtual memory. The central processor has a cycle time of 1 microsecond. It costs an additional 1 microsecond to access a page other than the current one. Pages have 1,000 words, and the paging device is a drum that rotates at 3,000 revolutions per minute and transfers 1 million words per second. The following statistical measurements were obtained from the system:
    -   One percent of all instructions executed accessed a page other than the current page.
    -   Of the instructions that accessed another page, 80 percent accessed a page already in memory.
    -   When a new page was required, the replaced page was modified 50 percent of the time.
Calculate the effective instruction time on this system, assuming that the system is running one process only and that the processor is idle during drum transfers.

1. (**important**) Consider the page table for a system with 12-bit virtual and physical addresses and 256-byte pages.
![[Pasted image 20230413080031.png]]
The list of free page frames is D, E, F (that is, D is at the head of the list, E is second, and F is last). A dash for a page frame indicates that the page is not in memory. Convert the following virtual addresses to their equivalent physical

-   9EF
-   111
-   700
-   0FF

2.  Discuss the hardware functions required to support demand paging.
    
3.  (**important**) Consider the two-dimensional array A: `int A[][] = new int[100][100];` where `A[0][0]` is at location 200 in a paged memory system with pages of size 200. A small process that manipulates the matrix resides in page 0 (locations 0 to 199). Thus, every instruction fetch will be from page 0. For three page frames, how many page faults are generated by the following array-initialization loops? Use LRU replacement, and assume that page frame 1 contains the process and the other two are initially empty.
```c
for (int j = 0; j < 100; j++)
  for (int i = 0; i < 100; i++)
      A[i][j] = 0;
```

```c
for (int i = 0; i < 100; i++)
  for (int j = 0; j < 100; j++)
      A[i][j] = 0;
```

4.  (**important**) Consider the following page reference string: `1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3, 7, 6, 3, 2, 1, 2, 3, 6`. How many page faults would occur for the following replacement algorithms, assuming one, two, three, four, five, six, and seven frames? Remember that all frames are initially empty, so your first unique pages will cost one fault each.
    -   LRU replacement
    -   FIFO replacement
    -   Optimal replacement
5.  Consider the following page reference string: `7, 2, 3, 1, 2, 5, 3, 4, 6, 7, 7, 1, 0, 5, 4, 6, 2, 3, 0 , 1`. Assuming demand paging with three frames, how many page faults would occur for the following replacement algorithms?
    -   LRU replacement
    -   FIFO replacement
    -   Optimal replacement
6.  Suppose that you want to use a paging algorithm that requires a reference bit (such as second-chance replacement or working-set model), but the hardware does not provide one. Sketch how you could simulate a reference bit even if one were not provided by the hardware, or explain why it is not possible to do so. If it is possible, calculate what the cost would be.
    
7.  (**important**) You have devised a new page-replacement algorithm that you think may be optimal. In some contorted test cases, Belady’s anomaly occurs. Is the new algorithm optimal? Explain your answer.
    
8.  Segmentation is similar to paging but uses variable-sized “pages.” Define two segment-replacement algorithms, one based on the FIFO page-replacement scheme and the other on the LRU page-replacement scheme. Remember that since segments are not the same size, the segment that is chosen for replacement may be too small to leave enough consecutive locations for the needed segment. Consider strategies for systems where segments cannot be relocated and strategies for systems where they can.
    
9.  (**important**) Consider a demand-paged computer system where the degree of multiprogramming is currently fixed at four. The system was recently measured to determine utilization of the CPU and the paging disk. Three alternative results are shown below. For each case, what is happening? Can the degree of multiprogramming be increased to increase the CPU utilization? Is the paging helping?
    -   CPU utilization 13 percent; disk utilization 97 percent
    -   CPU utilization 87 percent; disk utilization 3 percent
    -   CPU utilization 13 percent; disk utilization 3 percent

10.  We have an operating system for a machine that uses base and limit registers, but we have modified the machine to provide a page table. Can the page table be set up to simulate base and limit registers? How can it be, or why can it not be?