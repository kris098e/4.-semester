#### 1.  (**important**) Name two differences between logical and physical addresses.
1. physical is the location of the actual bits in hardware
2. logical addresses "pointers" to physical memory
	1. Made by the CPU


#### 2. (**important**) Why are page sizes always powers of 2?
Hvis page size ikke er 2 potens vil man spilde nogle offset-bits, da man ikke kan bruge alle alle bytes. 
Det vil også resultere i et ekstra check man skulle lave hver gang for at se om det var et valid sted i hukommelsen.

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
## 1.  (**very important**) Under what circumstances do page faults occur? Describe the actions taken by the operating system when a page fault occurs.
When you try to use a page, but the corresponding frame is not in main memory.
**look at figure 10.5**


Page faults occur when a process attempts to access a page of virtual memory that is not currently in physical memory (RAM). This can happen due to a variety of reasons such as a page being swapped out to disk or being allocated for the first time. When a page fault occurs, the operating system takes the following actions:

1.  The processor generates a page fault exception and transfers control to the operating system's kernel.
2.  The operating system determines the cause of the page fault and checks whether the access was legal or not. i.e in its address space.
3.  If the access was illegal (e.g., accessing a page that is not owned by the process), the operating system terminates the process with an appropriate error message.
4.  If the access was legal, the operating system determines the location of the page in the virtual memory space and checks whether the page is currently in physical memory (RAM) or not.
5.  If the page is in physical memory, the operating system updates the page table and restarts the instruction that caused the page fault.
6.  If the page is not in physical memory, the operating system selects a victim page to evict from physical memory to make room for the requested page. If the victim page has been modified, it needs to be written back to disk before it can be evicted. The operating system then loads the requested page into physical memory and updates the page table.
7.  Finally, the operating system restarts the instruction that caused the page fault.

Overall, page faults are a common occurrence in modern operating systems and the operating system's ability to handle them efficiently is critical to the performance and stability of the system.

## 2.  Assume that you have a page-reference string for a process with m frames (initially all empty). The page-reference string has length p, and n distinct page numbers occur in it. Answer these questions for any page-replacement algorithms:
-   What is a lower bound on the number of page faults?
1 page fault per page, so n. Because when each page has to occur atleaset once, and we havent seen the page the first time it was seen, it cannot be loaded as a frame. Therefore **n**
-   What is an upper bound on the number of page faults?
Upper bound of p, if we have a page fault every reference in the page-reference string

## 3. (**important**) Consider the following page-replacement algorithms. Rank these algorithms on a five-point scale from “bad” to “perfect” according to their page-fault rate. Separate those algorithms that suffer from Belady’s anomaly from those that do not.
-   LRU replacement
-   FIFO replacement
-   Optimal replacement
-   Second-chance replacement


Hard to tell, since some reference-strings are better for some, while not for others.
1. optimal replacement
2. LRU (Still has some logic holding the frames that are used)
3. Second-chance (still has logic for which to hold)
4. FIFO (no logic around which to hold onto)

FIFO suffers from Belady and also Second-chance (can make example where Second-chance would act like FIFO)

## 4.  An operating system supports a paged virtual memory. The central processor has a cycle time of 1 microsecond. It costs an additional 1 microsecond to access a page other than the current one. Pages have 1,000 words, and the paging device is a drum that rotates at 3,000 revolutions per minute and transfers 1 million words per second. The following statistical measurements were obtained from the system:
-   One percent of all instructions executed accessed a page other than the current page.
-   Of the instructions that accessed another page, 80 percent accessed a page already in memory.
-   When a new page was required, the replaced page was modified 50 percent of the time.
Calculate the effective instruction time on this system, assuming that the system is running one process only and that the processor is idle during drum transfers.

99% of all instructions takes only 1 microsecond
we then have 
$$0.99*1+0.01(p)$$
try to decide p 
$$p=0.8(1+1)+0.2*(L)$$

frequency:$f_{D}=\frac{3000r}{1ms}=\frac{3*10^3r}{60*10^{6}\micro s}=\frac{1}{20000 \micro s}$
$p_{D}=20000 \micro s \implies \frac{P_{0}}{2}=10000 \micro s$
speed of disk: $S_{D}=\frac{10^{6}w}{10^{6}\micro s}=\frac{1w}{1 \micro s}\implies \frac{1}{S_{D}*1000} = 1000 \micro s$
$$L=0.5(10000+1000)+0.5(2*(10000+1000))$$

The entire calculation, i.e the first, will result in 34 microseconds. I.e a 34 factor slowdown, when we go to disk 1% of the time

## 1. (**important**) Consider the page table for a system with 12-bit virtual and physical addresses and 256-byte pages.
![[Pasted image 20230413080031.png]]
The list of free page frames is D, E, F (that is, D is at the head of the list, E is second, and F is last). A dash for a page frame indicates that the page is not in memory. Convert the following virtual addresses to their equivalent physical

page is 256 bytes, so we need 8 bits for the offset. This means the first 4 bits is the page.

-   9EF
look up 9 and get 0, then the physical is 0EF, since EF is just the offset, and 0 is the frame.
-   111
look up the 1, and get 2 as the frame, and the offset is 11, which means the physical address is 211
-   700
No physical frame for 7, which means we have to grap a free frame, and D is the first free frame, which us the physical address D00
-   0FF
Next thing in free list is E, so the physical address will be 0FF


## 2.  Discuss the hardware functions required to support demand paging.
Valid bit, If check page where not valid, need Trap, backing store (disk), restart an instruction.

Valid bit, need to reference memory to check if the frame is there so we need to be able to translate memory. The process itself should of course not be the one also translating

## 3.  (**important**) Consider the two-dimensional array A: `int A[][] = new int[100][100];` where `A[0][0]` is at location 200 in a paged memory system with pages of size 200. A small process that manipulates the matrix resides in page 0 (locations 0 to 199). Thus, every instruction fetch will be from page 0. For three page frames, how many page faults are generated by the following array-initialization loops? Use LRU replacement, and assume that page frame 1 contains the process and the other two are initially empty.
```c
for (int j = 0; j < 100; j++)
  for (int i = 0; i < 100; i++)
      A[i][j] = 0;
```
$\frac{100}{2}*100=5000$

50 page faults per column, 100 columns
```c
for (int i = 0; i < 100; i++)
  for (int j = 0; j < 100; j++)
      A[i][j] = 0;
```
$\frac{100}{2}=50$ page faults. first get the 


## 4.  (**important**) Consider the following page reference string: `1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3, 7, 6, 3, 2, 1, 2, 3, 6`. How many page faults would occur for the following replacement algorithms, assuming one, two, three, four, five, six, and seven frames? Remember that all frames are initially empty, so your first unique pages will cost one fault each.
-   LRU replacement
-   FIFO replacement
-   Optimal replacement


## 5.  Consider the following page reference string: `7, 2, 3, 1, 2, 5, 3, 4, 6, 7, 7, 1, 0, 5, 4, 6, 2, 3, 0 , 1`. Assuming demand paging with three frames, how many page faults would occur for the following replacement algorithms?
-   LRU replacement
-   FIFO replacement
-   Optimal replacement



## 6.  Suppose that you want to use a paging algorithm that requires a reference bit (such as second-chance replacement or working-set model), but the hardware does not provide one. Sketch how you could simulate a reference bit even if one were not provided by the hardware, or explain why it is not possible to do so. If it is possible, calculate what the cost would be.
reference bit: 2nd chance

Use the valid bit, set it 0 as init, and when referenced the hardware will issue a trap every single reference, and we can catch this trap and set the "valid bit" to 1. This is horrible since we use the valid bit for something else, and we generate page faults each time we access memory.

   
## 7.  (**important**) You have devised a new page-replacement algorithm that you think may be optimal. In some contorted test cases, Belady’s anomaly occurs. Is the new algorithm optimal? Explain your answer.
No, since if it were better to use less frames, it cannot be optimal.

    
## 8.  Segmentation is similar to paging but uses variable-sized “pages.” Define two segment-replacement algorithms, one based on the FIFO page-replacement scheme and the other on the LRU page-replacement scheme. Remember that since segments are not the same size, the segment that is chosen for replacement may be too small to leave enough consecutive locations for the needed segment. Consider strategies for systems where segments cannot be relocated and strategies for systems where they can.
Using data to know when the segments was put in for FIFO, and then for LRU would use som bits to know this. Could use a stack and some IDs for FIFO.

Try to put every segment in consecutively
   
## 9.  (**important**) Consider a demand-paged computer system where the degree of multiprogramming is currently fixed at four. The system was recently measured to determine utilization of the CPU and the paging disk. Three alternative results are shown below. For each case, what is happening? Can the degree of multiprogramming be increased to increase the CPU utilization? Is the paging helping?
-   CPU utilization 13 percent; disk utilization 97 percent
Could be thrashing happening, since the CPU utilization is so low and disk utilization is so high. 

Paging is causing this problem, so paging is not helping
-   CPU utilization 87 percent; disk utilization 3 percent
Running as it should. Paging is helping of course, since it is implemented. 
COuld increase multiprogramming maybe.

-   CPU utilization 13 percent; disk utilization 3 percent
Not using all the resources, so it would be beneficial to up the degree of multiprogramming. Not thrashing, so increase CPU.

## 10.  We have an operating system for a machine that uses base and limit registers, but we have modified the machine to provide a page table. Can the page table be set up to simulate base and limit registers? How can it be, or why can it not be?
Base is where to looking at memory.
Limit is the maximum memory.


## 1.  Assume that a program has just referenced an address in virtual memory. Describe a scenario in which each of the following can occur. (If no such scenario can occur, explain why.)
-   TLB miss with no page fault 
If the TLB does not contain the page-to-frame look up, but the page-table does have it. 

-   TLB miss with page fault
If the TLB does not contain the page-to-frame look up, and the page does not either.  Also can happen if the page-table does the look up, but the frame is marked as invalid.

-   TLB hit with no page fault
TLB does contain the page-to-frame look up, and the frame is valid.

-   TLB hit with page fault
NOT POSSIBLE, since this cache should be kept in a valid state, such that there is no invalid frame mappings which fails.

## 2.  **Important** Consider a system that uses pure demand paging.
-   When a process first starts execution, how would you characterize the page-fault rate?
The page fault rate is very high, as no pages are loaded into memory for the process yet. This means that the first lookups will lead to page-faults

-   Once the working set for a process is loaded into memory, how would you characterize the page-fault rate?
The working-set is the set of pages which a process are actively using, therefore the page-fault rate should be low, if it is allowed to bring in all the pages it has used.

-   Assume that a process changes its locality and the size of the new working set is too large to be stored in available free memory. Identify some options system designers could choose from to handle this situation.
Thrashing would occur in a higher rate, CPU-rate decreases and disk-utilization is increasing.
1. Keep track of which pages are used the most,  and keep these in the working-set. 
	1. this would of course lead to many page-fault, as there is a reason the pages are in the working-set to begin with.
2. Put the process to sleep until memory becomes available, as the likelyhood of more page-faults happening increases, and these are very slow.
3. kill processes to get more memory
4. proceed execution.

## 3. repetition The following is a page table for a system with 12-bit virtual and physical addresses and 256-byte pages. Free page frames are to be allocated in the order 9, F, D. A dash for a page frame indicates that the page is not in memory.
![[Pasted image 20230419121407.png]]
Convert the following virtual addresses to their equivalent physical addresses in hexadecimal. All numbers are given in hexadecimal. In the case of a page fault, you must use one of the free frames to update the page table and resolve the logical address to its corresponding physical address.

as the pages are 256 bytes, we need 8bits for the offset. Then the page is 4 bits.

## 4. Consider the page table for a system with 16-bit virtual and physical addresses and 4,096-byte pages.
![[Pasted image 20230419121437.png]]
The reference bit for a page is set to 1 when the page has been referenced. Periodically, a thread zeroes out all values of the reference bit. A dash for a page frame indicates that the page is not in memory. The page-replacement algorithm is localized LRU, and all numbers are provided in decimal.
-   Convert the following virtual addresses (in hexadecimal) to the equivalent physical addresses. You may provide answers in either hexadecimal or decimal. Also set the reference bit for the appropriate entry in the page table.
Since the pages are 4096 Bytes, we need 12 bits for the offset, which then is the first 3 hexadecimals. 
    -   `0x621C`
It is just converting the 6 to whatever is at page 6. This is frame 8. The physical address is then `0x821C`
    -   `0xF0A3`
Looking in the page table we see, at F the frame 2. The physical address is then `0x20A3`
    -   `0xBC1A`
B is 11 in decimal. Answer: `0x4C1A`
    -   `0x5BAA`
`0xDBAA`
    -   `0x0BA1`
`0x9BA1`

Set all the reference bits to 1 for all of the referenced pages.

-   Using the above addresses as a guide, provide an example of a logical address (in hexadecimal) that results in a page fault.
`0x1000` As for page 1, the frame is missing. 

-   From what set of page frames will the LRU page-replacement algorithm choose in resolving a page fault?
The ones where the reference bits is still 0, as these have not been referenced.


## 5. (repetition) Apply the (1) FIFO, (2) LRU, and (3) optimal (OPT) replacement algorithms for the following paGe-reference strings:
-   `2, 6, 9, 2, 4, 2, 1, 7, 3, 0, 5, 2, 1, 2, 9, 5, 7, 3, 8, 5`
-   `0, 6, 3, 0, 2, 6, 3, 5, 2, 4, 1, 3, 0, 6, 1, 4, 2, 3, 5, 7`
-   `3, 1, 4, 2, 5, 4, 1, 3, 5, 2, 0, 1, 1, 0, 2, 3, 4, 5, 0, 1`
-   `4, 2, 1, 7, 9, 8, 3, 5, 2, 6, 8, 1, 0, 7, 2, 4, 1, 3, 5, 8`
-   `0, 1, 2, 3, 4, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0`


## 6.  Discuss situations in which the least frequently used (LFU) page-replacement algorithm generates fewer page faults than the least recently used (LRU) page-replacement algorithm. Also discuss under what circumstances the opposite holds.
LFU will generate fewer page-faults, when there are pages that are referenced many times, but there then come a short break in this pattern, where other pages are needed, and then will be using the pages that are used more frequently again.

there are circumstances where the LRU algorithm generates fewer page faults than the LFU algorithm. For example, in a system with a large cache, there may be pages that are frequently accessed but only for a brief period. In such a situation, the LFU algorithm may keep these pages in memory, assuming they are still active, and may replace other pages that are not as frequently accessed. However, the LRU algorithm will recognize that these pages have not been accessed recently and will replace them with more active pages, thereby reducing the number of page faults.

LFU bad when switching the working set. I.e a startup working set and to the rest of the code which we are gonna use a lot.

LRU worse: `1,1,2,2,3,4,1,1,2,2` with 3 frames. Better to swap out 3 with 4. 

## 7.  The KHIE (pronounced “k-hi”) operating system uses a FIFO replacement algorithm for resident pages and a free-frame pool of recently used pages. Assume that the free-frame pool is managed using the LRU replacement policy. Answer the following questions:

free-frame pool is when a process has just finished executing, then its frames is still in memory, and can be used.
![[KHIE.excalidraw]]
-   If a page fault occurs and the page does not exist in the free-frame pool, how is free space generated for the newly requested page?
use a free frame, get the correct data into this, and use it. Use the least recently used frame in the free-frame-pool

-   If a page fault occurs and the page exists in the free-frame pool, how are the resident page set and the free-frame pool managed to make space for the requested page?
Map the page to point to the corresponding frame, and add it to the memory of the process.

-   To what does the system degenerate if the number of resident pages is set to one?
swap in something from the working set with one from the free-frame pool using LRU, else we have to put something into 2 one of the free-frames. The system then degeneratues to LRU algorithm for paging always.

-   To what does the system degenerate if the number of pages in the free-frame pool is zero?
We have to go to the disk every time we have a page fault, since the page cannot be in the memory already. We then use FIFO always.

## 8.  Explain why compressed memory is used in operating systems for mobile devices.
Compressed memory is when an inactive process, which is still in memory, compresses its memory usage, such that  more RAM becomes available for the active processes. This is used in mobile devices, as they may not have as much memory available, and then background processes will compress its memory.
Have to decompress to use the memory again

A memory compressing algorithm is used, which will also be needing processing power.
Use this in mobile devices since, we may swap to it again fast, and then we dont want it to be looking like it is "starting up again".
Have more in memory.
In mobile devices we cannot swap pages, so we need to kill processes instead to free memory, therefore it is better to compress memory.


## 9.  Suppose that your replacement policy (in a paged system) is to examine each page regularly and to discard that page if it has not been used since the last examination. What would you gain and what would you lose by using this policy rather than LRU or second-chance replacement?
2nd change replacement will only evict something if necessary
This will just evict them if not used, not when necessary.

pros: 
* Should have more available memory always compared to using just replacing whenever needed.

cons:
* Does not consider how frequent a page is used. WIll maybe just throw it out. Maybe, we dont need to reclaim memory.
* Some occational-used pages may have been used between the passes through the pages, which will end not being cleaned, which is considered worse when comparing to lucky timing with more frequent pages being used, which may get evicted. 


Can use this if the system is under heavy load, and we need to reclaim a lot of memory. We can then swap back to fx LRU


## 10.  (**important**) Is it possible for a process to have two working sets, one representing data and another representing code? Explain.
Could be done if code is frequently used, and data is different.

## 11.  (**important**) In a 1,024-KB segment, memory is allocated using the buddy system. Which allocations are made (you could draw a tree illustrating the allocations) after the following memory requests are allocated:
Cannot use the blocks that are already split. If have memory size of 8 and have allocated two 4's, we cannot use the same 8, even tho 3 has been allocated to 4 and we have 5 left
-   Request 5-KB
-   Request 135 KB.
-   Request 14 KB.
-   Request 3 KB.
-   Request 12 KB.
![[Buddy_System_Memory.excalidraw]]

Next, modify the tree/allocations for the following releases of memory. Perform coalescing whenever possible:

-   Release 3 KB.
-   Release 5 KB.
-   Release 14 KB.
-   Release 12 KB.
This would result in only having the left tree to go down to 256, as we dont need to split that memory up.


## 12.  (**interesting**) The slab-allocation algorithm uses a separate cache for each different object type. Assuming there is one cache per object type, explain why this scheme doesn’t scale well with multiple CPUs. What could be done to address this scalability issue?
The slab-allocation algorithm uses a separate cache for each different object type, which can lead to scalability issues when multiple CPUs are involved. This is because each CPU has its own cache, and if there are multiple CPUs working on different object types, there can be contention for cache resources, leading to cache thrashing and decreased performance.

To address this scalability issue, one possible solution is to implement a shared cache that can be accessed by multiple CPUs. This shared cache could be designed to support multiple object types, and it would be responsible for managing and allocating memory for all object types. By using a shared cache, multiple CPUs can access the same cache and avoid cache thrashing, which can lead to improved performance.

Another solution is to use a hierarchical cache system where each CPU has its own cache, but there is also a shared cache that sits between the CPUs and the main memory. This shared cache can be used to cache frequently accessed data and reduce the number of memory accesses required, which can improve performance. This approach is commonly used in modern computer systems and can be effective in managing the cache resources of multiple CPUs.

Overall, to address the scalability issue of the slab-allocation algorithm with multiple CPUs, a shared cache or hierarchical cache system can be used to manage cache resources effectively and improve performance.