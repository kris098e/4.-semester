![[201906.pdf]]
# exercise 1
As dynamic scoping is used, we use the  x which was on the most recent activation record. Therefore, the program will write 10 and 2. WE write 10 since the ... 
**look at the comments**
```c
{ int x = 2;
	void foo(value int y){
		x = x + y;  // 6 + 5. Uses the x at line 5.
	}
	{ int x = 5;
		{ int x = 7; // becomes out of scope immediatly after.
		}
	foo(x++); // x = 5. But rererences in foo() uses 6. 
	write(x); // x = 6 + 5
	}
write(x); // the only x in scope is the x at line 1. write 2.
}
```

if static scope is used: Uses the `x` which is in the current block, if not found it looks out another block (which contains this block) if it finds it here it stops, else proceed with the look ups.

```c
{ int x = 2;
	void foo(value int y){
		x = x + y; // x = 2 + 5
	}
	{ int x = 5;
		{ int x = 7; // becomes out of scope immediatly after
		}
	foo(x++);  
	write(x); // write 6, uses the x in the current block, but it has been incremented.
	}
write(x);  // 7, changed in the call of foo()
```

The A-list can be used to implement the dynamic scope rule, searching through the variables which are most recently created, given the current environment/activation-record-structure.
![[Pasted image 20230419082905.png]]
Where the first x is 6 and the 2nd is 2. The out of scope x is not taken into consideration in the A-list, as it would be wasted memory to keep track of this aswell.

![[201906.pdf#page=2]]
# exercise 2
partial evaluator is a program given D0 and D1 and outputs D2
$p:(D_{1}, D_{2})\to D_{2}$
![[Pasted image 20230510122700.png]]
see that we have an interpreter written in L1 to L2 and from L2 to L3, so apply the first interpreter and can input to the next one.  So we get from L1 to L3. I.e an interpreter from L1 to L3

I does not matter what the partial evalutor is written in, it just means that the computer uses L0, and can output something in L1


# exercise 3
**call by name** means that the actual parameter is being replaced by what it was textually called with / expanded to what it was textually called with. 
Call by value-result 
**call by value-result** means that the actual parameter is copied into the formal parameter, which is used in the body of the procedure. Upon return of the call, what was changed to the formal-parameter is assigned to the actual-parameter. 

The program with static scope and call by name will look like this
```c
{
	int x = 7;
	int w = 1;
	void fie(name int y,z){
		int x = 1;
		z = y + z + x; // w = (1+1) + 1 + 1 = 4
	}
	fie(x+w,w);
	write(w); // w has been changed, as z was expanded to w. w = 4.
}
```

call by value result:
```c
{
	int x = 7;
	int w = 1;
	void fie(value_result int y,z){ // y = 8, z = 1
		int x = 1;
		z = y + z + x;  // z = 8 + 1 + 1 = 10
	}
	fie(x+w,w);
	write(w); // w was changed to 10 by the call of fie, as w was assigned value of z in the return of the function.
}
```

# exercise 4
## stop and copy
Stop and copy is a garbage collection algorithm used in programming languages to manage memory. The algorithm is based on the idea of dividing the heap memory into two equal parts: the "from-space" and the "to-space".

The algorithm works by first allocating memory in the from-space for the program's data structures. As the program runs, it creates and destroys objects, leaving some of the memory unused. When the from-space becomes full, the garbage collector pauses the program and starts the copying phase.

During the copying phase, the garbage collector traverses the objects in the from-space, copying the live objects to the to-space. The garbage collector updates all pointers in the live objects to point to their new location in the to-space. When the copying phase is complete, the from-space is completely empty, and the to-space contains all the live objects.

After the copying phase is complete, the garbage collector swaps the roles of the from-space and to-space, making the to-space the new from-space. This process frees up all the unused memory in the old from-space and makes it available for use by the program.

Stop and copy is a simple and efficient garbage collection algorithm that avoids the fragmentation problems that can occur with other algorithms. However, it can be slower than other algorithms for large programs, as it requires copying all the live objects to a new location in memory.


## Mark and Compact
Mark and Compact is a garbage collection algorithm used in programming languages to manage memory. The algorithm is based on the idea of marking all the live objects in the heap memory and compacting them to eliminate any fragmentation.

The algorithm works in two phases: the marking phase and the compacting phase. During the marking phase, the garbage collector traverses all the objects in the heap memory, starting from the roots (e.g. global variables, program stacks), and marks all the live objects by setting a flag or adding them to a data structure called the mark set.

In the compacting phase, the garbage collector moves all the live objects to a contiguous block of memory, and updates all the pointers in the program to point to the new memory locations of the objects. This process eliminates any fragmentation in the heap memory and ensures that the program can allocate memory continuously without running out of memory.

After the compacting phase is complete, the garbage collector releases the unused memory in the heap memory, making it available for use by the program.

Mark and Compact is a powerful algorithm that can handle both short-lived and long-lived objects in the heap memory. However, it can be slower than other algorithms for large programs, as it requires moving all the live objects to a new location in memory.


## difference
Stop and Copy and Mark and Compact are both garbage collection algorithms used to manage memory in programming languages, but they differ in their approach to memory management.

Stop and Copy algorithm divides the heap memory into two equal parts: the "from-space" and the "to-space". During program execution, live objects are allocated in the from-space. When the from-space becomes full, the garbage collector pauses the program and copies all the live objects to the to-space. The to-space becomes the new from-space, and the old from-space is completely empty and available for new objects. This algorithm requires extra memory for the to-space but is efficient and avoids fragmentation.

On the other hand, Mark and Compact algorithm works by marking all the live objects in the heap memory and compacting them to eliminate fragmentation. During the marking phase, the garbage collector traverses all objects in the heap memory and marks the live ones. In the compacting phase, the garbage collector moves all the live objects to a contiguous block of memory, updates all the pointers in the program, and releases the unused memory. This algorithm is powerful but slower than Stop and Copy as it requires moving all the live objects to a new location in memory and updating all the program's pointers.

In summary, Stop and Copy is a simpler and more efficient algorithm that avoids fragmentation by copying live objects from one space to another. Mark and Compact, while more complex, eliminates fragmentation by moving live objects to a contiguous block of memory. The choice of which algorithm to use depends on the specific needs and constraints of the program being developed.


## pros and cons for stop and copy
### pros
* simpler
In summary, stop-and-copy is generally faster than mark-and-compact because it only needs to copy the objects that are still in use, whereas mark-and-compact requires the additional step of compacting the memory space. However, the choice of which algorithm to use may depend on other factors, such as the specific requirements of the application, the amount of available memory, and the nature of the objects being managed.

When compacting the memory space, it may need to store information, such that it does not overwrite is at the place of which is trying to move a object

### cons
Although stop-and-copy garbage collection is generally faster than mark-and-compact, it does have some potential drawbacks that may make it less desirable in certain contexts. Here are a few cons to consider:

1.  Space Overhead: Stop-and-copy requires double the memory of the program being garbage collected because it needs to maintain two areas of memory. This can be a significant limitation in memory-constrained environments.
    
2.  Fragmentation: The process of copying objects can lead to memory fragmentation, as the memory space can become divided into many small free blocks. This can lead to memory fragmentation over time, making it difficult to allocate large contiguous blocks of memory when needed.
    
3.  Pause Times: The stop-and-copy algorithm requires a pause in the execution of the program while the copying process occurs. This pause can be a significant problem for real-time systems, where even short pauses can be unacceptable.
    
4.  Inefficient for Large Objects: The stop-and-copy algorithm may be less efficient for large objects because it needs to copy them in their entirety, even if only a small portion of the object is actually in use. This can lead to wasted memory and increased copying times.
    

In contrast, the mark-and-compact algorithm does not have these drawbacks because it does not require double the memory, it avoids memory fragmentation, it can handle large objects more efficiently, and it does not have long pauses during its execution. However, it may be slower than stop-and-copy for small to medium-sized programs. Ultimately, the choice of garbage collection algorithm depends on the specific requirements of the application and the available resources.

## Final thoughts
For mark and compact the algorithm has to compact the memory, as it is only allowed to used the working memory for making the memory contiguous. This means that is has to compact the memory, taking extra caution of not overwriting memory. The compacting in the same memory space is what is making it slower than stop-and-copy, since stop-and-copy only needs to copy it onto some memory for which it can use all memory, not concerned with overwriting. Stop-and-copy also needs additional memory, most of the time **double** the amount of memory of what the process actually needs. Where mark and compact does not need the additional memory

![[201906.pdf#page=2]]

# exercise 5
example:
```java
class A {
	int x;
	void foo(int i) {}
}

class B extends A {
	int x;
	void foo(int  i) {}
}
```
Here `class B`  shadows the variable `x` in class `A` for which it inherits.  Meanwhile it also overrides the `foo()`-function, for which it also inherrits. Class B shadows the variable `x` in `Class A` since you cannot access the variable in `class A` without type casting an instance of `class B` to `class A` . It overrides the function, which also means that we have to type cast, to get the implementation in `class A`.  
Example of how to access it:
```java
B b = new B();
A a = (A) b;

a.x //access the shadowed variable
a.foo(2) // access the overriden method
```

The concept of `virtual` is implemented in `C++`. This means that it can be overridden.  If java were to implement it, it would something like this
```java
class A {
	void bar() {write("not virtual")}
	virtual void foo() { write("hello") }
}

class B extends A {
	void bar() { write("virtual") }
	void foo() { write("virtual") }
}

main() {
	B b = new B()

	b.bar() // will print out "not virtual". cannot be overritten.
	b.foo() // will print out "virtual". The method can be overwritten.
}
```