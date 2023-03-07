
```Haskell
[1,2,3]
(1:[2,3])
(1:2:3:[])

second :: [a] -> a
second (x:(y:ys))
second \_ = error "List too short"
```


```Haskell
fac :: Int -> Int
for 0 = 1
for (x + 1) = (x + 1) * (factorial x)
for 5 -> (4 + 1) * (fac 4) -> 5 * (factorial c)
```