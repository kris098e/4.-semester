# 1. Using some pseudo-language, write a fragment of code such that the maximum number of activation records present on the stack at runtime is not statically determinable
```java
int j; // when not initialized this variable will get the value that is stored at the address it gets at runtime when executing the program
func(j);

func(int c) {
	if c == 0 return 0;
	else return func(c-1);
}
```
Can also take user input, which can only be determined at runtime

# 2. In some pseudo-language, write a recursive function such that the maximum number of activation records present at runtime on the stack is statically deter-minable. Can this example be generalised?
```java
int n = 4;

sum(int n) {
	if(n==1) return 1;
	return n + sum(n-1);
}
```
as we know we are gonna call the function n-1 times, and n is determened at compilation time/static memory allocation, the program knows n before runtime.

can also do this with tail-recursion, having the accumulator in function call as argument. This way we dont have to store any values other than the arguments. The call will just reuse the activation record of the tail (the function calling it). This can only be done if the function call is the last thing i.e in the above function is `+` not the function call.

# 3. Consider the following code fragment:
```java
A:{int X = 1;
  ....
  B:{X=3;
	  ....
  }
  ....
}
```
# Assume that B is nested one level deeper than A. To resolve the reference to X present in B, why is it not enough to consider the activation record which immediate precedes that of B on the stack? Provide a counter-example filling the spaces in the fragment with dots with appropriate code.


```java
A:{int X = 1;

  void foo() { x=3 }
  void bar() { int x = 5; foo() }
  bar(); // put bars activation record on the stack below A, which will put foo() on top of bar() aswel
  
  B:{X=3;
	  ....
  }
  ....
}
```
in the example we have the activation records: A, bar, foo, B

# 4. Consider the following program fragment written in a pseudo-language using static scope:
```c
void P1 {
	void P2 { body-ofi-P2
	}
	void P3 {
		void P4 { body-of-P4
		}
		body-of-P3
	}
	body-of-P1
}
```
# Draw the activation record stack region that occurs between the static and dy-namic chain pointers when the following sequence of calls, P1, P2, P3,P4,P2 has been made (is it understood that at this time they are all active: none has returned)
> _static-link_ : to the block (its activation record) that contains this block, **this can be known at compile time**
> _dynamic-link_ : to the activation record that was created before this

1. p1 has no pointers
2. p2 static pointer to p1 and  dynamic-link to p1
3. p3 static-link to p1 and dynamic-link to p2
4. p4 static-link to p3  and dynamic link to p3
5. p2 static link to P1 and dynamic link to p4

# 6. Is it easier to implement the static scope rule or the one for dynamic scope? Give your reasons
dynamic scope, only has to remember the last variable seen in the scope and use this. Static scope has to use activation records or implement CRT or A-list to find the variable needed.

static scope is easier for the programmer to use. 


