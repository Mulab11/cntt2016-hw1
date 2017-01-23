# TopCoder SRM 561 Orienteering 题解

作者：钟知闲

关键字：图论 数学 概率与期望

---

## 题目简述

以网格图的形式给出一个无根树，以及树的点集的一个子集 $C$。现从 $C$ 的所有大小为 $K$ 的子集中等概率选取一个子集 $S$，记 $\mathrm{length}$ 为树中经过所有 $S$ 中的点的最短路径长度（路径长度定义为经过的边数，可以重复经过同一条边，此时长度需要被计算多次）。给定无根树、点集 $C$ 以及整数 $K$，求 $\mathrm{length}$ 的期望值。

树的节点数不超过 $50\times 50$，$|C|\le 300$，$2\le K\le |C|$。

## 题解

在解决问题之前首先要明确 $\mathrm{length}$ 如何计算，即对于给定的点集 $S$，经过 $S$ 中所有点的最短路径长度应该怎么求。

由于本题给出的网格图是一个树，所以可以利用树的性质来解决问题。例如，树上任意两点 $u,v$ 间简单路径唯一，且该路径为 $u,v$ 间最短路径；树的每一条边都是割边，删除后导致 $u,v$ 不连通当且仅当该边在 $u$ 到 $v$ 的简单路径上，等等。

类比树上任意两点之间连通，可以得到一个基本的性质：

**性质1** 对于任意 $S\subseteq C$ 和 $a,b\in S$，存在一条从 $a$ 出发经过 $S$ 中所有点到达 $b$ 的路径。

**证明** 设 $S=\{v_0,v_1,...,v_{|S|-1}\}$，其中 $v_0=a$，$v_{|S|-1}=b$，构造路径 $P$，先从 $v_0$ 到 $v_1$，从 $v_1$ 到 $v_2$，…，最后从 $v_{|S|-2}$ 到 $v_{|S|-1}$。因为 $\forall i\in (1,|S|]$，$v_{i-1}$ 和 $v_i$ 在树上连通，所以这样构造的路径 $P$ 一定是合法的。

设 $P$ 是经过 $S$ 中所有点的最短路径，将 $S$ 中的点按照**第一次被 $P$ 经过的时间**排序，记为 $v_0,v_1,...,v_{|S|-1}$，那么有：

**性质2** $P$ 以 $v_0$ 为起点，$v_{|S|-1}$ 为终点。

**证明** 假如 $P$ 不以 $v_0$ 为起点，那么从 $P$ 的起点到 $v_0$ 这一段路径没有经过 $S$ 中的点，去掉后 $P$ 更短，与 $P$ 是最短路径矛盾。

类似地，如果 $P$ 不以 $v_{|S|-1}$ 为终点，则 $v_{|S|-1}$ 之后的路径可以去掉。

**性质3** $\forall i\in[1,|S|)$，$P$ 中第一次经过 $v_{i-1}$ 之后必沿着 $v_{i-1}$ 到 $v_i$ 的简单路径到达 $v_i$。

**证明** 如果 $P$ 中从第一次经过 $v_{i-1}$ 到第一次经过 $v_i$ 这一段不是简单路径，那么改成简单路径后 $P$ 更短，与 $P$ 是最短路径矛盾。

**性质4** 边 $e\in P$ 当且仅当删除 $e$ 后 $S$ 中存在两点不连通（**即 $\exists u,v\in S$，$e$ 在 $u$ 到 $v$ 的简单路径上**）。

**证明** 设删除 $e$ 后存在 $u',v'\in S$ 不连通，那么删除 $e$ 后不可能有 $u',v'\in P$，因此要使 $u',v'\in P$ 必有 $e\in P$。

如果删除 $e$ 后任意 $u',v'\in S$ 仍连通，说明 $\forall u',v'\in S$，$e$ 不在 $u'$ 到 $v'$ 的唯一简单路径上，因此 $e\not\in P$。

**性质5** 任意边 $e$ 在 $P$ 中经过最多 $2$ 次。

**证明** 假设 $e=(u,v)$ 在 $P$ 中出现了 $3$ 次或以上，第 $1$ 次为 $u\rightarrow v$，第 $2$ 次为 $v\rightarrow u$，第 $3$ 次为 $u\rightarrow v$，记 $P'$ 为第 $1$ 次经过 $e$ 后到第 $2$ 次经过 $e$ 前这一段从 $v$ 到 $v$ 的路径，那么可以把第 $1$ 次经过 $e$ 前到第 $2$ 次经过 $e$ 后的路径（$u\rightarrow v$，$P'$，$v\rightarrow u$）删掉，在第 $3$ 次经过 $e$ 后加上 $P'$ 这一段，这样 $P$ 经过的点集不变但长度减少了 $2$，与 $P$ 是最短路径矛盾。

**性质6** 边 $e$ 在 $P$ 中经过恰 $1$ 次当且仅当 $v_0$ 到 $v_{|S|-1}$ 的简单路径包含 $e$。

**证明** 若 $v_0$ 到 $v_{|S|-1}$ 的简单路径包含 $e$，那么删去 $e$ 后 $v_0$ 与 $v_{|S|-1}$ 不连通，故必有 $e\in P$。并且 $e$ 不会在 $P$ 中出现两次，否则若 $e=(u,v)$，第一次为 $u\rightarrow v$，第二次为 $v\rightarrow u$，因之后不再经过 $e$，故删掉 $e$ 后 $v_0$ 和 $v_{|S|-1}$ 均与 $u$ 在同一连通块，矛盾。

反过来，若边 $e=(u,v)$ 在 $P$ 中经过恰 $1$ 次，那么删去 $e$ 后，$v_0$ 与 $u$ 在同一连通块，$v_{|S|-1}$ 与 $v$ 在同一连通块，而 $u,v$ 不连通，从而 $e$ 在 $v_0$ 到 $v_{|S|-1}$ 的简单路径上。

根据以上性质，可以得到，对于点集 $S$，若经过 $S$ 中所有点的最短路径 $P$ 起点为 $u$，终点为 $v$，那么

$$
\begin{equation}
\mathrm{length}(P)=2|E_S-\mathrm{path}(u,v)|+|\mathrm{path}(u,v)| \\=2|E_S|-|\mathrm{path}(u,v)|
\label{Length}
\end{equation}
$$

其中，$\mathrm{length}(P)$ 为路径 $P$ 的长度，$E_S$ 为删除后会导致 $S$ 中存在两点不连通的边集，即出现在某两点 $u,v\in S$ 之间的简单路径上的所有边的集合，$\mathrm{path}(u,v)$ 为 $u,v$ 之间的简单路径的边集，显然 $\mathrm{path}(u,v)\subseteq E_S$。

显然要使 $\mathrm{length}(P)$ 最短，就要选择 $u,v$ 使得 $|\mathrm{path}(u,v)|$ 最大，即 $u,v$ 是 $S$ 中的最远点对。设 $a,b$ 是 $S$ 中的最远点对，由性质1，必定存在从 $a$ 到 $b$ 的合法路径，也就存在从 $a$ 到 $b$ 的最短路径，即满足 \eqref{Length} 的路径。

从而，设 $D_S$ 为 $S$ 中**最远点对**（所有 $u,v\in S$ 中，$|\mathrm{path}(u,v)|$ 的最大值）的距离，则

$$
\begin{equation}
\mathrm{length}=2|E_S|-D_S
\label{Answer}
\end{equation}
$$

现在我们考虑如何求 \eqref{Answer} 的期望值，即 $E(\mathrm{length})$。由期望值的性质不难得出

$$
\begin{equation}
E(\mathrm{length})=2E(|E_S|)-E(D_S)
\label{ExpectedValue}
\end{equation}
$$

因此只需分开计算 $|E_S|$ 和 $D_S$ 的期望值。

首先考虑如何计算 $|E_S|$。用 $E$ 表示树的边集，显然 $E_S\subseteq E$。$E$ 的子集很多，不能枚举每个子集计算其概率。不过不难发现 $E(E_S)=\sum_{e\in E}P(e\in E_S)$，即 $|E_S|$ 的期望就是每条边出现在 $E_S$ 内的概率之和，可以从这个角度进行思考。

对于 $e\in E$，$e\not\in E_S$ 当且仅当删去 $e$ 之后，$S$ 中的点全在同一个连通块内。设 $e$ 删去后的两个连通块 $A,B$（这里的连通块指的是点集）内属于 $C$ 的点数分别为 $s$ 和 $|C|-s$，由于 $C$ 的大小为 $K$ 的子集 $S$ 有 ${|C|\choose K}$ 个，满足 $S\subseteq A$ 的 $S$ 有 ${s\choose K}$ 个，满足 $S\subseteq B$ 的 $S$ 有 ${|C|-s\choose K}$ 个，且由于 $|S|=K\ge 2>|A\cap B|=0$，所以 $S\subseteq A$ 和 $S\subseteq B$ 互斥，故 $e\not\in E_S$ 的概率
$$P(e\not\in E_S)=\frac{s\choose K}{|C|\choose K}+\frac{|C|-s\choose K}{|C|\choose K}$$

因此
$$P(e\in E_S)=1-\frac{s\choose K}{|C|\choose K}-\frac{|C|-s\choose K}{|C|\choose K}$$

注意组合数的值可能很大，因此程序中直接计算可能溢出，超过浮点数的范围。记 $f(a,b,K)=\frac{a\choose K}{a+b\choose K}$，化简可得
$$f(a,b,K)=\frac{\frac{a!}{K!(a-K)!}}{\frac{(a+b)!}{K!(a+b-K)!}}=\frac{a!}{(a-K)!}\cdot\frac{(a+b-K)!}{(a+b)!}\\ =\frac{a(a-1)...(a-K+1)}{(a+b)(a+b-1)...(a+b-K+1)}$$

计算 $f(a,b,K)$ 的方法如下：
```
f(a, b, K):
    x = 1
    for i = 0 to K - 1:
        x = x * (a - i) / (a + b - i)
    return x
```
这样，根据期望的性质就能得出
$$E(|E_S|)=\sum_{e\in E}P(e\in E_S)\\ =\sum_{e\in E}(1-f(s_e,|C|-s_e,K)-f(|C|-s_e,s_e,K))$$

其中 $s_e$ 为删去 $e$ 之后其中一个连通块中属于 $C$ 的点数。这可以使用树形动态规划来求解：将无根树转成有根树，然后记 $s(v)$ 为以 $v$ 为根的子树中属于 $C$ 的节点个数，$c(v)$ 为 $v$ 的子节点集合。则可以计算所有的 $s(v)$：
\begin{equation}
s(v)=\sum_{v'\in c(v)}s(v')+[v\in C]
\label{TreeDP}
\end{equation}

若 $e=(u,v)$，则 $u,v$ 必有一个是另一个的父节点，不妨设 $u$ 是 $v$ 的父节点，那么 $s_e=s(v)$。

这样就能在 $O(|V|)$ 的时间内求出所有的 $s_e$，进而在 $O(|E|K)=O(|V|K)$ 的时间内求出 $E(|E_S|)$，其中 $V$ 为树的点集，$|V|=|E|+1$。由于 $|V|\le 50\times 50=2500$，$K\le 300$，这一步运行是比较快的。

接着再考虑如何计算 $E(D_S)$。因为 $C$ 中的点对只有 $|C|^2\le 300^2$ 个，所以可以枚举点对 $u,v\in C$，计算 $u,v$ 是 $S$ 的最远点对的概率。当然最远点对不唯一，为了使其唯一，我们重新定义一个点对 $u,v$ 的距离
$$d(u,v)=|\mathrm{path}(u,v)|+2^{-h(u)}+2^{-h(v)}$$

这里 $h(v)$ 是对每个点 $v$ 分配的编号，要求所有点的 $h(v)$ 是两两不同的正整数，这样 $d(u_1,v_1)=d(u_2,v_2)$ 要求两者的小数部分相同，即 $2^{-h(u_1)}+2^{-h(v_1)}=2^{-h(u_2)}+2^{-h(v_2)}$，考虑两者的二进制表示可知仅当 $\{u_1,v_1\}=\{u_2,v_2\}$ 时等式成立。于是不同的点对距离不同，最远点对就唯一了。

现在考虑计算 $a,b$ 是 $S$ 的最远点对（所有 $a,b\in S$ 中，$d(a,b)$ 的最大值）的概率，那么需要满足的条件有

$$
\begin{equation}
\forall v\in S-\{a,b\},\max\{d(v,a),d(v,b)\}<d(a,b)
\label{Cond1}
\end{equation}
$$

$$
\begin{equation}
\forall u,v\in S-\{a,b\},d(u,v)<d(a,b)
\label{Cond2}
\end{equation}
$$

事实上只要满足条件 \eqref{Cond1} 就够了。为什么呢？

假设现在条件 \eqref{Cond1} 已经满足了，那么对任意 $u,v\in S-\{a,b\}$，设 $D$ 为 $a$ 和 $b$ 间简单路径， $u',v'$ 为 $D$ 上的两点，满足 $u$ 到 $u'$ 的简单路径与 $D$ 不相交，$v$ 到 $v'$ 的简单路径与 $D$ 不相交（**删除后每个连通块恰有一个点属于 $D$，因为 $D$ 中的点数比 $D$ 中的边数多 $1$，且 $D$ 中的任意两点不可达**），且 $D$ 上从 $a$ 到 $b$ 先经过 $u'$ 再经过 $v'$，即
$$\mathrm{path}(a,u')\cup\mathrm{path}(u',v')\cup\mathrm{path}(v',b)=\mathrm{path}(a,b)$$

（否则交换 $u$ 和 $v$、$u'$ 和 $v'$）根据 \eqref{Cond1}，有
$$|\mathrm{path}(u,u')|+|\mathrm{path}(u',b)|+2^{-h(u)}+2^{-h(b)}
\\<|\mathrm{path}(a,u')|+|\mathrm{path}(u',b)|+2^{-h(a)}+2^{-h(b)}$$

即
$$|\mathrm{path}(u,u')|+2^{-h(u)}<|\mathrm{path}(a,u')|+2^{-h(a)}$$

同理
$$|\mathrm{path}(v,v')|+2^{-h(v)}<|\mathrm{path}(b,v')|+2^{-h(b)}$$

所以
$$d(u,v)=|\mathrm{path}(u,u')|+|\mathrm{path}(u',v')|+|\mathrm{path}(v',v)|
\\+2^{-h(u)}+2^{-h(v)}<|\mathrm{path}(a,u')|+|\mathrm{path}(u',v')|+|\mathrm{path}(b,v')|
\\+2^{-h(a)}+2^{-h(b)}=d(a,b)$$

因此我们证明了满足 \eqref{Cond1} 的同时必然满足 \eqref{Cond2}。

这样问题就简单很多了：对于每对 $a,b\in C$，统计满足 \eqref{Cond1} 的 $S$ 的个数。

在此之前，我们先进行预处理：对每个 $v\in C$，从 $v$ 出发做一遍广度优先搜索，就能得到 $v$ 到每个点的距离。这样的预处理复杂度是 $O(|C||V|)$ 的，没有时间上的问题。

预处理之后就可以找出 $C-\{a,b\}$ 中所有满足条件的点的集合 $F$，即
$$F=\{v\in C-\{a,b\}|\max\{d(v,a),d(v,b)\}<d(a,b)\}$$

注意程序实现的一个细节：比较 $u,v$ 的**新定义的距离**时，不是直接按照定理，而是按照**树上的距离**为第一关键字，$-h(u)$ 为第二关键字，$-h(v)$ 为第三关键字进行比较，这里假设 $h(u)<h(v)$。

现在考虑概率怎么算。首先 $C$ 一共有 ${|C|\choose K}$ 个大小为 $K$ 的子集，满足 $a,b\in S$ 且 $S-\{a,b\}\subseteq F$ 的子集 $S$ 有 ${|F|\choose K-2}$ 个（这是由于去掉确定的 $a,b$ 以外，要从 $F$ 中取 $K-2$ 个点作为 $S-\{a,b\}$），因此 $S$ 满足 \eqref{Cond1} 的概率为
$$\frac{|F|\choose K-2}{|C|\choose K}$$

同样地，为了避免溢出，可以将上式表示为 
\begin{equation}
\frac{K(K-1)}{|C|(|C|-1)}f(|F|,|C|-|F|-2,K-2)
\label{Value}
\end{equation}

然后用之前介绍的方法计算 $f(|F|,|C|-|F|-2,K-2)$。

这样，枚举点对 $a,b\in C$，再通过枚举得到 $|F|$，计算 \eqref{Value} 的值乘 $a,b$ 的距离，所有乘积的和就是 $E(D_S)$。时间复杂度为 $O(|C|^3)$，因为 $|C|\le 300$，所以可以通过。

最后，把 $E(|E_S|)$ 和 $E(D_S)$ 代入 \eqref{ExpectedValue} 就能求出 $\mathrm{length}$ 的期望值了。伪代码如下：
```
f(a, b, K):
    x = 1
    for i = 0 to K - 1:
        x = x * (a - i) / (a + b - i)
    return x

记 cnt 为 |C| 的值
将 C 中的点编号为 1, 2, ..., cnt

// 计算 S 的必经边数 |E_S| 的期望值 E1
E1 = 0
任意指定根节点 root，从 root 出发对树进行广度优先遍历（BFS），求出以 root 为根时每个点 v 的父节点 fa[v]
初始化所有 siz[v]:
    if v 在 C 中: 令 siz[v] = 1
    else: siz[v] = 0
按照 BFS 序的逆序枚举树上的点 v:
    if v 不是 root:
        更新 siz[fa[v]] = siz[fa[v]] + siz[v] // 倒序递推实现 (4) 式
        更新 E1 = E1 + 1 - f(siz[v], cnt - siz[v], K) - f(cnt - siz[v], siz[v], K) // 边 (v, fa[v]) 属于 E_S 的概率

// 计算 S 中最远点对距离的期望值 E2:
E2 = 0
枚举 C 中的点 r:
    从 r 出发进行广度优先遍历，求出 r 到 C 中所有点 v 的距离 d[r][v]

枚举 C 中的点 a:
    枚举 C 中的点 b，要求 b > a:
        F = 0
        枚举 C 中的点 v，要求 v 不等于 a 或 b:
            if 三元组 (d[a][v], -min(a, v), -max(a, v)) 和三元组 (d[b][v], -min(b, v), -max(b, v)) 字典序均小于三元组 (d[a][b], -min(a, b), -max(a, b)):
                更新 F = F + 1
		更新 E2 = E2 + d[a][b] * K * (K - 1) / cnt / (cnt - 1) * f(F, cnt - F - 2, K - 2); // (a, b) 为最远点对的概率
        
返回答案 2*E1-E2
```
