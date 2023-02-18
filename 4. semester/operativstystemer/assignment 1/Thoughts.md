*When connecting to ssh via VScode, just type krabr21@imada0.stud-srv.sdu.dk, and dont add the ssh infront*

Get errors when compiling since the .h files cannot be found
[can be that we should not compile the file, but only add it to the makefile as here](https://imada.sdu.dk/u/daniel/DM510-2023/system-call/#:~:text=asmlinkage%0Aint%20sys_hellokernel(%20int%20flag%20)%20%7B%0A%20%20printk(%22Your%20kernel%20greets%20you%20%25d%20times!%20%5Cn%22%2C%20flag)%3B%0A%20%20return%200%3B%0A%7D)
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
* . **remember to include the dm....  .o into the makefile**
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

