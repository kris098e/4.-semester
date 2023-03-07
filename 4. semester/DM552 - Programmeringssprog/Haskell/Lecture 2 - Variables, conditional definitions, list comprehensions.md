Program -> declaration
declaration -> type declaration | function declaration
Typedefinition -> var+ "::" type
var -> (a... z)(A|.. Z|a|...|z|0|...|9)
function definition -> fun left hand side - right hand side
function left hand side -> var pat*
right hand side -> "= exp | conditions right hand side +
cond rhs -> "|" exp = exp
and :: Bool -> Bool -> Bool
and x y | x = y | otherwise = false
and False (and...) -> False
and (x, y) | x = y | otherwise = False
f :: Bool -> Bool
f y = False
add :: Int -> (Int -> Int)
add x y = x + y
add :: (Int, Int) -> Int
add (x, y) = x + y
add 3 -> \\y -> 3+y (partial application)
sub 3 -> \\y -> 3-y
(swap sub) 3 -> \\x -> x - 3
curry :: ((a,b) -> c) -> a -> (b -> c)
curry f   f y = f(x, y)
curry add' -> add
uncurry :: a -> (a -> b -> c) -> ((a,b) -> c)
uncurry f (x,y) = f x y
and True y = True
and False y = False
and False True -> False
or False y = y
or _  _ = True
not :: Bool -> Bool
not True = false
not _  = True
length :: [a] -> Int
length [] = 0
length (x:xs) = 1 + length xs
three :: Int -> Int
three x = 3
a2a :: Int -> Int
a2a x = a2a (x + 1
three (a2a 4) -> 3
and :: (Bool, Bool) -> Bool

max :: Int -> Int -> Int
max x y | x > y = x | otherwise (true) = y

##### List comprehensions
exp -> var | const | var exp* | "\[" exp "|" (gen | exp)* "]" 
[x*x*x | x <- [1..10]]
[(x,y) | <- [1..10], y <- ["a" - "c"]]

##### Type declaration
type dec -> "data" type constructor var* "=" constr
type constr -> ("A"|...|"z")("A"|...| "Z"|"a"|...|"z"|"0"|...|"9")
data Bool = False | True
data List a = Empty | Insert a (List a)
trans Insert 23 (Insert 42 empty) = [23,42]
:t Insert
a -> list a -> List a
trans :: List a -> [a]
trans empty = []
trans (Insert x xs) = x:xs

data Tem = False | Maybe | True
and :: Tem -> Tem -> Tem
and False y = False
and True y = y
and maybe q -> q