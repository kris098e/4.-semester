# 1,3-6
![[Pasted image 20230411141313.png]]
$2*(10*10*4)+2*(10*4)+5*5=900$


# 3. Consider the following (Pascal) declarations:
type string = packed array [1..16] of char;
![[Pasted image 20230411141346.png]]
Have 16 bytes for the name
1 byte for the student, since it is bool
and then 4 bytes for an integer **or** 4 bytes for pointer socialsecno.

total of 21 bytes

**ANSWER**
in memory, we will have nothing at name, true for student, first we write the year, however it will later get overwritten by the **socialsecno**. This happens because we only have **one** memory allocation of 4 bytes for the year and the socialsecno.

So the memory will be nothing for name, true for student and C (the pointer) in memory

If the String pointer is fx 5 bytes, the field in the `Person` will just have 5 bytes of memory, even tho it may only be filled with 4 bytes.
![[Pasted image 20230411141355.png]]
```haskell
data Nat = Zero | Succ Nat

equal zero zero = True
equal (Succ _) zero = False
equal Zero (Succ _) = False
equal (Succ a) (Succ b) = equal a b
```
`Succ Zero` will be `1`, `Succ(Succ(zero))` will be `2`. So when it comes down when removing all those `Succ`, it will come down to `Zero`. 

Here `null` is `zero`

![[Pasted image 20230411141417.png]]
Yes they are the same, because T2 and T1 are the same when it comes to the structure


![[Pasted image 20230411141434.png]]
K has the type `a->b->a` 
H has the type `(a->Bool)->a->a->a`
G has the type `(a->a)->a->a`
