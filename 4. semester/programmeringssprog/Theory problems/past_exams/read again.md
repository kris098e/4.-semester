## In what conditions a static memory management is not enough to implement an interpreter or compiler for a language? Explain why.
When using recursive behaviour of functions. The amount of recursive calls can maybe not be determined at compile time, especially if the program takes in user input. This will lead to need for dynamic memory management

if there are user-input, the input may be too large, if not predefined the size of the input

## The following program is written using a pseudo-code. Assume that dynamic scoping is used. What does the following program write if shallow binding is used? Motivate the answer.

```java
{   
	int x = 0;
	int f(int y){
		return x+y; 
	}
	int g (int h(int b)){
		int x = 2;
		return h(1) + x; // in h x = 2, uses the environment from where the function is used. h(1) = 3. 3 + 2
	}
	{ 
		int x = 7;
		int z = g(f); // 
		write(z); // write 5
	}
}
```
Uses the environment from where the function is actually used.

## What does the previous program write if deep binding is used instead of shallow binding? Motivate the answer.
```java
{   
	int x = 0;
	int f(int y){
		return x+y; // x = 7, return 7 + 1
	}
	int g (int h(int b)){
		int x = 2;
		return h(1) + x; // 10
	}
	{ 
		int x = 7;
		int z = g(f); // f is binded such that x = 7 here, since we use dynamic scoping. Would be 0 if using static scoping since the x would be out of scope for the function call.
		write(z); // 10
	}
}
```
Remember that when using dynamic scope, it is first binding when calling the function with the function.
[[_07_procedures.pdf#page=24]]

# 1
## a
physcial machine is an implemented abstracted machine

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