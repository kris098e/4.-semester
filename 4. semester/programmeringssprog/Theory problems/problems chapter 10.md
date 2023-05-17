![[Pasted image 20230503083913.png]]
![[Pasted image 20230503083921.png]]
[[_10a_generics_and_implementation.pdf#page=11]] Here we should just believe they point to the vtable. 
they are the same. This means that all values will be 1 + 2 + 3 = 6. as seen by we go through in the vtable going from D to C to B to A and find the pointers needed.  

![[Pasted image 20230503084015.png]]
![[Pasted image 20230503084024.png]]
Again just think about it as it points to the same v-table, using the same values as D would use.

u prints 7
v prints 9
w prints 7
z prints 9

![[Pasted image 20230503084112.png]]
it is correct but only for overloading the method, not overriding.
A is not compatible with B
It has to chose the function in class A since it is given something of class A. Since B has stuff that A does not.
Method overloading

prints 8