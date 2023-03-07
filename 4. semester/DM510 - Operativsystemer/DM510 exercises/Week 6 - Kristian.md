
# 1.  What are the three main purposes of an operating system?

1.  Ressource allocation 
    
2.  Memory control 
    
3.  Interface for users for running software on the hardware 
    

# 2.  What is the main difficulty that a programmer must overcome in writing an operating system for a real-time environment?
Making sure that all the strict deadlines for the calls are met. 

# 3.  Keeping in mind the various definitions of operating system, consider whether the operating system should include applications such as web browsers and mail programs. Argue both that it should and that it should not, and support your answers.
Some OS Doesnt really need it, like an embedded system such as a microwave. 

For: 

-   Software could be made specificly for the OS, which could be improve performance. (memory applicaiton, ressource allocation and such already defined) 
    
-   Most consumers just wants an application out of the box to interract with. 
    

Against: 

-   If not used the software would just be lying around 
    


# 4.  How does the distinction between kernel mode and user mode function as a rudimentary form of protection (security)?

User-mode doesnt have access to certain instructions for the kernel 

Kernel mode is privilieged, and can directly read memory and other hardware. Full control of the hardware, of what is allowed by the operating system- 

# 5.  Which of the following instructions should be privileged?
    -   Set value of timer.
    -   Read the clock.
    -   Clear memory.
    -   Issue a trap instruction.
    -   Turn off interrupts.
    -   Modify entries in device-status table.
    -   Switch from user to kernel mode.
    -   Access I/O device.
-   Clear memory: privileged 
    
-   Turn off interrups: privileged 
    
-   Access I/O device: priveleged 
    
-   Set value of timer: if it is to the schedular for a program then priveleget, but just setting a timer in a program shouldnt be ofc. 
    
-   Read the clock: non privileged 
    
-   Issue a trap instruction: application that should interrupt, not privileged such that a program can call to wait 
    
-   Modify entries in device-status table: privileged 
    
-   Switch to kernel mode: the call should not be, such that users can switch 


# 6.  Some CPUs provide for more than two modes of operation. What are two possible uses of these multiple modes?
-   Virtual machine mode, should be there such that it can have some privileges 
    
-   Kernel mode 
    
-   More users for the system, which can have different modes enabled/ different privileges 
    

# 7. Give two reasons why caches are useful. What problems do they solve? What problems do they cause? If a cache can be made as large as the device for which it is caching (for instance, a cache as large as a disk), why not make it that large and eliminate the device?
-   Problems 
    -   Fast memory access, store more than registres 
-   Volatile memory, doesnt store when turning off. If making it bigger you also make the distance larger from the cores 
    
-   Cache coherrence 

# 8. How do clustered systems differ from multiprocessor systems? What is required for two machines belonging to a cluster to cooperate to provide a highly available service?
Cluster system: every node can run different operating systems, one can turn off and one can still be on. 

Multiprocessor systems: use the same hardware, operating system and such. 

They should be able to communicate, if they cant assign other nodes assignments, then it doesnt make sense to have multiple others. If one goes down, then antother should be able to take over 

# 9.  (**important**) What is the purpose of interrupts? How does an interrupt differ from a trap? Can traps be generated intentionally by a user program? If so, for what purpose?
-   Interrupts: make sure that multiple processes can run "at the same time", one process doesnt take up entire cpu for its duration 
    
-   Traps: software based interrupts. For applications to interrupt, use them to make system calls ... 
    

# 10.  Direct memory access is used for high-speed I/O devices in order to avoid increasing the CPU’s execution load.
    -   How does the CPU interface with the device to coordinate the transfer?
    -   How does the CPU know when the memory operations are complete?
    -   The CPU is allowed to execute other programs while the DMA controller is transferring data. Does this process interfere with the execution of the user programs? If so, describe what forms of interference are caused.
1.  . 
    
2.  Make an interrupt to the CPI to let it know that is done 
    
3.  No dirrect interferrence with eachother, but they both have to access memroy. If DMA is accessing memory, then CPU has to wait, such that they make user programs slower 


# 11.  (**important**) Rank the following storage systems from slowest to fastest:
    -   Hard-disk drives
    -   Registers
    -   Optical disk
    -   Main memory
    -   Nonvolatile memory
    -   Magnetic tapes
    -   Cache

1.  Registres 
    
2.  Cache 
    
3.  Main memory(RAM) 
    
4.  Nonvolatile memory (fx ssd) 
    
5.  Hard drives 
    
6.  Optical disk 
    
7.  Magnectic tapes 
    

# 12.  Describe some of the challenges of designing operating systems for mobile devices compared with designing operating systems for traditional PCs.
Interface is differnet, ie touch screen. 
Bone is small, memory, battery efficiency, cpu 

# C programming
1.  4 
    
2.  3 
    
3.  1 
    
4.  3 
    

1.  2 
    
2.  1 
    

-   1 : true, remember when swapping when given two pointers, when you dereference the pointer, you are at the actual location. Therefore when given a pointer *m, you can put a new value in m by *m = 42 
    

-   2 : true, calloc just puts it on the heap. Again when dereferncing the pointer we are at the exact location of the variable, and we can swap the contents. 
    

-   3: false, as the pointers are copied when passing it to another functions, we dont change the actual pointers given at function-call-site. 
    
-   
-   4: true, here we are given a pointer to the pointer, such that the original pointer will be given when dereferincing the pointer to the pointer.  

Its a message passing system, where a stack is used. Memcopy is used to write into a buffer. Remember to check if the buffer given is large enough to contain the message.