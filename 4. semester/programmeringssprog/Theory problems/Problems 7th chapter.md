- Chapter 7 exercises 1-5 (parameter passing) 
- Suggested Exercises
	- Chapter 7 exercises 6-9 (higher order + exceptions)
- Chapter 6 exercise 7 (call by name) 
- Chapter 5 exercise 7 
- Chapter 4 exercises 6-13

##### Chapter 7 - Suggested Exercises
6. Based on the discussion of the implementation of deep binding using closures, describe in detail the case of a language with dynamic scope.
**Moral is, when using dynamic scope the variables can change values at runtime, so we need to store the entire call stack previous to when the function was made**
   In a language with dynamic scope, the scope of a variable is determined based on the call stack at runtime. To implement deep binding using closures in such a language, closures need to capture not only the values of their free variables but also the entire call stack at the point of their creation. This is because the values of free variables in dynamic scope languages can change based on the call stack. The closure uses the value of the free variable that was in effect when it was created, rather than the current value of the variable.

if using association list, we can just have a pointer to where we need the variables from. Alternatively we can just use CRT and??? 
   
7. Consider the following fragment in a language with exceptions and call by value-result and call by reference:

```C
{int y=0;
void f(int x){
	x = x+1;
	throw E;
	x = x+1;
}
try{ f(y); } catch E {};
write(y);
}
```

State what is printed by the program when parameters are passed: 
(i) by value-result: Write 0 (since noting is returned from the function, **i.e an exception is thrown before the function terminates itself**. We first copy the whatever is in the actual parameter and use this. The "return value" is then what is assigned to y. When using `result-based passing` it is first at the last statement of the function, that we will update the value to the actual parameter)
(ii) by reference: Write 1

8. In a pseudo-language with exceptions, consider the following block of code:
```C
void ecc() throws X {
	throw new X();
}
void g (int para) throws X {
	if (para == 0) {ecc();}
	try {ecc();} catch (X) {write(3);}
}
void main () {
	try {g(1);} catch (X) {write(1);}
	try {g(0);} catch (X) {write(0);}
}
```

Say what is printed when main() is executed.
Write: 3
Write: 0

9. The following is defined in a pseudo-language with exceptions:
   
```C
int f(int x){
	if (x==0) return 1;
	else if (x==1) throw E;
	else if (x==2) return f(1);
	else try {return f(x-1);} catch E {return x+1;}
}
```

What is the value that is returned by f(4)?
4 (This is because the call when x=3 is the one that is in a try-catch block. If 3 was not in this, then x=4 would have to catch it.)

##### Chapter 7
1. On page 166, commenting on Fig. 7.1, it can be seen that the environment of the function foo includes (as a nonlocal) the name foo. What purpose does the presence of this name serve inside the block?
   
Fig. 7.1 Definition and use of a function
```C
int foo (int n, int a) {
	int tmp = a;
	if (tmp == 0) return n;
	else return n + 1;
}
...
int x;
x = foo(3,0);
x = foo(x + 1,1);
```
such that  it can call itself, recursion


2. State what will be printed by the following code fragment written in a pseudolanguage permitting reference parameters (assume Y and J are passed by reference).
```C
int X[10];
int i = 1;
X[0] = 0;
X[1] = 0;
X[2] = 0;
void foo (reference int Y,J){ // y = 0, J = 1
	X[J] = J + 1; // X[1] = 2
	write(Y); // x[j] = X[1] = 2
	J++; // J = 2
	X[J] = J; // X[2] = 2
	write(Y); // X[i] = X[2] = 2
}
foo(X[i],i); //x[1] = 0, i = 1 &
write(X[i]); // X[i] = X[2] = 2

```
Write: 2
Write: 2
Write: 2

3. State what will be printed by the following code fragment written in a pseudolanguage which allows value-result parameters:
```C
int X = 2;
void foo (valueresult int Y){
	Y++;
	write(X);
	Y++;
}
foo(X);
write(X);
```

Write: 2
Write: 4, but could also be 3 as the "++" may not have been evaluated before returning from the function.

4. The following code fragment, is to be handed to an interpreter for a pseudolanguage which permits constant parameters:

```C
int X = 2;
void foo (constant int Y){
	write(Y);
	Y = Y + 1;
}
foo(X);
write(X);
```
What is the most probable behaviour of the interpreter?
It will throw an error

alternatively it will write the `y` and then throw an error, which is not a nice behaviour, since it should just fail.

5. Say what will be printed by the following code fragment which is written in a pseudo-language allowing name parameters:

```C
int X = 2;
void foo (name int Y){
	X++; // 2 -> 3
	write(Y); // 3 + 1 -> write 4
	X++; // 3 -> 4
}
foo(X + 1);
write(X); // 4
```
have side-effect of y = x + 1.  So evaluate the x when seeing y.

Write: 4
Write: 4

##### Chapter 6
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


##### Chapter 5
7. Consider the following piece of code written in a pseudo-language using static scope and call by reference (see Sect. 7.1.2):
```C
{int x = 0;
int A(reference int y) {
	int x = 2;
	y = y + 1; // y, x = 1. x = 2 
	return B(y) + x; // B(y) + 2. B(2) + 2 = 4. return 9 + 2
}
int B(reference int y){
	int C(reference int y){
		int x = 3; 
		return A(y) + x + y; // A(1) + 3 + 1. 4 +3 + 1 = 8
	}
	if (y == 1) return C(x) + y;  // C(1) + 1 = 8 + 1 = 9. 
	else return x + y; // 2 + 2
}
write (A(x)); // write 11
}
```
Assume that static scope is implemented using a display. Draw a diagram showing the state of the display and the activation-record stack when control enters the function A for the second time. For every activation record, just give value for the field that saves the previous value of the display.

display: 1 entry for each static nesting. First points to the most outer scope. The sequence of calls is outer, (A,B), C
![[Display_chapter_7]]

##### Chapter 4
6. Say what will be printed by the following code fragment written in a pseudolanguage which uses static scope; the parameters are passed by a value.
```C
{int x = 2;
 int fie(int y){
	x = x + y;
	}
	
	{int x = 5;
	 fie(x);
	 write(x);
	}
 write(x);
}
```

1. Write: 5
2. Write: 7 (since fie changes x in the outer scope)

7. Say what is printed by the code in the previous exercise if it uses dynamic scope and call by reference.
   
1. Write: 10
2. Write: 2
   
8. State what is printed by the following fragment of code written in a pseudolanguage which uses static scope and passes parameters by reference.
```C
{int x = 2;
void fie(reference int y){
	x = x + y; // x = 2 + 5 = 7
	y = y + 1; // y = 5 + 1 = 6
}
{int x = 5;
 int y = 5;
 fie(x); // changes x to be equal to 6
 write(x); // 6
}
write(x);
}
```

1. Write: 6 (write in the scope where x was defined)
2. Write: 7 (fie changes the outer x)

9. State what will be printed by the following code fragment written in a pseudolanguage which uses static scope and passes its parameters by value (a command of the form foo(w++) passes the current value of w to foo and then increments it by one).
```C
{int x = 2;
void fie(value int y){
	x = x + y; // x = 2 + 5
}
{int x = 5;
 fie(x++);
 write(x); // 6
 }
write(x); // 7
}
```

Write: 6
Write: 7

10. State what will be printed by the following fragment of code written in a pseudo-language which uses static scope and call by name.
```C
{int x = 2;
void fie(name int y){
	x = x + y; // x = 2 + 5++
}
{int x = 5;
	{int x = 7
	}
 fie(x++); // changes x = 6
 write(x); // write 6
}
write(x); // 
}
```
1. Write: 6
2. Write: 7
	   
11. State what will be printed by the following code written in a pseudo-language which uses dynamic scope and call by reference.
```C
{int x = 1;
int y = 1;
void fie(reference int z){
	z = x + y + z; // z and y is referenced to the same value
	// y = 3 is used.
}
{int y = 3;
	{int x = 3 // comes out of scope right after we exit the block
	}
 fie(y); // y = 3 is used
 write(y);
}
write(y);
}
```

Write: 7
Write: 1

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

13. Consider the following fragment of code in a language with static scope and parameter passing both by value and by name:
```C
{int z= 0;
int Omega(){
	return Omega();
}
int foo(int x, int y){
	if (x == 0) return x;
	else return x + y;
}
write(foo(z, Omega() + z));
}
```

(i) State what will be the result of the execution of this fragment in the case in
which the parameters to foo are passed by name.

Writes 0 -> Omega is not evaluated due to name passing.
But by value the function is evaluated which will end up causing an error.

```C
{int z= 0;
int Omega(){
	return Omega();
}
int foo(int x, int y){
	if (x == 0) return x;
	else return x + y;
}
write(foo(z, Omega() + z));
}
```
(ii) State what will be the result of the execution of this fragment in the case in which the parameters to foo are passed by value.
	
Tries to evaluate omega due to value passing and will create infinite recursion
