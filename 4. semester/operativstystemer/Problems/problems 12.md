1.  (**important**) Explain why SSTF scheduling tends to favor middle cylinders over the innermost and outermost cylinders.
   Shortest seek time first  
   on average the requests are more possible towards the middle. More likely to serve these.
    
2.  (**important**) Why is it important to balance file-system I/O among the disks and controllers on a system in a multitasking environment?
To extend the lifetime of each disc
increase performance. More concurrency.
maximize utilization
    
3.  What are the tradeoffs involved in rereading code pages from the file system versus using swap space to store them?
   code page: pages for executable code.
    overhead for going through the file-system
	we need to allocate the swap space.
	
    
4.  Is there any way to implement truly stable storage? Explain your answer.
    store data for an infinite amount of time.
    
    laws of physics prevents this.
    
    
5.  (**rather easy, but will take long**) It is sometimes said that tape is a sequential-access medium, whereas a hard disk is a random-access medium. In fact, the suitability of a storage device for random access depends on the transfer size. The term streaming transfer rate denotes the rate for a data transfer that is underway, excluding the effect of access latency. In contrast, the effective transfer rate is the ratio of total bytes to total seconds, including overhead time such as access latency. Suppose we have a computer with the following characteristics: the level-2 cache has an access latency of 8 nanoseconds and a streaming transfer rate of 800 megabytes per second, the main memory has an access latency of 60 nanoseconds and a streaming transfer rate of 80 megabytes per second, the hard disk has an access latency of 15 milliseconds and a streaming transfer rate of 5 megabytes per second, and a tape drive has an access latency of 60 seconds and a streaming transfer rate of 2 megabytes per second.
	
    1.  Random access causes the effective transfer rate of a device to decrease, because no data are transferred during the access time. For the disk described, what is the effective transfer rate if an average access is followed by a streaming transfer of (1) 512 bytes, (2) 8 kilobytes, (3) 1 megabyte, and (4) 16 megabytes?
 **Shows that transfers of small amount of data is slow when it is not sequential from beginning. The effective transfer rate increases when more bytes are transfered.**
    2.  The utilization of a device is the ratio of effective transfer rate to streaming transfer rate. Calculate the utilization of the disk drive for each of the four transfer sizes given in part 1.
    3.  Suppose that a utilization of 25 percent (or higher) is considered acceptable. Using the performance figures given, compute the smallest transfer size for a disk that gives acceptable utilization.
    4.  Complete the following sentence: A disk is a randomaccess device for transfers larger than bytes and is a sequential-access device for smaller transfers.
       random for **larger than the block size**, sequential if we can read less.
       
    5.  Compute the minimum transfer sizes that give acceptable utilization for cache, memory, and tape.
    6.  When is a tape a random-access device, and when is it a sequential-access device?
If we access the data sequentially it is sequential. If we jump through it, it is not random

6.  Could a RAID level 1 organization achieve better performance for read requests than a RAID level 0 organization (with nonredundant striping of data)? If so, how?
    Multithread the reading, start differently in the mirrored blocks.
    
    concurrent access to the blocks. Using both the mirrored blocks and the regular blocks to read from
    
7.  (**important**) Give three reasons to use HDDs as secondary storage.
    non-volatile
    cheap memory storage
    faster than tapes
    SSDs gets slow when filled up with large amount of data (>80% mem) since it has to erase data and then write when replacing. I.e you can fill it more up.
    Store a lot of data
    more proven compared to SSD's. We know exactly what the techonologies can do.
    can recover data from it
    better lifetime than NVM's
    
    
8.  (**important**) Give three reasons to use NVM devices as secondary storage.
    Non Volatile Memory
    defined in the book as devices that does not have moving parts
	
	non-volatile
	No moving parts, instant access
	Faster
	normal use leads to more life time than HDDs
	getting cheaper and cheaper
    
    
9.  None of the disk-scheduling disciplines, except FCFS, is truly fair (starvation may occur).
    -   Explain why this assertion is true.
      shortest seektime first may always have a request closer than anything else
      
      You could stay on the same cylinder, if there always comes a request the cylinder the head is at.
      
    -   Describe a way to modify algorithms such as SCAN to ensure fairness.
     same as for regular process schedulaing. Implement aging. 
      
    -   Explain why fairness is an important goal in a multi-user systems.
      Such that processes dont starve, responsiveness.
      Requests dont wait unreasonably long
      
    -   Give three or more examples of circumstances in which it is important that the operating system be unfair in serving I/O requests.
     Real time systems - having strict deadlines
     Writing metadata for files, prioritize these, since we slow down the system if we dont prioritize these
      
      
10.  (**easy**) Suppose that a disk drive has 5,000 cylinders, numbered 0 to 4,999. The drive is currently serving a request at cylinder 2,150, and the previous request was at cylinder 1,805. The queue of pending requests, in FIFO order, is: `2,069; 1,212; 2,296; 2,800; 544; 1,618; 356; 1,523; 4,965; 3,681` Starting from the current head position, what is the total distance (in cylinders) that the disk arm moves to satisfy all the pending requests for each of the following disk-scheduling algorithms?
    -   FCFS
    -   SCAN (go from side to side, servce requests when found)
      sort the list.  All the request are available
      the next from 2150 is 2296->2800 -> 3681 -> 4965->(go to 4999 and back. So add 34\*2)->2069->1618->1523->1211->544->356
      The distance is **7492**
    -   C-SCAN
    
11.  (**repetition**) Compare and contrast HDDs and NVM devices. What are the best applications for each type?
## NVMs
generally faster
better fx in phones

## HDDs
Cheaper, more memory compacted
Discs has moving parts. Don t put it on the phone
    
    
12.  (**important**) Consider a RAID level 5 (ASSUME ITS LEVEL 4) organization comprising five disks, with the parity for sets of four blocks on four disks stored on the fifth disk. How many blocks are accessed in order to perform the following?
    -   A write of one block of data
      two blocks are read and written to. Read first to check if the parity bit should change
      two blocks. The block they want to write to, and the parity block
     . 
    -   A write of seven continuous blocks of data
      it has 4 blocks of data, and 1 block the parity of these blocks
      ![[RAID.excalidraw]]
    has to access 9.
    write 4 blocks, then change parity bit. 5 blocks
    Read the parity bit in the parity bit block before modifying the 3 blocks, then modify the parity bit. 
    
      
      
13.  Assume that you have a mixed configuration comprising disks organized as RAID level 1 and RAID level 5 disks. Assume that the system has flexibility in deciding which disk organization to use for storing a particular file. Which files should be stored in the RAID level 1 disks and which in the RAID level 5 disks in order to optimize performance?
## raid 1
big files here, can optimize performance by optimizing performance when reading

## raid 5
Just the overhead, but less memory usage

    
14.  (**important**) The reliability of a storage device is typically described in terms of mean time between failures (MTBF). Although this quantity is called a “time,” the MTBF actually is measured in drive-hours per failure.
    -   If a system contains 1,000 disk drives, each of which has a 750,000hour MTBF, which of the following best describes how often a drive failure will occur in that disk farm: once per thousand years, once per century, once per decade, once per year, once per month, once per week, once per day, once per hour, once per minute, or once per second?
      $$\frac{750.000}{1000}=750hrs$$
    -   (**far-going camparison**) Mortality statistics indicate that, on the average, a U.S. resident has about 1 chance in 1,000 of dying between the ages of 20 and 21. Deduce the MTBF hours for 20-year-olds. Convert this figure from hours to years. What does this MTBF tell you about the expected lifetime of a 20-year-old?
      hours in a year multiplies divided by 1/1000. covert it to years.  The MTBF is 1000 years
      it tells us that if we stay 20 years old for 1000 years we are expected to fail. Tells us nothing
      .
      -  The manufacturer guarantees a 1-million-hour MTBF for a certain model of disk drive. What can you conclude about the number of years for which one of these drives is under warranty?
		
      dwadwa
15.  Discuss the reasons why the operating system might require accurate information on how blocks are stored on a HDD disk. How could the operating system improve file-system performance with this knowledge?
