[[01_abstract_machine.pdf#page=30]]

1.3, 1.5, 1.6, 1.7

- Homework assignment from slides
	
	$\text { Peval }^{L 0}{ }_{L 0}\left(\text { Peval }^{L 0}{ }_{L 0}, \text { Peval }^{L 0}{ }_{L 0}\right)$

	We get a Program evaluation that is an optimized Program evaluation

3. Describe the differences between the interpretative and compiled implementations of a programming language, emphasizing the advantages and disadvantages.

	Interpretive and compiled implementations of a programming language refer to the ways in which code written in a programming language is executed.

	**Interpretive** implementations are executed directly from the source code, without any pre-compilation step. The code is read and executed line by line, and any errors or exceptions are raised during the execution process. This type of implementation is generally slower than compiled implementations, but it offers several advantages:
	
	-   Easy to use: No pre-compilation step is needed, making it easier to get started with the language.
	    
	-   Flexible: The code can be easily modified and tested during runtime.
	    
	-   Cross-platform compatibility: Interpretive implementations are not tied to a specific operating system or architecture, which makes it easier to port the code to different platforms.
	    
	-   Debugging: Debugging is easier with interpretive implementations, as the code is executed line by line, and any errors or exceptions can be caught immediately.    

	- Slow

	- Flexible

	- Still have a source
	
	**Compiled** implementations, on the other hand, require a pre-compilation step, where the source code is transformed into machine code that can be executed directly by the computer's processor. Compiled implementations are generally faster than interpretive implementations, but they come with some disadvantages:
	
	-   Slow development: The pre-compilation step slows down the development process, as the code must be recompiled every time it is changed.
	    
	-   Lack of flexibility: Once compiled, the code cannot be easily modified during runtime.
	    
	-   Platform dependence: Compiled implementations are tied to a specific operating system and architecture, and cannot be easily ported to different platforms.
	    
	-   Difficult debugging: Debugging compiled code can be more difficult, as errors may only be caught during runtime.    

	- Harder to make

	- Inflexible

	- Does not have source
	
	In conclusion, the choice between interpretive and compiled implementations of a programming language will depend on the specific needs of the project and the trade-offs that the developer is willing to make between speed, ease of use, and flexibility.

5. What are the advantages in using an intermediate machine for the implementation of a language?

	Virtual machines, or intermediate machines, are more commonly used in compiled languages, as they provide a platform-independent environment for executing code and can help to improve performance, security, and deployment.

	An intermediate machine can help to improve performance, security, and deployment.

	We need only $n + m$ compilers rather than $n *  m$

6. The first Pascal environments included:
	• A Pascal compiler, written in Pascal, which produced P-code (code for the intermediate machine);
	• The same compiler, translated into P-code;
	• An interpreter for P-code written in Pascal.
	
	To implement the Pascal language in an interpretative way on a new host machine means (manually) translating the P-code interpreter into the language on the host machine. Given such an interpretative implementation, how can one obtain a compiled implementation for the same host machine, minimising the effort required? (Hint: think about a modification to the compiler for Pascal also written in Pascal.)

	Pa -> pascal
	Pc -> p code

	$C_{p_a \rightarrow P_c}^{P_a}$
	$C_{p_a \rightarrow P_c}^{P_c}$
	$I_{P C}^{Pa}$


	$\begin{array}{l}\text { Mannally compile } I_{p_c}^{p_a} \text { into } T_{p c}^L \\\end{array}$
	
	after $C_{p_a \rightarrow P_c}^{P_a}$ into $C_{P_a \rightarrow L}^{P_a}$ 

	$I_{P C}^L\left[C_{P_a \rightarrow Pc}^{P_C}, C_{P_a \rightarrow L}^{P_a}\right]=C_{P_a \rightarrow L}^{Pc}$


	$I_{P C}^L\left[C_{P_a \rightarrow L}^{P_C}, C_{P_a \rightarrow L}^{P_a}\right]=C_{P_a \rightarrow L}^L$


7. Consider an interpreter, $\mathscr{I}_{\mathscr{L} 1}^{\mathscr{L}}(X, Y)$, written in language $\mathscr{L}$, for a different language, $\mathscr{L}$ 1, where $X$ is the program to be interpreted and $Y$ is its input data. Consider a program $P$ written in $\mathscr{L} 1$. What is obtained by evaluating i.e., from the partial evaluation of $\mathscr{I}_{\mathscr{L} 1}^{\mathscr{L}}$ with respect to $P$ ? (This transformation is known as Futamura's first projection.)

	Fatumas first prediction
	
	An compiler is achieved L1 -> L

