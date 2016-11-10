# StringGame
作者：徐明宽

关键词：字符串处理 决策

## 题目简述
现在有一个不含相同元素的仅包含小写字母的**等长**字符串的集合S，两个人用它玩游戏：第一个人选择S中的一个字符串X，把它的字符任意排列，并把字母表（所有26个英文字母）任意排列。然后第二个人可以把S中除了X以外的所有字符串的字符任意排列。现在把所有字符串按第一个人给出的字母表排列方式比较字典序，如果X比其他所有字符串的字典序都严格小，则第一个人赢，否则第二个人赢。

现在问第一个人选择哪些字符串会赢。（双方均采用最优策略）

数据规模：记$$n$$为字符串的数量，$$len$$为S中字符串的长度，则$$2 \leq n \leq 50$$，$$1 \leq len \leq 50$$。为了方便描述复杂度，定义字母数量$$alphabet = 26$$。

## 算法一
当字母表确定以后，两个人肯定会把S中的每个字符串中的字符按字母表排序，比如说字母表是`dbacefgh...z`，那么字符串`aabbcc`会被排列成`bbaacc`，字符串`banana`会被排列成`baaann`。可以发现原字符串中字母的顺序是没有用的，只有每个字母的个数有用。比较两个字符串的字典序也就是按字母表的顺序比较每个字母的个数，顺序靠前的字母更多的字符串字典序小。比如字母表是`dbacefgh...z`时比较`aabbcc`和`banana`两个字符串，`d`数量一样，再看`b`的数量前者比后者多，于是前者比后者字典序小。

我们可以枚举第一个人选的字符串X，然后看能不能选一个字母表使得第一个人赢。假设我们维护了一个*擂台*集合，最开始所有字符串都在*擂台*上，然后看字母表的第一个字母，所有这个字母的数量同样最多的字符串留在*擂台*上，其他字符串被打下*擂台*，然后再看字母表的第二个字母……我们的目标是构造字母表使得所有26轮过后有且仅有字符串X还在*擂台*上。

于是我写了个搜索，搜字母表依次填哪个字母（当然不去搜那些会把X打下*擂台*的字母），加了2个剪枝：

- 如果X和另外某个字符串Y的每个字母的数量都一样，那么不可能满足要求（不可能有一轮把Y打下*擂台*而不把X打下*擂台*）（这个剪枝在调用搜索函数之前）；

- 如果当前在*擂台*上的所有字符串包含的某个字母的数量都相同，那么字母表填这个字母没有意义（不会把任何一个字符串打下*擂台*），就不填它。

然后这个看似$$O(alphabet! \cdot n^2 + len \cdot n)$$的算法就AC了。下面来分析一下实际时间复杂度是多少。

### 分析
第一个人输有且仅有两种情况：

- 在某一轮，字符串X被打下*擂台*了；
- 在所有26轮后，还有别的字符串在*擂台*上。这种情况其实已经被第一个剪枝剪掉了，因为这个“别的字符串”只可能和X的每个字母的数量都一样。

如果最后结论是第一个人能赢，我们可以发现这个搜索跑得飞快。事实上它根本不会回溯。或者说，决策字母表每个位置填哪个字母看似复杂，实际上**填哪个都是对的**。下面来用数学归纳法证明一下这件事。

因为第一个人能赢，所以存在和我们搜索的前0个字母相同的满足要求的字母表。

对于任意$$0 \leq i < 26$$，假设存在和我们搜索的前i个字母相同的满足要求的字母表，不妨任取其中一个字母表A。

观察我们搜索到的第i+1个字母，如果和A的第i+1个字母相同（i=25时必然是这种情况），那么很好，A就是一个和我们搜索的前i+1个字母相同的满足要求的字母表；如果和A的第i+1个字母不同，那么在A中找到我们搜索的第i+1个字母，假设它是第k个（k > i+1），把它拎出来提到第i+1的位置，得到一个字母表A’（A’的前i+1个字母和我们搜索的相同），那么对于字母表A’的第i+2到第k轮，很显然字符串X都不会被打下*擂台*，而第i+1轮由于是搜出来的，自然字符串X也不会被打下*擂台*。所以字母表A’第k轮后字符串X还在*擂台*上。

可以发现字母表A’第k轮后的*擂台* **包含于**字母表A第k-1轮后的*擂台*，而且所有字母表A第k轮打下去的字符串对于字母表A’来说早在第i+1轮就被打下去了，所以字母表A’第k轮后的*擂台* **包含于**字母表A第**k**轮后的*擂台*，也就是说A’前k轮的选择至少不会比A差，而连A都能让第一个人赢了，自然A’也是可以让第一个人赢的字母表（即，第k轮后的每一轮，A’的*擂台*都包含于A的*擂台*而且字符串X还在*擂台*上，所有26轮后也是如此，所以A’的*擂台*最后剩下的只可能是X这一个字符串）。**所以一定存在一个和我们搜索的前i+1个字母相同的满足要求的字母表。**

综上，存在和我们搜索的前26个字母相同的满足要求的字母表，即搜索会直接搜出一个满足要求的字母表。

因此，如果最后结论是第一个人能赢，这个搜索的总时间复杂度为$$O({alphabet}^2 \cdot n^2 + len \cdot n)$$。

那么如果最后结论是第一个人会输呢？好像没法证明复杂度不是阶乘级的啊……于是我随手出了组数据把自己在topcoder上AC的[程序](xumingkuan/search.cpp)卡TLE了~~（说好的topcoder数据很强呢）~~，数据如下（当字符串X为第一个字符串时，实际上最后两个字符串注定了第一个人会输，但第2~24个字符串却使c~y这23个字母都可以填，于是这个搜索要花23的阶乘量级的时间才能确定第一个字符串会使第一个人输）：

```
abcdefghijklmnopqrstuvwxy
abcdefghijklmnopqrstuvwxz
abcdefghijklmnopqrstuvwyz
abcdefghijklmnopqrstuvxyz
abcdefghijklmnopqrstuwxyz
abcdefghijklmnopqrstvwxyz
abcdefghijklmnopqrsuvwxyz
abcdefghijklmnopqrtuvwxyz
abcdefghijklmnopqstuvwxyz
abcdefghijklmnoprstuvwxyz
abcdefghijklmnoqrstuvwxyz
abcdefghijklmnpqrstuvwxyz
abcdefghijklmopqrstuvwxyz
abcdefghijklnopqrstuvwxyz
abcdefghijkmnopqrstuvwxyz
abcdefghijlmnopqrstuvwxyz
abcdefghiklmnopqrstuvwxyz
abcdefghjklmnopqrstuvwxyz
abcdefgijklmnopqrstuvwxyz
abcdefhijklmnopqrstuvwxyz
abcdeghijklmnopqrstuvwxyz
abcdfghijklmnopqrstuvwxyz
abcefghijklmnopqrstuvwxyz
abdefghijklmnopqrstuvwxyz
acdefghijklmnopqrstuvwxyz
bcdefghijklmnopqrstuvwxyz
aacdefghijklmnopqrstuvwxy
bbcdefghijklmnopqrstuvwxy
```

嗯所以这个算法的时间复杂度的确是阶乘级的……

## 算法二
其实在算法一的分析里面就已经推导出正解该怎么做了：同样枚举第一个人选的字符串X，如果发现搜索搜不到了，不要回溯，直接返回第一个人会输就好了。或者说，每轮随便选一个使字符串X不被打下*擂台*的字母，如果没有这种字母就返回第一个人会输（因为如果第一个人能赢则一定可以选出来）；如果26轮都选出来了，则如果*擂台*上只剩X了就返回第一个人能赢，否则返回第一个人会输。总时间复杂度为$$O({alphabet}^2 \cdot n^2 + len \cdot n)$$。