# !REMEMBER AT EXAM!
1. Dont answer on questions which you are not 100% sure of. Negative points will bring **atleast** 1 of your correct answers down.

# THINGS YOU THOUGHT WRONG ABOUT(things written down is what is actually correct)
## KNN
true: with a big $k$ you have a larger bias, the complexity of the model is very low. So
* Big K:
	* **High bias**. because you have very low complexity, the data around you speaks a lot less, meaning you have very high bias since the nearest neighbors should speak a lot.
	* **low variance**: you remember a lot less. You just let the whole data set speak
		* **This means we have underfitting**

## Kmeans
* Big K:
	* **low bias**: its like having KNN with small K. This means that you let the points around speak more having a higher variance.
	* **high variance**: Since we have a big K, this means that we have to remember more. 
		* **This means we have overfitting**
![[Pasted image 20230625123448.png]]

# Clustering
+ k-means and EM-clustering does not use preference score, it is not what you think it is
+ EM is the Circle exercises of calculating the probability for each point belonging to a cluster
+ Mac-queen is order dependant while lloyd-forgy is not

# Training error
+ underfitting means that we have high test error & training error usually with less parameters

# Apriori
+ When looking into if the set should be there after the merge, remember to check for **all subsets**. Fx: `AEF`, then you will have to find `AE`, `AF`, `EF`

# Silhuette score
+ Look into how to calculate by hand

# decision trees
**information gain** & **gini index** see [[_DM566-2023-part6.pdf#page=64]]


# Mads.md 18 decision trees, SVMs perceptron
1. False: Not so binary should not be. This would be multiple vandrette and lodrette lines
2. True: Perceptron is like a neural network, can learn functions
3. False: Does not maximize distance between points
4. False: just like 1
5. True: activation function which is just linear
6. True: Binary split
7. **False: Does not maximize the distance to each support vector. H2 could be a support vector**