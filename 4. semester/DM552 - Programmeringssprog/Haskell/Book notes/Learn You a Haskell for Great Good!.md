### Random notes
Typeclass constraint => function -> function

### Introduction
Haskell is a _purely functional programming language_. In imperative languages you get things done by giving the computer a sequence of tasks and then it executes them. While executing them, it can change state.  In purely functional programming you don't tell the computer what to do as such but rather you tell it what stuff _is_. The factorial of a number is the product of all the numbers from 1 to that number, the sum of a list of numbers is the first number plus the sum of all the other numbers, and so on. You express that in the form of functions.

Haskell is _lazy_. That means that unless specifically told otherwise, Haskell won't execute functions and calculate things until it's really forced to show you a result. That goes well with referential transparency and it allows you to think of programs as a series of _transformations on data_.

Haskell is _statically typed_. When you compile your program, the compiler knows which piece of code is a number, which is a string and so on. That means that a lot of possible errors are caught at compile time. If you try to add together a number and a string, the compiler will whine at you. Haskell uses a very good type system that has _type inference_. That means that you don't have to explicitly label every piece of code with a type because the type system can intelligently figure out a lot about it.

Haskell is _elegant and concise_. Because it uses a lot of high level concepts, Haskell programs are usually shorter than their imperative equivalents. And shorter programs are easier to maintain than longer ones and have less bugs.

#### Deeper dive - How to (Interactive mode)
The interactive mode is invoked by typing in ***ghci*** at your prompt. If you have defined some functions in a file called, say, ***myfunctions.hs***, you load up those functions by typing in *:l myfunctions* and then you can play with them, provided myfunctions.hs is in the same folder from which ghci was invoked. If you change the .hs script, just run ***:l myfunctions*** again or do :r.

#### Starting out (2. chapter)
##### Basic arithmetic 
```Haskell
ghci> (50 * 100) - 4999  
1  
ghci> 50 * 100 - 4999  
1  
ghci> 50 * (100 - 4999)  
-244950
```

##### Boolean expressions
```Haskell
ghci> True && False  
False  
ghci> True && True  
True  
ghci> False || True  
True   
ghci> not False  
True  
ghci> not (True && True)  
False
```

Checking for equality
```Haskell
ghci> 5 == 5  
True  
ghci> 1 == 0  
False  
ghci> 5 /= 5  
False  
ghci> 5 /= 4  
True  
ghci> "hello" == "hello"  
True
```

##### Using _infix_ and _prefix_ functions
.* is a function that takes two numbers and multiplies them. As you've seen, we call it by sandwiching it between them. This is what we call an _infix_ function. Most functions that aren't used with numbers are _prefix_ functions. Let's take a look at them.

```Haskell
ghci> succ 8  
9
```

```Haskell
ghci> min 3.4 3.2  
3.2  
ghci> max 100 101  
101
```

##### Making functions

```Haskell
doubleUs x y = doubleMe x + doubleMe y

doubleSmallNumber' x = (if x > 100 then x else x*2) + 1
```

##### Lists
In Haskell, lists are a _homogenous_ data structure. It stores several elements of the same type. That means that we can have a list of integers or a list of characters but we can't have a list that has a few integers and then a few characters.

```Haskell
ghci> let lostNumbers = [4,8,15,16,23,42]  
ghci> lostNumbers  
[4,8,15,16,23,42]
```
using the ++ operator

```Haskell
ghci> [1,2,3,4] ++ [9,10,11,12]  
[1,2,3,4,9,10,11,12]  
ghci> "hello" ++ " " ++ "world"  
"hello world"  
ghci> ['w','o'] ++ ['o','t']  
"woot"
```
Watch out when repeatedly using the ++ operator on long strings. When you put together two lists (even if you append a singleton list to a list, for instance: [1,2,3] ++ [4]), internally, Haskell has to walk through the whole list on the left side of ++.
Putting something at the beginning of a list using the : operator (also called the cons operator) is instantaneous.

```Haskell
ghci> 'A':" SMALL CAT"  
"A SMALL CAT"  
ghci> 5:[1,2,3,4,5]  
[5,1,2,3,4,5]
```

Notice how : takes a number and a list of numbers or a character and a list of characters, whereas ++ takes two lists.
If you want to get an element out of a list by index, use !!. The indices start at 0.
But if you try to get the sixth element from a list that only has four elements, you'll get an error.

```Haskell
ghci> "Steve Buscemi" !! 6  
'B'
```

Lists can be compared if the stuff they contain can be compared. When using <, <=, > and >= to compare lists, they are compared in lexicographical order. First the heads are compared. If they are equal then the second elements are compared, etc.

```Haskell
ghci> [3,2,1] > [2,1,0]  
True
```

Here are some basic functions that operate on lists:
- ***head*** takes a list and returns its head. The head of a list is basically its first element.
- ***tail*** takes a list and returns its tail. In other words, it chops off a list's head.
- ****last** takes a list and returns its last element.
- ***init*** takes a list and returns everything except its last element.
- ***length*** takes a list and returns its length, obviously.
- ***null*** checks if a list is empty. If it is, it returns True, otherwise it returns False. Use this function instead of xs == [] (if you have a list called xs)
- ***reverse*** reverses a list.
- ***take*** takes number and a list. It extracts that many elements from the beginning of the list.
- ***drop*** works in a similar way, only it drops the number of elements from the beginning of a list.
- ***maximum*** takes a list of stuff that can be put in some kind of order and returns the biggest element.
- ***minimum*** returns the smallest.
- ***sum*** takes a list of numbers and returns their sum.
- ***product*** takes a list of numbers and returns their product.
- ***elem*** takes a thing and a list of things and tells us if that thing is an element of the list. It's usually called as an infix function because it's easier to read that way.

```Haskell
ghci> head [5,4,3,2,1]  
5

ghci> tail [5,4,3,2,1]  
[4,3,2,1]

ghci> last [5,4,3,2,1]  
1

ghci> init [5,4,3,2,1]  
[5,4,3,2]

ghci> length [5,4,3,2,1]  
5

ghci> null [1,2,3]  
False  
ghci> null []  
True

ghci> reverse [5,4,3,2,1]  
[1,2,3,4,5]

ghci> take 3 [5,4,3,2,1]  
[5,4,3]
ghci> take 5 [1,2]  
[1,2]

ghci> drop 3 [8,4,2,1,5,6]  
[1,5,6]

ghci> minimum [8,4,2,1,5,6]  
1  
ghci> maximum [1,9,2,3,4]  
9

ghci> sum [5,2,1,6,3,2,5,7]  
31  
ghci> product [6,2,1,2]  
24

ghci> 4 `elem` [3,4,5,6]  
True
```

##### List ranges

```Haskell
ghci> [1..20]  
[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20]

ghci> [2,4..20]  
[2,4,6,8,10,12,14,16,18,20]
```

Watch out when using floating point numbers in ranges! Because they are not completely precise (by definition), their use in ranges can yield some pretty funky results.

- ***cycle*** takes a list and cycles it into an infinite list. If you just try to display the result, it will go on forever so you have to slice it off somewhere.
- ***repeat*** takes an element and produces an infinite list of just that element. It's like cycling a list with only one element.
- ***replicate*** replicates a value x times. **replicate 3 10** returns [10,10,10].

##### List comprehensions

Predicates go after the binding parts and are separated from them by a comma. The element is included in the list only if all the predicates evaluate to True.
```Haskell
ghci> [x*2 | x <- [1..10], x*2 >= 12]  
[12,14,16,18,20]

ghci> [ x | x <- [50..100], x `mod` 7 == 3]  
[52,59,66,73,80,87,94]

ghci> [ x*y | x <- [2,5,10], y <- [8,10,11]]  
[16,20,22,40,50,55,80,100,110]
```

##### Tuples
Unlike a list, a tuple can contain a combination of several types. A tuple of size two (also called a pair) is its own type, which means that a list can't have a couple of pairs in it and then a triple (a tuple of size three).

Functions:
- ***fst*** takes a pair and returns its first component.
- ***snd*** takes a pair and returns its second component. Surprise!
- ***zip*** takes two lists and then zips them together into one list by joining the matching elements into pairs. What happens if the lengths of the lists don't match? The longer list simply gets cut off to match the length of the shorter one. Because Haskell is lazy, we can zip finite lists with infinite lists:

```Haskell
ghci> fst (8,11)  
8
ghci> snd (8,11)  
11

ghci> zip [1,2,3,4,5] [5,5,5,5,5]  
[(1,5),(2,5),(3,5),(4,5),(5,5)]
```
