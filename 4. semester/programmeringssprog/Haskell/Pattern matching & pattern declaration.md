# pattern matching
```haskell
fac :: Int -> Int
fac 0 = 1
-- pattern match on x+1 means you get fx. fac 5 in, x will then be 4
fac (x+1) = (x+1)*fac(x)


fac2 x | x == 0 = 1
	   | x > 0 = x + (fac(x-1))
```

```Haskell
half 0 = 0
half (x+2) = 1 + half(x)
half x = -1 * (half(-1*x))
```

# pattern declaration
```Haskell
pi::Float
pi = 3.1416
```




# .
can make local declarations by writing and indented"where" after a function delcaration, which makes the functions after "where" local to the function. theese "where"-functions may also only be evaluated once _since its lazy_ , and the function can run faster, if it uses theese more than 1 time

# functions
## Map
```HASKELL
map f xs = [f x | x <- xs]
```
could then have f = some length function

```haskell
map' f [] = []
map' f (x:xs) = (f x) : (map f xs)
```

## Filter
define a function which takes some input and outputs Bool
and then
```haskell
filter f xs = [x | x <- xs, f x]
```
which will filter the xs

