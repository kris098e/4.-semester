[[exercise04.pdf]]

#### Exercise 4-1 : Distance functions
##### a)
Is not a distance due to the requirement $d: S \times S \rightarrow \mathbb{R}_0^{+}$, and that it might return a negative result
$$
d(x, y)=\sum_{i=1}^n\left(x_i-y_i\right)
$$

##### b)
$$
d(x, y)=\sum_{i=1}^n\left(x_i-y_i\right)^2
$$

Is not a distance function because it's not square rooted after squared

It is reflexive, symmetric and strict
Semi-metric, Ultra-metric

##### c)

$$
d(x, y)=\sqrt{\sum_{i=1}^{n-1}\left(x_i-y_i\right)^2}
$$

Euclidian norm
It is reflexive and symmetric.
Pseudo-metric

d)

$$
d(x, y)=\sum_{i=1}^n\left\{\begin{array}{lll}
1 & \text { iff } & x_i=y_i \\
0 & \text { iff } & x_i \neq y_i
\end{array}\right.
$$

Not a distance function

e)

$$
d(x, y)=\sum_{i=1}^n\left\{\begin{array}{lll}
1 & \text { iff } & x_i \neq y_i \\
0 & \text { iff } & x_i=y_i
\end{array}\right.
$$

Manhattan norm
It is reflexive, symmetric, strict and triangle inequality
Metric



#### Exercise 4-2 : Distances on a database  

It is reflexive, symmetric and triangle inequality
Pseudo-metric

|D1|D2|Eq?|
|---|---|---|
|1|2|1 = False|
|1|3|0 = True|
|1|4|1 = False|
|1|5|sqr(5) = False|
|1|6|sqr(13) = False|
|2|4|0 = True|

It makes sense as long as we don't assume it to be strict. 


#### Exercise 4-3 : k-means 1-dimensional Example  

|Iteration|Cluster 1|Cluster 2|Cluster 3|
|-|-|-|-|
|0|u = 2: 2,3|u = 4: 4|u = 6: 10, 11, 12, 20, 25, 30|
|1|u = 2,5: 2, 3|u = 4: 4, 10, 11|u = 18: 12, 20, 25, 30|
|2|u = 2,5: 2, 3, 4|u = 8,33: 10, 11, 12|u = 21,75: 20, 25, 30
|3|u = 3: 2, 3, 4|u = 11: 10, 11, 12|u = 25: 20, 25, 30

After iteration 3, nothing happens, it stays the same

#### Exercise 4-4 : Silhouette Coefficient  

$$
\begin{aligned}
& P 1:=\langle 10,1\rangle: \\
& P 2:=\langle 2,3\rangle: \\
& P 3:=\langle 3,4\rangle: \\
& P 4:=\langle 1,5\rangle: \\
& P 5:=\langle 7,7\rangle: \\
& P 6:=\langle 6,8\rangle: \\
& P 7:=\langle 7,8\rangle: \\
& P 8:=\langle 7,9\rangle:
\end{aligned}
$$

pic 1
Blue cluster
$S_{c} = 0.7216083745$

Red cluster
$S_{c} = 0.9763782102$

pic 2
Blue cluster
$S_{c} = 1$

Red cluster
$S_{c} = 0.8458266631$

pic 2
Blue cluster
$S_{c} = 0.9640058627$

Red cluster
$S_{c} = 0.8351578274$

Se Maple documents

#### Exercise 4-5 : Tools


