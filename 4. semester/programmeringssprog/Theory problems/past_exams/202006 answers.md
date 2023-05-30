[[202006.pdf]]
# 1
## a
Overriding refers to the process of defining a method in a subclass that already exists in the superclass. When a method is called on an object of the subclass, the version of the method defined in the subclass is called, rather than the one defined in the superclass. The method in the subclass must have the same name, return type, and parameter list as the method in the superclass, in order to override it.

Overloading, on the other hand, refers to the process of defining multiple methods in a class with the same name, but with different parameters. The methods can have different return types or different numbers and types of parameters. When a method is called, the appropriate version of the method is selected based on the number and types of arguments passed to it.

## b
The key difference between overriding and overloading is that overriding is used to provide a different implementation for an existing method in a subclass, whereas overloading is used to define multiple methods with the same name but different parameters.

## c
For Q1 we just overload the method, when providing something of type A will return something of type A. Having 2 methodsfor `fie`

For Q2 we again just overload the class. Having 2 methods for `fie`

For Q3 C is superclass of B therefore it can act as B and therefore the parameter is correct, however the return type is a subclass of B, and therefore A cannot be used as a B which will result in runtime errors.

For Q4 A is a subclass of B and cannot be used as a B. The return value can act as a type B tho, but since the parameter says less, this will run into runtime issues.

## d
Only Q4 since it is the only one having return value which is covariant and the argument being contravariant


# 2
Language for which the interpreter/compiler is written in is the lower, and from and to is the upper

a. yes it is
b.
![[Pasted image 20230510122032.png]]

# 3 
## Define in your own words the notion of side effects?
Illustrate this with an example

```java
{
	int a = 0;

	int foo() {
		a++;
		return 2;
	}

	foo();
}
```
Here, when calling foo, it alters a. This means that it changes the programs state which is not directly related to the functions returnvalue. 

## Why are side effects important? What are their pros and cons?
It is important to be able to make more flexible programs, bringing a programs state forward to where the programmer wants it to go.

Most of the times side effects are undesirable since it often introduce complicated programs, since it fx is hard to see how many times the function is called if some conditions are used. They can introduce bugs, since it is hard to keep track of this global variable

However if used responsibly it can make a programmers life easier, fx. introducing a global count-variable, where each function call will increment this count as a side-effect. Logic could then be implemented around this side effect


## By reading the specification of the C++ language, you notice that it guarantees that arguments will be evaluated linearly and will not interleave, but that there are not guarantee of evaluation of parameters or expressions in any specific order. Consider the following C-like program.
```c++
v = 0
write(v++ + v,v)
```
What will this program print? If there are more possibilities list all of them. Motivate your answer.

Since there are no guarantee of the ordering of the evaluation,  the output can be:

from left to right:
write(1, 1)

from right to left:
write(0,0)

arguments evaluate from left to right, but the (v++ + v) is evaluated with the v first, and then v++:
write(0, 1)

# 4
## What does the term cast and coercion mean?
Casting means to get one variable from one type to another data type via explicitly writing in the code that it should be cast to a different type. Fx
```java
String b = "hej";
Object k = (Object)b;
```
Type coercion means from an expression the type is coerced from the result. Fx in python 
```python
x = 2 + 2.3
```
x ends up being a float, even tho an int and float is used, but to capture the entire result x has to be a float

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

## Discuss the pros and cons of cast and coercion
The pros of casting is that the programmer can clearly see which type a variable will have, but the cons is that the programmer itself has to think about type casting the types which may result in an error if done incorrectly, and also the programmer has to spend time on type casting. The compiler is most of the times more clever than the programmer so the compiler should be better most of the times, however this leaves control to the compiler instead of the programmer which may both be a con and pro, since the compiler may not do what the programmer expect, but most of the time it should do what the programmer expects, which leaves the programmer doing less work.

## Assuming you would like to design a language to develop mission critical software, would you chose to support in your language a cast or coercion mechanism? Motivate your answer.
I would choose a type casting language, since the programmer should have full control of what is happening, which should not be left up to a compiler decision. Then of course the code should be read by multiple persons, ensuring the program is correct. While also being tested. If the programmers are competent the language should be using casting and if a good compiler is used, where the same tests passes then a coercion mechanism should be used, making it easier for the programmers.