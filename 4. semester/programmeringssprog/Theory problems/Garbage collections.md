# page 261 / 274
![[Pasted image 20230418142711.png]]

## 8.
all  has the same keys, while pointing to the same object, which has a lock with that number

## 9.
notes: 
* We have a the key for the lock to bar. 
* bar does not have a pointer to an object since it is freed.

## 10.
note:
* remember that we only have a reference to the `p.next` since we garbage collect the others, and only return a pointer to the last object.

## 11.
The one with reference count = 0 goes to the free-list.

## 12.
Note that as the one that is referenced by the one with 0 references, it also gets 0 references.

