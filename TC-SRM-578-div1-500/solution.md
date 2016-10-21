# WolfInZooDivOne
作者：叶珈宁

关键词：计数 DP 前缀和优化
## 题目简述
有一个长度为$$n$$的序列，你需要给每个位置填上0或者1。现在给出$$m$$个形如$$(l_i,r_i)$$的限制，表示区间$$[l_i,r_i]$$的和不能超过2。

问有多少种合法的序列。

$$n,m\leq 300$$.

## 算法
可以设计一个DP，用$$dp_{i,j}$$表示，最后一个1在位置$$i$$，倒数第二个1的位置在$$j$$的合法方案总数。

设$$p(i)=\min\limits_{r_k\geq i}l_k$$，则有$$dp_{i,j}=\sum\limits_{k<\min(j,p(i))}dp_{j,k}$$。

从左往右扫，可以用一个multiset维护所有区间的左端点，然后动态删去$$r_k=i-1$$的那些区间，multiset里的最小值就是$$p(i)$$。

因为转移的时候要询问前缀和，所以在DP做完一个$$i$$的时候，做一遍前缀和来优化复杂度，DP的复杂度就可以做到$$\mathcal{O}(n^2)$$。

```
For(i,1,n){
		int t=*Set.begin();
		f[i][0]=1;
		rep(j,1,t)inc(f[i][j],f[j][j-1]);//临界点左边的情况
		rep(j,t,i)inc(f[i][j],f[j][t-1]);//临界点右边的情况
		rep(j,1,i)inc(f[i][j],f[i][j-1]);//前缀和优化
		inc(an,f[i][i-1]);//统计答案
		for(int x:li[i])Set.erase(Set.find(x));//删除右端点为i的线段
	}
```

而处理$$p(i)$$的复杂度可以做到$$\mathcal{O}(m\log n)$$，最后的总复杂度是$$\mathcal{O}(n^2+m\log n)$$。