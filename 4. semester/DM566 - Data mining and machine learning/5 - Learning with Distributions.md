[[DM566-2023-part5.pdf]]


[[DM566-2023-part5.pdf#page=21]]
##### Covariance
Definition 1.9 (Covariance)
The covariance of two random variables $X$ and $Y$ is
$$
\operatorname{Cov}(X, Y)=E[(X-E[X])(Y-E[Y])]
$$
Theorem 1.10
For any two random variables $X$ and $Y$,
$$
\operatorname{Var}[X+Y]=\operatorname{Var}[X]+\operatorname{Var}[Y]+2 \operatorname{Cov}(X, Y)
$$

##### Correlation
Definition 1.11 (Correlation)
The correlation coefficient of two random variables $X$ and $Y$ is given by
$$
\operatorname{Corr}(X, Y)=\rho_{X, Y}=\frac{\operatorname{Cov}(X, Y)}{\sqrt{\operatorname{Var}[X]} \sqrt{\operatorname{Var}[Y]}}
$$

It is strong i we get a line (-1.00;1.00)
Parted: Low variance (0.00)

##### Independence and Expectation
Variance 0 -> Independent

Theorem 1.12
If $X$ and $Y$ are two independent random variables, then
$$
E[X \cdot Y]=E[X] \cdot E[Y]
$$
Corollary 1.13
If $X$ and $Y$ are independent random variables, then
$$
\operatorname{Cov}(X, Y)=0
$$
and
$$
\operatorname{Var}[X+Y]=\operatorname{Var}[X]+\operatorname{Var}[Y]
$$

##### Variance of Sum and Sum of Variances
Theorem 1.14
Let $X_1, X_2, \ldots, X_n$ be mutually independent random variables. Then
$$
\operatorname{Var}\left[\sum_{i=1}^n X_i\right]=\sum_{i=1}^n \operatorname{Var}\left[X_i\right]
$$

##### Mean and Median
For any random variable $X$ with finite expectation $E[X]$ and finite median $m$,
1. the expectation $E[X]$ (= mean) is the value of $c$ that minimizes $E\left[(X-c)^2\right]$
2. the median $m$ is a value of $c$ that minimizes $E[|X-c|]$.

Note that:
This is why we use different objective functions, $T D^2$ and $T D$, for $k$-means and $k$-medoids, respectively.