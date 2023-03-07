[[05_memory.pdf]]
[[05a_implementing_scoping.pdf]]

Chapter 5 exercises 1,2,3,4,6

#### Memory
[[05_memory.pdf#page=2]]
Types of memory allocation
- Static
	- Cannot be used for recursion due to overriding the same block again and again.
- Dynamic
	- Dynamic allocation is important in recursion. We need to know the number of instances of objects needed -> too many copies

[[05_memory.pdf#page=9]]
Example
Observation
- It is slower to use the activation records due to memory allocation and the creation and deleting than just using a while loop.

[[05_memory.pdf#page=12]]
If something can not be saved in the stack due to too low memory (fx. too large a vector), a heap can be used

[[05_memory.pdf#page=17]]
Issues with non continued blocks and fixed sized blocks using too much spaced compared to how much is practically used

#### Implementing scoping
[[05a_implementing_scoping.pdf#page=4]]
Static link: Points to the block containing it (calling it/the caller) rather that the previous block

Static vs dynamic
	Static:
		- Easy visibility
		- Renaming variables are plausible
	Dynamic
		- Simple to implement