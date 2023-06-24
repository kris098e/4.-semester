# THINGS YOU THOUGHT WRONG ABOUT(things written down is what is actually correct)
true: with a big $k$ you have a larger bias

# MODULES
Remember to try out all of the scripts on windows, seeing if you have all of the modules which are used installed

# Clustering
+ k-means and EM-clustering does not use preference score, it is not what you think it is
+ EM is the Circle exercises of calculating the probability for each point belonging to a cluster
+ Mac-queen is order dependant while lloyd-forgy is not

# Training error
+ underfitting means that we have high test error & training error usually with less parameters

# Scripts
Naive bayes classifier script does not work

# Apriori
+ When looking into if the set should be there after the merge, remember to check for **all subsets**. Fx: `AEF`, then you will have to find `AE`, `AF`, `EF`

# Silhuette score
+ Look into how to calclulate by hand

# decision trees
remember how to calculate via information gain and gini index

# Mads.md 18 decision trees, SVMs perceptron
1. False: Not so binary should not be. This would be multiple vandrette and lodrette lines
2. True: Perceptron is like a neural network, can learn functions
3. False: Does not maximize distance between points
4. False: just like 1
5. True: activation function which is just linear
6. True: Binary split
7. **False: Does not maximize the distance to each support vector. H2 could be a support vector**
