[[DM566-2023-part2.pdf]]

Feature Spaces:  
  - Descriptors  
  - Image/text features  
  
Clustering:  
  - Partitional clustering  
  - Visualization  
  - Non-metric spaces  
  - Initialization  
  - Model selection and evaluation

Norm?! = Euclidian distance

### Feature spaces
##### Aggregations of Features
- mode: the value with largest frequency (Largest number)
- median: the central element in the sample ordered by value
- arithmetic mean: $$
\mu=\bar{x}=\frac{1}{n} \cdot \sum_{i=1}^n x_i
$$
##### Spaces and Distance Functions

L2 norm
$$
\begin{aligned}
& L_2(x, y)= \sqrt{(x-y)(x-y)} \\
\end{aligned}
$$
$$
\begin{aligned}
& x=\left(\begin{array}{ll}
x_1 \\
x_2
\end{array}\right) \quad y=\left(\begin{array}{l}
y_1 \\
y_2
\end{array}\right) \quad M=\left(\begin{array}{ll}
a_{11} & a_{12} \\
a_{21} & a_2
\end{array}\right)
\end{aligned}
$$

### Clustering
#### Categories of Clustering Approaches 

[[DM566-2023-part2.pdf#page=46 |(Basics and k-means)]]
##### Partitioning 
###### Basics
- model: clusters are compact sets of points 
- parameter: (usually) number k of clusters, distance measure 
- looks for a flat partitioning into k cluster with maximal compactness

centroid $\mu_C$ : mean vector of all points in cluster $C$

$$
\mu_{C_i}=\frac{1}{\left|C_i\right|} \cdot \sum_{o \in C_i} o
$$

measure of compactness for a cluster C:
$$
T D^2(C)=\sum_{p \in C} \operatorname{dist}\left(p, \mu_C\right)^2
$$

##### k-means Clustering
- Lloyd/Forgy Algorithm
- MacQueen Algorithm
	- a centroid is immediately updated when some point changes its assignment 
	- k-means has very similar properties, but the result now depends on the order of data points in the input file

pros
- efficient: $\mathcal{O}(k \cdot n)$ per iteration, number of iterations is usually in the order of 10.
- easy to implement, thus very popular
cons
- $k$-means converges towards a local minimum
- $k$-means (MacQueen-variant) is order-dependent
- deteriorates with noise and outliers (all points are used to compute centroids)
- clusters need to be convex and of (more or less) equal extension
- number $k$ of clusters is hard to determine
- strong dependency on initial partition (in result quality as well as runtime)

##### Density-based
- model: clusters are areas of high density, separated by areas of low density 
- parameter: minimal density in some cluster, distance measure 
- looks for a flat partitioning into clusters exceeding some minimal density

##### Hierarchical
- model: compactness, density,. . . 
- parameter: distance measure for points and for clusters 
- looks for a hierarchy of clusters (e.g., given as a tree), joins the most similar clusters at a given level of the hierarchy 
- flat clusters can be derived by cutting the tree on some level

##### Other categories
Alternative categorizations could sort approaches according to the algorithmic approach or to the application scenario of specialized approaches: 
- many variants of techniques, such as fuzzy clustering, graph-theoretic algorithms, neuronal nets 
- specializations to special data characteristics (time series, graphs, high-dimensional data, stream data, uncertain data etc.)