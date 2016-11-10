#SemiPerfectPower
作者： 权大磊

关键词： 数学公式推导

#题目描述
定义了一种半完美数，一个数 $$n$$ 被称为半完美数当且仅当存在 $$a、b、c$$ 三个整数使得 $$b > 1,  1 ≤ c < a,  n = c * a ^ b$$ 。 现给出一个区间 $$[L, R]$$ 之间有多少个半完美数。

数据范围： $$ 1 ≤ L, R ≤ 8 * 10,000,000,000,000,000 $$

#题解

问题转化为 $$ 1 - n $$ 中半完美数个数。

第一可以发现，可以只考虑 $$ b == 2 $$ 或 $$ b == 3 $$ 。

当 $$ b > 3 $$ 且 $$b$$ 为偶数时，设 $$ b = 2k$$ , $$ n = c * ( a ^ 2 ) ^ k $$ , 显然 $$ k > 1， 1 ≤ c < a ^ 2$$, 转化为了原问题， 同理 $$ b$$ 为奇数设为 $$ b = 2k+1 $$ 时也可以化为 $$ n = (c*a)*(a^2)^k$$ 。 

我们先来看指数为 $$2$$ 时, 我们另设未知数（接下来未知数与前面无关）， 求 $$ n = a * x ^ 2 $$ 的 $$n$$的个数， 可以发现若 $$a$$ 有完全平方因子， 我们可以把它转移到 $$x$$ 中去， 仍是合法形式， 且对应唯一一种， 所以我们可以枚举不含完全平方因子的数来计算。

我们枚举 $$a$$ ， 又有 $$a * x ^ 2 ≤ n, 1 ≤ a < x $$ ， 所以 $$ a < x ≤ ( n / a )$$ ^ $$ (1/2) $$(开根自己脑补向下取整)。所以个数为 $$(n/a)$$ ^ $$(1/2) - a$$ 。 $$a$$ 只用枚举到 $$n*(1/3)$$。

 ![](QQ图片20161110183038.png)
然而当指数为 3 时， 我们将其设为 $$ n = b * y ^ 3 $$ , 若果 $$b$$ 有完全立方因子， 也可将其转入$$y$$ 中，同理得：
![](QQ图片20161110183603.png)