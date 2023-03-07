![[Pasted image 20230228111232.png]]
static scope: follow the variable one block out until it is found.
First foo increments the outer x, then fie increments the outer x thus **2 is printed both times**.
Can also be seen as, when compiling and we go down sequentially through the program, we associate the X with what is most recently read, when we get to the function declaration

![[Pasted image 20230228111511.png]]
Dynamic scope uses the most recent value to increment.

if y > 0 we print 1. Because that x which is used and changed around is the x in the scope.
else we print 0, as the changed X in fie() is the X defined most recently. I.e we dont use the outermost X. The X is not scoped, as its just a function call 


# 3. Consider the following code fragment in which there are gaps indicated by (\*)and (\*\*). Provide code to insert in these positions in such a way that:
``` java
{int i;
(**)
for (i=0; i<=1; i++){
	int x;
	(**)
	x= foo();
	}
}
```
a. If the language being used employs static scope, the two calls to the proce-
dure foo assign the same value to x.
The function foo must be appropriately declared at (\*)
b. If the language being used employs dynamic scope, the two calls to the pro-
cedure foo assign different values to x.
The function foo must be appropriately declared at (\*)
``` java
{int i = 0;
 int j = 0;
int foo() { return j; }
for (i=0; i<=1; i++){
	int x;
	int j = i;
	x= foo();
	}
}
```

# 4. Provide an example of a denotable object whose life is longer than that of the references (names, pointers, etc.) to it.

``` c
int x = 0;
void foo(int *y) {
	write(*y);
}
foo(*x);
```
x lives after the foo() call, and y does not, and it is a reference to it. 

# 5. Provide an example of a connection between a name and a denotable object whose life is longer than that of the object itself.
```c
int* x = malloc(sizeof(int));
int* y = x;
free(x);
```
The object is gone, but we still have a reference to the object, so the connection is still there.

```c
int *foo() {
	int x = 5;
	return &x;
}

int *y = foo();
write (*y);
```
We still have pointer to x, but the denotable object is gone after `foo()`

