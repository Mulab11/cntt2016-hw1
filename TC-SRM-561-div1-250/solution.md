# TopCoder SRM 561 ICPCBalloons 题解

作者：钟知闲

关键字：枚举 贪心

---

## 题目简述

一场比赛有 $m$ 道题，编号为 $0$ 到 $m-1$，其中第 $i$ 题最多有 $\mathrm{maxAccepted}[i]$ 个队伍通过。有 $n$ 种颜色互不相同的气球，编号为 $0$ 到 $n-1$，第 $i$ 种气球的个数为 $\mathrm{balloonCount}[i]$，大小为 $\mathrm{balloonSize}[i]$（气球只有 `M` 和 `L` 两种大小，同种颜色气球大小相同）。现在要给通过每道题的队伍发气球，具体地，对于每道题，都要给通过这道题的每个队伍各发一个气球，要求同一题发的所有气球颜色和大小相同，不同的题发的气球颜色不同。

给定长度为 $n$ 的数组 $\mathrm{balloonCount}$，$\mathrm{balloonSize}$ 及长度为 $m$ 的数组 $\mathrm{maxAccepted}$，求至少要将多少个气球重新染色（气球可以染成任意颜色，染色后大小不变）才能保证气球足够发给通过每道题的队伍。如果无解，返回 $-1$。

$1\le n\le 50$，$1\le m\le 15$，$1\le\mathrm{balloonCount}[i]\le 100$，$1\le\mathrm{maxAccepted}[i]\le 100$。

## 题解

如果确定哪些气球要染成哪些颜色，使得存在一种分配气球的方案，比较困难。我们需要一种新的思路。

不妨考虑先确定每道题对应的气球种类。假设对于每题 $i$，已经确定了该题对应的气球是第 $t_i$ 种（**注意 $t_i$ 可能不是一开始 $n$ 种气球颜色之一，因为可以染色，故 $t_i$ 可能不小于 $n$，当 $i\ge n$ 时 $\mathrm{balloonCount}[i]=0$，$\mathrm{balloonSize}[i]$ 可以任意**），那么至少要重新染色多少个气球，才能使得对于每道题 $i$，第 $t_i$ 种气球的个数不少于 $\mathrm{maxAccepted}[i]$ 呢？

记 $A_i=\mathrm{maxAccepted}[i]$，$C_i=\mathrm{balloonCount}[i]$，不难发现，如果出现这两种情况之一
\begin{equation}
\sum_{\begin{array}{c}0\le i<n \\ \mathrm{balloonSize}[t_i]=\mathrm{M}\end{array}}A_i>\sum_{\begin{array}{c}i\ge 0 \\ \mathrm{balloonSize}[i]=\mathrm{M}\end{array}}C_i
\label{OutOfRangeM}
\end{equation}

或

\begin{equation}
\sum_{\begin{array}{c}0\le i<n \\ \mathrm{balloonSize}[t_i]=\mathrm{L}\end{array}}A_i>\sum_{\begin{array}{c}i\ge 0 \\ \mathrm{balloonSize}[i]=\mathrm{L}\end{array}}C_i
\label{OutOfRangeL}
\end{equation}

那么一定无解，这是因为如果 \eqref{OutOfRangeM} 成立， `M` 气球将不够用；如果 \eqref{OutOfRangeL} 成立， `L` 气球将不够用。

如果 \eqref{OutOfRangeM} 和 \eqref{OutOfRangeL} 都不成立，那么总能通过给
\begin{equation}
\sum_{i=0}^{n-1}\max\{A_i-C_{t_i},0\}
\label{MinPaint}
\end{equation}
个气球染色使得气球够用**（并且不存在染色气球个数更少的方案，因为至少要将 $\max\{A_i-C_{t_i},0\}$ 个气球染成 $t_i$ 的颜色才能使题 $i$ 的气球够用）**，策略如下：

> * 对于每道题 $i$，先将 $\min\{A_i,C_{t_i}\}$ 个 $t_i$ 气球分配给题 $i$；

> * 分配完以后，所有满足 $A_i>C_{t_i}$ 的题 $i$ 还缺 $A_i-C_{t_i}$ 个气球，将与 $\mathrm{balloonSize}[i]$ 大小相同的这么多数量的未分配气球重新染色分配给题 $i$。

所以，如果已经确定了每题对应的气球种类 $t_i$，那么很容易判断是否有解（式 \eqref{OutOfRangeM}\eqref{OutOfRangeL}），也很容易算出最少重新染色多少个气球（式 \eqref{MinPaint}）。然而枚举所有的 $t_i$ 效率太低，有没有什么更好的办法呢？

首先观察式 \eqref{OutOfRangeM} 和 \eqref{OutOfRangeL} 可以发现，有解与否只和每题对应气球的大小 $\mathrm{balloonSize}[t_i]$ 有关，我们可以枚举每题的气球大小 $\mathrm{balloonSize}[t_i]$ 是 `M` 还是 `L`，枚举量为 $2^m\le 2^{15}$，是可以接受的。

如果已经确定了每题对应的气球大小，下一步怎么做？把题目和气球按 `M` 和 `L` 分成两组，每一组的每题 $i$ 匹配一种气球 $t_i$，要求同一组的题目 $t_i$ 互不相同，最小化 \eqref{MinPaint}。`M` 和 `L` 两组是互不影响的，可以分开匹配。问题在于：对于每一组，如何匹配才能使得 \eqref{MinPaint} 最小？

假设 `M` 大小的气球有 $n$ 个，按个数从大到小排序为 $C_1\ge C_2\ge ...\ge C_n$，选用 `M` 大小的气球的题目有 $m$ 道，按通过数从大到小排序为 $A_1\ge A_2\ge...\ge A_m$，则可以使用贪心算法来匹配：第 $1$ 题对应第 $1$ 种气球，第 $2$ 题对应第 $2$ 种气球，……，第 $m$ 题对应第 $m$ 种气球。用 $t_i$ 表示第 $i$ 题对应的气球种类编号，则该贪心算法可以描述为
$$\forall i=0,1,...,m-1,t_i=i$$
正确性不难证明：最优匹配中，如果存在 $k$ 使得 $t_k\ne k$，取最小的这样一个 $k$，那么 $t_k>k$（因为 $\forall i=0,1,...,k-1,t_i=i$），如果第 $k$ 种气球未被别的题使用，那么将 $t_k$ 改成 $k$，则 $A_k-C_k\le A_k-C_{t_k}$，比原来更优；如果第 $k$ 种气球已被另一题 $k'>k$ 使用，即 $t_{k'}=k$，那么交换 $t_k$ 和 $t_{k'}$，则
\begin{equation}
\max\{A_k-C_k,0\}+\max\{A_{k'}-C_{t_k},0\}\\ \le \max\{A_k-C_{t_k},0\}+\max\{A_{k'}-C_k,0\}
\label{Swap}
\end{equation}
比原来更优。

关于 \eqref{Swap} 的证明：记 $a=A_k-C_k$，$b=A_{k'}-C_k$，$l=C_k-C_{t_k}$，则 $a\ge b$，$l\ge 0$，因为
$$\max\{x+l,0\}-\max\{x,0\}=\begin{cases}0,&x<-l,\\x+l,&-l\le x<0\\l,&x\ge 0\end{cases}$$
是一个关于 $x$ 不降的函数，所以 
$$\max\{a+l,0\}-\max\{a,0\}\ge\max\{b+l,0\}-\max\{b,0\}$$
于是 \eqref{Swap} 得证。

这样，我们就得到了一种算法：枚举每题对应气球大小，贪心确定每题对应气球种类。伪代码如下：

```
记 M 大小的每种气球个数从大到小排序后前 m 个为 M[0], M[1], M[2], ..., M[m-1]，L 大小的每种气球个数从大到小排序后前 m 个为 L[0], L[1], L[2], ..., L[m-1]，不足 m 个则后面补 0
将 maxAccepted[0], ..., maxAccepted[m-1] 从大到小排序

ans = Infinity
// i: 已确定的题数
// M_cnt, L_cnt: 已分配M和L气球种数
// M_rest, L_rest: 剩余M和L气球总个数
// cost: 已重新染色的气球数
dfs(i, M_cnt, L_cnt, M_rest, L_rest, cost):
    if i = m:
        if cost < ans: 更新 ans = cost // 更新答案
    else:
        // 枚举题 i 的气球颜色，用个数最多的一种气球来匹配
        // 要求个数不能超过总数
        if M_rest >= maxAccepted[i]:
            dfs(i + 1, M_cnt + 1, L_cnt, M_rest - maxAccepted[i], L_rest, cost + max(maxAccepted[i] - M[M_cnt], 0)
        if L_rest >= maxAccepted[i]:
            dfs(i + 1, M_cnt, L_cnt + 1, M_rest, L_rest - maxAccepted[i], cost + max(maxAccepted[i] - L[L_cnt], 0)
            
调用 dfs(0, 0, 0, Ms, Ls, 0)，其中 Ms 和 Ls 分别为 M 和 L 气球总个数，则 ans 为答案（若 ans = Infinity，答案为 -1）
```

该算法复杂度 $O(2^m)$，可以通过本题。
