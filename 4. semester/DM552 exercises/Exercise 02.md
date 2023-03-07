Assignments: Chap 4 1-5

#### 1
Consider the following program fragment written in a pseudo-language which uses static scope and where the primitive $read (Y)$ allows the reading of the variable $Y$ from standard input.

```
	...
	int X = 0;
	int Y;
	
void fie(){
	X++;
}
void foo(){
	X++;
	fie();
}
read(Y);
if Y > 0 {
	int X = 5;
	foo();
	}
else foo();
write(X);
```

State what the printed values are.

[[04_name_scopes.pdf#page=18]]
• A non-local name is resolved in the block that encloses it

It prints 2 whatever the input for y


#### 2
Consider the following program fragment written in a pseudo-language that uses dynamic scope.

```
	...
int X;
X = 1;
int Y;
void fie() {
	foo();
	X = 0;
}
void foo(){
	int X;
	X = 5;
}
read(Y);
if Y > 0{
	int X;
	X = 4;
	fie();
	}
else fie();
write(X);
```

State which is (or are) the printed values.

[[04_name_scopes.pdf#page=19]]

the possible printed values are 0 and 1, depending on the value of $Y$.

If input y > 0: prints 1
else: prints 0


#### 3
Consider the following code fragment in which there are gaps indicated by (\*)
and (\*\*). Provide code to insert in these positions in such a way that:
- a. If the language being used employs static scope, the two calls to the procedure
	foo assign the same value to x.
- b. If the language being used employs dynamic scope, the two calls to the procedure 
	foo assign different values to x.
The function foo must be appropriately declared at (\*).

```
{int i;
(*)
for (i=0; i<=1; i++){
	int x;
	(**)
	x = foo();
	}
}
```

Solution:

```
int i = 0; 
int j = 0;

int foo() { 
	return j; 
	} 
	
for (int i = 0; i <= 1; i++) { 
	int x; 
	int j = i;
	x = foo(); 
	} 
```


#### 4
Provide an example of a denotable object whose life is longer than that of the references (names, pointers, etc.) to it.

```
int x = 0;
void foo(int * y){
	write(*y);
}

// Error
foo(&x);
```

#### 5
Provide an example of a connection between a name and a denotable object whose life is longer than that of the object itself.

```
int * foo(){
	int x = 0;
	return &x;
}

int * y = foo(){
	//Error
}
```