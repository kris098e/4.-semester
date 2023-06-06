# Function lookup
To find out which function is used, if type casting to a parent class, it still uses the derrived class.

If having a super class, but and putting this to be equal to an instance of the derived class, it uses the child classes method, but it only knows about the methods which it itself has. Uses dynamic lookup, or vtable for this to be possible.

![[Pasted image 20230606131416.png]]

# Abstract machines
(Abstract Machine) Assume that we are given a programming language, L . An abstract machine for L , denoted by M L , is any set of data structures and algorithms which can perform the storage and execution of programs written in L.

Typical abstraction of this is the physical computer

Can be realized in
+ hardware
+ firmware
+ software
![[Pasted image 20230606123334.png]]


# Late binding
fx used in inheritance, where the class inherits a function, i.e it does not have its own implementation of the function but gets it from its parent. At runtime the function is found by looking into the vtable.

# type equivalence
name: two types are the same if they have the same name
```java
type A b = c;
type A l = d;
```
 here b and l are of the same type.

if using weak equivalence by name

```java
type A = record ... end
type B = A
```
Here A and B are the same if using weak equivalence, since B is just an alias of B

structural is if two types has the same structure
**example**

# Pointer reversal in garbage collection
Since memory is low, we want to use as little memory as possible when traversing the objects. therefore, for `pointer-reversal` the needed storage is:
For this to work, pointers to the current node and its parent must be stored, but just these two needs space on the stack. We need the pointer to the pointer to the parent of the node as well since if we want to update the pointer from the child to the parent, we must also have a pointer to the parent. If we update the child to point to the parent before having a pointer to the child-node then we lose the information on the child node.

# Display
## c
Can access the element at the k'th level in constant 2 times, if we know that we need to access an element which k levels above this nested block. 
		* Works in the way that each time we enter a nesting a new pointer is created to this block. I.e the k'th entry in this table of pointers to the nestings, points to k'th nesting. However when we enter a new block in the same k'th nesting level, the pointer must then also be updated. 
		* The backtracking pointer is used since when popping of the activation record for this procedure, we then know which activation record should be activated again, which is the one that called the procedure.

It brings advantages in the form of speed,  I.e we can lookup the k'th level of backtracking in constant time, if we know which level holds this variable that we seek. If using static we would have to follow the static chain pointers k times, i.e it is linear time. 

More advantages???

# interpreters and compilers
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

# Describe what deep binding and shallow binding are
#deep_binding the passed function or returned function uses the environment from where it is created. This is done via closures, capturing the environment and using the variables from where it is created. It uses the scope of where the function is defined
#shallow_binding the passed function or returned function uses the environment from where it is called. Where closures are used.  I.e it uses the scope of the where the function is called.

When returning a function it also needs to capture the activation records indefinetly or until there is no longer a pointer to the returned function, since it may use out of scope variables when the function has returned. 

# In what conditions a static memory management is not enough to implement an interpreter or compiler for a language? Explain why.
When using recursive behaviour of functions. The amount of recursive calls can maybe not be determined at compile time, especially if the program takes in user input. This will lead to need for dynamic memory management

if there are user-input, the input may be too large, if not predefined the size of the input

## b
The heap is where a process can allocate memory within the given process-address-space. This can be done dynamicly, where if a program needs to store a variable, it can allocate space for it and can then also free this memory when it is not needed anymore. A variable can be whatever data structure is specified.

Main purpose is the variable size objects,  not FIFO life and when the program can allocate memory during runtime fx having pointers.

If kept on the stack we have memorize where the specific variable is on the stack if we want to move around, and free something.
The stack is also mostly used for temporarily kept values, i.e fx for local variables which are popped after the function returns

## c
When using recursive functions. Since the implementation of activation records uses a stack-structure, which has a finite amount of space, if it cannot be determined from a non-runtime environment how many activation records are pushed onto the call stack, then the execution may run into `StackOverFlow`, since it may push too many activation records on the stack. This is where the activation records can also be stored on the heap, providing additional memory.

Large data structures and arrays may not be stored on the stack, since the stackframe is a fixed size.
When taking input from a user.

# What an activation record contains
1. local variables

2. intermediate results

3. parameters

4. dynamic chain pointer

5. static chain pointer

6. return address for the result

7. return address for which to give control back

  

1. intermediate results

2. local variables

3. dynamic chain pointer


# Exceptions
## Please describe how exceptions can “naively” be implemented by using the the stack and activation records.
**Another approach is to put each exception handler on the stack, popping one for one the exception handler checking if the handler matches the exception, which will then give control back to block which it may point to. If not it just terminates like the example above**

## Describe one limitation of implementing exceptions by using only the the stack and activation records.
We expect that exceptions are rare, such that we dont want  this extra overhead of memory.
And also if a block does not call another function it does not need to be put on the stack of activation records, but if we want to store the exception handler on the stack then it has to be put on the stack

## Write two pseudocode programs showing an example of cast and an example of coercion (max 3 lines each). Explain what an interpreter would do when processing your pseudocode programs.

```java
String b = "hej";
Object k = (Object)b;
```
it will store value B as a string
it will attempt to convert b into an object and store it as an object in k.

```python
x = 2 + int(2.3)
```
It will try to cast 2.3 to an int, rounding down or up based on the rules
then evaluate the expressions with 2 ints, using the addition function in use.
lastly it will assign it to x.

```python
x = 2 + 2.3
```
it will evaluate the expression and coerce the final result type from the two result, based on the fact that the addition between these two have to be the same type, capturing as much information as possible thereby promoting the int 2 to a float

## Why are side effects important? What are their pros and cons?
It is important to be able to make more flexible programs, bringing a programs state forward to where the programmer wants it to go.

Most of the times side effects are undesirable since it often introduce complicated programs, since it fx is hard to see how many times the function is called if some conditions are used. They can introduce bugs, since it is hard to keep track of this global variable

However if used responsibly it can make a programmers life easier, fx. introducing a global count-variable, where each function call will increment this count as a side-effect. Logic could then be implemented around this side effect

**Key idea in imperative programming, a key idea in function programming not to have this
I.e in imperative programming, we are not ensured that the function will be pure, and they are always pure in functional programming**

# Polymorphic type system
A polymorphic type system is a type system that allows values to have more than one type. In other words, **a polymorphic type system allows a single function or variable to accept or work with values of different types.**

There are two main forms of polymorphism in type systems:

1. **Parametric polymorphism**: This is a form of polymorphism in which a function or data type is generic and can operate on values of different types. This is often achieved through the use of type variables. For example, in the programming language Java, the ArrayList class is a parametrically polymorphic data type, allowing it to store elements of any type. They can then work with infinitely many types

THIS MEANS THAT FUNCTIONS AND TYPES CAN WORK WITH MORE TYPES. I.e **Generics**


2. .**Ad hoc polymorphism**: This is a form of polymorphism in which a function or operator can have different implementations depending on the types of its arguments. This is often achieved through the use of overloaded functions or operators. For example, in the programming language Python, the '+' operator is ad hoc polymorphic, allowing it to perform addition on different types of values such as integers, floats, and strings.
Overloading, specifying how the function should work with specific types.

Polymorphic type systems can make code more flexible, modular, and reusable. They can also help catch errors at compile time by ensuring that functions and variables are used only in ways that are compatible with their defined types.

### Subtype polymorphism
Having super classes and extending classes. The extending classes can then be used like it is the superclass.

# A-list
**Remember it is not just the x which we are putting in the A-list. It is every variable**.
![[Pasted image 20230531104302.png]]
Where the first x is 6 and the 2nd is 2. The out of scope x is not taken into consideration in the A-list, as it would be wasted memory to keep track of this aswell.

# Virtual
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

When using dynamic lookup we are forced to look into the v-table.


# Type-safety
Refers to the contravariant and covariant problems of the functions.
Java only overrides if the arguments are the same, else it overloads the methods. All java-programs will actually compile, since it will just either override or overload.

All classes in C++ are static unless it has virtual modifier, and vice versa in java.

# 4 202208
## a
Since when using call by name and there are name clashes, it uses the variable found in an outer scope. i.e in the function it will use the outer `i` when x is used, since there are name clashes.

Equivalent of asking formal parameter evaluated in the
environment of the caller
[[_07_procedures.pdf#page=16]]

```java
int i = 1;
int [] A = new int [5];
void fie (name int x, name int y) {
	int i = 3;
	x = x+1; // outer i = 2
	y = 1; // A[2] = 1
	A[i] = 3; // A[3] = 3
	A[A[i]] = 4; // A[3] = 4
}
for (j = 0; j <= 4; j += 1) {
	A[j] = 0;
}
fie(i, A[i]);
write(A[1]); // 0
write(A[2]); // 1
write(A[3]); // 4
write(A[i]); // A[2], 1
```

# Types
The two rules are 
### structural equivalence
The two types are the same if they have the same structure. This means that
```java
class Wine {
	int year;
	int age;
}

class Student {
	int age;
	int year;
}
```
the two classes are equivalent if comparing by structural equivalence.  Since they look the same in memory, i.e having 2 ints and just that.
![[Pasted image 20230531095946.png]]

### name equivalence
Two types are the same, if they have the same name. So if we have two ints, they are of the same type, and they are the same type. Comparing String and int will then of course be evaluated to false.


# Side-effects
## Why are side effects important? What are their pros and cons?
It is important to be able to make more flexible programs, bringing a programs state forward to where the programmer wants it to go.

+ complicated
+ introduce bugs most of the time
Most of the times side effects are undesirable since it often introduce complicated programs, since it fx is hard to see how many times the function is called if some conditions are used. They can introduce bugs, since it is hard to keep track of this global variable

However if used responsibly it can make a programmers life easier, fx. introducing a global count-variable, where each function call will increment this count as a side-effect. Logic could then be implemented around this side effect

**Key idea in imperative programming, an key idea in function programming not to have this
I.e in imperative programming, we are not ensured that the function will be pure, and they are always pure in functional programming

# Vtable
Virtual Function Table, i.e it does not contain all of the variables but only the functions. If a function has been overriden, the vtable only contains one entry for the function 

# Display
When drawing the display, remember the back pointers to the block within the same nesting. look at
[[mockup_exam_answers.pdf#page=2]]

# Mark and compact
does not just require two times over the heap, requires multiple scans over the heap. That is, 1 for marking, 1 for computing the positions where the blocks will be moved to be contigous, 2nd update the internal pointers to the objects, and third actually moving the objects.

# Type compatability
The types are the same but has different formal definition. Meaning that if a and b both have the type C, they are formally different but are considered to be the same if not looking at the stored data. **two types are the equivalent if they formally different but can be considered interchangeable**

type compatability is when a type can be used anywhere another type can be used. This does not go both ways. I.e a subtype can be used where a supertype is needed, but not the other way around.
read [[mockup_exam_answers.pdf#page=5]]

# 4th chapter
## Denotable objects
denotable object is the object itself. I.e if we have a pointer to somewhere that lives in memory or the stack, the actual thing living in main memory or the stack is the denotable object. We can then have references to it after it is freed or popped from the stack, which means the reference lives longer than the object itself. If we have two pointers to the same thing, and one is removed after a function call then the object lives longer than the reference to it, since we now only have 1 pointer to it.

## dynamic scoping
remember that the variables still have to be in scope. I.e if we call a function and the function defines some variable, then when the function has returned it is no longer in the activation records and the variable it had defined becomes out of scope. This means that we dont alter the new variable in the previous function, but something in the scope of the caller to this function. **look at question  2 in the answers to problems 4th chapter**

12. State what will be printed by the following fragment of code written in a pseudo-language which uses static scope and call by reference.
    
```C
{int x = 0; // First updated to 1 & 2
int A(reference int y) {
	int x = 2;
	y = y + 1; // Global x is set to 1 & 2
	return B(y) + x; // global x = 2 -> y = 1 -> Return 13 + 2 = 15 & y = 2 -> Return 4 + 2 = 6 -> Returns 15
}
int B(reference int y // y = 1 & y = 2){
	int C(reference int y){ // y = 1
		int x = 3;
		return A(y) + x + y; // y = 1 & A(1) = 6 + 3 + 2 = 11
	}
	if (y == 1) return C(x) + y; // x = 1, y = 2 when used c(1) = 11 + 2 -> return 13
	else return x + y; //x = 2 & y = 2 -> return 4
}
write (A(x)); 
}
```
Here we assume that we first evaluate the first side of an expression and then the next. `C(x) + y` is called, y = 1, however `C(x)` changes `y=2`. which means we end up using `y=2`.

Write: 15

# 5th chapter
**it seems that the functions activation records are not popped from the stack when they have finished executing. Fx look at below problem. p3 can still point to the activation record of p2 after it is done executing.**
 Consider the following program fragment written in a pseudo-language using static scope:
```c
void P1 {
	void P2 { 
		body-of-P2
	}
	void P3 {
		void P4 { 
			body-of-P4
		}
		body-of-P3
	}
	body-of-P1
}
```
## Draw the activation record stack region that occurs between the static and dy-namic chain pointers when the following sequence of calls, P1, P2, P3,P4,P2 has been made (is it understood that at this time they are all active: none has returned)
> _static-link_ : to the block (its activation record) that contains this block, **this can be known at compile time**
> _dynamic-link_ : to the activation record that was created before this

1. p1 has no pointers
2. p2 static pointer to p1 and  dynamic-link to p1
3. p3 static-link to p1 and dynamic-link to p2
4. p4 static-link to p3  and dynamic link to p3
5. p2 static link to P1 and dynamic link to p4


# chapter 6
Remember that when using static scoping we also use deep binding? However at the exam, explain what will be printed if it were shallow and deep binding just to be sure.
7. Say what the following code block prints. This code is written in a language with static scope and call by name. The definition of the language contains the following phrase: “The evaluation of the expression E1 ◦ E2 where ◦ is any operator, consists of 
   (i) the evaluation of E1; 
   (ii) then the evaluation of E2; 
   (iii) finally, the application of the operator ◦ to the two values previously obtained.”
```C
{int x = 5;
int P(name int m){
	int x = 2;
	return m + x; // 5++ + x -> 5 + 2
}
write(P(x++) + x); // 7 + 6 = 13
}
```
paste x++ into the expression. As it uses deep binding, or static binding, it uses the x that is in the scope of the caller, when passing `x++`.

# Chapter 10
When typecasting to a superclass of a class, it will still be using the original methods and the variables within this. However when accessing the variables, it will be using the super.

![[Pasted image 20230529141903.png]]
```java
class test {
    public static void main(String[] args) {
        A a = new A();
        B b = new B();
        a.hello();
        b.hello();
        a = (A)b;
        a.hello();
        System.out.println(a.x);
        System.out.println(b.x);
    }
}

class A {
    int x = 2;
    void hello() { System.out.println("Hello"); }
}
class B extends A {
    int x = 4;
    void hello() { System.out.println("Bonjour"); }
}
class C {
    void hello() { System.out.println("Hola"); }
}
```
