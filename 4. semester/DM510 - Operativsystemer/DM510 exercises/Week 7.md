Prepare for the Tutorial Session in Week 07 from Chapter 2 the following exercises

1.  What is the purpose of system calls?
	1. For processes to communicate
	2. Finde fejl i systemet
	3. For processorer kan kommunikere med hardware
	4. Interfacing between processes and the system
	5. example: fork, read write, open
2.  What system calls have to be executed by a command interpreter or shell in order to start a new process on a UNIX system?
	1. New process: Fork
	2. Clear for new process: Exec
	3. Wait till process has terminated: wait
	4. Like fork: Clone
3.  What is the purpose of system programs?
	1. Providing basic operation for using the operating system
	2. To execute specific tasks
	3. File manipulation
	4. Standard functionality
4.  What is the main advantage of the layered approach to system design? What are the disadvantages of the layered approach?
	5. Layered approach can be easier to understand
	6. If you change something it is easier to implement, and expect that the other layers works perfectly when changing one.
	7. Disadvantage: Slower
5.  List five services provided by an operating system, and explain how each creates convenience for users. In which cases would it be impossible for user-level programs to provide these services? Explain your answer.
		
```pdf
{
"url" : "Appendix DM510 - Operativsystemer/ch02.pdf",
"page" : 7
}
```

6.  How could a system be designed to allow a choice of operating systems from which to boot? What would the bootstrap program need to do?
	1. Bootstrap program: When the computer starts the bootloader must be started

7.  What are the advantages and disadvantages of using the same system-call interface for manipulating both files and devices?
	1. Pro:
		1. Portability
		2. Reduced complexity
		3. No need for system calls for many devices

	2. Con:
		1. Overhead
		2. Reading independently

8.  Describe why Android uses ahead-of-time (AOT) rather than just-in-time (JIT) compilation.
	1. It will run faster
	2. Energy efficient
	3. Less likely to fail or crash

9.  How are iOS and Android similar? How are they different?
	1. Same
		1. General characteristics (Energy sufficient)
	2. Different:
		1. Openness (Security, allowance)
		2. UI

10.  What are the two models of interprocess communication? What are the strengths and weaknesses of the two approaches?
	1. Shared memory model
		1. Controlling the shared memory (race conditions)
		2. Harder to implement
	2. Message passing mode
		1. easier to implement
		2. slower

11.  What is the main advantage of the microkernel approach to system design? How do user programs and system services interact in a micro-kernel architecture? What are the disadvantages of using the microkernel approach?
	1. Kernel has the bare minimum
		1. Process scheduling
		2. Memory management
		3. Communicating between processes (shared memory etc.)
	2. Pro:
		1. More security
		2. smaller system
		3. more reliable 
		4. more security
	3. Con:
		1. Overhead by communication through kernel

# Some more C programming exercises:

-   The following is the code to allocate memory for a 2-dimensional array of fixed size 8×8.

    ```C
    #include <stdio.h>
    int main() {
    int x;
    int y;
    int array[8][8];
    for ( x = 0; x < 8; x++ ) {
      for ( y = 0; y < 8; y++ )
        array[x][y] = x * y;
    }
    }
    ```

    -   Where in the memory is the matrix stored?
	    - It's stored in on the stack
    -   Provide the code for a variant of the code that allocated the memory dynamically.
	    
	 ```C
    #include <stdio.h> 
    #include <stdlib.h> 
    int main() { 
	    int x, y; 
	    int** array = (int**) malloc(sizeof(int*) * 8); 
	    
	    for (x = 0; x < 8; x++) { 
		    array[x] = (int*) malloc(sizeof(int) * 8); 
	    for (y = 0; y < 8; y++) { 
		    array[x][y] = x * y; 
		} 
	} 
	    // use the array... 
	    // free the memory 
	    
	    for (x = 0; x < 8; x++) { 
		    free(array[x]); } 
	    free(array); 
	    return 0; }
    ```
    -   Where is your dynamically allocated memory stored?
	    - In memory
_____
-   What is the output of the following C program?
i is 17
i is 18

```c
#include <stdio.h>

int main(int argc, char** argv)
{
  stupid();
  stupid();
  return 0; 
}

int stupid()
{
  static int i=17;
  printf("i is %d\n", i);
  i++;
}
```

____
-   Discuss the following C program, and put it in relation to the function declaration as found by the man page of the library function for sorting an array: `void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));`

	- The sorting is comparing elements. Can be used if wanting to compare something specific.
.

```C
#include <stdio.h>
#include <stdlib.h>

static int comp(const void * x, const void * y)
{
  int a = (int)(*(int*)x);
  int b = (int)(*(int*)y);

  if (a==b)
    return 0;
  else
    if (a < b)
        return -1;
    else
        return 1;
}

int main(int argc, char* argv[])
{
   int numbers[10]={1892,45,200,-98,4087,5,-12345,1087,88,-100000};
   int i;

  /* Sort the array */
  qsort(numbers,10,sizeof(int),comp) ;
  for (i=0;i<9;i++)
    printf("Number = %d\n",numbers[ i ]) ;
  return 0;
}
```

____
-   Discuss the result of the following C program. If possible, try it on different machines. In order to understand the results, find out what a sequence point is.
	- sequence point: ?
	- 
.

```C
#include <stdio.h>

#define SQR(a)((a)*(a))
#define CUB(a)((a)*(a)*(a))


inline static int cub(int x) { return x*x*x; }

int main()
{
        int x;

        x=3;
        printf("square? :%d\n",SQR(x));
        printf("x:       %d\n",x);

        x=3;
        printf("square? :%d\n",SQR(++x));
        printf("x:       %d\n",x);

        x=3;
        printf("cub?    :%d\n",CUB(x++));
        printf("x:       %d\n",x);

        x=3;
        printf("cub?    :%d\n",CUB(++x));
        printf("x:       %d\n",x);

        x=3;
        printf("cub?    :%d\n",cub(++x));
        printf("x:       %d\n",x);

        return 0;
}
```

-   Follow the C-tutorial for FILE I/O on [https://www.cprogramming.com/tutorial/cfileio.html](https://www.cprogramming.com/tutorial/cfileio.html) and answer the quiz questions.