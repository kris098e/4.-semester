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
