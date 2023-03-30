
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


partial :: Num a => a -> a
partial = (+)42

-- suggest type for apply f x = f x.        apply :: (a->b) -> a -> b. 2nd argument has same type as what the f function takes in. 
-- compose f g x = f (g x).                 compose :: (c -> d) -> (a->c) -> a -> d. g input type is same as input. f input has to have the same
--                                          type as g output.

modIdx :: [a] -> (a -> a) -> Int -> [a]
modIdx xs f i = [ if j == i then f x else x | (j, x) <- zip [0..] xs ]

setIdx :: [a] -> a -> Int -> [a]
setIdx xs x i = modIdx xs (f x) i
    where 
        f x = const x


plustalk :: Show a => a -> a -> a -> String
plustalk x y z = show x ++ " plus " ++ show y ++ " is " ++ show z

fizzbuzz :: (Show a, Integral a, Eq a) => a -> String
fizzbuzz x 
    | mod x 3 == 0 && mod x 5 == 0 = "Fizzbuzz"
    | mod x 3 == 0 = "Fizz"
    | mod x 5 == 0 = "Buzz"
    | otherwise = show x



-- remove duplicates
compress :: (Eq a) => [a] -> [a]
compress (x:[]) = [x]
compress (x : y : ys)
    | x == y = x : auxcompress ys y -- if they are the same explore further if more duplicates
    | otherwise = x : compress (y:ys) -- otherwise keep x and traverse the list

-- method will only be called if duplicate
auxcompress :: (Eq a) => [a] -> a -> [a]
auxcompress (x:[]) c
    | x == c = [] -- if they are the same and this method has been called with the pattern, dont take the x as it is duplicated
    | otherwise = [x]
auxcompress (x : xs) c
    | x == c = auxcompress xs c -- if they are the same ignore this x
    | otherwise = x : compress xs -- if not, go futher with the rest of the list


-- TA
compress' :: Eq a => [a] -> [a]
compress' [] = []
compress' (x:xs) = x : compress' (dropWhile( (==) x) xs)


myDropWhile :: Eq a => (a -> Bool) -> [a] -> [a]
myDropWhile _ [] = []
myDropWhile p (x : xs)
    | p x = myDropWhile p xs
    | otherwise = x:xs

myTakeWhile :: Eq a => (a -> Bool) -> [a] -> [a]
myTakeWhile _ [] = []
myTakeWhile p (x : xs)
    | p x = x:myTakeWhile p xs
    | otherwise = []


pack :: (Eq a) => [a] -> [[a]]
pack [] = []
pack (x : xs) = (x : takeWhile ((==) x) xs) : pack (dropWhile ((==) x) xs)
