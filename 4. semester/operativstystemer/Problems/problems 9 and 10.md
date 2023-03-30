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
