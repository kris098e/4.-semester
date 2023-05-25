[[202208.pdf]]

# 1
## a
Overriding is when a subclass to a superclass rewrites the implementation of a method. For this to work the subclass' method has to be covarant with the original return type, i.e the return type to the method has to be a subtype of the original return type, and the parameters need to be contraviant, i.e they need to be a supertype to the original arguments. Or else the return type and arguments can just be of the same time.

```java
class triangle {

	String shape() { return "in triangle" }
}

class multiTriangle extends triangle {

	String shape() { return "in multiTrinagle" }
}

triangle tr = triangle()
tr.shape() // returns "in triangle"

multiTriangle mtr = multiTriangle()
mtr.shape() // returns "in multiTriangle"
```

## b 
overloading is when multiple functions has the same name, but the functions differs in amount of arguments or different kinds of parameters. The return type may also differ, but the amount of arguments and type on the arguments or the ordering of the arguments will determine which function to use.

```java
class hej {
	String hello(int times) { return "hello " + times + " times" }
	String hello(int times, String name) { return "hello " + name + " " + "times " + times}
}

hej h = hej()
h.hello(2) // return "hello 2 times"
h. hello(2, "spag") // return hello spag times 2
```

## c
Q1 return value is not covariant so it will cause a threat.
Q2 parameter is not contravariant, so it will cause a threat
Q3 return value is not covariant, so it will cause a thrat
Q4 is allowed since C is covariant with B and paramater is contraviant with B

# 2
## a
[[_05_memory.pdf#page=7]]
**dynamic chain pointer** to point to the activation record just above this one. Can be used for dynamic scoping and for backtracking

**static chain pointer** used to know which activation record contains this one, and can be used for static scoping.

**return address** such that the program knows where to continue exection when done with this activation record.

**return address for the result** where to store the result for what is calculated in this activation record.

**local variables** such that we in this activation record can store variables that are needed for the execution of this.

**intermediate results** if we have a calculation $\frac{a}{b}+\frac{c}{d}$ it will store $\frac{a}{b}$ such that it can calulcate $\mathrm{Re}sult+\frac{c}{d}$

**parameters** for the function

## b
The stack is a LIFO structure where variables can be stored. It used when storing arguments for a function and also local variables to a procedure, which is then popped of the stack when returning from the procedure. This means it can be used instead of allocating memory on the heap, and when using stack, the programmers does have to think about the deallocation and allocation of memory, since it is managed by the stack. 

Can also store the activation records. Can be used for static memory allocation aswel, i.e not using malloc

## c
Can access the element at the k'th level in constant 2 times, if we know that we need to access an element which k levels above this nested block. 
		* Works in the way that each time we enter a nesting a new pointer is created to this block. I.e the k'th entry in this table of pointers to the nestings, points to k'th nesting. However when we enter a new block in the same k'th nesting level, the pointer must then also be updated. 
		* The backtracking pointer is used since when popping of the activation record for this procedure, we then know which activation record should be activated again, which is the one that called the procedure.

It brings advantages in the form of speed,  I.e we can lookup the k'th level of backtracking in constant time, if we know which level holds this variable that we seek. If using static we would have to follow the static chain pointers k times, i.e it is linear time. 

More advantages???

# 3
## a
It is used to iterate over some specified body until some certain critera is met. This can fx be a `for-loop` and `while-loop` both specifying when to stop based on some boolean value

## b
1. goto
2. : `labeling` can label where to go

## c
1.  Readability and Maintainability: The uncontrolled use of "goto" statements can make code difficult to read and understand. It can create complex and non-linear control flow, making it harder to reason about the program's behavior and maintain the code over time.
    
2.  Spaghetti Code: Extensive use of "goto" statements can lead to "spaghetti code" where the control flow jumps unpredictably between different sections of the code. This can make the code hard to follow, debug, and modify.
    
3.  Error-Prone: Incorrect or misplaced use of "goto" statements can introduce bugs and logical errors in the program. It becomes challenging to track the flow of execution and ensure proper control flow.
    
4.  Structured Programming: The use of "goto" conflicts with the principles of structured programming, which promote modular and well-organized code. Structured programming emphasizes the use of control structures like loops and conditionals to achieve predictable and maintainable code.


## d
A tail recursive function is a recursive function where the last operation perfomed is the recursive call. This means that the compiler or interpeter can reuse the activation record which it is in optimizing performance. It can do this since it does not need to store additional values but what is in the arguments of the function

```java
function factorial(n, acc = 1)
    if n == 0
        return acc
    else
        return factorial(n - 1, acc * n)
```
https://stackoverflow.com/questions/33923/what-is-tail-recursion

Does not need to store any additonal variables for the return value but what is in the arguments.


# 4
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
	y = 1; // A[3] = 2, feel like this should be A[2]? but we have to use the environment of the caller?????????
	A[i] = 3; // A[3] = 3
	A[A[i]] = 4; // A[3] = 4
}
for (j = 0; j <= 4; j += 1) {
	A[j] = 0;
}
fie(i, A[i]);
write(A[1]); // 0
write(A[2]); // 0
write(A[3]); // 4
write(A[i]); // A[2], 0
```

## b
Dynamic scoping uses the last in scope variable that matches the name on the call stack.
Still uses the environment of the caller when evaluating the formal parameters.
```java
int i = 1;
int [] A = new int [5];
void fie (name int x, name int y) {
	int i = 3;
	x = x+1; // outer i = 2
	y = 1; // A[2] = 2
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


## c
Pass by value just copies the value and put it into the formal parameters
```java
int i = 1;
int [] A = new int [5];
void fie (value int x, value int y) {
	int i = 3;
	x = x+1; // x = 2
	y = 1; // y = 1
	A[i] = 3; // A[3] = 3
	A[A[i]] = 4; // A[3] = 4
}
for (j = 0; j <= 4; j += 1) {
	A[j] = 0;
}
fie(i, A[i]);
write(A[1]); // 0
write(A[2]); // 0
write(A[3]); // 4
write(A[i]); // A[1], 0
```

## d
```java
int i = 1;
int [] A = new int [5];
void fie (reference int x, reference int y) {
	int i = 3;
	x = x+1; // i = 2
	y = 1; // A[1] = 1, pointed to A[1] in the actual parameters
	A[i] = 3; // A[3] = 3
	A[A[i]] = 4; // A[3] = 4
}
for (j = 0; j <= 4; j += 1) {
	A[j] = 0;
}
fie(i, A[i]);
write(A[1]); // 1
write(A[2]); // 0
write(A[3]); // 4
write(A[i]); // i = 2, A[2], 0
```