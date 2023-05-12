# Chapter 15

1.  (**repetition**) Explain how the VFS layer allows an operating system to support multiple types of file systems easily.
   > Virtual File System, not implemented in the kernel how the file system is supposed to work. The regular calls to fx  open, read ... are just forwarded to the implemented VFS which is mounted .
   > Abstraction
    
	We just have an interface for which methods can be used
    
2.  Why have more than one file system type on a given system?
    > fx can have ondedrive or google drive, the regular file system ...
    
    Different features for each file system, some may be implemented such that they are faster and some may be implemented to use less space, some may have error correction ...
    
     
3.  On a Unix or Linux system that implements the procfs file system, determine how to use the procfs interface to explore the process name space. What aspects of processes can be viewed via this interface? How would the same information be gathered on a system lacking the procfs file system?
    
    Be able to look at information about each process.
    procfs, i.e the `/proc`-folder  is mounted onto the file system such that it lives in main-memory, and all the files does not exist on the file-system/disc.
    
	If it didnt exist we would need another infterface, fx. make new system calls to retrieve information 
    
4.  Why do some systems integrate mounted file systems into the root file system naming structure, while others use a separate naming method for mounted file systems?
    > all the regular mounted file systems mounts on root file system
    
    could have another way to mount it, i.e not using `/` as prefix and go into the mountpoint. It could fx be in windows where it could be a network file-system, such that they are seperated from the regular file-system
    
5.  Given a remote file access facility such as ftp, why were remote file systems like NFS created?
    > both are remote file systems
     
	Better to have the files on the regular file system (work on them like if they were on the computer), instead of having to connect to some server first and fetch what we want to work on    
    
6.  (**important, specifically (b)**) Given a mounted file system with write operations underway, and a system crash or power loss, what must be done before the file system is remounted if: (a) The file system is not log-structured? (b) The file system is log-structured?
    
    a. if we have done something and it is not written to mounted file system, then it has to check the state. Fx if something is freed, and it does not know it is freed.
    
    b. just write all changes that has been logged and not written to the file system, and then run from there. If It were in the middle of something without it got to write to the log, then there may still be some flaws.
    
7.  Why do operating systems mount the root file system automatically at boot time?
    
    Convience such that we dont have to ourself mount it.
    Something in the root file system may be crucial to be started when booted. 
    Sometimes the boot may be living in the actual root-filesystem.
    
8.  (**important**) Why do operating systems require file systems other than root to be mounted?
    no reason to mount something that we dont need
    security, one user may mount something it needs, while another user should not have access to it. 


# Chapter 16

1.  (**important**) Buffer-overflow attacks can be avoided by adopting a better programming methodology or by using special hardware support. Discuss these
    Write proper code, such that it isnt allowed to write more than the buffer size
   > Use something such that we cannot execute something on the stack.
     
    
2.  (**important**) What is the purpose of using a “salt” along with a user-provided password? Where should the salt be stored, and how should it be used? 
	salt is a random that is put into the password, such that if we have the same password for two application, it will have different hashes.  I.e it is concatted with the password. It should be stored next to the hashes. The salt does not need to be a secret.
    
    
3.  (**important**) An experimental addition to UNIX allows a user to connect a watchdog program to a file. The watchdog is invoked whenever a program requests access to the file. The watchdog then either grants or denies access to the file. Discuss two pros and two cons of using watchdogs for security.
    
    Watchdog is just kind of like permission checking. Could be controlled more centrally, fx can be for an entire company. Could control which time it is allowed to be opened.
    
    cons may be that it could be hacked, i.e security should be in place. The watchdog i centralized such that it used for all computers in the company, it i will touch everyone if something happens to it. Also it may become slower this filesystem since it needs more checks, and maybe the watchdog is slower than regular checks.
    
4.  Make a list of six security concerns for a bank’s computer system. For each item on your list, state whether this concern relates to physical, human, or operating-system security.
    
5.  What commonly used computer programs are prone to man-in-themiddle attacks? Discuss solutions for preventing this form of attack.
    
6.  (**important**) Why doesn’t Dkd,N(Eke,N(m))���,�(���,�(�)) provide authentication of the sender? To what uses can such an encryption be put?
    
7.  (**important**) Mobile operating systems such as iOS and Android place the user data and the system files into two separate partitions. Aside from security, what is an advantage of that separation?