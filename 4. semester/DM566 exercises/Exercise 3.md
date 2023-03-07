[[exercise03.pdf]]
[[solution03.pdf]]

### Exercise 3-1: Support based on closed frequent itemsets  

### A

```pdf
{
"url" : "Appendix DM566 - Data mining and machine learning/Lattice diagram.pdf",
"page" : 1
}
```

### B
![[Part 1 - Introduction + Frequent Pattern Mining#Closed (Frequent) Itemsets|Closed (Frequent) Itemsets]]

![[Lattice cfi.jpg]]
Small errors in the image

$\sigma = 2 \to 20$
ACDE 
BCDE 
CDE 
BCE 
BCD 
ACE 
ACD 
ABE 
ABD 
ABC 
AC 
AD 
AE 
BC 
CD 
CE 
D 
C 
A 
{}

$\sigma = 4 \to 11$
ACE: 4 
CDE: 4 
AC: 5 
AD: 4 
BC: 4 
CD: 5 
CE: 6 
A: 7 
C: 7 
D: 6 
{}

### C







### Exercise 3-2: Apriori 
Threshold $\sigma = 2$

1. Take all variation of the endings with the same prefix and add it to the set (The first time: just take all variation, meaning all the different elements/values)
2. If not all the variations of it (parts of the element) can be found in the earlier set, then prune
3. If the threshold $\sigma$ is not met, then prune
4. Repeat

#### C1 and S1
| TranslD | Items |
| :--- | :--- |
| 1 | A B C |
| 2 | B G |
| 3 | C D E |
| 4 | A B D E |
| 5 | A B D |
| 6 | C E F G |
| 7 | A D E F |
| 8 | A C E F G |
| 9 | A D G |
| 10 | A B C E |

S1
| A | 7 |
| :--- | :--- |
| B | 5 |
| C | 5 |
| D | 5 |
| E | 6 |
| F | 3 |
| G | 4 |

#### S2

| AB | 4 |
| :--- | :--- |
| AC | 2 |
| AD | 4 |
| AE | 4 |
| AF | 2 |
| AG | 2 |
| BC | 2 |
| BD | 2 |
| BE | 2 |
| BG | ~~1~~ |
| CD | ~~1~~ |
| CE | 4 |
| CF | 2 |
| CG | 2 |
| DE | 2 |
| DF | ~~1~~ |
| DG | ~~1~~ |
| EF | 3 |
| EG | 2 |
| FG | 2 |

#### S2 to S3
| AB | 4 |
| :--- | :--- |
| AC | 2 |
| AD | 4 |
| AE | 4 |
| AF | 2 |
| AG | 2 |
| BC | 2 |
| BD | 2 |
| BE | 2 |
| CE | 4 |
| CF | 2 |
| CG | 2 |
| DE | 2 |
| EF | 3 |
| EG | 2 |
| FG | 2 |

#### C3

| ABC |-|
| :--- |-|
| ABD |-|
| ABE |-|
| ~~ABF~~ |-|
| ~~ABG~~ |-|
| ~~ACD~~ |-|
| ACE |-|
| ACF |-|
| ACG |-|
| ADE |-|
| ~~ADF~~ |-|
| ~~ADG~~ |-|
| AEF |-|
| AEG |-|
| AFG |-|
| ~~BCD~~ |-|
| BCE |-|
| BDE |-|
| CEF |-|
| CEG |-|
| CFG |-|
| EFG |-|

#### S3 to S4
| ABC |-|
| :--- |-|
| ABD |-|
| ABE |-|
| ACE |-|
| ACF |-|
| ACG |-|
| ADE |-|
| AEF |-|
| AEG |-|
| AFG |-|
| BCE |-|
| BDE |-|
| CEF |-|
| CEG |-|
| CFG |-|
| EFG |-|

#### C4

| ABC | 2 |
| :--- | :--- |
| ABD | 2 |
| ABE | 2 |
| ACE | 2 |
| ACF | ~~1~~ |
| ACG | ~~1~~ |
| ADE | ~~1~~ |
| AEF | 2 |
| AEG | ~~1~~ |
| AFG | ~~1~~ |
| BCE | ~~1~~ |
| BDE | ~~1~~ |
| CEF | 2 |
| CEG | 2 |
| CFG | 2 |
| EFG | 2 |

#### S4 to S5
| ABCD |-|
| :--- |-|
| ABCE |-|
| ABDE |-|
| CEFG |-|

#### C5
One is left

- CEFG


### Exercise 3-3: Color-histograms and distance functions  

$p:=[2,4,7]$
$q:=[5,6,8]$
$w:=[2,2.5,3]$

$\begin{aligned} M_1:=\left[\begin{array}{lll}1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1\end{array}\right] \\ & \end{aligned}$

$\begin{aligned} & M_2:=\left[\begin{array}{ccc}1 & 0.8 & 0.6 \\ 0.5 & 1 & 0.9 \\ 0.5 & 0.7 & 1\end{array}\right]  \\ & \end{aligned}$

$\operatorname{dist}_2(p, q)=\sqrt{14}$
$\text{ dist }_1(p, q)=6$
$\operatorname{dist}_{\infty}(p, q)=3$
$\operatorname{dist}_w(p, q, w)=5.567764363$

### A)

|Histogram|Red|Orange|Blue|
|---------|---|------|----|
|Q|1|8|7|
|A|1|4|4|
|B|8|1|7|
|C|2|4|9|
|D|1|2|13|


### B)
$q:=[1,8,7]$
$a:=[1,4,4]$
$b:=[8,1,7]$
$c:=[2,4,9]$
$d:=[1,2,13]$

$\operatorname{dist}_1(p, q):=\left|p_1-q_1\right|+\left|p_2-q_2\right|+\left|p_3-q_3\right|$

$\text { dist }_2(a, q)=\sqrt{ 25 }$
$\text { dist }_2(b, q)=\sqrt{ 98 }$
$\text { dist }_2(c, q)=\sqrt{ 21 }$
$\text { dist }_2(d, q)=\sqrt{ 72 }$

### C)
It doesn't account for if the same color is split up in the picture or is one




### Exercise 3-4: Visualisation Tool

