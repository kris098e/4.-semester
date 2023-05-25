# 1
## a
(Abstract Machine) Assume that we are given a programming lan-
guage, L . An abstract machine for L , denoted by M L , is any set of data structures and algorithms which can perform the storage and execution of programs written in L.

I.e it is an abstraction of a physical machine, letting us focus on the software needing to be implemented leaving all thoughts about implementation of hardware and type of hardware out.

Different ways:
1. Realization in Hardware
2. Emulation or simulation via Firmware
3. Interpretation or simulation via Software

1 is always theoretically possible but
• Used only for low-level machines or dedicated
machines
• Maximum speed
• No flexibility

2: data structures and algorithms but realized by
micro-programs, residing in a read-only memory
• Microprogrammable (physical) machine
• High speed
• Greater flexibility than pure HW

3: data structures and algorithms of the abstract machine but
realized through programs written in the language of the
host machine
• Any Host machine works
• Less speed
• Maximum flexibility.

## b
The interpeter is used to execute and translate a specific language on the abstract machines. The interpeter is needed, such that the language written in a different language than what the abstract understands, it can be translated into the instructions the abstract machine understands line by line, which can then be executed. 

fetching, decoding and executing is what the interpreter does

## c
Interpetrers are easier to write, and usually requires less memory. It generates no intermediate files, i.e does not generate an executable. 
It keeps the overall structure of the program intact, i.e it does not optimize on the code, but executes the program line by line. Therefore the debugging may also be easier, since the program is not scrambled
It is generally faster to interpet a program than to compile it and then run it, since the compiler has to look at the entire source code to look for optimizations.

Interpreters uses dynamic type checking is more flexible. Fx
```java
In static checking
int x;
x = if true then 3 + 4 else "foo";
// is always rejected, while it is dynamically corrected
```

## d
The speed of a compiled program is faster, since it does not have to translate the source program machine code at runtime. The errors are caught when compiling the program instead of running some part of the code and then running into errors.  It is faster when ran multiple times, and the compiler can also optimize the code


# 2
## a
An activation record is used to have control over the sequence of procedure calls in a given program, holding information about which procedure called this one (where to return control when finished with this procedure), can trace back to which variables should be used in this subroutine/activation record, which address or register to return the result in, local variables, the actual parameters of this function, and also the intermidiate result.

If not a subroutine, and fx just an if-statement it only has local variables, intermidate result and dynamic-chain-pointer.

## b
The heap is where a process can allocate memory within the given process-address-space. This can be done dynamicly, where if a program needs to store a variable, it can allocate space for it and can then also free this memory when it is not needed anymore. A variable can be whatever data structure is specified.


If kept on the stack we have memorize where the specific variable is on the stack if we want to move around, and free something.

## c
When using recursive functions. Since the implementation of activation records uses a stack-structure, which has a finite amount of space, if it cannot be determined from a non-runtime environment how many activation records are pushed onto the call stack, then the execution may run into `StackOverFlow`, since it may push too many activation records on the stack. This is where the activation records can also be stored on the heap, providing additional memory.

Large data structures and arrays may not be stored on the stack, since the stackframe is a fixed size.

## d
The buddy system is a memory allocation method, where we start with a big block of memory with a size of $2^k$, and then when a block of size `n` is requested,the block is split into blocks of memory with size $2^{k-1}$, then one of the blocks is split into something of size $2^{k-2}$ until a block size is found such that $2^{m}\geq n>2^{m-1}$ where a block size of $2^m$ is used. When the block is not needed anymore, it is returned to the free-list where it will be merged with its buddy which is done in a recursive manner up, merging the new block with its buddy until this cannot be done anymore due to a blocks buddy being used or it reaches $2^k$ -size again.
**advantage** is compared to the static fixed sized blocks in the free list, it is possible to provide less internal fragmentation in the blocks due to better fitting. However as the fibonacci-method of controlling the block sizes can lead to smaller jumps in the sizes of the blocks, it may lead to less internal fragmentation, but will also result in more blocks being created than the buddy system due to the smaller jump it takes in block sizes, providing worse performance than the buddy system, but less internal fragmentation.

also helps with external fragmentation because they can be combined again.

# 3
## a
A type is a collection of values with operations to manipulate these values.

scalar type: int floats boolean chars
composite: combinations of scalar types

## b
They are equivalent when they have the same structure in memory. fx

```java
class K {
	int b,
	int a
}

class C {
	int a,
	int b
}
```
In memory they will have two ints right next to each other

## c
It uses structual equivalence

## d
The overall goal of the unification algorithm is to infer a consistent and unified type for each expression in a program. By analyzing the relationships and constraints between types, the algorithm aims to produce a type assignment that allows for correct and type-safe execution of the program while minimizing the need for explicit type annotations by the programmer.

# 4
