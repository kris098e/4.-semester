# 1
## Describe in your own words what is an exception and what is the difference between an exception and an error
#exception_error_exercise
An exception is raised during a program when some condition is not met, and therefore the normal execution flow of the program can not continue. This can be handled in specific ways, but if no handling of this condition is met, the program will stop with some error code or message. If an exception-handler is implemented the program execution is continued from this implementation. The exception-handling is usually implemented via a `try-catch` block, trying some execution, and if the execution fails, there can be a catch statement which will handle the exception. This could be logging something or just continue some different execution way.

An error on the other hand is when the program is not in a recoverable state, and cannot be handled in other way than the program stopping, usually also logging what went wrong and which conditions made the error occur. This can fx be a C program accessing memory that is out of its address space. 

To sum up the difference is that an exception can be handled, and an error cannot. The exception can continue execution while the error stops the program.

## Consider the following pseudo code of a language with exceptions
```java
void f() throws X {
throw new X();
}

void g (int sw) throws X {
	if (sw == 0) { f(); }
	try { f(); }
	catch (X e) { write("in_g"); }
}

...
try { g(1); }
catch (X e) { write("in_main"); }
```
What does this code print when executed? Please explain why.

The program calls g with 1 resulting in f being called, throwing an exception which is caught in g, meaning it is not passed to `main`, writing `"in_g"`. 

## Please describe how exceptions can “naively” be implemented by using the the stack and activation records.
#exception_exercise
When an exception is throwing the activation record is unwinded, dropping each activation record in the call stack until a matching catch block is found. If a catch block is found that is conditioned on the specific exception-type, the control is given to the specific block with this catch block, which can then do whatever logic is has defined in the catch block. If no catch block is found in the call stack, the program will terminate with some error, which usually is an `unhandled exception error` with the given exception method and type.

Another approach is to put each exception handler on the stack, popping one for one the exception handler checking if the handler matches the exception, which will then give control back to block which it may point to. If not it just terminates like the example above

## Describe one limitation of implementing exceptions by using only the the stack and activation records.
We would have to go through each activation record one by one, where some of the blocks may not even have an exception handler implemented. Therefore it would be better to fx have a table with a pointer to the activation records, where this table is sorted, such that the closest activation record is stored first and then the first exception handler is the last element. Then when an exception is raised it should lookup and exception handler for this specific exception, where this table should then have the entries <exception-type, pointer-to-activation-record>. Taking the first one and going to that block, freeing all local variables and activation records in the blocks below this and give control to this block. This could also be done via hashmap where the java-like syntax could be `HashMap<Class<Exception>, List<Address-pointer>>`, accessing all handlers for the specific exception where the corresponding list should be sorted as described above.

# 2
## ????????????????????????????????????????????






# 3
## In the context of Object orientation, define what we mean with the term inheritance. Why is it useful?
#Object_orientation_exercise
#Inheritance_exercise
Inhertiance in Object orientation is when a derrived class inherits the methods and variables from its superclass, which powerful in terms of not needing to make duplicate code, if the derrived class may need some of the methods or variables from the superclass.

## What are the differences of single and multiple inheritance? 
Single inheritance means that a class can only inherit from a single super class. In multiple inheritance a class can inherit from multiple classes. 


## Name a problem that can emerge when dealing with multiple inheritance.
Ambiguity is a problem, fx if a class is derrived from two classes which both a function with the same name, it is not possible to know which function should be accessed, when calling the function from within the derived class or in an instance of this class. Extra steps has to be taken, i.e one approach can be to take the first specified class' method if name clashes occur, or if name clashes occur, the class can itself specify which function it wants using some techniques, which could fx be if the two super classes are `class Animal` and `class Human` which has the method `method eat()` the derived class, fx `class Anton` which extends both of the above classes, it could speciy the method it wants with `class Anton extends Human, Animal specification Human::eat`, meaning it wants the Human's eat method.

## Describe how single inheritance can be implemented using linked lists.
Taking an example into use with
```java
class Super {
	int a;
	int b;

	fun greet();
}

class Derived extends Super{
	int a;
	int c;

	fun greet();
	fun eat();
}

Derived d = new Derived();
```
the LinkedList could then in the first node store the variables for Derived in an array, which first lists `a, c` in Derived and then `a, b` for Super, but which is also visible from the class `Derived` , i.e the array would look like
```listing
Array[0] = *Derived.a
Array[1] = *Derived.c
Array[2] = *Super.a
Array[3] = *Super.b
```
Then when wanting to find which variable to use when calling upon `d.(some variable)` it will go through the attributes to find the first one appearing. 

The next Node would store the functions. This is stored in a similar array-structure where Derived-functions are stored first, and then Super's functions taking the first function that matches.

This way the methods are used from Derived if they are called upon an instance of Derived, but if inherited from Super it will call these if not found in Derived.

If the super methods or variables are to be called from d it can just specify an offset, which should be number of variables or functions in the Derived class.

# 4
## Consider the following pseudo code of a language using static scoping, call by reference, and evaluating expressions from left to right.
```java
{
	int x = 0;
	int A(reference int y) {
		int x=2;
		y=y+1; // outer x = 1, outer x = 2
		return B(y)+x; // B(x) + x = 13 + 2 = 13, 4 + 2 = 6
	}
	int B(reference int y){
		int C(reference int y){
			int x = 3;
			return A(y)+x+y; // A(x) + 3 + y, 6 + 3 + 2 = 11
		}
	if (y==1) return C(x)+y; // C(x) + y, 11 + 2 = 13 
	else return x+y; // 2 + 2 = 4
	}
	write (A(x)); // pointer to outer x. write 15
	write (x); // write 2
}
```
What does it print? Motivate your answer.

first x is changed to 1 and then B is called with the same reference to the outer x, This puts a halt to the evaluation of the expressions B(y) + x until B is finished executing since it is evaluated from left to right.  The statement of y=\=1 is hen hit, returning C(x) + y, halting the execution until C is finished executing. The x is a reference to the outer x. this calls A(y) + x +y resulting in the halt of this until A(y) returns, where the y is a reference to the outer x.  This will increment the outer x to 2, returning B(y) + x, which returns 2 + 2 since x is the outer x and y is a reference to the outer x. The call to A from C is then evaluated to 4 + 2 since x is 2 and B returned 4. The call to C from within B is then returning  6 + 3 + 2, since the y used is a reference to the outer x with is 2, the inner x is 3 and A returned 6. The call to B from A returns 11 + 2 since C returned 11 and y is a reference to the outer x which is  2. Finally the first call to A from the main function is returning 13 + 2 since B returned 13 and x is 2 at this time. Writing out 15 and writing 2

## What does the previous program print if dynamic scoping is used instead of static scoping? Motivate your answer and show how the stack looks like immediately after the invocation of B for the second time.
```java
{
	int x = 0;
	int A(reference int y) {
		int x=2;
		y=y+1; // outer x = 1, 1st x A = 2 + 1 = 3 
		return B(y)+x; // B(x) + 2 = 14 + 2 = 16, B(x in first A) + 2, return 5 + 2
	}
	int B(reference int y){
		int C(reference int y){
			int x = 3;
			return A(y)+x+y; // A(x in first A) + 3 (the x in A is out of scope) + x in first A, 7 + 3 + 3 = 13 
		}
	if (y==1) return C(x)+y; // C(x in first A) + outer x, 13 + 1 = 14
	else return x+y; // return x in 2nd A and x in 1st A, 2 + 3 
	}
	write (A(x)); // reference to outer x, write 16
	write (x); // 1
}
```
[[Acitivation_record_stack.excalidraw]]
Where the stack grows downwards. No activation records are popped until after B is finished executing (5 is popped after the call), then A is popped (4 is popped) and so on.

at first the outer x is used as a reference in A. This is then incremented to 1. Then B(outer x) is called waiting with the + x operation. Since y is equal to 1 we enter C(x in 1st A) + y where y is a reference to outer x. The x in 1st A is used because it is the last seen in the dynamic scoping. Then A(x in 1st A) + x + (x in first A) is called, which increments the first x in A to 3 returning B(x in 1st A) + (x in 2nd A) which returns x in 2nd A + x in 1st A = 5.  Then the 2nd call to A is evaluated to 5 + 2 = 7. The call to C from B is evaluated to 7 + 3 + 3 = 13, using the x in 1st A as the y, the x local to C since the x in A is out of scope. This is then passed along the first call to B evaluating to 13 + (outer x) = 14. Which is passed along to first A evaluating to 14 + 2 finally writing 16 and 1.


## What does the previous program print if static scoping, call by reference are used but expressions are evaluated from right to left?
```java
{
	int x = 0;
	int A(reference int y) {
		int x=2;
		y=y+1; // outer x = 1, outer x = 2
		return B(y)+x; // B(outer x) + 2 = 11 + 2 = 13, 4 + 2 = 6
	}
	int B(reference int y){
		int C(reference int y){
			int x = 3;
			return A(y)+x+y; // A(y) + 3 + 1,  return 6 + 3 + 1 = 10
		}
	if (y==1) return C(x)+y; // C(outer x) + 1, 10 + 1 = 11
	else return x+y; // 2 + 2
	}
	write (A(x)); // write 13
	write (x); // write 2
}
```