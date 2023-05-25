# Chapter 17
1.  (**very important**) What are the main differences between capability lists and access lists?
    capability list: the permission are stored at the user
    access list: the permissions for each user is stored at the file
    
    
2.  A Burroughs B7000/B6000 MCP file can be tagged as sensitive data. When such a file is deleted, its storage area is overwritten by some random bits. For what purpose would such a scheme be useful?
    Dont want the sensitive data, since there is a reason why we have deleted it in the first place. Want it to be random bits, since if we overwrites it with the same sequence or same bits, it can be exploited such that maybe there will be stored a sensitive data file again there or right next to the region of the overwritten bits
    
    
3.  (**important**, repetition)In a ring-protection system, level 0 has the greatest access to objects, and level n (where n > 0) has fewer access rights. The access rights of a program at a particular level in the ring structure are considered a set of capabilities. What is the relationship between the capabilities of a domain at level j and a domain at level i to an object (for j > i)?
   When at j you have less capatabilities than when at level i
   
    
4.  The RC 4000 system, among others, has defined a tree of processes (called a process tree) such that all the descendants of a process can be given resources (objects) and access rights by their ancestors only. Thus, a descendant can never have the ability to do anything that its ancestors cannot do. The root of the tree is the operating system, which has the ability to do anything. Assume that the set of access rights is represented by an access matrix, A. A(x,y) defines the access rights of process x to object y. If x is a descendant of z, what is the relationship between A(x,y) and A(z,y) for an arbitrary object y?
    z has more or equal the rights of x
    
    
5.  What protection problems may arise if a shared stack is used for parameter passing?
    There may occur some race-condition, which will result in undefined behaviour. Then a function does not know if the variable on the stack is what it is supposed to do, and it can do something on this data that it should not
    
    
6.  Consider a computing environment where a unique number is associated with each process and each object in the system. Suppose that we allow a process with number n to access an object with number m only if n > m. What type of protection structure do we have?
    hierarchical structuring, the ones with big n can access a lot. If we want to make changes we have to change the PID which will result in clashes and a lot of chaos
    
    
7.  Consider a computing environment where a process is given the privilege of accessing an object only n times. Suggest a scheme for implementing this policy.
	 add a counter to the object. Can add it to the object or the domain, can add it to the file struct with an array of counters and users. 
   
    
8.  If all the access rights to an object are deleted, the object can no longer be accessed. At this point, the object should also be deleted, and the space it occupies should be returned to the system. Suggest an efficient implementation of this scheme.
    Garbage collection, reference count, when no one has access it is garbage collected. The counter should be atomic
    
    
9.  (**important**) Why is it difficult to protect a system in which users are allowed to do their own I/O?
if the user can themselves go right into the harddisk. I.e can say you want to get a specific place in harddisc

If we can go right to hardware, then we have to implement the security at hardware level instead of operating system level. Which is harder. When the user can do more, it is harder to secure

When we go to hardware, we usually do it through kernel-mode, i.e we have to be privileged

1.  (**important**) Capability lists are usually kept within the address space of the user. How does the system ensure that the user cannot modify the contents of the list?
   The user accesses the capbility list indirectly, it is a protected object. It is a special file which the user cannot access. Should be in kernel-mode to access it.
   
    
2.  The access-control matrix can be used to determine whether a process can switch from, say, domain A to domain B and enjoy the access privileges of domain B. Is this approach equivalent to including the access privileges of domain B in those of domain A?
    No, since domain A and B may have different privileges. If you are at domain A and switch to B, you may not even be able to go back to domain A

3.  What hardware features does a computer system need for efficient capability manipulation? Can these features be used for memory protection?
    Can store the files in a format such that we know where the capability
    Can have a tag on the file which stores the capability.
    
    
    
4.  Discuss the strengths and weaknesses of implementing an access matrix using capabilities that are associated with domains.
    It is the users responsibility to present the credentials instead of going through the entire access list
    It is quicker to copy the permissions, since we dont have to go through all file
    
    If we have an entire group it is harder to revoke all the accesses instead of just removing the group from the file
    The users a located somewhere in the system, where we have to find these first before we can revoke them
    
    
5.  (**important**) What is the need-to-know principle? Why is it important for a protection system to adhere to this principle?
   The user only gets to know what it needs to know, and nothing else. If the user can get access to something it does not need to know, it can do something with it, which is should not
   
    
6.  Describe how the Java protection model would be compromised if a Java program were allowed to directly alter the annotations of its stack frame.
    If we have a program that should not be able to execute something privileged, but it does get it either way, then it can do anything it wants.
    
    
7.  (**important**) How does the principle of least privilege aid in the creation of protection systems?
   Think about domains, should only be able to access need-to-know. Basicly just need-to-know
   
# chapter 18

1.  (**important**) Describe the three types of traditional hypervisors.
    it is virtual machine managers
    
    0: the VMM is in the firmware. When booting, we can only boot virtual machines
    1: The VMM is integrated into the operating-system, the operating system boots different virtual machines. The operating system **is** the combination of these booted operating system. fx WSL, can access the main operating system, windows
    2: Software we download, that is a VMM. fx virtual box
    
2.  (**important**) Describe four virtualization-like execution environments, and explain how they differ from “true” virtualization.
    **emulators**: translate the instructions to the machine code which the main operating system understands
    **paravirtulization**: virtual machine knows that it is running on a host, which can then optimize some of the instructions. It knows it is not running on native hardware. It can make better ways down to the original hardware
    **programming environment virtualization**: optimized for different programming languages, fx JVM. We dont virtualize the hardware.
    **application containment**: Virtualize a process. The process then thinks it is the only programming running
    
    
3.  (**important**) Why are VMMs unable to implement trap-and-emulate-based virtualization on some CPUs? Lacking the ability to trap and emulate, what method can a VMM use to implement virtualization?

	**it is called binary-translation**
    When the CPU can put the process to sleep and emulate some of the instructions it has given. We use trap-and-emulate to act as kernel-mode. The VM will trap the hosting operating-system and emulate the instructions it was given.
    
    Some CPUs dont have that much difference between what is privileged and what is not. If it does not know much about the kernel-mode, then it has a hard time knowing what to do. **workaround** the VM has a bit to know if it is in kernel-mode. The VM can just tell the CPU to execute the instructions either way, since it does not know about kernel-mode and user-mode. The VM then becomes the one that tells if it is okay to execute the instructions or not, since the native-CPU can just execute them either way.	   
    
    
    The CPU does not know when to change from kernel-mode to user-mode and vice versa. The VM does itself have to tell if the instruction has to be run in kernel-mode or user-mode
    
4.  (**important**) What hardware assistance for virtualization can be provided by modern CPUs?
    The CPU has a bit that tells if the VM is in kernel-mode or in user-mode
    The CPU also has a bit telling if the CPU is executing for the VM or the hosting operating-system
    As a VM cannot just make I/O, there are special pipelines to the I/O to the hosting operating system to make I/O. a I/O pipeline
    Seperate pipeline for interrups and traps
    
    The main bottleneck is the CPU and I/O
    
    
5.  (**important**) What is docker? What is a docker image? What is a docker container?
    Lightweight VM
    
    
6.  (**important**) What is a unikernel?
mini-kernel. Compile a small kernel with the operating system we want, with some added applications/drivers. Bare minimum back-bone for a kernel   
   