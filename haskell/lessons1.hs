square x = x * x

doubleIt :: Int -> Int
doubleIt x = x * 2

doubleIfSmallNumber :: Int -> Int
doubleIfSmallNumber x = (if x < 100 then x * 2 else x) + 1

weirdBehaviour 1 = 1
weirdBehaviour 2 = 5
weirdBehaviour x = x*2

listInterpitation :: [Char] -> [Char]
listInterpitation [] = "he"
listInterpitation x = if length x == 1 then take 5 (cycle x) else take 10 (cycle x)

myhead :: [a] -> a
myhead [] = error "Empty List"
myhead (x:xs) = x

mytail :: [a] -> [a]
mytail (x:xs) = xs

mynull :: [a] -> Bool
mynull [] = False
mynull x = True

myLast :: [a] -> a
myLast (x:xs) = if mynull xs then x else myLast xs

myLength :: [a] -> Int
myLength [] = 0
myLength (x:xs) = 1 + myLength xs

myRepeat :: a -> [a]
myRepeat x = x:(myRepeat x)

myReplicate :: a -> Int -> [a]
myReplicate x i = if i > 1 then x:(myReplicate x (i-1)) else x:[]

myMaximum :: Int -> Int -> Int
myMaximum x y = if x >= y then x else y

mySum :: [Int] -> Int
mySum [] = 0
mySum (x:xs) = x + mySum xs  

myReverse :: [a] -> [a]
myReverse [] = []
myReverse (x:xs) = ((myReverse xs)++x:[])

root :: (Floating t, Ord t) => t -> t -> t -> (t,t)
root a b c
    | d == 0 = (calcrootOnce, calcrootOnce)
    | d > 0 = (calcrootTwice, calcrootTwice)
    | d < 0 = error "d has no solutions"
    where
        d = (b*b) - 4*a*c
        calcrootOnce = a*b*c
        calcrootTwice = a+b*c


root' :: (Floating t, Ord t) => t -> t -> t -> (t,t)
root' a b c =
    let d = (b*b) - 4*a*c
        calcrootOnce = a*b*c
        calcrootTwice = a-b*c
    in case compare d 0 of 
                 EQ -> (calcrootOnce, calcrootOnce)
                 GT -> (calcrootTwice, calcrootTwice)
                 LT -> error "d has no solutions"
    -- or:  in case (d > 0) of True -> ... False -> ...

second :: [a] -> a
second (a : b : xs) = b 
second _ = error ".."
 

secondLast :: (Ord a) => [a] -> a
secondLast [] = error "not long"
secondLast (x : []) = error "not long"
secondLast (x:xs)
    | length xs == 1 = x
    | otherwise = secondLast xs

swap :: (a, b) -> (b, a)
swap (x1, x2) = (x2, x1)

pair :: a -> (a,a)
pair x = (x, x)

palindrome :: (Ord a) => [a] -> Bool
palindrome xs
    | xs == [] = True
    | xs == reversed = True
    | otherwise = False
    where
        reversed = reverse xs

palindrome' :: (Ord a) => [a] -> Bool
palindrome' list = reverse list == list

twice :: (a -> a) -> a -> a
twice f x = f (f x)


flatten :: [[a]] -> [a]
flatten lists = [x | list <- lists, x <- list]

flatten' :: [[a]] -> [a]
flatten' [] = []
flatten' (xs : xss) = xs ++ flatten' xss


alternate :: Floating a => [a] -> [a]
alternate xs = f xs
    where
        f [] = []
        f (y : ys) = y : g ys
        g [] = []
        g (y : ys) = negate y : f ys



