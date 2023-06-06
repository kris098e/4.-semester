# 1
## Describe the concept of overriding
#overriding when a derived class implements its own logic of an already existing method in the superclass, such that there only exists one method with this overridden function in the derived class, instead of what exists in the parent.

## Describe the concept of overloading
#overloading
When a class has multiple methods with the same name, but they vary in the argument types or then number of entries or the ordering of the arguments or the return time

## What does it means that a method is virtual? Has Java virtual methods?
#virtual means that you specify which method may be overriden, i.e specifying if the derrived classes can override the inheritted method or not. Java has this, static methods may  NOT be overriden and every other method may be overriden

## Consider the following C++-like pseudo-code language allowing the usage of virtual methods by using the virtual keyword

``` java
class Base {
public:
	void NonVirtual() {
		write("Not virtual");
	}
	virtual void Virtual() {
		write("Not virtual");
}
}
class Derived : public Base {
public:
	void NonVirtual() {
		write("Derived not virtual");
	}
	void Virtual() {
		write("Derived virtual");
	}
};
int main() {
	Base a = new Base();
	Base b = new Derived();
	
	a.NonVirtual(); // "Not virtual"
	a.Virtual(); // "Not virtual"
	b.NonVirtual(); // "Not virtual"
	b.Virtual(); // "Derived virtual"
}
```
What does this code print when main is executed? Please explain why.
The methods that are marked as virtual can be overridden, the  methods not marked as virtual cannot.

Virtual methods mean that when using the method, we use the **dynamic lookup** for finding the function, instead of the static lookup. I.e here b also has the base type `Base` but the virtual method uses the **dynamic lookup**. We could make it print both of the methods in `Derived` if we make a new `c` by `Derived c = new Derived()` which only has the methods for Derived
# 2
## Describe what an activation record is.
#activation_record an activation record is used when calling a procedure/function, to store the values necessary for giving the control back to the caller, and also holds information for the variables needed. It holds a pointer to the previous activation record, which is where to return control to, actual parameters for the function, local variables/temporary variables and intermediate results in the function, where to store the result of the function, and a static chain pointer for where to look if using static scope. 

## Describe what a dynamic chain pointer is
#dynamic_chain_pointer is used to access the previous activation record, stored in the activation record. This is used when using dynamic scope for finding which variables to use in the procedure, and also for which activation record to continue with when returning from this procedure.

## What do we mean with static memory management?
#static_memory_management
The memory is assigned in compile time, i.e after the program is compiled into an executable no change to memory specification can be made dynamicly in the program. It is generally faster since there will be no overhead of memory allocation and deallocation during the executing, since everything involving memory management is done at startup. However of course it is unflexible, and if the memory usage cannot be determined at compile time, the compiler will have to guess. If the memory is too big it will lead to internal fragmentation, and if it guesses to low, the program may finish with undefined behaviour or will simply not execute

## In what conditions a static memory management is not enough to implement an interpreter or compiler for a language? Explain why.
When using recursive behaviour of functions. The amount of recursive calls can maybe not be determined at compile time, especially if the program takes in user input. This will lead to need for dynamic memory management

Too large structs or arrays
if there are user-input, the input may be too large, if not predefined the size of the input

# 3
## Name at least two conditional commands and describe what they do
`if`-statement will execute the code in the if-block only if a condition is fulfilled.

`switch`-statement will only execute the code in the case that it matches the condition.

## What is a tail recursive function?
#tail_recursion A tail recursive function is where, in a recursive function, the last operation done is the function call. This may lead to the ability of the compiler or interpreter to reuse the current stack-frame/activation record to execute the function again, since it does not need to store additional data. fx

```java
int sum1(int n) {
	if (n == 0) return 0;
	return n + sum(n-1);
}

int sum1(int n, int acc) {
	if (n == 0) return acc;
	return sum(n-1, acc + n);
}
```
if the first is executed with 3 it will be
```math
3 + sum(2)
3 + (2 + sum(1))
3 + (2 + (0))
3 + 2
5
```

instead of
```math
sum(3, 3)
sum(2, 5)
sum(1, 6)
```
I.e the program can begin the calculation right away instead of using additional stack-frames to store the intermediate result

## Provide the pseudo-code of a tail recursive function that computes the factorial of a positive integer (i.e., n! = n ∗ (n − 1) ∗ (n − 2) ∗ . . . ∗ 1).
```java
// precon: acc = 1 when called from outside the function
int fact(int n, int acc) {
	if n == 1 return acc;
	return fact(n-1, acc*n)
}
```

## Explain why a tail recursion function can lead to performance gains compared to a non tail-recursive function.
look at question b. And dont have to make additional activation record

# 4
## Describe the notion of closure. What is it used for?
#closure s are used to capture an environment, of variables and values, which is used when we want to pass functions as arguments and return functions in a function.  Which variables should the passed function and or returned function use? There are two methods, **deep binding** and **shallow binding** which will be explained in the next question

## Describe what deep binding and shallow binding are
#deep_binding the passed function or returned function uses the environment from where it is created. This is done via closures, capturing the environment and using the variables from where it is created. It uses the scope of where the function is defined
#shallow_binding the passed function or returned function uses the environment from where it is called. Where closures are used.  I.e it uses the scope of the where the function is called.

When returning a function it also needs to capture the activation records indefinetly or until there is no longer a pointer to the returned function, since it may use out of scope variables when the function has returned. 

## With static scoping, can we use deep biding, shallow binding, or both? Why?
#static_scoping
Static scoping most often is seen in the context with deep binding, however there are some crafted examples where static scoping with shallow binding will provide different results than with deep binding.

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
		int z = g(f); // f is binded such that x = 7 here, since we use dynamic scoping. Would be 0 if using static scoping
		write(z); // 10
	}
}
```
Remember that when using dynamic scope, it is first binding when calling the function with the function.
[[_07_procedures.pdf#page=24]]

