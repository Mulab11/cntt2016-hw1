# EllysChessboard

---

作者：闵梓轩 王聿中

关键词：动态规划，曼哈顿距离

## 题目简述

> 一个$$8*8$$的棋盘上有若干个位置上需要放棋子，放置第一个棋子的代价为0，之后放置每一个棋子的代价是这个棋子与之前放置的所有棋子的曼哈顿距离的最大值，即$$cost_{i} = max \left\{ \left|x_{i}-x_{j}\right|+\left|y_{i}-y_{j}\right|\right\} \left( 0 < j < i\right)$$，确定一个顺序使得总代价最小。

---

为了方便，以下我们设$$n$$为所需要放置棋子的格子数。

### 算法一

枚举所有可能的放置排列，然后计算代价，求最小值，时间复杂度$$O\left(n!n^{2}\right)$$

### 算法二

状态压缩DP，记录$$f_{S}$$为已经放置S这个集合棋子的最小的代价，状态转移方程为$$f_{S}=min\left\{f_{S-\left\{i\right\}}+cost_{i}\right\}\left(i \in S\right)$$，时间复杂度$$O\left(2^{n}n^{2}\right)$$

### 算法三

考虑在算法一中如何快速计算每一个棋子的代价。  
公式：$$\left|a-b\right|=max\left\{a-b,b-a\right\}$$  
$$cost_{i}=max\left\{\left|x_{i}-x_{j}\right|+\left|y_{i}-y_{j}\right|\right\}\\
=max\left\{max\left\{ x_{i}-x_{j},x_{j}-x_{i} \right\} +max\left\{ y_{i}-y_{j} , y_{j}-y_{i} \right\} \right\}\\
=max\left\{max\left\{\left(x_{i}+y_{i}\right)-\left(x_{j}+y_{j}\right),\left(x_{j}+y_{j}\right)-\left(x_{i}+y_{i}\right)\right\},max\left\{\left(x_{i}-y_{i}\right)-\left(x_{j}-y_{j}\right),\left(x_{j}-y_{j}\right)-\left(x_{i}-y_{i}\right)\right\}\right\}\\
=max\left\{\left|\left(x_{i}+y_{i}\right)-\left(x_{j}+y_{j}\right)\right|,\left|\left(x_{i}-y_{i}\right)-\left(x_{j}-y_{j}\right)\right|\right\}$$  
如果我们定义重新定义一个棋子的新坐标$$x_{i}^{'}=x_{i}+y_{i},y_{i}^{'}=x_{i}-y_{i}$$  
，那么$$cost_{i}=max\left\{\left|x_{i}^{'}-x_{j}^{'}\right|,\left|y_{i}^{'}-y_{j}^{'}\right|\right\}$$  
于是我们在算法一中使用新坐标进行计算代价时只需要记录之前的棋子中x/y的最小/最大值（$$x_{min},x_{max},y_{min},y_{max}$$），即可$$O\left(1\right)$$计算出该棋子的代价。  
此时算法二中的状态也可以从取完一个集合等价转换成取完以$$x_{min},x_{max},y_{min},y_{max}$$为边界的矩形内的点（可以证明当矩形扩大时再取这些点不会比没扩大时代价更小）。  
设坐标范围为$$l$$新的DP状态数为$$O\left(l^{4}\right)$$（其中自带$${0.5}^{2}$$的常数），状态转移枚举新取的点为$$O\left(l^{2}\right)$$（由于点的数目不变，因此自带$${0.5}^{2}$$的常数），计算代价花费$$O\left(l^{2}\right)$$（仍自带$${0.5}^{2}$$的常数），总的时间复杂度为$$O\left(l^{8}\right)$$，同时由于新坐标的范围由于两个坐标相加减变为了原来的两倍，所以$$l<16$$。
~~上述复杂度看起来不能通过，但是实际运行时达不到上述复杂度所该有的运算量，我也无法证明是常数过小，还是上面的时间复杂度上界估算不紧确。如果是后者，欢迎各位大佬给出更紧确的复杂度上界。~~
由于有$${0.5}^{6}$$的常数，因此这个算法可以通过本题。