*When connecting to ssh via VScode, just type krabr21@imada0.stud-srv.sdu.dk, and dont add the ssh infront*
# https://www.quora.com/Why-do-we-need-Interprocess-Communications bec
# does anonymous pipes use kernel mode? does the named pipe?
**understood the problems:** When two processes wants to communicate, they can either use shared-memory, message-passing or pipes. Shared memory uses a shared segment of memory, using kernel-mode when creating the shared memory, and user space when accessing it. Message passing via mail-boxes has to use the kernel-level to store the messages somewhere in memory, where we can communicate with this mailbox via syscalls, I.e it has to use some created memory, that is not in the specific processes that uses this memory for storing and retrieving messages. Pipes has two options: anonymous and named. Anonymous pipes are used to pipe data into some shared memory file, where if the pipe is unidirectional, one end of the pipe is the write end, and the read is the read end of the pipe. in bidirectional pipes, both ends can be used to write and read. Named pipes can be used accross multiple processes, which doesn't have to be parent to child. They use a typical file, which is written to and read from. This then also includes entering kernel-mode when writing and reading, as we read and write to an existing file on the file-system, from different processes.


![[Pasted image 20230303115216.png]]

```
put
/**
   * **!!PUT MOST OF THIS TEXT IN THE REPORT!!**
   * 
   * begin the updating of the entire datastructure. Critical not to be interrupted.
   * i.e if check for bottom == NULL is true we enter the block, but are halted. another 
   * process checks the same condition, executes the code, and the same code is executed
   * in the interrupted process, then we lose a message.
   * Also in the else case, if msg->previous=top goes through, and we get interrupted before
   * we can execute top=msg, then another process might say top=(its process top), the interupted
   * process starts again, and sets its message to top.
  */
```

```
get
/**
   * As we only use interrupt handling for concurrency, and not synchronization on the stack,
   * I choose to disable interrupts for almost the entire function. This will decrease chances
   * of two processes getting the same message as fx top, freeing memory that is already freed
   * in another process...
   * 
   * the if statement is also contained in the interrupt disabled code, since, we first enable
   * it after we enter the if-statement-block then we could be interrupted right after getting
   * into the block, while another process could update top to be equal to null, which would
   * mean we are in invalid state, as the msg would be null. 
  */
```
# Overall thought: ensure the user are not allowed to make mistakes, guide the process via errors
Hereunder
* have chosen that if error occurs, we dont pass any message / put any message, as in my implementation this will be seen as an invalid state. If the copying encounters errors, it can be debugged based on how many bytes were not written
* Chosen that when touching the overall stack structure, we are not to be interrupted and other processes cannot access this code, if they run the same code. As this is only the concurrency of processes, it does not matter if we synchronize on the structure, as when interrupts are disable, mutual exclusion kicks in and no other processes cannot touch the structure, as the code updating the structure, is inside the critical region.


# cannot test for put too small length, as `copy_from_user` only writes how many bytes as length defines.

# get fails if too small buffer compared to buffer stored - `stack smashing`

# test put fail on allocating memory, by putting until no more memory for the process?



# man kan have null
# access_ok() kan man ikke få til at breake?

# use perror("")??

# ENOMEM?? skal denne bruges til memory fejl-allocate

### Thoughts
1. follow the guide for the sycall
2. REMEMBER TO UPDATE LIST FOR SOURCES
# updates 
* `arch/x86/include/generated/uapi/asm/unistd_64.h`
* `arch/x86/entry/syscalls/syscall_64.tbl`
	* `451	common	dm510_msgbox_put	sys_dm510_msgbox_put`
	* `452	common	dm510_msgbox_get	sys_dm510_msgbox_get`
* `arch/um/include/asm/dm510_msgbox.h` possibly wrong format? however i think this is just a header file to know what it is
* `arch/um/kernel/dm510_msgbox.c` remember to include the h file from the other folder?
* `arch/um/kernel/Makefile` 
## The function-names has to match `sys_dm...`, i am pretty sure, look at 
### implement 
1. Copy the code he has given
2. *REMEMBER TO CHECK FOR ERROR AND PARAMTERS*
3. Before reading or writing check if it ok to access memory
* writing to the buffer
	* use copy_to_user to copy the message, and use kfree to free this message.
	* remember to update the stack
* reading from the buffer
	* check message length and allocate memory (remember null byte)
	* allocate memory for new struct
	* use copy_from_user into the buffer
	* assign the message to the struct
	* put on top of stack
* 

