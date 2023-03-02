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

-- slow --
myReverse :: [a] -> [a]
myReverse [] = []
myReverse (x:xs) = ((myReverse xs)++x:[])

-- fast --
myReverse' :: [a] -> [a]
myReverse' xs = myReverseAux [] xs

myReverseAux :: [a] -> [a] -> [a]
myReverseAux acc [] = acc
myReverseAux acc (x:xs) = myReverseAux (x : acc) xs

myelem :: Eq a => a -> [a] -> Bool
myelem _ [] = False
myelem x (y : ys) = x == y || myelem x ys

-- [x+2 | x <- [1,2,3,4]]
-- [[x] | x <- [1,2,3,4]]
-- [x | x<-"hej", x/='e']

filter1 :: (Eq a) => a -> [a] -> Bool
filter1 _ [] = True
filter1 x (y:ys) 
    | x == y = False
    | otherwise = filter1 x ys

filterChars :: (Eq a) => [a] -> [a] -> [a]
filterChars xs y = [x | x <- xs, filter1 x y];


lengthArrFromStrings :: [[a]] -> [Int]
lengthArrFromStrings strings = [length string | string <- strings]

stringsWithAtLeast4Chars :: [[a]] -> [[a]]
stringsWithAtLeast4Chars strings = [string | string <- strings, (length string)>=4]

-- Try using list comprehensions and/or functions to filter the persons,
-- e.g. people starting with 'A', or people with more than 5 letters in their
-- name, or people older than 50
filterPersons :: [([Char], Int)] -> [([Char], Int)]
filterPersons zipped = [(name, age) | (name, age) <- zipped, (head name) /= 'A', (length name) < 6, age < 50]

personsPatterns :: ([Char], Int) -> [Char]
personsPatterns (name, age)
    | (head name) == 'A' = "you start with A"
    | age > 0 = "you are real"
    | otherwise = "i dont know anything about you"


-- not correct calculation. cannot bother.
ageCalculator :: (Int, Int, Int) -> (Int, Int, Int) -> Int
ageCalculator (bday, bmonth, byear) (cday, cmonth, cyear)
    | bmonth > cmonth = cyear - byear - 1
    | otherwise = cyear - byear

insert :: Ord a => a -> [a] -> [a]

insertionSort :: Ord a => [a] -> [a]
insertionSort [] = []
insertionSort (x : xs) = insert x (insertionSort xs)