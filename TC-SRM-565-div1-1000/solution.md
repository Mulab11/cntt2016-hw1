# UnknownTree
作者:陆宇暄 陈俊锟

关键词:计数 分类讨论

## 题目简述
给定长度为$$n$$的数组$$a[],b[],c[]$$问满足以下条件的无根树的个数(对大质数取模).
$$*.$$有$$n+3$$个点标号分别为$$0,1,2,3,......,n-2,n-1,A,B,C$$
$$*.$$树的边权是正整数
$$*.$$对于标号为$$x$$的点,和点$$A$$的距离为$$a[x]$$,和点$$B$$的距离为$$b[x]$$,和点$$C$$的距离为$$c[x]$$.

保证$$1 \leq n \leq 50 $$,$$a[],b[],c[] \leq 10^8$$.

## 分析
考虑只有一个数组$$a[]$$的约束的情况,方案数显然等于$$\prod_i(1+\sum_j dis_j<dis_i)$$

考虑如何将题目中的问题转化为该问题,题目中的树可以分为以下几类:

![](/TC-SRM-565-div1-1000/img1.png)

$$*.$$对于链状的情况,只需要计算每个点在链上的$$5$$种相对位置即可.

![](/TC-SRM-565-div1-1000/img2.png)

$$*.$$对于Y字形的情况,则要考虑$$6$$种相对位置.

![](/TC-SRM-565-div1-1000/img3.png)

每张图相同颜色的情况比较相似,可以共同考虑.
至此,我们有了一个大致框架.

## 算法1
显然的,只有一个数组$$a[]$$的约束时,可以排序后快速计算,复杂度为$$O(n \times log(n))$$.

###Y字形部分
对于Y字形,可以枚举中间点$$x$$,然后就可以得到$$A$$,$$B$$,$$C$$的具体信息,就可以判断其他的点在这$$3$$大类中属于哪个大类以及挂在哪个位置,随后调用一个约束的算法即可.
由于树是带编号的,所以不同中间点的树总是不同的,可以把这些答案直接相加得到这个部分的结果.

###链状部分
对于链状的情况,哪个特殊点在中间位置是等价的,不妨设$$A$$点在中间位置.这种情况**不能**直接获得$$A$$,$$B$$,$$C$$的具体信息,枚举很容易造成重复,不是很好统计,有如下两种解决方法:
####枚举+判重
枚举每个点在链上的情况,统计出所有可能的$$pair(dis(A,B),dis(B,C))$$,用一个map判重后类似Y字形部分计算.
####直接干
找到离$$A$$点最近的点$$x$$,$$x$$点**必然**存在于$$A$$,$$B$$,$$C$$所在链上,直接讨论$$x$$点的位置(共有$$4$$种),然后类似Y字形部分计算.

时间复杂度:   $$O(n^2 \times log(n))$$

##一些后话
这个题目说得简单(划掉),细节却十分繁琐,分享一下本人调试程序是遇到的一些问题:  
$$*.$$由于边权要是整数,所以有**很多**时候计算距离要$$/2$$时要先判定是否是$$2$$的倍数.  
$$*.$$如果一个子树中不存在一个在$$A$$,$$B$$,$$C$$链上的点就会挂不上去,而且不能存在一个以上.  
$$*.$$map< int,vector< int > >能大大简化代码,千万不要纠结于常数(大佬们当我没说).  


## 算法2

这道题的关键在于关键点（A、B 或 C）两两的链上的点。

考虑有现在的信息可以做什么：我们可以取出两个关键点之间的非关键点构成的链。首先，两个点 A、B 之间的距离就是 $$\min(a_i+b_i)$$，因此所有满足 $$a_p+b_p=\min(a_i+b_i)$$ 的点 $$p$$ 都在链上。为了求出链的顺序，我们将这些点按照 $$a_i$$ 排序即可。排序可以离散化之后基数排序，因此取出一条链的复杂度为 $$O(n)$$。

我们可以实现一个 ```solve(E)``` 函数，传入一个边集 $$E=\{(x_i,y_i,v_i)\}$$，返回如果至少加入 $$E$$ 中的这些边，方案数是多少，其中必须保证“加入了 $$E$$ 这些边之后，关键点两两的链上的点都确定了”。为了计算出这个方案，我们可以取出关键点两两之间的链，然后链上的点的方案就唯一了；对于不在关键点两两的链上的点 $$i$$，每个点都要找一个点 $$j$$ 做父亲，并且这里父亲的方案是互不影响的，则根据乘法原理方案数就是每个点父亲的方案数乘起来。$$j$$ 能是 $$i$$ 的父亲（其中 $$i$$ 是不在关键点两两的链上的点，$$j$$ 不一定）的充要是 $$a_i-a_j = b_i-b_j = c_i-c_j > 0$$，这可以转化为 $$a_j< a_i, b_j-a_j=b_i-a_i, c_j-a_j=c_i-a_i$$，可以（在外部）按照 $$a$$ 排序后，用哈希表维护 $$(b_j-a_j,c_j-a_j)$$，因此这样一次 ```solve``` 的复杂度为 $$O(n)$$。

现在，我们就可以枚举关键点之间的链上的情况了。可以先考虑特殊情况：某两个关键点的链上没有任何非关键点的情况。判断两个关键点是否有可能满足这个条件可以这样：设我们要判断的两个关键点数组分别为 $$a_i$$ 和 $$b_i$$，则必然满足所有 $$|a_i-b_i|$$ 全部相等（且全都等于两个关键点的距离），$$O(n)$$ 判断即可。判断完后，我们就可以考虑以下两种情况了：

1. 三个点两两之间的链上都没有非关键点：那么一定存在一条链是 $$A-B-C$$ 或 $$A-C-B$$ 或 $$B-A-C$$，对每种情况调用一次 ```solve``` （加入三种情况的边）即可。

2. 有且只有两个点之间的链上没有非关键点：那就枚举两个点（不妨设为 A、B），再枚举第三个点（不妨设为 C）是在 A 还是 B 的子树里面。不妨设在 A 的子树里面，那么我们就 $$O(n)$$ 暴力取出 A 到 C 的链（并判断非法），用链中的边集并上 $$(A,B,距离)$$ 调用一次 ```solve```。

现在考虑最一般的情况：三个点两两之间的链上都有非关键点。我们先求出两两之间链上的点集，则这些点集必须满足：有且只有一个点会出现在每一条链上（即 A、B、C 三点的 LCA，设为中心点），其他点必然出现在偶数（0 或 2）条链上。不满足则说明没有这种情况。中心点有可能是关键点或非关键点，如果是非关键点，则可以直接找出只出现了一次的点，将其作为中心点之后，加边（并判断各种非法情况，比如加入的边边权冲突、两个关键点的链上没有非关键点）后调用一次 ```solve``` 函数；如果是关键点，则可以通过链长找出这个关键点（也要判断是否有保证每两个关键点之间都至少存在一个非关键点），加边后调用一次 ```solve``` 函数。这样，所有情况就都考虑清楚了。

由上述分析，调用 ```solve``` 函数的次数是一个常数，与 $$n$$ 无关，因此本算法的复杂度为排序复杂度 $$O(n\log n)$$。（我提交的代码中 ```solve``` 函数用了 $$O(n^2)$$ 暴力求父亲的方案数）
