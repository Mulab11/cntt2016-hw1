# RandomPaintingOnABoard

作者：罗煜楚

关键词：数学 概率 期望 枚举 状态压缩 动态规划

## 题目简述

给出一个$$n\times m$$的棋盘，每个格子上有一个0到9的数字，所有的数字之和为S，现在玩一个游戏，一开始所有的格子都是白色的，每一回合你要按一定的概率选择一个格子，并将这个格子染黑（已经被染黑的格子可能被重复染色），如果一个格子上的数字为$$x$$，那么这个格子被选择的概率是$$\frac{x}{S}$$，当在某一回合之后，如果发现这个棋盘的每一行每一列都至少有一个格子是黑色的，那么游戏结束，请求出游戏结束的期望回合数。

$$1 \leqslant n,m \leqslant 21$$

$$1 \leqslant n \times m \leqslant 150$$

每个格子上的数字保证在0到9之间

保证每一行每一列至少有一个格子上的数字非0

## 算法

首先我们注意到由于$$1 \leqslant n \times m \leqslant 150$$，而$$13 \times 13 = 169$$所以n，m中小的那一个不会超过12，我们可以将数据范围看作$$n \leqslant 12, m \leqslant 21$$。

如果直接计算期望的回合数，公式是这样的：


$$
E(\text{number of steps}) = \sum_{i=0}^\infty {i P(\text{i steps are needed}) }
$$


这个公式还有个i的系数，不太好算，于是我们可以将计算期望的公式变一下。  
由于


$$
P\left(\text{i steps are needed}\right) = P\left(\text{Not done after i-1 steps}\right) - P\left(\text{Not done after i}\right)
$$


所以可以推出


$$
\begin{align} E\left(\text{number of steps}\right) &= \sum_{i=0}^\infty {i P\left(\text{Not done after i-1 steps}\right)} - \sum_{i=0}^\infty {i P\left(\text{Not done after i steps}\right)} \\ E\left(\text{number of steps}\right) &= 0 * P\left(\text{Not done after -1 steps}\right) + \sum_{i=1}^\infty {i P\left(\text{Not done after i-1 steps}\right)} \\ &- \sum_{i=1}^\infty {\left(i - 1\right) P\left(\text{Not done after i-1 steps}\right)} \\ E\left(\text{number of steps}\right) &= \sum_{i=1}^\infty {\left(i P\left(\text{Not done after i-1 steps}\right) - \left(i-1\right) P\left(\text{Not done after i-1 steps}\right) \right)} \\ E\left(\text{number of steps}\right) &= \sum_{i=1}^\infty {P\left(\text{Not done after i-1 steps}\right)} \end{align}
$$


所以我们就只需要算出经过i回合之后游戏没有结束的概率了，这就很好解决了。由于游戏没有结束，那么一定是有一些行或列之中一个格子都没有被选中，这就是一个简单的容斥原理的应用


$$
\begin{align} P\left(\text{Not done after } i \text{ steps}\right) &= \sum_{ x \in \left( \text{rows } \cup \text{ columns} \right) } { \left(1 - P(x) \right)^i } \\ &- \sum_{ \left\{x_0,x_1\right\} \subseteq \left( \text{rows } \cup \text{ columns} \right) } { \left(1 - P\left\{x_0,x_1\right\} \right)^i } \\ &+ \sum_{ \left\{x_0,x_1,x_2\right\} \subseteq \left( \text{rows } \cup \text{ columns} \right) } { \left(1 - P\left\{x_0,x_1,x_2\right\} \right)^i } \\ &- \sum_{ \left\{x_0,x_1,x_2,x_3\right\} \subseteq \left( \text{rows } \cup \text{ columns} \right) } { \left(1 - P\left\{x_0,x_1,x_2,x_3\right\} \right)^i } \\ &+ ... \end{align}
$$


我们先将每一行每一列不被选中的概率加起来，即$$(1-P(x))^i$$，然后发现对于有两个行/列的情况，我们计算了两次，所以要减去$$(1-P \left\{ x_{0}, x_{1} \right\} )^i$$，而有三个行/列的情况，在算一个的时候算了3次，算两个时减去3次，所以又少算了，有要加上$$(1-P \left \{ x_1, x_2, x_3 \right \})$$...，所以最后形式如下


$$
\begin{align} P\left(\text{Not done after } i \text{ steps}\right) &= \sum_{ s \subseteq \left( \text{rows } \cup \text{ columns} \right) , \left|s\right| \text{ is odd} } \left( 1 - P\left(s\right) \right) ^ i \\ &- \sum_{ s \subseteq \left( \text{rows } \cup \text{ columns} \right) , \left|s\right| \text{ is even} } \left( 1 - P\left(s\right) \right) ^ i \end{align}
$$


然后我们将这个公式于之前算期望的公式结合起来得到：


$$
\begin{align} E\left(\text{number of steps}\right) &= \sum_{i=0}^\infty { \left( \sum_{\text{odd }s } {\left( 1 - P\left(s\right) \right) ^ i} - \sum_{\text{even }s}{\left( 1 - P\left(s\right) \right) ^ i} \right)} \\ E\left(\text{number of steps}\right) &= \sum_{\text{odd }s } {\left( \sum_{i=0}^\infty \left( 1 - P\left(s\right) \right) ^ i \right) } - \sum_{\text{even }s}{\left( \sum_{i=0}^\infty \left( 1 - P\left(s\right) \right) ^ i \right)} \end{align}
$$


对于$$\sum_{i=0}^\infty (1-P(s))^i$$可以使用等比数列求和求出等于1+$$\frac{1-P(s)}{1-(1-P(s))}$$，这里不会有$$P(s)=0$$的情况，但是要注意$$P(s)=1$$的特殊情况。

此时我们又发现一个问题，在枚举不被选中行/列的集合s时，复杂度为$$2^{n+m}$$可能非常大，但是我们注意到n的范围只有12，是非常小的，而且格子上的数字都是0~9的小数字，格子上的数字和也不大，于是我们就可以用Dp来解决。

首先由于n很小，所以我们可以枚举s集合中的行是那一些，我们把这些行的概率求和，然后对于每一列，我们算出如果选择这一列，概率和还会增加多少，我们用$$res[i]$$记录在第i列但不在选择的行中的格子上的数字和是多少，我们按列Dp，Dp状态$$f[i][j][0/1]$$表示当前考虑了前i列，当前的选择了的列的$$res$$之和是多少，0/1表示选择了的列的集合大小为奇数还是偶数，d的不同集合的个数。

转移方程：


$$
f[i][j][k] = f[i-1][j][k] + f[i-1][j-res[j]][k \oplus 1]
$$


求出了概率为一特定值的集合的个数，我们就可以直接带入之前的公式计算即可，于是我们就在$$O(2^{n} \times m \times S)$$的时间里解决了这道题。

