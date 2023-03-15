# 1. Define, in any programming language, a function, f , such that the evaluation of the expression (a + f (b)) ∗ (c + f (b)) when performed from left-to-right has a result that differs from that obtained by evaluating right-to-left.
```java
int a = 5;
int b = 3;
int c = 3;

int f(b) {
	int temp = a
	a = 0 
	return temp + b;
}
```
If right to left `a` will be 0 when used, but if from left to right `a` will still be used as the initial value.

Any function that alters a will evaluate to different results

# 5. Consider the following function
```java 
int ninetyone (int x){
	if (x>100)
		return x-10;
	else
		return ninetyone(ninetyone(x+11));
}
```
Is this tail recursive? Justify your answer.

_(algorithmic technique) Definition: **A special form of recursion where the last operation of 
a function is a recursive call**. The recursion may be optimized away by executing the call in 
the current stack frame and returning its result rather than creating a new stack frame._

It is not since the last operation is not a function call, we have to evaluate the inner before we can calculate the outer.  The last thing is **not** the function call, as we have two functions being called. 

# 6. The following code fragment is written in a pseudo-language which admits bounded iteration (numerically controlled) expressed using the for construct.
```java
z=1;
for i=1 to 5+z by 1 do{
	write(i);
	z++;
}
write(z);
```
What is printed by write?
_The condition should be evaluated the first time we enter, i.e when `z=1`_ and we have a guard of
`1 to 6 by 1` 

What is printed by write?
write(i)
1
2
3
4
5
 
write(z)
6

