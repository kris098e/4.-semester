[[DM566-2023-part3.pdf]]

Classification:  
 - Introduction  
 - Bias in learning  
 - Overfitting/underfitting  
 - Evaluation  
 - k-NN algorithm


TR=TRaining set
TE=TEst set

domain D = feature space
C = {c1, c2, c3} = classes/**Labels**/**Oracle**/**Ground-truth-labels** 
$f:D\to C$

Predictive-truth-labels are when we predict from a training set something else that isnt inside the known set we trained on

from training set get the hypothosis function that should map $h(o) = f(o)$ where $h(o): D \to C$ as closely as possible.

good to have a function outcome that we know what happens, i.e not just two magical numbers multiplied onto some value. Easier to sell in the real world, as buyers wants to know what they are buying


Agorithms can have **INDUCTIVE BIAS** (_restrictions on the classification function_), fx. having strict lines seperating the class or curly lines or perfect cirkular lines
Algorithm of choise for machine learning comes with **certain biases** Herefore we can choose which bias we want when we have some domain knowledge.

we cant know if we have the perfect apporimation $h: D\to C$ to the true function $f: D\to C$ 

Computational learning theory(COLT)????? => Vlad Vapnik??????????????????

**overfitting is bad**

more specific functions with (i.e more variables, more AND and OR operators used 
=complexity), are not better to understand what is going on. Going more general means less variables needed, singleing in on the most important variables

complexity = higher if we have more AND, OR statements.

when having too high complexity (more variables and booleans) then we are likely to overfit, and we cannot use the function on outside dataset, as much as a more general one with less variable (as this would simply be more an **rembering exercise**). There is a sweet spot to how complex it should be. Too high complexity is also called _remembering data_

**there are both underfitting and overfitting. But there is a sweet spot**

**Biace-variance dilemma**
- variance: how flexible the algorithm is

an algorithm also contain **training error** which can be calculated. We can also have **Test error**

**when training:** can use 50% of a dataset as TR and the remaining 50% is used for the TE to evaluate the output function. We can do this a bit of times and take the average

to figure out if the function **overfits** we see how similar the TR-error and compare it to the TE-error. THey should be similar. If the TR-error is very low and the TE-error is high, then we know we are overfitting

Therefore we look at the **m-fold Cross-Validation** to validate the TR-error and TE-error


can have multiple hypothosis classes/functions, an decide which one does better. i.e $h=\{h_{1}, h_{2}, h_{3}\dots\}$

**training capacity=amount of memory we train on** this is also always contains more variables when the capacity increases.?????

the difference between the test error and training error, we can just take the difference to see if they vary a lot. better if they dont vary from eachother

Nowadays the data sets and models are so big that we just choose a test-set and a training set, freeze it here, train and then evaluate. **The data is big enough, such that we only get a small gain in knowledge if we use other evaluation**

TP= true positive
FP= false positive
FN= false negative

precision=$\frac{TP}{TP+FP}$: ratio that the model for the model to make a positive prediction, how accurrately did it make this prediction
recall=$\frac{TP}{TP+FN}$: ratio of how many times we predict correcly, when the case should be predicted to positive.

# KNN (k-nearest neighbours) -> non-parametric model
1. lazy learner -> no training phase
2. Big memory usage -> if we have 1 trillion data points, we have to store the entire data set on the fx. mobile phone that runs the app.
	1. Need to query all other data points to find the closest point -> very slow
		1. i.e prediction time is proportional to the data set size

# Bias and its relationship to KNN
bias means: take into account a lot of data -> data plays less role in the decision e.g 1NN is less biased than 20NN because new data does not play as huge role for 1NN.

Bias and variance: 
* Bias -> data doesnt matter as much 
* Variance -> data plays higher role, new data might change the entire output








----------------------------------
Slides noter

#### Introduction
[[DM566-2023-part3.pdf#page=3|Bias-free Learning?]]

##### Classification – Supervised Learning

- For some domain $\mathcal{D}$ and a set of classes $C=\left\{c_1, \ldots, c_k\right\}, k \geq 2$, each $o \in \mathcal{D}$ belongs uniquely to some $c \in C$, i.e., there is a function $f: \mathcal{D} \rightarrow C$.
- Given a set of objects $O=\left\{o_1, o_2, \ldots, o_n\right\} \subseteq \mathcal{D}$ and a mapping $(O \rightarrow C) \subset f$ (examples):
   We want to also map any object $o_m \in \mathcal{D} \backslash O$ to $C$.
- Supervised vs. unsupervised:
	- In clustering, we don't have any information on $C$.
	- In classification, we have examples (a training set) to guide (supervise) the learning process.

Predicted data should be the same as the *ground truth* labels.

- A classifier is trained on some training set $T R \subseteq O$ to learn the mapping function (a model or hypothesis) $h: \mathcal{D} \rightarrow C$.
- Ideally we have $\forall o \in T R: h(o)=f(o)$ (if not for all, we should have this at least for most examples $o$ ).
- After training, the classifier should also work on $\mathcal{D} \backslash T R$ and predict the correct class, i.e., $h \approx f$.
- $f$ is called "the target function".

Assumption $1.1$ (The inductive learning assumption)
Any ***hypothesis*** found to approximate the target function well over a sufficiently large set of training examples will also approximate the target function well over other examples.

##### Training of a classifier
[[DM566-2023-part3.pdf#page=8|Example Training of a Classifier]]

##### Intuition
- Data $\subset \mathcal{D} \times C$ are generated by some (natural / technical / social / ...) statistical process.
- The observed data are examples for the effect of the process.
- The challenge for the learning algorithm is to generate a model to explain the process.
- $h$ is an approximation of $f$, a hypothesis to explain the data.
- In the ideal case, the hypothesis $h$ is interpretable and helps to understand the data-generating process.
- Pragmatically, $h$ might be useful for predictions although it might not be interpretable.

Sometimes the models created by machines might not be explainable, but it's a preference.

##### Classification Algorithms and their Hypothesis-Space
- Based on training data, a classifier typically provides a hypothesis that separates the examples belonging to different classes from each other.
- Each classification algorithm comes with (more or less strict) assumptions on how separation can be achieved or defined.
- These assumptions (implicitly) define a hypothesis space $\mathcal{H}$, the space of hypotheses that could possibly be learned by the given algorithm.

***Inductive BIAS*** is how you choose to split up the data even when incapsulating the same elements (Linear lines, round lines og squiggly lines etc. to split the classes) and sometimes it's a design choice to make a simple split and accept some margin of error due to the simplicity. [[DM566-2023-part3.pdf#page=14|Simple separation and decision tree]]

#### Bias-free Learning?
[[DM566-2023-part3.pdf#page=16|Bias-free Learning?]]

##### Hypothesis Space and Bias
- The hypothesis space is a manifestation of the so-called "bias".
- Some algorithm, due to the restrictions of its hypothesis space, will prefer certain hypotheses, i.e., the algorithm has a bias.
- In general, we do not know if $f \in \mathcal{H}$, i.e., whether or not we can actually approximate $f$ (well enough) with some (or any) specific classification algorithm.
- Note that a hypothesis space can be infinite and yet restricted.

[[DM566-2023-part3.pdf#page=19|Example: Some Concept of Enjoying Sport]]

Definition $1.1$
For any two hypotheses, $h_j$ and $h_k$, over $X, h_j$ is more general than or equal to $h_k$ if and only if:
$$
\forall x \in X: h_k(x)=\text { Yes } \Rightarrow h_j(x)=\text { Yes }
$$

##### Basic Algorithm
Algorithm $1.1$ (Find-S [Mitchell, 1997])
> 1. Initialize $h$ to the most specific hypothesis in $\mathcal{H}$
	2. For each positive training instance $x$
		For each attribute constraint $a_i$ in $h$
			If the constraint $a_i$ is satisfied by $x$
			Then do nothing
			Else replace $a_i$ in $h$ by the next more general constraint that is satisfied by $x$
	3. output hypothesis $h$

Discussion:
- Finds the most specific hypothesis consistent with the positive examples in the training data - is it the only consistent hypothesis?
- Why should we prefer more specific hypotheses over more general ones?

##### Bias-free Learning
- Should we allow for more complex/generous assumptions to reduce the bias (i.e., to get rid of restrictions of the hypothesis space)?
- Allow disjunctions? Negations?
- A disjunctive hypothesis "if Sky=Sunny or Sky=Cloudy, then Yes" can list all positive examples.
- We could actually cover any concept with an arbitrarily complex hypothesis.
- Is this what we want?

Watch out for **overfitting** when trying to training too much with a training set. It is important to be balanced between **overfitting** and **underfitting**. Increasing the complexity is likely to be overfitting.

[[Graph between overfitting and underfitting.jpg]]
 If the training data and the test data is very different, it is likely overfitting or underfitting.

#### Evaluation of Classifiers
[[DM566-2023-part3.pdf#page=28|Evaluation of Classifiers]]

#### Problem of Evaluation
- A database $\mathcal{D}$ is representing a domain by the sample of available data, there is a function $f: \mathcal{D} \rightarrow C$, mapping each object to a class $c_i \in C$.
- $O \subseteq \mathcal{D}$ is the set of objects where we know about the class (i.e., we know $f(o)$ for all $o \in O$, but not for any $o \in \mathcal{D} \backslash O)$.
- Let $h$ be a classifier (model, hypothesis), trained on a training set $T R \subseteq O$.

Problem:
- We want a good quality (performance, approximation of the target function $f$ ) of $h$ over $\mathcal{D}$, yet we cannot know anything about the quality of $h$ over $\mathcal{D} \backslash O$.
- $h$ has been optimized for $T R$.
- If we test $h$ on $T R$, we will typically get an optimistic estimate of the performance over $\mathcal{D}$.
- The phenomenon that $h$ performs better on $T R$ than on $\mathcal{D}$ overall is called overfitting:
	- Often, the amount of training data is not sufficient to generalize reliably ("small sample size bias").
	- If the data sample is too small to truly represent the domain, there is no sufficient ground to reject overspecialized hypotheses.
	- In general, the weaker the bias of a learning algorithm, the more susceptible is it to overfitting.

##### The Separation of Training and Testing Data
To get a more realistic estimate of the performance of some classifier over $\mathcal{D}$, we separate training data $T R \subset O$ and test data $T E \subset O, T R \cap T E=\emptyset$.
- $T R$ is used to train the classifier (fit the model, select the hypothesis).
- $T E$ is used to evaluate the classifier.
- The purpose is to estimate the performance (success-/error-rate) of the classifier. Therefore:
	- $T R$ and $T E$ need to be independent $(T R \cap T E=\emptyset)$.
	- Both, $T R$ and $T E$ should represent the classification problem as good as possible.
	- For some learning problems (benchmark datasets), a separation into $T R$ and $T E$ is available.
- Problem: If it is not clear whether $O$ is already too small to allow for a good generalization, we do not really want $T R$ to be even smaller.

TR > TE -> overfitting
TR ~ TE -> similar

##### m-fold (k-fold) Cross-Validation
Motivation: We want to use as much data as possible for training, and as much as possible for testing.

Algorithm $1.2$ (m-fold cross-validation)
>1. Separate the set $O$ in $m$ equal-size, mutually disjoint subsets.
>2. Get $m$ different pairs of $T R$ and $T E$ by using each of the $m$ subsets as $T E$ once and the remaining $m-1$ subsets for training.
>3. On these $m$ pairs of $T R$ and $T E$, train and test $m$ independent classifiers.
>4. Average the $m$ observed performances.
>5. Repeat 1-4 several times.

[[DM566-2023-part3.pdf#page=34|Example with validation]]
Having a training data set of 5 do:
1. Training data 1-4 and test 5 -> Accuracy from 5
2. Training data 1-3, 5 and test 4 -> Accuracy from 4
3. Training data 1-2, 4-5 and test 3 -> Accuracy from 3
4. Training data 1, 3-5 and test 2 -> Accuracy from 2
5. Training data 2-5 and test 1 -> Accuracy from 1

The average of the test acc is used as the test error

##### Stratification
Stratification aims at representing the class proportions in each fold.
- minimum requirement: each class should be present in the training set.
- stratified cross-validation: the distribution of classes within each training and test set should reflect the distribution of the classes in $O$
Standard approach (rule of thumb):
10-fold, stratified cross-validation, repeated 10 times

*Note that:*
The evaluation procedure has the purpose of estimating the performance on $\mathcal{D} \backslash O$. In order to get the best possible classifier, we would use all available labeled data $(O)$ for training.

##### The Bootstrap
In the bootstrap procedure, a training set is created from $O$ by drawing with replacement:
- We take $|O|$ objects from $O$, where the same object could be drawn several times.
- A sample $T R$ contains on average $63 \%$ of the objects in $O$. Some are present several times in $T R$, some $(\approx 37 \%)$ are not present at all:
	- For $|O|=n$, an individual object in $O$ has a chance of being drawn of $\frac{1}{n}$ each turn, that is, it is not drawn with probability $1-\frac{1}{n}$.
	- After $n$ draws, a specific object has not been drawn with probability $\left(1-\frac{1}{n}\right)^n$
	- For large $n:\left(1-\frac{1}{n}\right)^n \approx e^{-1} \approx 0.368$, hence this procedure is also called "the $0.632$ bootstrap"

##### Leave-one-out or Jackknife Test
Algorithm $1.3$ (Leave-one-out)
> $\forall o_j \in O$ : take $o_j$ as test object for a classifier trained on $O \backslash\left\{o_j\right\}$.
	average the performance estimate over all test objects

Discussion:
- For $|O|=n$, this is an $n$-fold cross-validation.
- Pro: no random effect
- Con: stratification is not possible
- In general, the Jackknife test leads to a relatively pessimistic performance estimate.

##### Confusion Matrix
The confusion matrix represents the number of correctly and incorrectly predicted classes per actual and per predicted class:

[[DM566-2023-part3.pdf#page=38|Example with confusion matrix]]

##### Quality Measures for Classifiers
Given a classifier $h$, a training set $T R \subseteq O$, and a test set $T E \subseteq O \cdot f(o)$ is the actual class of $o, h(o)$ is the class predicted by the classifier $h$. Then we have: accuracy of $h$ on $T E$ :

$$
\operatorname{acc}_{T E}(h)=\frac{|\{o \in T E \mid h(o)=f(o)\}|}{|T E|}
$$
true classification error:
$$
\operatorname{err}_{T E}(h)=\frac{|\{o \in T E \mid h(o) \neq f(o)\}|}{|T E|}
$$
apparent classification error:
$$
\operatorname{err}_{T R}(h)=\frac{|\{o \in T R \mid h(o) \neq f(o)\}|}{|T R|}
$$

##### Focus on Individual Classes
If we focus on a single class (the “positive” class) vs. all other classes (the “negative” class), the confusion matrix can be read as follows:
|  | predicted positive | predicted negative |
| :--- | :---: | :---: |
| given positive | TP (true positive) | FN (false negative) |
| given negative | FP (false positive) | TN (true negative) |

This notation is also often used in two-class problems, where we have a particular interest to detect cases of the “positive” class, e.g., medical tests on specific diseases.

##### Quality Measures for Individual Classes
recall: proportion of test objects of some class $c_i$ that have been predicted correctly

$$
\begin{aligned}
& f_i=\left\{o \in T E \mid f(o)=c_i\right\}: \\
& \operatorname{recall}_{T E}(h, i)=\frac{\left|\left\{o \in f_i \mid h(o)=f(o)\right\}\right|}{\left|f_i\right|}
\end{aligned}
$$

Recall for class 3 [[DM566-2023-part3.pdf#page=38|Example with confusion matrix]]
$$recall = \frac{50}{50+7}$$

precision: proportion of test objects predicted as class $c_i$ that actually belong to class $c_i$

$$
\begin{aligned}
h_i=\left\{o \in T E \mid h(o)=c_i\right\} & : \\
\operatorname{precision}_{T E}(h, i) & =\frac{\left|\left\{o \in h_i \mid h(o)=f(o)\right\}\right|}{\left|h_i\right|}
\end{aligned}
$$

Precision for class 3
$$Prec = \frac{50}{50+12}$$

#### k-Nearest Neighbor Classification
##### Instance-based Learning
A simple classifier: assign to a new object the class of the nearest neighbor in the training data

we can visualize class regions by Voronoi cells

##### k-Nearest Neighbor Classification
- potential problem: nearest neighbor might be an outlier, somehow unusual, misleading
- take more than one neighbor into consideration: $k$ nearest neighbor classifier

**decision set**: the set of $(k)$ nearest neighbors considered for the classification decision
**decision rule**: how to decide the class, given the potentially different classes of the $k$ nearest neighbors
take the majority vote
potentially weighted votes
Let $x_1, \ldots, x_k$ be the $k$ nearest neighbors of instance $x_q$ :

$$h\left(x_q\right)=\arg \max _{c \in C} \sum_{i=1}^k w_i \delta\left(c, f\left(x_i\right)\right)$$ where $$\delta(a, b)=\left\{\begin{array}{l}1 \text { if } a=b \\ 0 \text { otherwise }\end{array}\right.$$

##### Decision Set
[[DM566-2023-part3.pdf#page=53|Decision Set]]

- $k$ too small: classifier is sensitive to outliers
- $k$ too large: potentially takes objects belonging to other classes into the decision set
- medium $k$ : best quality
- rule of thumb: $1 \ll k \leq 10$, but consider, e.g., size of classes in training set

##### Decision Rule
- standard: choose majority class in decision set
- advanced: put weights on the class votes
	- by distance, typically squared inverted distance:
$$
\text { weight }(\text { dist })=\frac{1}{\operatorname{dist}^2}
$$
		- by class proportions:
		  If a class is small, it has a smaller chance of being the majority in some decision set.

Example: 2 classes, $95 \% A, 5 \% B$, the labels of some decision set (e.g., labels of the 7 nearest neighbors of $x$ ) are $\{A, A, A, A, B, B, B\}$
- standard decision rule: $h(x)=A$
- votes weighted based on class size: $h(x)=B$

#### Instance-based Learning
- Instance-based learning does not provide an explicit description of the target function. 
- Training examples are simply stored. 
- Generalization beyond the training examples is postponed until a new instance must be classified (“lazy learner”). 
- High flexibility (low bias) because the target function is actually estimated locally and differently for each new instance instead of once for the entire instance space.

##### Discussion 

1. Lazy learner -> no training phase
2. Prediction time $\alpha$ * |$D$| -> Show stopper
3. Training data has to be stopped -> semi show stopper

BIAS increases when the dataset (k) increases
We want to be between BIAS (many NN) and variance (1 NN)

pros
- easy to apply: requires only training data and distance function
- often good classification accuracy
- incremental: easy adaptation to new training data
- no training required ("lazy learner")
cons
- inefficient prediction: each decision requires $k$ nearest neighbor query
- does not deliver explicit knowledge about classes
- difficult to choose $k$, esp. if classes are of very different size
