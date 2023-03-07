[[01_abstract_machine.pdf]]
[[02_bnf_semantics.pdf]]

Chap 2 -> Focus on the key parts

## syntax 
* what defines a correct sentence
	* definition of what is correct and what is not
* does so via the BNF algorithm (using context-free grammaer)
	* The expression tree, has to come to the root for the sentence to have correct syntax.
	* However the syntax also has have additional rules, I.e in java (this is an example of contextual grammar)
		``` java
			String R;
			int i = R + 2
		```
		R does not have the correct type, this also has to be checked.
	
## semantics
what happens when an operation is done, what a specific instruction (given some syntax) does to the specific state of the program. have a state where X = 2, and then later the state changes to X = 3.
### implementation
* must not be too exact, must leave room for flexibility, such that different implementations are possible, but following the same semantic.
* 
![[Pasted image 20230221114432.png]]
_to the last part:_ c1 will be performed given the state σ

## pragmatics
**Answers the question** what is the purpose of this construct?” or “what use is a certain command?”. it evolves with the use of the language. For example, there is the principle that
jumps (gotos) should be avoided at all possible times. The choice of the most ap-
propriate mode for passing parameters to a function is also a pragmatic question, as
is the choice between bounded and unbounded iteration

## Implementation
The implementation of the syntax tree and the semantics can be different in the different implementation of a certain specificiation