
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
Two types are the same, if they have the same name. So if we have two ints, they are of the same time, and they are the same type. Comparing String and int will then of course be evaluated to false.


# Side-effects
## Why are side effects important? What are their pros and cons?
It is important to be able to make more flexible programs, bringing a programs state forward to where the programmer wants it to go.

Most of the times side effects are undesirable since it often introduce complicated programs, since it fx is hard to see how many times the function is called if some conditions are used. They can introduce bugs, since it is hard to keep track of this global variable

However if used responsibly it can make a programmers life easier, fx. introducing a global count-variable, where each function call will increment this count as a side-effect. Logic could then be implemented around this side effect

**Key idea in imperative programming, an key idea in function programming not to have this
I.e in imperative programming, we are not ensured that the function will be pure, and they are always pure in functional programming

# Vtable
Virtual Function Table, i.e it does not contain all of the variables but only the functions

# Display
When drawing the display, remember the back pointers to the block within the same nesting.
look at
[[mockup_exam_answers.pdf#page=2]]

# Mark and compact
does not just require two times over the heap, requires multiple scans over the heap. That is, 1 for marking, 1 for computing the positions where the blocks will be moved to be contigous, 2nd update the internal pointers to the objects, and third actually moving the objects.

# Type compatability
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
