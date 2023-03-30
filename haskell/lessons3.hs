import Data.Char

mymap :: (a -> b) -> [a] -> [b]
mymap f xs = [f x | x <- xs]

auxToUpper :: [Char] -> [Char]
auxToUpper [] = []
auxToUpper (x : xs) = toUpper x : auxToUpper xs

mymapzip :: Num a => (a -> a -> b) -> [a] -> [b]
mymapzip f xs = [f i x | (i,x) <- zip [1 ..] xs]

