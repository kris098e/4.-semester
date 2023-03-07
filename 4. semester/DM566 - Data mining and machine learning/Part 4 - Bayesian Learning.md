[[DM566-2023-part4.pdf]]

Bayesian Learning:  
 - Axioms of probability  
 - Independence and conditional probability  
 - Bayes' rule  
 - Probabilistic learning


[[DM566-2023-part4.pdf#page=4]]
#### Can we Formalize “Confidence”?
We encountered a measure called "confidence" that should tell us how reliable a discovered association rule is.
We interpreted:
- The higher the confidence for some rule ' $X \Rightarrow Y$ ', the more likely $Y$ is present in transactions that contain $X$.
- The confidence is an estimate of the conditional probability of $Y$ given $X$.
Can we formalize this interpretation?

Boyesian -> Subjective

Frequentist definition
$$Pr(event) = \lim_{ \#trials \to \infty }(\frac{\#events}{\#trials})$$
Pr meaning probability

From x => y we can get:
- Support/frequency
- Confidence

[[DM566-2023-part4.pdf#page=6]]
### Sample space
The sample space $\Omega$ is the set of all (disjoint) possible outcomes of some random process.
>Examples:
- If we role a dice, we have $\Omega=\{1,2,3,4,5,6\}$.
- If we flip a coin, we have $\Omega=\{H, T\}$.

- Sample space: The sample space Ω is the set of all (disjoint) possible outcomes of some random process.

[[DM566-2023-part4.pdf#page=7]]
#### Events
A subset $E \subseteq \Omega$ of individual outcomes of a random process can define an "event".

>Examples:
- We role a die. Every element of $\Omega=\{1,2,3,4,5,6\}$ is a simple or elementary event.
- We could be interested in the event "The die shows an even number" $=\{2,4,6\} \subseteq \Omega$.
- We flip a coin. We could have the elementary event "head" $\subseteq \Omega$.

A family of sets $\mathcal{F}$ represents the allowable events. Each set in $\mathcal{F}$ is a subset of $\Omega$, i.e., $\mathcal{F} \subseteq \wp(\Omega)$.

- Events: A subset E ⊆ Ω of individual outcomes of a random process can define an “event”.

[[DM566-2023-part4.pdf#page=8]]
#### Probability Function
>Definition $1.1$ (Probability Function)
>	A probability function is any function $\operatorname{Pr}: \mathcal{F} \rightarrow \mathbb{R}$ that satisfies the following conditions:
>		1. $\forall E: 0 \leq \operatorname{Pr}(E) \leq 1$;
>		2. $\operatorname{Pr}(\Omega)=1$; and
>		3. for any finite or countably infinite sequence of pairwise mutually disjoint events $E_1, E_2, E_3, \ldots$ :
>$$
\operatorname{Pr}\left(\bigcup_{i \geq 1} E_i\right)=\sum_{i \geq 1} \operatorname{Pr}\left(E_i\right) .
$$

[[DM566-2023-part4.pdf#page=9]]
#### Probability Space
>Definition $1.2$ (Probability Space)
>A probability space is given by three components:
>	1. a sample space $\Omega$;
>	2. the allowable events $\mathcal{F} \subseteq \wp(\Omega)$; and
>	3. a probability function $\operatorname{Pr}: \mathcal{F} \rightarrow \mathbb{R}$.

#### Event Combinations
Because events are sets, we can use standard set theory notation to express combinations of events.
- $E_1 \cap E_2$ denotes the occurrence of both, $E_1$ and $E_2$ (i.e., their co-occurrence).
- $E_1 \cup E_2$ denotes the occurrence of either $E_1$ or $E_2$ (or both).
- $E_1 \backslash E_2$ denotes the occurrence of event $E_1$ without $E_2$ occurring as well.
- $\bar{E}=\Omega \backslash E$ denotes the complementary event of $E$.

Examples:
	Suppose we roll two dice. Given events $E_1$ and $E_2$ :
	$E_1$ the first die is a 1
	$E_2$ the second die is a 1
	- $E_1 \cap E_2$ : both dice are 1
	- $E_1 \cup E_2$ : at least one of the dice lands on 1.
	- $E_1 \backslash E_2$ : the first die is a 1 and the second die is not.

Examples:
	Let $E$ be the event that by rolling a die we obtain an even number.
	- Then $\bar{E}$ is the event that we obtain an odd number.
	- What are the events $\overline{E_1}, \overline{E_1 \cup E_2}, \overline{E_1 \cap E_2}$ ? (Overline not visible?)

#### Why is set theory getting more relevant in probability theory?
Uncertainty Quantification:
	1. Epistemic uncertainty $101 < \infty$  $\to$ Robustness, safety, Reliable, sample-efficiency.
	   If a model can say that it doesn't know, then it makes it possible to make a different case in that situation.
	2. Aleatoric uncertainty $\to$ precision uncertainty, like a weight might have an uncertainty of $\pm0.5 kg$

[[DM566-2023-part4.pdf#page=21]]
### Independent Events
Definition $1.5$ (Independent Events)
Two events $E$ and $F$ are independent if and only if
$$
\operatorname{Pr}(E \cap F)=\operatorname{Pr}(E) \cdot \operatorname{Pr}(F) .
$$
More generally, events $E_1, E_2, \ldots, E_k$ are mutually independent if and only if
$$
\forall I \subseteq[1, k]: \operatorname{Pr}\left(\bigcap_{i \in I} E_i\right)=\prod_{i \in I} \operatorname{Pr}\left(E_i\right)
$$

[[DM566-2023-part4.pdf#page=23]]
##### Intuition
- If events $A$ and $B$ are independent then knowledge about event $A$ does not change the probability of $B$.
- If $A$ and $B$ are not independent, then we can quantify the conditional probability of $A$ subject to our knowledge of event $B$.

- We look for the probability of $E \cap F$ within the sets of events defined by $F$.
- Because $F$ restricts the sample space, we normalize the probabilities by dividing by $\operatorname{Pr}(F)$.
- If $E$ and $F$ are independent, information about $F$ should not affect the probability of $E$.

Example:
Probability of the event $E_1$ "outcome of a die roll is even": $\frac{3}{6}$. Probability of the event $E_2$ "the outcome is $\leq 3$ ": $\frac{3}{6}$.
Probability of $E_1 \cap E_2$ : "the outcome is even and is $\leq 3$ ":
$$
\operatorname{Pr}\left(E_1 \cap E_2\right)=\frac{1}{6}=\frac{6}{36} \neq \frac{9}{36}=\frac{3}{6} \cdot \frac{3}{6}=\operatorname{Pr}\left(E_1\right) \cdot \operatorname{Pr}\left(E_2\right)
$$
$\Rightarrow$ The two events are not independent.

***Definition 1.6 (Conditional Probability)***
The conditional probability that event $E$ occurs given that event $F$ occurs is
$$
\operatorname{Pr}(E \mid F)=\frac{\operatorname{Pr}(E \cap F)}{\operatorname{Pr}(F)}
$$
The conditional probability is well-defined only if $\operatorname{Pr}(F)>0$.

Note that:
If $E$ and $F$ are independent and $\operatorname{Pr}(F) \neq 0$, we have:
$$
\operatorname{Pr}(E \mid F)=\frac{\operatorname{Pr}(E \cap F)}{\operatorname{Pr}(F)}=\frac{\operatorname{Pr}(E) \operatorname{Pr}(F)}{\operatorname{Pr}(F)}=\operatorname{Pr}(E)
$$

#### The Condition Defines a Probability Space
$\operatorname{Pr}(X \mid E)$ defines a proper probability function on the sample space $E$ (cf. Definitions $1.1$ and 1.2):
$$
\begin{aligned}
& \operatorname{Pr}(\emptyset \mid E)=\frac{\operatorname{Pr}(\emptyset \cap E)}{\operatorname{Pr}(E)}=\frac{\operatorname{Pr}(\emptyset)}{\operatorname{Pr}(E)}=0 \\
& \operatorname{Pr}(E \mid E)=\frac{\operatorname{Pr}(E \cap E)}{\operatorname{Pr}(E)}=\frac{\operatorname{Pr}(E)}{\operatorname{Pr}(E)}=1
\end{aligned}
$$
For any two disjoint events $A$ and $B$ :
$$
\begin{aligned}
\operatorname{Pr}(A \cup B \mid E) & =\frac{\operatorname{Pr}((A \cup B) \cap E)}{\operatorname{Pr}(E)} \\
& =\frac{\operatorname{Pr}(A \cap E)+\operatorname{Pr}(B \cap E)}{\operatorname{Pr}(E)} \\
& =\operatorname{Pr}(A \mid E)+\operatorname{Pr}(B \mid E)
\end{aligned}
$$

### Independence and Conditional Probability
#### Quality Measures for Association Rules
- Support: $s(X \Rightarrow Y)=s(X \cup Y)$ or in relative terms: frequency $f(X \cup Y)=\frac{s(X \cup Y)}{|\mathcal{D}|}$
- Confidence: $\operatorname{conf}(X \Rightarrow Y)=\frac{s(X \cup Y)}{s(X)}$
- Lift: Lift $(X \Rightarrow Y)=\frac{\operatorname{conf}(X \Rightarrow Y)}{f(Y)}$
- Jaccard: $\operatorname{Jaccard}(X \Rightarrow Y)=\frac{s(X \cup Y)}{s(X)+s(Y)-s(X \cup Y)}$
- conviction: conviction $(X \Rightarrow Y)=\frac{1-f(Y)}{1-\operatorname{conf}(X \Rightarrow Y)}$

##### Probabilistic Interpretation: Support (Frequency)
The frequency of an itemset in the database can be seen as an empirical estimate of its probability, given the sample represented by the database:
$$
\operatorname{Pr}(X)=\frac{s(X)}{|\mathcal{D}|}
$$
Note that:
$$
\operatorname{Pr}(X \cap Y)=\frac{s(X \cup Y)}{|\mathcal{D}|}
$$
Although $X$ and $Y$ are sets in both cases,
probabilistically, $\cap$ denotes the co-occurrence of events, while for itemsets, $\cup$ denotes that both itemsets need to be present.

##### Probabilistic Interpretation: Confidence
The confidence is the conditional probability that a transaction contains the consequent $Y$ given that it contains the antecedent $X$ :
$$
\begin{aligned}
\operatorname{conf}(X \Rightarrow Y) & =\frac{s(X \cup Y)}{s(X)} \\
& =\frac{\operatorname{Pr}(X \cap Y)}{\operatorname{Pr}(X)} \\
& =\operatorname{Pr}(Y \mid X)
\end{aligned}
$$
- The confidence of a rule $X \Rightarrow Y$ is not a useful measure unless we compare it with the frequency of $Y$, i.e., the prior (unconditional) probability.
- If we have $\operatorname{Pr}(Y \mid X)<\operatorname{Pr}(Y)$ this means that in the presence of $X, Y$ becomes less likely as it is unconditionally!
  (Not the rule, but this fact could be interesting, though!)

##### Probabilistic Interpretation: Lift
We can see Lift as normalization of the confidence by the prior probability of the consequent:
$$
\begin{aligned}
\operatorname{Lift}(X \Rightarrow Y) & =\frac{\operatorname{conf}(X \Rightarrow Y)}{f(Y)} \\
& =\frac{\operatorname{Pr}(X \cap Y)}{\operatorname{Pr}(X) \operatorname{Pr}(Y)}
\end{aligned}
$$
- ratio of the observed joined probability of $X$ and $Y$ to the joint probability expected for statistically independent events (Definition 1.5).
- Lift is a (symmetric!) measure for the surprise of a rule.
- Values around 1: boring.
- Much smaller/larger values: interesting!

##### Probabilistic Interpretation: Jaccard
The Jaccard coefficient in general is a measure for the similarity between two sets:
$$
\begin{aligned}
\operatorname{Jaccard}(X \Rightarrow Y) & =\frac{s(X \cup Y)}{s(X)+s(Y)-s(X \cup Y)} \\
& =\frac{\operatorname{Pr}(X \cap Y)}{\operatorname{Pr}(X)+\operatorname{Pr}(Y)-\operatorname{Pr}(X \cap Y)} \\
& =\frac{\operatorname{Pr}(X \cap Y)}{\operatorname{Pr}(X \cup Y)} \quad \text { (Lemma 1.3) }
\end{aligned}
$$
A symmetric measure of how often both, $X$ and $Y$, occur simultaneously, relative to the occurrence of both or either overall.
- Similarity of the itemsets $X$ and $Y$ based on their individual occurrences and their co-occurrences.

##### Probabilistic Interpretation: Conviction
Conviction of a rule measures the expected error: how often does $X$ occur in a transaction where $Y$ does not?
(How often does the rule fail?)
$$
\text { conviction } \begin{aligned}
(X \Rightarrow Y) & =\frac{1-f(Y)}{1-\operatorname{conf}(X \Rightarrow Y)} \\
& =\frac{\operatorname{Pr}(\bar{Y})}{1-\frac{\operatorname{Pr}(X \cap Y)}{\operatorname{Pr}(X)}}=\frac{\operatorname{Pr}(X) \operatorname{Pr}(\bar{Y})}{\operatorname{Pr}(X)-\operatorname{Pr}(X \cap Y)} \\
& =\frac{\operatorname{Pr}(X) \operatorname{Pr}(\bar{Y})}{\operatorname{Pr}(X \cap \bar{Y})}=\frac{1}{\operatorname{Lift}(X \Rightarrow \bar{Y})}
\end{aligned}
$$
- compares the observed joint probability of $X$ and $\bar{Y}$ with their joint probability expected for independence
- asymmetric measure

Lift and conviction is the inverse of each other and therefore is irrelevant to typically show both.

[[DM566-2023-part4.pdf#page=37]]
### The Probality and Bayers' Rule
#### The Law of Total Probability

[[DM566-2023-part4.pdfpage=39|Proof of The Law of Total Probability]]
***Theorem $1.7$ (The Law of Total Probability)***
Let $E_1, E_2, \ldots, E_n$ be mutually disjoint events in the sample space $\Omega$, and let $\bigcup_{i=1}^n E_i=\Omega$. Then
$$
\operatorname{Pr}(B)=\sum_{i=1}^n \operatorname{Pr}\left(B \cap E_i\right)=\sum_{i=1}^n \operatorname{Pr}\left(B \mid E_i\right) \operatorname{Pr}\left(E_i\right) .
$$

#### Bayes’ Rule
Theorem $1.8$ (Bayes' Rule)
Let $E_1, \ldots, E_n$ be mutually disjoint events, and let $\bigcup_{i=1}^n E_i=\Omega$. Then for any other event $B, \operatorname{Pr}(B)>0, j=1, \ldots, n$ :
$$
\begin{aligned}
\operatorname{Pr}\left(E_j \mid B\right) & =\frac{\operatorname{Pr}\left(E_j \cap B\right)}{\operatorname{Pr}(B)} \\
& =\frac{\operatorname{Pr}\left(B \mid E_j\right) \operatorname{Pr}\left(E_j\right)}{\sum_{i=1}^n \operatorname{Pr}\left(B \mid E_i\right) \operatorname{Pr}\left(E_i\right)}
\end{aligned}
$$

##### Bayes’ Rule (Simple Form)
In its simple form, we have only two events, $A$ and $B$, $\operatorname{Pr}(A) \neq 0, \operatorname{Pr}(B) \neq 0$ :
$$
\operatorname{Pr}(A \mid B)=\frac{\operatorname{Pr}(B \mid A) \operatorname{Pr}(A)}{\operatorname{Pr}(B)}
$$

Example: [[DM566-2023-part4.pdf#page=42]]

$$
\operatorname{Pr}(I \mid S)=\frac{\operatorname{Pr}(S \mid I) \operatorname{Pr}(I)}{\operatorname{Pr}(S)}
$$

Likelihood

$$\operatorname{Pr}(S \mid F) = 0.8$$
$$\operatorname{Pr}(S \mid A) = 0.4$$
$$\operatorname{Pr}(S \mid I) = 0.9$$
...

$$\operatorname{Pr}(S \mid I)$$
S -> Observation experience
I -> Hypothesis/Cause 

Prior knowledge
$$Pr(F) = 0.5$$
$$Pr(A) = 0.4$$
$$Pr(I) = 0.1$$

Posterior model
$$Pr(I|S)$$
Evidence
$${\operatorname{Pr}(S)}$$



? Likelihood -> (There's No likelihood of data!)
? Probability -> an outcome given an output.
? Evidence -> outcome

### Probabilistic Learning
##### k-Nearest Neighbor Classification Revisited

If a model is 95% right it is interpreted as true

##### Maximum Likelihood Classification

$$
h_{MAP} = \arg \max _{c_i \in C} \operatorname{Pr}\left(a_q \mid c_i\right) \operatorname{Pr}\left(c_i\right)
$$

#### Model types
$$
\operatorname{Pr}(I \mid S)=\frac{\operatorname{Pr}(S \mid I) \operatorname{Pr}(I)}{\operatorname{Pr}(S)}
$$

Generative models
$$\operatorname{Pr}(S \mid I) \operatorname{Pr}(I)$$

Discriminative models
$$\operatorname{Pr}(I \mid S)$$
