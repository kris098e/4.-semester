

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
When typecasting to a superclass of a class, it will still be using the original methods and the variables within this. However when accessing the variables, it will be using the super?
