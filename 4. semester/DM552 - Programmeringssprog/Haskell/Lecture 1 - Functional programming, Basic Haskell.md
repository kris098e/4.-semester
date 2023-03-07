*Haskell* ([Wiki](https://wiki.haskell.org/Introduction))
Haskell is a computer programming language. In particular, it is a polymorphically statically typed, lazy, purely functional language, quite different from most other programming languages. The language is named for Haskell Brooks Curry, whose work in mathematical logic serves as a foundation for functional languages. Haskell is based on the lambda calculus, hence the lambda we use as a logo.

*Functional programming* ([webopedia](https://www.webopedia.com/definitions/functional-programming/))
Functional programming is the process of constructing programs by applying and composing pure functions, avoiding shared state, mutable data, and side effects. It is a declarative programming paradigm, meaning it’s focused on what to solve. It contrasts with the imperative programming style, such as object oriented programming, in which the focus is on how to solve. Functional programming uses expressions instead of statements, meaning that an expression is evaluated to produce a value.

Functional code is more concise, predictable, and easier to test than imperative code because functions are treated as values and passed to functions as parameters. Programming languages that support functional programming include JavaScript, Scala, Lisp, Erlang, and Haskell.

**Advantages and Disadvantages of Functional programming** ([geeksforgeeks](https://www.geeksforgeeks.org/functional-programming-paradigm/))

**Advantages:**  

1.  Pure functions are easier to understand because they don’t change any states and depend only on the input given to them. Whatever output they produce is the return value they give. Their function signature gives all the information about them i.e. their return type and their arguments.
2.  The ability of functional programming languages to treat functions as values and pass them to functions as parameters make the code more readable and easily understandable.
3.  Testing and debugging is easier. Since pure functions take only arguments and produce output, they don’t produce any changes don’t take input or produce some hidden output. They use immutable values, so it becomes easier to check some problems in programs written uses pure functions.
4.  It is used to implement concurrency/parallelism because pure functions don’t change variables or any other data outside of it.
5.  It adopts lazy evaluation which avoids repeated evaluation because the value is evaluated and stored only when it is needed.

**Disadvantages:**  

1.  Sometimes writing pure functions can reduce the readability of code.
2.  Writing programs in recursive style instead of using loops can be bit intimidating.
3.  Writing pure functions are easy but combining them with the rest of the application and I/O operations is a difficult task.
4.  Immutable values and recursion can lead to decrease in performance.

**Applications:** 

-   It is used in mathematical computations.
-   It is needed where concurrency or parallelism is required.


#### About Haskell and Code

[] = empty list (x: l') = a list starting with x and continuing with the list l' [23, 42] = (23: (43:[])) 

Function for length:
``` Haskell
length :: [a] -> int 
// [a] list of type a length [] = 0 
// empty list = 0 length (_ : xs) = 1 + length xs
```

Function for summing
```Haskell
sum :: Num a => [a] -> a sum [] = 0 sum (x : xs) = x + sum xs
```

Function for reversing a list

```Haskell
rev :: [a] -> [a] rev [] = [] 
// ++ append operator rev (x : xs) = (rev xs) ++ [x]
```

Function for reversing with back insert function
```Haskell
revr :: [a] -> [a] 
revr [] = [] revr (x : xs) = bi 
(rev xs) x 

(:) :: a -> [a] -> [a] 
bi :: [a] -> a -> [a] 
bi [] x = [x] 
bi (x : xs) y = x : 
bi xs y
```

List constructor: :)) :: a -> [a] -> [a] - does not compute anything just creates the list

Faster reverse function with accumulator
```Haskell
frev :: [a] -> [a] frev xs = help xs [] help :: [a] -> [a] -> [a] help [] ys = ys help (x : xs) ys = help xs (x : ys)
```

A program in Haskell is a list of declarations, of which there are two types - Program => declaration program | nothing: 
	1. Type declaration (var1, var2 :: type): - example: length :: [a] -> int - Start with a number of variable(s) - E.g., squre, cube :: int -> int // defines square and cube to be of type int, takes int and gives int. 
	2. Function declaration (): - example: length (\_ : xs) = 1 + length xs - LHS can be a function, pattern or variable. - RHS can be an expression, function or variable