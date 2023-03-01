*When connecting to ssh via VScode, just type krabr21@imada0.stud-srv.sdu.dk, and dont add the ssh infront*

# _kommet til concurrency_ der er noget der ikke helt fungerer, stacken bliver ikke opdateret korrekt? (prøv at flytte local_irq... til at blive større). 

# Overall thought: ensure the user are not allowed to make mistakes, guide the process via errors

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

