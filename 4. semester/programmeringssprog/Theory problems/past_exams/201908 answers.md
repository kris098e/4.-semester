![[201908.pdf]]
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

## b
In deep binding, a variable reference in a nested function is resolved to the value of the variable in the environment where the function was defined, rather than the environment where the function is called. This means that if the variable's value is changed after the nested function is defined, the nested function will use the updated value.

In shallow binding, on the other hand, a variable reference in a nested function is resolved to the value of the variable in the environment where the function is called, rather than the environment where the function was defined. This means that if the variable's value is changed after the nested function is defined, the nested function will still use the original value.

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
inner(); // Output: 10 if shallow (use the enivornment it is called from), output: 20 if deep (use environment it was defined in).
```

## c
The following program is written using a pseudo-code. Assume that dynamic scoping is used. What does the following program write if shallow binding is used? Motivate the answer.
```c
{ 
	int x = 2;
		int f(int y){
			return x+y;
		}
	int g (int h(int b)){
		int x = 4;
		return h(3) + x;
	}
	{ 
	int x = 6; 
	int z = g(f); 
	write(z) 
	} 
}
```
When f is defined x = 2. However as we use shallow binding, it uses the environment in which is called. 
The procedure g calls f, but x = 4 here. Therefore the call to g is `(4+3+4)=11`. Therefore it will write out `11`.

## d.
f would use the environment it was defined in. I.e x=6.
Therefore the calculation in g would be `(6+3+4)=13`. 

## e.
With static scoping, f would us e `x=2` as its x-value.
Therefore it would be looking like it was using deep-binding, as the environment it was defined in, is also using `x=2`. Using softbinding here would not matter, as the calling environment is out of scope for the function f.
The output would then be `(2+3+4)=9`

# exercise 2
![[201908.pdf#page=2]]
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
		w = v; // y = x = 1000
		v = v+w+z; // x = x + y + 10 = 1000 + 1000 + 10 = 2010
		z = 1000;
	}
	{ 
		int x = 20;
		int y = 50;
		int z = 100;
		foo(x, y);
		write(x,y,z); // write(20,50,100)
	}
	write(x,y,z); // write(2010, 1000, 1000)
}
```

## b. 
Yes we can call by reference in the previous code example. This will alter what is given as the actual parameters when altering the formal parameters in the code.
```c
{ 
	int x = 2;
	int y = 5;
	int z = 10;
	void foo(reference int v, reference int w)
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
	write(x,y,z); // write(2, 5, 10)
}
```

# exercise 4.
![[201908.pdf#page=3]]
## a.
Type: collection of values (homogeneous and
effectively presented) equipped with a set of
operations to manipulate these values

In the context you provided, homogeneous means that all the values in the collection are of the same type. For example, a homogeneous collection of values could contain only integers or only strings, but not a mix of both.

Effectively presented means that the collection is well-organized and can be easily accessed and manipulated. This could refer to the way the collection is structured, how the values are labeled or indexed, and how the set of operations to manipulate these values are defined and accessible. An effectively presented collection should be clear and intuitive to use for anyone who needs to work with it.


### use cases
They are used storing data, in the correct form. Such that if we want to store an integer, it is stored in x-amount of bits, and we can efficiently use operations on it, that are defined for this data type.

## b.
In computer programming, a scalar type is a data type that represents a single value, while a composite type represents a collection of values.

Scalar types include primitive types such as integers, floating-point numbers, characters, and Boolean values. These types are used to store simple values that can be easily manipulated by the computer.

An example of a scalar type is an integer. Integers represent whole numbers and can be used to store values such as 1, 2, 3, and so on. Another example of a scalar type is a character, which can be used to store individual letters or symbols.

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

### name equivalence
Two types are the same, if they have the same name. So if we have two ints, they are of the same time, and they are the same type. Comparing String and int will then of course be evaluated to false.

## d.
A polymorphic type system is a type system that allows values to have more than one type. In other words, a polymorphic type system allows a single function or variable to accept or work with values of different types.

There are two main forms of polymorphism in type systems:

1.  Parametric polymorphism: This is a form of polymorphism in which a function or data type is generic and can operate on values of different types. This is often achieved through the use of type variables. For example, in the programming language Java, the ArrayList class is a parametrically polymorphic data type, allowing it to store elements of any type.
    
2.  Ad hoc polymorphism: This is a form of polymorphism in which a function or operator can have different implementations depending on the types of its arguments. This is often achieved through the use of overloaded functions or operators. For example, in the programming language Python, the '+' operator is ad hoc polymorphic, allowing it to perform addition on different types of values such as integers, floats, and strings.
    

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

