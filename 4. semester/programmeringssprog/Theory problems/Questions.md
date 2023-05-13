![[Pasted image 20230503083913.png]]
![[Pasted image 20230503083921.png]]
they are the same? 
**Why are they the same?** Dont think they are the same, since a does not know about the `n` in class D. B does not know about the `n` either?

# problems 5th chapter
## Assume that B is nested one level deeper than A. To resolve the reference to X present in B, why is it not enough to consider the activation record which immediate precedes that of B on the stack? Provide a counter-example filling the spaces in the fragment with dots with appropriate code.


```java
A:{int X = 1;

  void foo() { x=3 } // shouldnt this also change the reference in the activation record for A?
  void bar() { int x = 5; foo() }
  bar(); // put bars activation record on the stack below A, which will put foo() on top of bar() aswel
  
  B:{X=3;
	  ....
  }
  ....
}
```
Why does this work? Isnt foo and bar activation records popped from the stack, as they become out of scope immediatly after they are called? Also the X created in bar will become out scope after the bar() function is done. The reference to X in A should be enough, when the reference is changed in the activation records of the functions, as this should be reflected in the activation record of A if it is changed within A?

# chapter 4
10. State what will be printed by the following fragment of code written in a pseudo-language which uses static scope and call by name.
```C
{int x = 2;
void fie(name int y){
	x = x + y; // x = 2 + x++ = x = 2 + 2
}
{int x = 5;
	{int x = 7
	}
 fie(x++); // changes x = 6
 write(x); // write 6
}
write(x); //  How does this become 7?
}
```
1. Write: 6
2. Write: 7
