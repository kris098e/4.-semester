[[exercise02.pdf]]
[[solution02.pdf]]

Exercise 2-1: Combinatoric explosion
Exercise 2-2: Itemsets and Association Rules
Exercise 2-3: Apriori candidate generation
Exercise 2-4: The monotonicity of confidence
Exercise 2-5: Tools

##### Exercise 2-1: Combinatoric explosion

(a)
It is $2^{3}$ = 8

{}
{"cherries"}
{“bananas”}
{“apples”}
{“apples”, “bananas”}
{“cherries”, “bananas”}
{"cherries", “apples”}
{"bananas", "cherries", “apples”}

(b)
$2^7$ = 128 transactions

(c)
$2^n$ permutations

(d)
3 items with exactly two items (i.e., 2-itemsets)

3 itemset -> 3
5 itemsets -> n = 5, k = 2 -> 10
k itemsets -> 

$$\frac{n!}{k!(n-k)!}$$

##### Exercise 2-2: Itemsets and Association Rules

Support (Number of time occuring)
Confidence (Support devided with the number of the left side occurring)

(a)
Support = 4
confidence = 4/5 = 80 %

(b)
Support = 4
Confidence = 4/7 = 57 %

(c)

$$\frac{6!}{3!(6-3)!} = 20$$

(d)

$$
\sum_{i=1}^{5}(2^{6-i} - 1) = 602
$$

(e)



(f)
s({Bread, butter}) = 5

(g)
conf(Bread => butter)

##### Exercise 2-3: Apriori candidate generation

{1, 2, 3}, {1, 2, 4}, {1, 2, 5}, {1, 3, 5}, {2, 3, 4}, {2, 3, 5}, {2, 3, 6}, {2, 5, 6}, {3, 4, 5}, {3, 5, 6}

candidate 4-itemsets

Join:
{1, 2, 3, 4}, {1, 2, 3, 5}, {1, 2, 4, 5}, {2, 3, 4, 5}, {2, 3, 4, 6}, {2, 3, 5, 6}

Pruning:
{1, 2, 3, 5}, {2, 3, 5, 6}



##### Exercise 2-4: The monotonicity of confidence

