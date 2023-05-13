[[202006]]
# 1
## a
Overriding refers to the process of defining a method in a subclass that already exists in the superclass. When a method is called on an object of the subclass, the version of the method defined in the subclass is called, rather than the one defined in the superclass. The method in the subclass must have the same name, return type, and parameter list as the method in the superclass, in order to override it.

Overloading, on the other hand, refers to the process of defining multiple methods in a class with the same name, but with different parameters. The methods can have different return types or different numbers and types of parameters. When a method is called, the appropriate version of the method is selected based on the number and types of arguments passed to it.

## b
The key difference between overriding and overloading is that overriding is used to provide a different implementation for an existing method in a subclass, whereas overloading is used to define multiple methods with the same name but different parameters.

## c
For Q1 we just overload the method, when providing something of type A will return something of type A. Having 2 methodsfor `fie`

For Q2 we again just overload the class. Having 2 methodsfor `fie`

For Q3 C is superclass of B therefore it can act as B and therefore the parameter is correct, however the return type is a subclass of B, and therefore A cannot be used as a B which will result in runtime errors.

For Q4 A is a subclass of B and cannot be used as a B. The return value can act as a type B tho, but since the parameter says less, this will run into runtime issues.

## d
As just specified, Q1 and Q2 will be allowed both runtime and compile time. However Q3 will not compile since the return value is not a supertype of B. Q4 will be able to compile, but if the parameter is acted upon as if it were a B it will run into runtime issues.

# 2

# 3 
