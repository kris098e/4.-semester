# exercise 1
## a
A closure is such that a function can use all the variables it needs, to execute the function. I.e it remembers the environment it needs to successfully complete the function call.
```javascript
function outerFunction() {
  var outerVariable = "Hello, ";

  function innerFunction(name) {
    console.log(outerVariable + name);
  }

  return innerFunction;
}

var greeting = outerFunction();
greeting("John"); // Output: "Hello, John"
```
It remembers the `outervariable`, since it cannot be executed with this. 

```java
{
int x = 2;
void h() { print(x); }
e(h);
}

function e((void h())) {
    h();
}
```
Here `h` has to remember, by using closures, to use the variable `x`

## b
Deep binding binds the environment at the time a procedure is passed as an argument, while shallow binding binds the environment at the time a procedure is actually called.

```javascript
var x = 10;

function outerFunction() {
  var x = 20;

  function innerFunction() {
    console.log(x);
  }

  return innerFunction;
}

var inner = outerFunction();
inner(); // Output: 10 if shallow (use the enivornment when it is called), output: 20 if deep (use environment it was called defined).
```


```java
{
int x = 2;
void h() { print(x); }
e(h);
}

function e((void h())) {
    int x = 4;
    h(); // if shallow, print 4, if deep, print 2. 
}
```

## c
The following program is written using a pseudo-code. Assume that dynamic scoping is used. What does the following program write if shallow binding is used? Motivate the answer.
```c
{ 
	int x = 2;
	int f(int y){
		return x+y; // 4 + 3
	}
	int g (int h(int b)){
		int x = 4;
		return h(3) + x; // 7 + 4 = 11
	}
	{ 
	int x = 6; 
	int z = g(f);
	write(z) // write 11
	} 
}
```
When f is defined x = 6, however when calling f, x = 4

## d.
f would use the environment it was defined in. I.e x=6.
Therefore the calculation in g would be `(6+3+4)=13`. 

## e.
With static scoping, f would us e `x=2` as its x-value.
Therefore it would be looking like it was using deep-binding, as the environment it was defined in, is also using `x=2`. Using shallow binding here would not matter, as the calling environment is out of scope for the function f.
The output would then be `(2+3+4)=9`

# exercise 2
![[Pasted image 20230531105555.png]]


# exercise 3.
## a.
Calling by name will expand the formal parameters to the actual parameters. Therefore when writing `v` it replaces it with `x` when calling the function in the example.
Static scoping means the program will use the variable which is in the current scope, if it is not here, it goes out to the block which contains this block, if not found here it goes further ...
```c
{ 
	int x = 2;
	int y = 5;
	int z = 10;
	void foo(name int v, name int w){ // v = x, w = y
		int x = 1000;
		w = v; // y = x = 2. uses outerscope x
		v = v+w+z; // outer x = 2 + 2 + 10 = 14
		z = 1000; // = 1000
	}
	{ 
		int x = 20;
		int y = 50;
		int z = 100;
		foo(x, y);
		write(x,y,z); // write(20,50,100)
	}
	write(x,y,z); // write(14, 2, 1000)
}
```

## b. 
Yes we can call by reference in the previous code example. This will alter what is given as the actual parameters when altering the formal parameters in the code.
```c
{ 
	int x = 2;
	int y = 5;
	int z = 10;
	void foo(reference int v, reference int w) {
		int x = 1000;
		w = v; // y = x = 20
		v = v+w+z; // x = x + y + 10 = 20 + 20 + 10 = 50
		z = 1000;
	}
	{ 
		int x = 20;
		int y = 50;
		int z = 100;
		foo(x, y); // changed y to be equal to 20, x to be 50
		write(x,y,z); // write(50, 20, 100) 
	}
	write(x,y,z); // write(2, 5, 1000)
}
```

## c.
call by value will make a copy of the actual parameters, and use these when using the formal parameters
```c
{ 
	int x = 2;
	int y = 5;
	int z = 10;
	void foo(value int v, value  int w) {
		int x = 1000;
		w = v; // w = x = 20
		v = v+w+z; // v = 20 + 20 + 10 = 50 
		z = 1000;
	}
	{ 
		int x = 20;
		int y = 50;
		int z = 100;
		foo(x, y); 
		write(x,y,z); // not changed, as static scope used, and by value. write(20, 50, 100)
	}
	write(x,y,z); // write(2, 5, 1000)
}
```

# exercise 4.
## a.
Type: collection of values (homogeneous and
effectively presented) equipped with a set of
operations to manipulate these values

Type: Collection of homogeneous values which can presented, while have a set of operations to manipulate it.

In the context you provided, homogeneous means that all the values in the collection are of the same type. For example, a homogeneous collection of values could contain only integers or only strings, but not a mix of both.

Effectively presented means that the collection is well-organized and can be easily accessed and manipulated. This could refer to the way the collection is structured, how the values are labeled or indexed, and how the set of operations to manipulate these values are defined and accessible. An effectively presented collection should be clear and intuitive to use for anyone who needs to work with it.


### use cases
They are used for storing data, in the correct form. Such that if we want to store an integer, it is stored in x-amount of bits, and we can efficiently use operations on it, that are defined for this data type.

Encapsulating data in collections are useful when we want to iterate some collection

## b.
A scalar type is a single value, not made up of other values and their operations
while a composite type is made up of other scalar types.

Scalar types include primitive types such as integers, floating-point numbers, characters, and Boolean values. These types are used to store simple values that can be easily manipulated by the computer.

Composite types, on the other hand, include arrays, structures, and classes. These types are used to group related values together into a single object.

An example of a composite type is an array. An array can store a collection of values of the same data type, such as a list of integers or a list of strings. Another example of a composite type is a structure, which can store related values of different data types, such as a person's name, age, and address.

## c.
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

## d.
A polymorphic type system is a type system that allows values to have more than one type. In other words, a polymorphic type system allows a single function or variable to accept or work with values of different types.

There are two main forms of polymorphism in type systems:

1.  Parametric polymorphism: This is a form of polymorphism in which a function or data type is generic and can operate on values of different types. This is often achieved through the use of type variables. For example, in the programming language Java, the ArrayList class is a parametrically polymorphic data type, allowing it to store elements of any type. They can then work with infinitely many types

THIS MEANS THAT FUNCTIONS AND TYPES CAN WORK WITH MORE TYPES. I.e **Generics**


2. .  Ad hoc polymorphism: This is a form of polymorphism in which a function or operator can have different implementations depending on the types of its arguments. This is often achieved through the use of overloaded functions or operators. For example, in the programming language Python, the '+' operator is ad hoc polymorphic, allowing it to perform addition on different types of values such as integers, floats, and strings.
Overloading, specifying how the function should work with specific types.

Polymorphic type systems can make code more flexible, modular, and reusable. They can also help catch errors at compile time by ensuring that functions and variables are used only in ways that are compatible with their defined types.

## e.
### Ad hoc polymorphism
Function overloading, have implementation for different types, depending on how it is used.

### Parametric polymorpism
When a function or a data type can be used with values of different types. fx a `List<T>` in java. This is parametric polymorphism, as it can be used on multiple types.

### Explicit parametric polymorphism

### Implicit Parametric polymorphism

### Subtype polymorphism
Having super classes and extending classes. The extending classes can then be used like it is the superclass.



# exercise 5
## One way to distinguish objects that are still alive (garbage detection) is the reference counting technique. Briefly describe this technique
An object holds a reference count, i.e if the program still holds a pointer to this object in memory. When no pointers are kept to the object, i can safely be garbage collected and deallocated.  

## Mention one pros and one/two cons of reference counting compared to marking and copying?
pros: can be done on the fly, i.e each time the reference count is decremented, the program can check if the reference count has gone to 0, and deallocate the object. Compared to marking and copying where it will first start when memory is needed that cannot be given, or some threshhold specified, which will pause the program for longer than the simple check for if the reference count has gone to 0. This means that reference counting will deal with the garbage collection right away, instead of postpone it until some threshold of memory.

cons: the extra memory added to each object may become large, since it needs this additional memory, also occupying some additional memory.
it does not line up the objects for contiguous blocks. This means that each time an object are to be created the memory is searched for a free space, which may take longer since the memory is scattered in the address space, instead of when using a contiguous block of memory, you can just go to the end of the allocated blocks and start allocating there. I.e reference counting will end up creating more internal fragmentation

## Consider the following fragment written in a pseudo-language with a reference-counting garbage collector.
```c
class C { int n; C next;}
C foo(){
	C p = new C(); // object OGG1
	p.next = new C(); // object OGG2
	C q = new C();// object OGG3
	q.next = p.next;
	return p.next;
}
C r = foo();
```
State what are the values of the reference counters for the three objects after execution of line q.next = p.next and then of line C r = foo(). Motivate your answer. Are there any objects that can be returned to the free list? If so, which ones?

**q.next = p.next**: 
	p points to object OGG1
	p.next points to object OGG2
	q points to OGG3
	q.next points to OGG2
	
	1 to OGG1
	2 to OGG2
	1 to OGG3

**C r = foo()**
pointer to OGG2
nothing points to OGG1
nothing points to OGG3

only pointer to OGG2 and the others can be returned to the free list.