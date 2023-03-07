### Exercise 2-1 Combinatoric explosion
#### A) A database contains transactions over the following items: “apples”, “bananas”, and “cherries”. Howmany different combinations of these items can exist (i.e., how many different transactions couldpossibly occur in the database)?(We do not distinguish whether a transaction contains a fruit once or several times, e.g., if someonebought one apple or several apples would just result in the transaction containing “apples”.)
$2^3=\{\{\}, (A), (B), (C), (A,B), (A,C), (B,C), (A,B,C)\}$

#### B) The database now also contains the items “dates”, “eggplants”, “figs”, and “guavas”. How many pos-sible transactions do we have now? 
$$\begin{align}
2^7=128
\end{align}$$


#### C) How many combinations (possible different transactions) do we have with n items?
$$\begin{align}
2^n
\end{align}$$

#### D) How many transactions with exactly two items (i.e., 2-itemsets) can we have when the databasecontains 3 items? When it contains 5 items? How many k-itemsets do we have when the database contains n items?
if we dont care about that A,B} is different from {B,A} then it is calculated by 
$$\begin{align}
\frac{n!}{(n-k)!}
\end{align}$$
the number of k-itemsets of n different items is the expression
$$\begin{align}
\frac{n!}{k!(n-k)!}
\end{align}$$

### Exercise 2-2 Itemsets and and association rules Given a set of transactionsTaccording to the following table:
![[Pasted image 20230217082553.png]]

#### a) What are the support and confidence of {milk} => {Diapers}?
We see _Milk_ 5 times and *Diapers together with Milk 4 times* the confidence is then
$$\begin{align}
\frac{4}{5}=0.80
\end{align}$$
The support is then 4 since we see diaparers with milk 4 times
#### b) What are the support and the confidence of {Diapers}⇒{Milk}?
we see *Diapers* 7 times and *Diapers together with milk 4 times* i.e the confidence of this rule is then
$$\begin{align} 
\frac{4}{7}
\end{align} $$
#### c) What is the maximum number of size-3 itemsets that can be derived from this data set?
The database contains {beer, cookies, milk, diapers, bread, butter} such that we have 6 items. We calculate this by the formula 
$$\begin{align}
\frac{n!}{k!(n-k)!} = \frac{6!}{3!(6-3!)}=20
\end{align}$$

#### d) What is the maximum number of association rules that can be extracted from this dataset (includingrules, that have zero support)?



#### e) What is the maximum size of frequent itemsets that can be extracted (assuming σ >0)?

6,9 as they are the biggest itemsets, and as the support just has to be 1 then they simply just have to exist in the database

#### f) Find an itemset (of size 2 or larger) that has the largest support.
Just look at the table
s({bread, butter}) = 5

#### g) Find a pair of items, a and b, such that the rules {a}⇒{b} and {b}⇒{a} have the same confidence.

bread => butter and butter => bread has the same confidence.


### Exercise 2-3: Apriori candidate generation
Given the frequent 3-itemsets
$$\begin{align}
\{1,2,3\},\{1,2,4\},\{1,2,5\},\{1,3,5\},\{2,3,4\},\{2,3,5\},\{2,3,6\},\{2,5,6\},\{3,4,5\},\{3,5,6\}
\end{align}$$
List all candidate 4-itemsets following the Apriori joining and pruning procedure.
![[Pasted image 20230217085005.png]]
##### joining
$$\begin{align}
\{1,2,3,4\}, \{1,2,3,5\}, \{1,2,4,5\}, \{2,3,4,5\}, \{2,3,4,6\}, \{2,3,5,6\}
\end{align}$$
##### pruning
$\{1,2,3,4\}\{1,2,4,5\},\{2,3,4,5\},\{2,3,4,6\},$ are removed because they contain itemsets that are not in the frequent $(k-1)-itemset \notin S_{k-1}$ 
We then end up with
$$\begin{align}
\{1,2,3,5\}, \{2,3,5,6\}
\end{align}$$

### Exerice 2-4: The monotonicity of confidence
#### Theorem 2.1 in the Lecture states:
Given:
— itemset X
— Y⊂ X,Y $\neq\{\}$
If conf(Y⇒(X \\ Y))< c, then ∀ Y′ ⊂ Y
$$\begin{align}
conf(Y′⇒(X\Y′))< c.
\end{align}$$
#### a) prove the theorem
Which makes sense since the support the $Y'$ can only be larger or equal to $Y$ and $X union Y$ can only be the same for all subsets of y, as Y⊂ X and when unioning X and Y we will get full X

What is stated is that, an association rule Y => X \ Y is < c. I.e if we look at 
$$\begin{align}
X=\{Milk, Sugar, Flour\} \\ 
\end{align}$$
then if we choose
$$\begin{align}
Y=\{Milk,Sugar\}
\end{align}$$
And the confidence is low for the rule
$$\begin{align}
Y\X\implies X
\end{align}$$
I.e
$$\begin{align}
\{Milk,Sugar\}\implies\{Flour\}
\end{align}$$
Then for all subsets of Y containing what is taken out of y will also have lower confidence. I.e
$$\begin{align}
\{Milk\} \implies\{Sugar, Flour\}
\end{align}$$

#### b) Sketch an algorithm (pseudo code) that generates all association rules with support σ or above and a minimum confidence ofc, provided the set F of all frequent itemsets (w.r.t. σ) with their support, efficiently using the pruning power of the given theorem
``` java
call rules with all frequents as testSet

Map<Item, Item> rules(Set<Item> frequents, int threshold, double conf, 
					Item testSet) {

	// Only run if testSet is not the empty set.
	Map<Item, Item> rules;
	{
		// Start with large subset of 
		List<Item> subset = testSet.permutes(0, #itemsInItem - 1)
		// item excluding subset : subset
		Map<Item, Integer> rulesForThisItem;
		
		for(Item test : subset) {
		int countSeen = 0
			for(Item item : frequents) {
				if(test in item) {
					countSeen++
					rulesForThisItem.atKey(testWithOutSubset)++
				}
			}
			if(countSeen > threshold) {
				for(key, value in rulesForThisItem) {
					if(value/count > conf)
						// if conf is high enough for this association rule, add 
						// it 
						// to the association rules
						rules.put(key, item)
				}
			}
			// when seen enough times, we continue with the subset
			for(Item subsetWith1Less : subset.permute1Less) {
				map = rules(frequents, threshold, conf, testSet)
				// add all rules with high enough confidense
				map.putAll(rules)
			}
		}
		}
	}
	return rules
}
```
