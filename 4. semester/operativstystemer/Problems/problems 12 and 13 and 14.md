# 12
1.  (**important**) State three advantages of placing functionality in a device controller, rather than in the kernel. State three disadvantages.
> device controller is a device driver on the disc 

# Advantages
Might be able to make the device controller more specific i.e it can run faster
Make the kernel smaller and simpler

# Disadvantages
Programming in hardware may be less trivial, more expensive to buy the parts for the device controller. But can do some of the programming in firmware
The device controller is not so modular, as you have to reprogram the hardware instead of just the kernel code.
   
2.  Why might a system use interrupt-driven I/O to manage a single serial port and polling I/O to manage a front-end processor, such as a terminal concentrator?
> front-end-processor is something that needs a lot of I/O
> Polling is busy wait
> interrupt driven is "please tell me when you are done", and then do something


 
3.  (**important**, repetition) How does DMA increase system concurrency? How does it complicate hardware design?
   Allows I/O without using the CPU, since we can do more I/O.
Complicates it with synchronization with CPU and DMA when both wants to access the memory. 


1.  Why is it important to scale up system-bus and device speeds as CPU speed increases?
Such that the CPU does not wait on the system-bus, such that we have less bottle-necks

1.  What are the advantages and disadvantages of supporting memory- mapped I/O to device-control registers?
> Memory mapped I/O, means that the registers that the CPU can change are mapped into main memory instead of just being accessed only through not memory 

Kernel may have less instructions, since we dont need the special instructions -> simplyfying the system
There may be special instructions for each device, which is good to remove

Need to protect the memory, because we as users should not be able to change these registeres, since we might break them. Also this introduces some security risks

  
6.  (**important**, new) Describe three circumstances under which blocking I/O should be used. Describe three circumstances under which nonblocking I/O should be used. Why not just implement nonblocking I/O and have processes busy-wait until their devices are ready?
>Blocking refers to operations that block further execution until that operation finishes while non-blocking refers to code that doesn't block execution
 If you fx try to read and something is not available, then you are blocked
 if you try to read and something is not available, then you get control back. Come back again later 

If you have nothing useful to do before you can get the data, then there is no point to not block until the data is available.

If you dont need the additional data, then you will just move on to do the code, and ask again later.

Dont busy wait if we can do nonblocking, since we will waste resources

# 13
1.  Why do some systems keep track of the type of a file, while still others leave it to the user and others simply do not implement multiple file types? Which system is “better”?
> all of the operating systems that we know of does not differentiates between the file

It is leaved to the user, when the block just contains the metadata in some location in the  block for the file. 

If it differentiates, if you fx make a `.jpg` then the operating system will create a special block for you

It may use less space since we dont need that much memory for the metadata. May be able to allocate better space, i.e less fragmentation, since it knows how to handle each file better.


1.  Similarly, some systems support many types of structures for a file’s data, while others simply support a stream of bytes. What are the advantages and disadvantages of each approach?
> We are used to just the stream of bytes 

May be able to do some better management of how the files are stored. Fx if we have a database file, then we might want to access it differently. I.e it becomes more specialized
Will be more complicated to implement the structure of this, as each file may be stored differently.

If we do the stream of bytes, the program has to manage how the stream of bytes are written and stored.
If we just use a stream of bytes, then we fx. can interact with a device just like it is a byte. I.e like how we did when we accessed the device file in 2nd assignment.

    
3.  Could you simulate a multilevel directory structure with a single-level directory structure in which arbitrarily long names can be used? If your answer is yes, explain how you can do so, and contrast this scheme with the multilevel directory scheme. If your answer is no, explain what prevents your simulation’s success. How would your answer change if file names were limited to seven characters?
Just have a variable which holds the current absolute path, and just remove this from the beginning of each paths, and search through the rest. Easy to simulate

You would still be able to do it, but it is veryyyy complicated and completely pointless


1.  Consider a system that supports 5,000 users. Suppose that you want to allow 4,990 of these users to be able to access one file.
    -   How would you specify this protection scheme in UNIX?
	make a group and add the users, specify the file to that you have to be in this group to access the file.

    -   Can you suggest another protection scheme that can be used more effectively for this purpose than the scheme provided by UNIX?
Dont want to add almost all users to this group. So just specify that these users cannot access the file.

1.  (**important**) Provide examples of applications that typically access files according to the following methods:
    -   Sequential
Media files, text processing
    -   Random
database file (jump to random tables fx), video editors

1.  If the operating system knew that a certain application was going to access file data in a sequential manner, how could it exploit this information to improve performance?
Prefetch some of the information that it will read next, since we know that we want to read the file sequentially, which typically means we want to read the entire file


# 14
1.  (**important**) Consider a file currently consisting of 100 blocks. Assume that the file-control block (and the index block, in the case of indexed allocation) is already in memory. Calculate how many disk I/O operations are required for contiguous, linked, and indexed (single-level) allocation strategies, if, for one block, the following conditions hold. In the contiguous-allocation case, assume that there is no room to grow at the beginning but there is room to grow at the end. Also assume that the block information to be added is stored in memory.
    1.  The block is added at the beginning.
contigous: Have to move the entire file a bit to the right to make room for the new text.  need to read each block and write to a new block. Then we need $2*blocks + 1=201$ 
linked: make a new block, make it point to the head, and make this one the head of the linked blocks. This would result in 1 block access, for writing to the new block
indexed: make a new block, and make the index block point to the new block. As the index block is already in memory, we only touch the new block.
    1.  The block is added in the middle.
**contgious:**  calculate the middle block. So we access half of them, 50, and push these. so we do $50*2+1$
**linked:** We dont know which is the middle, so we first need to access 50 to get to the middle block. Make a new block, make the 49th block to point to the new 50th and make the new block point to the previous middle. This will result in 52 in total.
**indexed:** make a new block and make the 50th entry point to the new block. This result in 1 block being accessed
    1.  The block is added at the end.
**contigous**: Calculate the end and write there, 1 block access
**linked:** access all of the blocks, 100, make a new block, write to the previous last block and make it point to the new end. I.e 2 accesses to the previous last blocks and make a new. This result in 102 blocks being accessed
**index:** just 1, make a block, update the in memory index-block. 
    1.  The block is removed from the beginning.
**contigous:** just 1,  or you have to switch it back accessing all the existing ones shiting them back, Then the answer is $99*2$
**linked:** read the first block to get the pointer to the 2nd block, so just 1 access.
**indexed:** dont need to go disc it all if we just update the first index. If we have to 0 the first 1 then we access 1. The book wants to say 0.

    1.  The block is removed from the middle.
49\*2
52
0
    1.  The block is removed from the end.
change the file size, 0
if we have tail pointer then its 0, else its 100. Have to go through all, 99 reads and then write the 99th to update its pointer.


2.  (**important**) Why must the bit map for file allocation be kept on mass storage, rather than in main memory?
    Non-volatile memory, if the power turns off, then it will be lost
    
    
3.  (**repetition**) Consider a system that supports the strategies of contiguous, linked, and indexed allocation. What criteria should be used in deciding which strategy is best utilized for a particular file?
    contigous is faster than indexed for random access, since we only have to do one lookup for the first block and then we can calculate the next. We have to lookup the indexblock and then block to read for the indexed. Therefore contigous is faster. 
    
    Linked can only be used for sequential access
    
    
4.  (**important**) Consider a file system that uses a modified contiguous-allocation scheme with support for extents. A file is a collection of extents, with each extent corresponding to a contiguous set of blocks. A key issue in such systems is the degree of variability in the size of the extents. What are the advantages and disadvantages of the following schemes?
> extent means we can allocate extra blocks as the primary size. I.e when we allocate we allocate extends. This may be 2 blocks


    1.  All extents are of the same size, and the size is predetermined.
	    just responds to allocating bigger blocks.
       
    2.  Extents can be of any size and are allocated dynamically.
	if we know a file may be bigger, we can allocate more size intially.
	Harder to implement, since we have to be able to allocate more blocks
	This just corresponds to congious allocation. 

    3.  Extents can be of a few fixed sizes, and these sizes are predetermined.
	buddy system, find the lowest power of 2, but only allow dont a certain size.
	WILL create internal fragmentation, since we can only allocate a certain size, which may be too big


5.  Contrast the performance of the three techniques for allocating disk blocks (contiguous, linked, and indexed) for both sequential and random file access.
    contigous is faster both sequential and random file access, but get external fragmentation
    linked is worse than contigous for both
    indexed is better than linked for both sequential and random access, but only a tiny bit better for sequential since we know where the blocks will be in advance, since we can read them off the index-block
    
    
6.  Discuss how performance optimizations for file systems might result in difficulties in maintaining the consistency of the systems in the event of computer crashes.
	most of the performance optimizations are keeping it in main-memory which makes it faster, then it will not store this in main memory, since we want to keep it in main memory for as long as possible.
	
	Uses log-journaling in the file-system writing fewer times to disc.
	
	The current state of the file-system will then be mostly volatile.
	
    
7.  (**important**) Consider a file system on a disk that has both logical and physical block sizes of 512 bytes. Assume that the information about each file is already in memory. For each of the three allocation strategies (contiguous, linked, and indexed), answer these questions:
    -   How is the logical-to-physical address mapping accomplished in this system? (For the indexed allocation, assume that a file is always less than 512 blocks long.)
	Block size is 512 bytes, meaning 9 bits are used for  this. So if we want the block number, we divide the logical address with 512, or shift the bits 9 times to get the block in memory
	
	**contigous**:  in the metadata we have a start, fx 512, then we divide this with 512 and get the first block, which is where we want to start .This means $\frac{x}{512}$
      
    -   If we are currently at logical block 10 (the last block accessed was block 10) and want to access logical block 4, how many physical blocks must be read from the disk?
      
      **contigous:** 1, we just have to do the calculation of $\frac{x}{512}=4$
      **indexed:** start from the index block, and get to which block we want to read. I.e calculate which block to get to, meaning we only access the index block.
      
8.  (**important**) Consider a file system that uses inodes to represent files. Disk blocks are 8 KB in size, and a pointer to a disk block requires 4 bytes. This file system has 12 direct disk blocks, as well as single, double, and triple indirect disk blocks. What is the maximum size of a file that can be stored in this file system?
	The inode has pointers to all 12 direct disk blocks. Then it has a pointer to a block which has pointers to other blocks which holds data. Double means it points to a block which has pointers to other blocks, which has pointers to other blocks, which then contains data

	can have 8kB/4B pointers to block in a block. This means if we fill up the block we only pointers we can have this many pointers to block, which can have 8kb each. 
	$12*8kB+\left( \frac{8kb}{4}*8kb \right)+\left( \left( \frac{8kb}{4} \right)^2*8kb \right)+\left( \left( \frac{8kb}{4} \right)^3*8kb \right)=64TB$
	
	