# EllysChessboard

---

作者：闵梓轩 王聿中 徐明宽

关键词：动态规划，曼哈顿距离，贪心优化DP

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
设坐标范围为$$l$$新的DP状态数为$$O\left(l^{4}\right)$$（其中自带$${0.5}^{2}$$的常数），状态转移枚举新取的点为$$O\left(l^{2}\right)$$（由于点的数目不变，因此自带$${0.5}^{2}$$的常数），计算代价花费$$O\left(l^{2}\right)$$（仍自带$${0.5}^{2}$$的常数），总的时间复杂度为$$O\left(l^{8}\right)$$，同时由于新坐标的范围由于两个坐标相加减变为了原来的两倍，所以$$l < 16$$。
~~上述复杂度看起来不能通过，但是实际运行时达不到上述复杂度所该有的运算量，我也无法证明是常数过小，还是上面的时间复杂度上界估算不紧确。如果是后者，欢迎各位大佬给出更紧确的复杂度上界。~~
由于有$${0.5}^{6}$$的常数，因此这个算法可以通过本题。

### 算法四

同样进行坐标转换$$x_{i}'=x_{i}+y_{i},y_{i}'=x_{i}-y_{i}$$ ，DP状态定义为$$f\left(x_{mn},x_{mx},y_{mn},y_{mx}\right)$$（注意区别于$$x_{min},x_{max},y_{min},y_{max}$$，例如可能不存在一个棋子的横坐标为$$x_{mn}$$）表示取完以$$x_{mn},x_{mx},y_{mn},y_{mx}$$为边界的矩形内的所有棋子的最小代价。转移时并不用枚举所有新取的点，因为新取的点一定在矩形的最边上一行或一列（先取更远的点肯定不优）；或者说，$$f\left(x_{mn},x_{mx},y_{mn},y_{mx}\right)$$只会由$$f\left(x_{mn}+1,x_{mx},y_{mn},y_{mx}\right)$$、$$f\left(x_{mn},x_{mx}-1,y_{mn},y_{mx}\right)$$、$$f\left(x_{mn},x_{mx},y_{mn}+1,y_{mx}\right)$$、$$f\left(x_{mn},x_{mx},y_{mn},y_{mx}-1\right)$$转移而来。可以花$$O\left(l^{2}\right)$$的时间算出当前矩形里的棋子的x/y的最小/最大值（$$x_{min},x_{max},y_{min},y_{max}$$），即可在每次$$O\left(l\right)$$的时间内计算代价，枚举（第一个）新取的点共$$O\left(l\right)$$个，于是总时间复杂度降到了$$O\left(l^{6}\right)$$。

也可以花$$O\left(l^{4}\right)$$的时间预处理每个矩形里的棋子的x/y的最小/最大值。同时我们发现并不用枚举所有新取的点——虽然（第一个）新取的点有$$O\left(l\right)$$种取法，但是只有$$4$$种不同的矩形，对于每种矩形一定有一种取法是最优（不比其他所有取法差）的。不妨设新取了最上面一行（即改变了$$y_{mx}$$），如果这一行只有$$\leq 1$$个点则无需讨论；否则，取这行的任何一个点以后$$y_{max}, y_{min}$$均不会再改变，如果取这行的所有点以后$$x_{min}, x_{max}$$均未改变，那么任何一种取法的代价均相同；否则，不妨设$$x_{min}$$改变，则我们显然应该先取那些不改变$$x_{min}$$的点以使代价最小，于是$$f\left(x_{mn},x_{mx},y_{mn},y_{mx}\right)$$应该由$$f\left(x_{min},x_{mx},y_{mn},y_{mx}\right)$$（经由$$f\left(x,x_{mx},y_{mn},y_{mx}\right)$$，其中$$x \in (x_{mn}, x_{min})$$）而不是$$f\left(x_{mn},x_{mx},y_{mn},y_{mx}-1\right)$$转移而来（$$x_{max}$$改变或者$$x_{min},x_{max}$$均改变的情况与之类似），所以无论现在选择了哪种取法均不会改变DP的结果（因为这种转移方式本身就不是唯一最优的（我们刚才找到了另一种一定不比这种差的转移方式），所以把代价计算得大一些也无所谓）。
于是我们可以只枚举这$$4$$种矩形而不是枚举$$O(l)$$个（第一个）新取的点，然后以任意顺序计算这$$O(l)$$个点的代价，总时间复杂度就降到了$$O\left(l^{5}\right)$$。

### 算法五

考虑对算法四进一步优化。每次转移时新取的棋子的代价为$$\max\{x_i - x_{min}, x_{max} - x_i, y_i - y_{min}, y_{max} - y_i\}​$$，而（不妨设）新取一行时这$$O\left(l\right)​$$个棋子的$$y_i​$$均相同（就是$$y_{max}​$$或$$y_{min}​$$），所以代价为$$\max\{x_i - x_{min}, x_{max} - x_i, y_{max} - y_{min}\}​$$。看上去$$O\left(l\right)​$$个这种式子的和还是不太好优化，但是我猜想存在一种最优的DP转移方案使得$$x_i​$$不等于$$x_{min}​$$或$$x_{max}​$$时$$x_i - x_{min}​$$和$$x_{max} - x_i​$$均不超过$$y_{max} - y_{min}​$$，这样预处理一下棋子个数的前缀和就能在$$O(1)​$$的时间内转移了（代价就等于$$num \cdot \max\{x_{max} - x_{min}, y_{max} - y_{min}\}​$$，其中$$num​$$为棋子个数）。总时间复杂度为$$O\left(l^{4}\right)​$$。代码通过了system test但我不太会证明这个算法的正确性，欢迎大家给出证明或者叉掉我的[代码](xumingkuan.cpp)。
