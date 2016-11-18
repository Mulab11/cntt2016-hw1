# TheSquareRootDilemma
作者：徐明宽

关键词：简单数论 平方数 平方因子 枚举 分块 线性筛 莫比乌斯函数 次线性复杂度（一道easy弄了这么多关键词……）

## 题目简述
输入两个正整数$$N, M$$，输出有多少组有序数对$$(A, B)$$满足$$1 \leq A \leq N, 1 \leq B \leq M$$且$$ \left(\sqrt{A} + \sqrt{B} \right)^2$$是整数。
保证$$N, M \leq 77777$$。

## 分析
因为$$ \left(\sqrt{A} + \sqrt{B} \right)^2 = A + B + 2\sqrt{AB}$$，所以$$ \left(\sqrt{A} + \sqrt{B} \right)^2$$是整数等价于$$AB$$是完全平方数。（证明：如果$$AB$$是完全平方数，那么显然$$ \left(\sqrt{A} + \sqrt{B} \right)^2 = A + B + 2\sqrt{AB}$$为整数；如果$$AB$$不是完全平方数，那么$$\sqrt{AB}$$为无理数，$$ \left(\sqrt{A} + \sqrt{B} \right)^2 = A + B + 2\sqrt{AB}$$自然也是无理数，也就不是整数了。）

我们可以将$$A$$和$$B$$中的所有平方因子除去以后所得的数分别记为$$a$$和$$b$$（即：将$$A$$分解质因数，设 $$A = p_1^{2k_1+1} \times p_2^{2k_2+1} \times ... \times q_1^{2w_1} \times q_2^{2w_2}$$（其中$$p_i, q_i$$是质数，$$k_i$$是非负整数，$$w_i$$是正整数），令$$a = p_1 \times p_2 \times ... $$；由$$B$$计算$$b$$的方法类似）。那么因为$$AB$$是完全平方数，所以$$ab$$也是完全平方数。于是对于任意质数$$p | a$$，有$$p^2 | ab$$，又因$$a$$和$$b$$都没有平方因子，所以$$p^2$$不整除$$a$$，于是$$p | b$$。所以$$a | b$$。同理，$$b | a$$。**于是有$$a = b$$。**

## 算法一
分析到这里，我们可以得出一个算法：枚举$$A$$，由于$$A / a$$是$$A$$的约数中最大的完全平方数，我们可以通过枚举不超过$$A$$的所有完全平方数看是不是$$A$$的约数（当然直接把$$A$$分解质因数也行）来计算出$$a$$，也就得到了$$b$$，那么$$B$$一定是$$b$$的完全平方数倍，枚举这个倍数，这样就能找出所有有序数对$$(A, B)$$了。时间复杂度是$$O(N \times (\sqrt{N} + \sqrt{M}))$$，空间复杂度是$$O(1)$$。

## 算法二
换一种思路，考虑枚举$$a$$，计算有多少组对应的有序数对$$(A, B)$$。如果我们枚举了$$a$$（也就是$$b$$）（注意$$a$$只能取不包含平方因子的数），那么只需让$$A / a, B / b$$为完全平方数，并且$$1 \leq A \leq N, 1 \leq B \leq M$$即可满足要求。当$$a, b$$确定时，$$A, B$$可以取的值的数量分别与不超过$$\lfloor N / a \rfloor$$和$$\lfloor M / b \rfloor$$的完全平方数个数相同，即分别为$$\big\lfloor\sqrt{\lfloor N / a \rfloor}\big\rfloor$$和$$\big\lfloor\sqrt{\lfloor M / b \rfloor}\big\rfloor$$。

现在的问题就变成了找出所有$$a$$，即不超过$$ \min(N, M)$$的所有不包含平方因子的数。我们可以用筛法求出来，即把所有（大于$$1$$的）完全平方数的倍数筛掉，剩下的就是不包含平方因子的数。这样做的时间复杂度是$$ \min(N, M) \times \sum_{i = 1}^{\lfloor \sqrt{ \min(N, M)} \rfloor}{i^{-2}} = O( \min(N, M))$$。然后枚举$$a$$，将对应的$$A$$和$$B$$的数量乘起来（即$$\big\lfloor\sqrt{\lfloor N / a \rfloor}\big\rfloor \times \big\lfloor\sqrt{\lfloor M / a \rfloor}\big\rfloor$$）计入答案即可。总时间复杂度与空间复杂度都是$$O( \min(N, M))$$。

## 算法三

下面来探讨一下复杂度低于线性的算法。

根据算法二，答案$$ =\sum_{a=1}^{\min(N, M)} \mu^2(a) \cdot \big\lfloor\sqrt{\lfloor N / a \rfloor}\big\rfloor \cdot \big\lfloor\sqrt{\lfloor M / a \rfloor}\big\rfloor$$ 。

注意到根据容斥原理，$$\sum_{a=1}^{n} \mu^2(a) = \sum_{i=1}^{\lfloor \sqrt{n} \rfloor} \mu(i) \cdot \lfloor \frac{n}{i^2} \rfloor$$ 可以在较低的时间复杂度内计算，而$$\big\lfloor\sqrt{\lfloor N / a \rfloor}\big\rfloor \cdot \big\lfloor\sqrt{\lfloor M / a \rfloor}\big\rfloor$$的取值个数又不是很多，所以可以考虑分块，即对于$$\big\lfloor\sqrt{\lfloor N / a \rfloor}\big\rfloor \cdot \big\lfloor\sqrt{\lfloor M / a \rfloor}\big\rfloor$$的每种取值计算对应的一段$$\mu^2$$的区间和。

假设我们用线性筛预处理了$$S$$以内的$$\mu$$的前缀和以及$$\mu^2$$的前缀和。（下面为了方便描述，不妨设$$N<M$$）那么对于$$a$$从$$S$$到$$N$$，$$\big\lfloor\sqrt{\lfloor N / a \rfloor}\big\rfloor$$从$$\big\lfloor\sqrt{\lfloor N / S \rfloor}\big\rfloor$$下降到$$1$$，$$\big\lfloor\sqrt{\lfloor M / a \rfloor}\big\rfloor$$从$$\big\lfloor\sqrt{\lfloor M / S \rfloor}\big\rfloor$$下降到$$\big\lfloor\sqrt{\lfloor M / N \rfloor}\big\rfloor$$，所以$$\big\lfloor\sqrt{\lfloor N / a \rfloor}\big\rfloor \cdot \big\lfloor\sqrt{\lfloor M / a \rfloor}\big\rfloor$$一共只有不超过$$\big\lfloor\sqrt{\lfloor N / S \rfloor}\big\rfloor + \big\lfloor\sqrt{\lfloor M / S \rfloor}\big\rfloor - \big\lfloor\sqrt{\lfloor M / N \rfloor}\big\rfloor$$种取值。

对于任意$$n​$$，计算$$\sum_{a=1}^{n} \mu^2(a)​$$时，$$\lfloor \frac{n}{i^2} \rfloor​$$一共只有不超过$$O(n^{1/3})​$$种取值（因为要么$$i \leq n^{1/3}​$$，要么$$\lfloor \frac{n}{i^2} \rfloor \leq n^{1/3}​$$），所以如果$$S \geq \lfloor \sqrt{n} \rfloor​$$，$$\sum_{a=1}^{n} \mu^2(a)​$$就能在$$O(n^{1/3})​$$的时间内计算。因此，如果$$\lfloor \sqrt{N} \rfloor\leq S < N​$$，这个算法的总时间复杂度为
$$O\left(\left(\big\lfloor\sqrt{\lfloor N / S \rfloor}\big\rfloor + \big\lfloor\sqrt{\lfloor M / S \rfloor}\big\rfloor - \big\lfloor\sqrt{\lfloor M / N \rfloor}\big\rfloor\right) \cdot N^{1/3} + S\right)$$ $$=O\left(\lfloor\sqrt{\lfloor M / S \rfloor}\big\rfloor \cdot  N^{1/3} + S\right)$$。

综上，当$$\max(N, M) \geq \left(\min(N, M)\right)^{7/3}​$$时（这道题中$$N​$$和$$M​$$是同级的，一般不会出现这种情况），取$$S = \min(N, M)​$$，可得时间复杂度$$O(\min(N, M))​$$；否则，取$$S = \left(\max(N, M)\right)^{1/3} \cdot \left(\min(N, M)\right)^{2/9}​$$，可得时间复杂度$$O(\left(\max(N, M)\right)^{1/3} \cdot \left(\min(N, M)\right)^{2/9})​$$。（更直观地，当$$N = M​$$时，时间复杂度为$$O(N^{5/9})​$$）