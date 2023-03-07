[[DM566-2023-part1.pdf]]
Book: Karl papper - All life is problem solving

Introduction: 
 - Data science  
 - Knowledge discovery from data  
 - Data mining methods  
 - Preprocessing  
 - Transformation  
 - Evaluation  

Frequent Pattern Mining:  
 - Sets and relations  
 - Item sets  
 - Definitions and prob. refinements  
 - The monotonicity property  
 - Apriori algorithm  
 - Association rule mining

### Introduction
##### Data Mining and Related Areas
- Mathematics Statistics (Precision)
- Databases Data Management (Scalability)
- Domain Knowledge (Flexibility)
- Programming Implementation (Performance)

##### Data Mining Techniques
- Clustering
- Outlier detection
- Frequent pattern mining 
- Classification

#### Definition: Knowledge Discovery from Data (KDD) 
[[DM566-2023-part1.pdf#page=23 |KDD Model]]

> “**KDD is the nontrivial process of identifying valid, novel, potentially useful, and ultimately understandable patterns in data.**”
> 
> \- *Fayyad et al., 1996*

**KDD process model**
- *Focusing*
	- get the data 
	- organize data (file/database) 
	- select relevant data
- *preprocessing* 
	- integrate heterogeneous data (low noise -> no errors, few outliers, relevant information)
	- check for completeness 
	- check for consistency
- *transformation* 
	- discretize numeric attributes 
	- infer new attributes 
	- select relevant attributes
- *data mining*
	- generate patterns or models
- *evaluation* 
	- quantify how valid, novel, useful and understandable the derived patterns and models are.
	- assess “interestingness” for the user
	- validate models statistically
	- Evaluation of descriptive models (clustering, outlier detection, frequent pattern mining, classification)

The hardest thing to control is finding good data set that can be used as background for research and the the last steps using the data to retrieve knowledge (See link). The steps in between comes along the way.

##### Validation and verification
Validation and verification are two terms often used in the context of testing and quality assurance in software engineering.

- **Validation**: the process of checking whether a product, system, or component meets its specified requirements and design, and that it has been implemented correctly. It aims to ensure that the product is error-free and operates as expected based on the predefined criteria.
- **verification**: the process of evaluating a product, system, or component to ensure that it satisfies the customer's needs and requirements. It aims to ensure that the right product has been built, and that it satisfies the intended use and requirements of the customer.

##### Patterns and Models
- **predictive models**: A predictive model should describe (known) data in a way suitable to make predictions on unknown data.
- **descriptive models**: A model should provide insight in the data, help to understand the underlying structure, correlations, properties etc.

A data mining model can be both, descriptive and predictive.
Based on both could be a prescriptive model: Learn from the data for the future: a model to tell you what to change, or how to implement details (typically related to optimization problems).

##### Categories of Learning
- **Supervised** (e.g., classification, regression, outlier detection): An in general unknown attribute is learned, based on examples (training data) where the attribute is known. Emphasis on predictive modeling. 
- **Unsupervised** (e.g., clustering, outlier detection, association rules) The data are distinguished/organized in different groups without previously known examples. Emphasis on descriptive modeling. 
- **Semi-supervised** (e.g., clustering, outlier detection) Semi-supervised techniques are guided by using some information (e.g., only one class is known, or some constraints restrict clustering results)

### Frequent Pattern Mining
#### Sets

##### Definition
A set is a collection of objects (e.g. $s = {1,4,9}$ ). Where the *elements* of the set each are unique.

We can define sets
- **extensionally**: by enumerating the elements that define the set (e.g., S = {1, 4, 9}).
- **intensionally**: by characterizing the elements of the set, 
	- describing what condition (the “characteristic function” of the set) holds for all the elements and only for the elements of the set (e.g. S = {x| √ x ∈ N AND x < 15} — read ‘|’ as ‘for which holds’ or ‘such that’). 
	- The intensional definition typically resorts to a domain over which the set is defined (here: $\mathbb{N}$).

##### Properties
- A set can be finite (e.g., S = {1, 2, 3, . . . , n} with a size (cardinality e.g., |S| = n)
- A set can be countably infinite
		$\begin{aligned} S & =\{1,-1,3,-3,5,-5, \ldots\} \\ & =\left\{x \mid x=2 k+1 \text { OR } x=-2 k+1, k \in \mathbb{N}_0\right\}\end{aligned}$
- A set can be uncountable (e.g., $\mathbb{R}$).
- A set can be empty: $S=\{\}=\emptyset .|S|=0$

##### Algebra
An algebra is defined over a base set Ω, all sets involved in the algebra are subsets of Ω.
Basic operations for $S, T \subseteq \Omega$ :
- *union*               | $S \cup T \equiv\{x \mid x \in S \vee x \in T\}$
- *intersection*      | $S \cap T \equiv\{x \mid x \in S \wedge x \in T\}$
- *complement*     | $\bar{S} \equiv S^C \equiv\{x \mid x \notin S\}$
- *difference*         | $S \backslash T \equiv\{x \mid x \in S \wedge x \notin T\}$
- *product*            | $S \times T \equiv\{(x, y) \mid x \in S \wedge y \in T\}$
- *powerset*          | $\mathcal{P}(S) \equiv \wp(S) \equiv 2^S \equiv\{T \mid T \subseteq S\}$

Powersets: Sets of sets

##### Properties of Homogeneous Relations
|Property|Meets requirements Iff|
|----------|--------------|
|Relation $R \subseteq S_1 \times S_2 \times S_3 \times \ldots \times S_n$ is homogeneous|$S_1=S_2=S_3=\ldots=S_n$|
|A binary homogeneous relation $R \subseteq S \times S$ is reflexive|$\forall x \in S:(x, x) \in R$|
|Symmetric|$\forall x, y \in S:(x, y) \in R \Rightarrow(y, x) \in R$|
|Antisymmetric|$\forall x, y \in S:(x, y) \in R \wedge(y, x) \in R \Rightarrow x=y$|
|Transitive|$\forall x, y, z \in S:(x, y) \in R \wedge(y, z) \in R \Rightarrow(x, z) \in R$|
|Total|$\forall x, y \in S:(x, y) \in R \vee(y, x) \in R$|

##### Order
A relation $R \in S \times S$ can be an order:
$R$ is a partial order if $R$ is antisymmetric and transitive.
$R$ is a total order if $R$ is a partial order and is total.
$R$ is a strict order if $R$ is a partial order and is not reflexive

##### Functions
- A function is a mapping from some set (the domain) to some set (the image).
- We can see functions as relations with particular properties: a univalent (or right-unique) relation over domain and image.
- Formally, a function $f$ is a binary relation over $D \times I$ : $f \subseteq D \times I$, for which holds:
$$
(x, y) \in f \wedge(x, z) \in f \Rightarrow y=z
$$
	i.e., for each $d \in D, f$ maps to at most one $i \in I$.
- Notation:
$$
(x, y) \in f \Longleftrightarrow y=f(x) \Longleftrightarrow f(x)=y \Longleftrightarrow f: x \mapsto y
$$

#### Item sets
##### Association Rules
- *items* fx. bread, butter, eggs, milk etc. 
- *transaction* a set of items 
- *rule* $L \Rightarrow R, L, R \subseteq$ items, $L \cap R=\emptyset$
	- *L* left-hand-side or antecedent
	- *R* right-hand-side or consequent

##### Definition: Frequent Itemsets
- *items*: $I=\left\{i_1, \ldots, i_m\right\}$ a set of literals (e.g., items in a shop) 
- *itemset*: $X \subseteq I$ (e.g., the items in a basket) 
- *transaction*: $T=\left(t i d, X_{t i d}\right)$ designates a specific itemset 
- *transaction database $\mathcal{D}$* : a set of transactions 
- *order*: items in an itemset are ordered by some strict total order (e.g., alphabetical order of the literals), i.e.:
$$
X=\left(x_1, x_2, \ldots, x_k\right) \Rightarrow x_1<x_2<\ldots<x_k
$$
- *length of an itemset*: number of elements contained in the itemset
- *k-itemset*: an itemset of length $k$ (e.g., $\mathrm{T} 1$ is a 4 -itemset, $\mathrm{T} 4$ is a 1-itemset)

##### Cover, Support, Frequency
- *cover of an itemset*: set of all transactions that contain the itemset: $\operatorname{cover}(X)=\left\{\left(\right.\right.$ tid, $\left.X_{\text {tid }}\right) \mid\left(\right.$ tid, $\left.\left.X_{\text {tid }}\right) \in \mathcal{D} \wedge X \subseteq X_{\text {tid }}\right\}$ 
- *support of an itemset*: the support $s$ of an itemset $X(s(X))$ is the number of transactions containing $X$ (i.e., the size of the cover set): $s(X)=|\operatorname{cover}(X)|$
- *frequency of an itemset*: the frequency of an itemset $X$ is its support relative to the database size $f(X)=\frac{s(X)}{|\mathcal{D}|}$
- *frequent itemset*: given some support threshold $\sigma$, an itemset $X$ is frequent (w.r.t. $\sigma$ ) iff: $s(X) \geq \sigma$ or equivalently $f(X) \geq \frac{\sigma}{|\mathcal{D}|}$

[[DM566-2023-part1.pdf#page=74|Test knowledge of frequent itemset mining: Problem 1]]

##### Association Rule
- *association rule*: expresses an implication of the form $X \Rightarrow Y$, where $X$ and $Y$ are itemsets, $X \cap Y=\emptyset$
- *implication*: describes a co-occurrence, not a causality
	An association rule does not necessarily need to hold in all cases. We can describe its strength (or weakness), based on the observed cases:
- *support*: The support of an association rule in $\mathcal{D}$ is the support of the union of its components:
$$
s(X \Rightarrow Y)=s(X \cup Y)
$$
- *frequency*: Analogously, $f(X \Rightarrow Y)=f(X \cup Y)$
- *confidence*: $\operatorname{conf}(X \Rightarrow Y)=\frac{s(X \cup Y)}{s(X)}$

[[DM566-2023-part1.pdf#page=77|Test knowledge of frequent itemset mining: Problem 1 part 2]]

Trying to satisfy
1. Support is large
2. Confidence is large 
3. Size of the itemset X U Y

##### Find Frequent Itemsets: The naive algorithm 
[[DM566-2023-part1.pdf#page=78|The naive algorithm]]

##### Monotonicity and Anti-Monotonicity
[[DM566-2023-part1.pdf#page=80|Lattice of Itemsets]]

$\sigma$  is the threshold

Observation:
- If $X$ is frequent, all subsets $X^{\prime} \subseteq X$ are frequent as well. 
- If $X$ is not frequent, neither any superset $X^{\prime} \supseteq X$ can be frequent.

Due to the anti-monotonicity, we can summarize solutions by their border in the lattice:
- An itemset $X$ belongs to the border (w.r.t. some $\sigma$ ), if:
	- $\forall Y \subset X: Y$ is frequent (w.r.t. $\sigma$ )
	- $\forall Z \supset X: Z$ is not frequent (w.r.t. $\sigma$ )
- positive border: $X$ itself is frequent (also: " $X$ is a maximal frequent itemset")
- negative border: $X$ itself is not frequent

##### Maximal frequent itemsets
Maximal frequent itemsets can be used as a condensed representation of a solution, as all frequent itemsets can be derived from the maximal frequent itemsets.
*Note that:*
The anti-monotonicity property of support is also called downward-closure property.

##### Closed (Frequent) Itemsets
closed itemset: An itemset $X$ is closed if none of its immediate supersets has exactly the same support as $X$. closed frequent itemset: An itemset is a closed frequent itemset (w.r.t. some $\sigma$ ) if it is a closed itemset and is frequent (w.r.t. $\sigma$ ).
Closed frequent itemsets represent a solution (all frequent itemsets) and their support.

#### Apriori Algorithm [Srikant and Agrawal, 1996]
##### Idea
[[DM566-2023-part1.pdf#page=90|Idea]]
1. find frequent 1 -itemsets first, then 2 -itemsets, 3 -itemsets etc. (breadth-first search in the lattice)
2. for finding $(k+1)$-itemsets $C_{k+1}$ : consider only those as candidates, where all $k$-itemsets $C_k \subset C_{k+1}$ are frequent
3. count frequency of all $k$-itemset candidates in a single database scan (hashing of the candidate itemsets)

##### Pseudo Code: Algorithm 2.1
Apriori $(I, \mathcal{D}, \sigma)$
$S_1=\{$ frequent 1 -itemsets $\} ;$
$k=2 ;$
while $S_{k-1} \neq \emptyset$ do
$\quad C_k=$ AprioriGenerateCandidates $\left(S_{k-1}\right) ;$
$\quad$for each transaction $T \in \mathcal{D}$ do
	$\quad C_T=\left\{c \in C_k \mid c \subseteq T\right\} ;$
	$\quad$for each $c \in C_T$ do
		$\quad c$. count++;
$\quad S_k=\left\{c \in C_k \mid\right.$ c.count $\left.\geq \sigma\right\}$
   k++;$
return $\cup_k S_k ;$

##### Algorithm 2.2 (AprioriGenerateCandidates($S_{{k-1}}$))
1. join:
	two frequent $(k-1)$-itemsets $p, q \in S_{k-1}$ are joined if they are identical in the **first** (order!) $k-2$ items:
$$
\begin{aligned}
p \in S_{k-1}: & (\underline{A, B}, C) \\
q \in S_{k-1}: & (\underline{A, B}, D) \\
\hline \Rightarrow & \left(A, B, C, D) \quad \in C_k\right.
\end{aligned}
$$
2. pruning:
	remove all $k$-itemsets from $C_k$ that contain any $(k-1)$-itemset $\notin S_{k-1}$

**Small example**
$S_3=\{(1,2,3),(1,2,4),(1,3,4),(1,3,5),(2,3,4)\}$
1. join: $C_4=\{(1,2,3,4),(1,3,4,5)\}$
2. pruning: remove $(1,3,4,5)$
result: $C_4=\{(1,2,3,4)\}$

##### Apriori Example
[[DM566-2023-part1.pdf#page=94|Apriori Example]]
##### Find Frequent Itemsets $X$ with $f(X) \geq 0.3$
##### C1 and S1
[[DM566-2023-part1.pdf#page=108|C1 and S1]]

$f(X) ≥ 0.3)$
D = database size
$f = \frac{s(x)}{|D|} \to f * s$
$0.3 = \frac{?}{12} \to s(x) = 0.3 * 12 = 3,6$

$\sigma=30 \% \Leftrightarrow$ support $\geq 4$

| 1 | B E G H |
|-|-|
| 2 | A B C E G H |
| 3 | A B C E F H |
| 4 | B C D E F G H L |
| 5 | A B E K H |
| 6 | B E F G H I K |
| 7 | A B D G H |
| 8 | A B D G |
| 9 | B D F G |
| 10 | C E F |
| 11 | A C E F H |
| 12 | A B E G |

##### C1 and S1
[[DM566-2023-part1.pdf#page=108|C1 and S1]]

| **A** | 7 |
| :---: | :---: |
| **B** | 10 |
| **C** | 5 |
| **D** | 4 |
| **E** | 9 |
| **F** | 6 |
| **G** | 8 |
| **H** | 8 |
| I | ~~1~~ |
| J | ~~0~~ |
| K | ~~2~~ |
| L | ~~1~~ |

##### C2 and S2
[[DM566-2023-part1.pdf#page=122|C2 and S2]]
| **AB** | 6 | **CE** | 5 |
| :---: | :---: | :---: | :---: |
| A | ~~3~~ | **CF** | 4 |
| AD | ~~2~~ | CG | ~~2~~ |
| **AE** | 5 | **CH** | 4 |
| AF | ~~2~~ | DE | ~~1~~ |
| **AG** | 4 | DF | ~~2~~ |
| **AH** | 5 | **DG** | 4 |
| BC | ~~3~~ | DH | ~~2~~ |
| **BD** | 4 | **EF** | 5 |
| **BE** | 7 | **EG** | 5 |
| **BF** | 4 | **EH** | 7 |
| **BG** | 8 | FG | ~~3~~ |
| **BH** | 7 | **FH** | 4 |
| CD | ~~1~~ | **GH** | 5 |

##### S2 to C3 with pruning
[[DM566-2023-part1.pdf#page=128|S2 to c3 with pruning]]

##### C3 and S3
[[DM566-2023-part1.pdf#page=142|C3 and S3]]
| **ABE** | 4 | **BEH** | 6 |
| :---: | :---: | :---: | :---: |
| **ABG** | 4 | BFH | ~~3~~ |
| **ABH** | 4 | **BGH** | 5 |
| AEG | ~~2~~ | **CEF** | 4 |
| **AEH** | 4 | **CEH** | 4 |
| AGH | ~~2~~ | CFH | ~~3~~ |
| **BDG** | 4 | **EFH** | 4 |
| BEF | ~~3~~ | **EGH** | 4 |
| **BEG** | 5 |

##### S3 to C4 with pruning
[[DM566-2023-part1.pdf#page=147|S3 to c4 with pruning]]

##### C4 and S4
[[DM566-2023-part1.pdf#page=156|C4 and S3]]
| ABEH | ~~3~~ |
| :---: | :--- |
| **BEGH** | 4 |

##### Maximal Frequent Itemsets and Closed Frequent Itemsets
[[DM566-2023-part1.pdf#page=175|Maximal Frequent Itemsets and Closed Frequent Itemsets]]

*Note refs* for MFI and CFI
**[[Part 1 - Introduction + Frequent Pattern Mining#Monotonicity and Anti-Monotonicity|Monotonicity and Anti-Monotonicity]]** 
**[[Part 1 - Introduction + Frequent Pattern Mining#Maximal frequent itemsets|Maximal frequent itemsets]]** and **[[Part 1 - Introduction + Frequent Pattern Mining#Closed (Frequent) Itemsets|Closed (Frequent) Itemsets]]** 

##### Efficiency
- naïve algorithm: count frequency of all $k$-itemsets, for all $\left(\begin{array}{l}I \\ k\end{array}\right)$ *k*-itemsets, for all *k*
- number of possible itemsets $0 \leq k \leq|I|$ ?
- Apriori: one database scan for all frequent $k$-itemset candidates of a given $k$
- reduction of number of candidates by the anti-monotonicity principle of frequency: generate only candidates that have a chance to be frequent (join of frequent $(k-1)$-itemsets and pruning)

##### Experiments
[[DM566-2023-part1.pdf#page=178|Experiments]]
Why does the graph rise in the start? There are a minimum number of ingredients to cook a meal

##### Association Rule Mining
- **association rule**: expresses an implication of the form $X \Rightarrow Y$, where $X$ and $Y$ are itemsets, $X \cap Y=\emptyset$
- **implication**: describes a co-occurrence, not a causality
	An association rule does not necessarily need to hold in all cases. We can describe its strength (or weakness), based on the observed cases:
- **support**: The support of an association rule in $\mathcal{D}$ is the support of the union of its components:
$$
s(X \Rightarrow Y)=s(X \cup Y)
$$
- **frequency**: Analogously, $f(X \Rightarrow Y)=f(X \cup Y)$
- **confidence**: $\operatorname{conf}(X \Rightarrow Y)=\frac{s(X \cup Y)}{s(X)}$

[[DM566-2023-part1.pdf#page=188|Test knowledge of association Rule Mining: Problem 2]]

##### Find Association Rules
This is part of the Apriori algorithm [Srikant and Agrawal, 1996].

for frequent itemset $X$ :
- for each $Y \subset X, Y \neq \emptyset$, build the rule $Y \Rightarrow(X \backslash Y)$
- $\operatorname{conf}(Y \Rightarrow(X \backslash Y))=\frac{s(X)}{s(Y)}$
- delete rules with confidence below a given threshold $c$

*Note that:*
For all involved itemsets $(X, Y,(X \backslash Y)$ ), we have the support from the solution of Problem 1 (stored or reconstructable from closed frequent itemsets). Thus we don't need a single database scan here.

##### Monotonicity of Confidence
Theorem $2.1$
>Given:
>- itemset $X$
>- $Y \subset X, Y \neq \emptyset$
>If $\operatorname{conf}(Y \Rightarrow(X \backslash Y))<c$, then $\forall Y^{\prime} \subset Y$ :
$$
\operatorname{conf}\left(Y^{\prime} \Rightarrow\left(X \backslash Y^{\prime}\right)\right)<c
$$

This property allows the construction of all association rules satisfying some confidence threshold from all frequent itemsets with a procedure similar to the Apriori construction of frequent itemsets, but without database scan. [Srikant and Agrawal, 1996]

[[DM566-2023-part1.pdf#page=191|Pruning of Association Rules]]
[[DM566-2023-part1.pdf#page=192|Example: Pruning of Association Rules]]

##### Interpretation of Support and Confidence
support: measures the frequency of the item set
- rules with very low support may occur simply by chance
- rules with low support are uninteresting from a business perspective
confidence: measures the reliability of the rule
- $X \Rightarrow Y$ - the higher the confidence, the more likely $Y$ is present in transactions that contain $X$
estimate of the conditional probability of $Y$ given $X$

##### Limitations of Support and Confidence as Measures
[[DM566-2023-part1.pdf#page=194|Tea and coffee example]]

{tea} => {coffee}
support = 150

$\frac{s({tea, coffee})}{s{tea}}$ = ${\frac{150}{200}}$

$800$ -> $s({coffee}) = \frac{800}{1000} = 0.8$

##### Interestingness
Other measures to assess the interestingness of a rule include:
- Lift: $\operatorname{Lift}(A \Rightarrow B)=\frac{\operatorname{conf}(A \Rightarrow B)}{f(B)}$
- Jaccard: $\operatorname{Jaccard}(A \Rightarrow B)=\frac{s(A \cup B)}{s(A)+s(B)-s(A \cup B)}$
- conviction: conviction $(A \Rightarrow B)=\frac{1-f(B)}{1-\operatorname{conf}(A \Rightarrow B)}$


### Questions
What is the cover?

Where does the following (Hvad hører følgende til?)
[[DM566-2023-part1.pdf#page=157]] Going back (Maximal Frequent Itemsets and Closed Frequent Itemsets)

Time notation for this algorithm:
- O is defined by |D|, |I| and k
- $O(|D|* 2^{|I|})$ = $O(database~size* 2^{|number~of~items|})$
