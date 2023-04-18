![[_exercise09.pdf#page=1]]
[[solution07.pdf#page=1]]
calculating Pr(+|Bayes optimal):
$$Pr(+|Bayes optimal)=0.4*0.6+0.7*0.3+0.5*0.1=0.5$$
Since they sum up to 1 the propability for both classes, the then **a is true**.

o2:
calculating Pr(+|Bayes optimal):
$$Pr(+|Bayes optimal)=0.1*0.6+0.5*0.3+0.8*0.1=0.29$$
therefore Pr(|Bayes optimal) = 1-0.29

o3:
$$Pr(+|Bayes optimal)=0.0*0.6+0.4*0.3+0.6*0.1=0.18$$
therefore Pr(|Bayes optimal) = 1-0.18

o4:
$$Pr(+|Bayes optimal)=0.2*0.6+0.7*0.3+0.5*0.1=0.38$$

o5:
$$Pr(+|Bayes optimal)=0.5*0.6+0.1*0.3+0.2*0.1=0.35$$
a. true
b. false
c. true
d. false
e. false

![[_exercise09.pdf#page=2]]
[[_DM566-2023-part4.pdf#page=74]]
a.
$pr(c|+1)=\frac{1}{4}$
$pr(D|+1)=\frac{1}{4}$
$pr(+1|Data)=\frac{4}{8}$

$Pr(C|+1)pr(D|+1)pr(+1|Data)=\frac{1}{4}*\frac{1}{4}*\frac{4}{8}=0.03125$

$pr(c|-1)=\frac{2}{4}$
$pr(D|-1)=\frac{0}{4}$
$pr(-1|Data)=\frac{4}{8}$

multiply by 0, the test query is equal to 0 for **-1**


normalise:
$\frac{0.03125}{0.03125+0}=1$
**a=true** since probaility of the +1 is 1 and for negative its 0.

b. 
$pr(A|+1)=\frac{1}{4}$
$pr(D|+1)=\frac{1}{4}$
$\frac{1}{4}* \frac{1}{4}* \frac{1}{2}=0.03125$

$pr(A|-1)=\frac{1}{4}$
$pr(D|-1)=\frac{0}{4}$
multiply by 0, end up having 0.

normalise:
$\frac{0.03125}{0.03125+0}=1$

**False** since the probability equals 100%

c.
$pr(B|+1)=\frac{2}{4}$
$pr(F|+1)=\frac{1}{4}$
$\frac{2}{4}* \frac{1}{4}* \frac{1}{2}=\frac{2}{32}$

$pr(B|-1)=\frac{1}{4}$
$pr(F|-1)=\frac{1}{4}$
$\frac{1}{4}* \frac{1}{4}* \frac{1}{2}=\frac{1}{32}$

normalise:
$\frac{\frac{2}{32}}{\frac{2}{32}+\frac{1}{32}}=0.6667$
given +1, which means it is higher.

therefore it is **true**

d.
$pr(A|+1)=\frac{1}{4}$
$pr(F|+1)=\frac{1}{4}$

$pr(A|-1)=\frac{1}{4}$
$pr(F|-1)=\frac{1}{4}$

Therefore when we normalise it will be 50% for both, therefore it is **true**???


e.
**true**


![[_exercise09.pdf#page=3]]
**recall: proportion of test objects of
some class c i that have been
predicted correctly**
[[_DM566-2023-part3.pdf#page=38]]
#### recall A:
$f_{i}=5$
$$recall=\frac{3}{5}$$
#### recall B:
$f_{i}=5$
$$recall=\frac{4}{5}$$

**precision: proportion of test objects predicted as class c i that
actually belong to class c i**
#### precision A:
$h_{i}=4$
$$precision=\frac{3}{4}$$

#### precision B:
$h_{i}=6$
$$precision=\frac{4}{6}$$


a. false
b. true
c. false
d .true
e. false