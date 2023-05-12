[[202006.pdf#page=2]]
# 2
partial evaluator is a program given D0 and D1 and outputs D2
$p:(D_{1}, D_{2})\to D_{2}$
![[Pasted image 20230510122700.png]]
see that we have an interpreter written in L1 to L2 and from L2 to L3, so apply the first interpreter and can input to the next one.  So we get from L1 to L3. I.e an interpreter from L1 to L3

I does not matter what the partial evalutor is written in, it just means that the computer uses L0, and can output something in L1

# 1.3 Describe the differences between the interpretative and compiled implementations of a programming language, emphasising the advantages and disadvantages.

## compiler
### advantages
* Faster to run when precompiled
* 
### cons
* code for compilers are more complex and harder to implement
* inflexible, may destroy the overall structure of the program (does not have the source), when compiling to the machine code - fx. doing tricks to make it faster

## Inerpreter
### advantages
* easier to make
* flexible, still have the overall structure and source
### cons
* Slow


# 1.5 What are the advantages in using an intermediate machine for the implementation of a language?
the idea is that we translate a program into another intermidate program. If we want the code to be run on 3 different machines, we need to make 3 compilers (1 for each ). If we use intermidate machines we can then compile the program into an intermediate prorgram, and  then this program can then have compilers for each. We leave the responsibility to the intermediate program to have compilers
* we need only n+m  compilers, rather than n\*n compilers. because we compile down to 1 program and then this program compiles into m other. If we have only the program, we have n programs that has to write compilers for the n other machines that wants to run the code



# 1.6 The first Pascal environments included:
• A Pascal compiler, written in Pascal, which produced P-code (code for the
intermediate machine);
• The same compiler, translated into P-code; (probably such that the intermediate machine could also compile a Pascal program into P-code such that it can compile the pascal without another machine.)
• An interpreter for P-code written in Pascal.
## To implement the Pascal language in an interpretative way on a new host machine means (manually) translating the P-code interpreter into the language on the host machine. Given such an interpretative implementation, how can one obtain a compiled implementation for the same host machine, minimizing the effort required? (Hint: think about a modification to the compiler for Pascal also written in Pascal.)
the notation means 
function[program, input] = output
![[Pasted image 20230222112107.png]]
compile a program written in pa to pc, which is written in Pc. We can then change what the compiler (given as input) is written in to Pc, which gives us the compiler written in Pc, which compiles a program from Pa to L. 
The interpeter is the meaning of: Think about having a python script written in python for a program writte in in Pc. We would still need `python3 compile.py program.pc` , as we only have the interpeter. So the language is L and we interpet a program written in Pc.

![[Pasted image 20230221102253.png]]
![[Pasted image 20230222104056.png]]
last Peval: when we partially evaluate a program written in M and we are given an interpeter from M -> L, then we have given the entire input $P^M$, to the interpeter generating a program in $P^L$.