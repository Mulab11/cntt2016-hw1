#YamanoteLine

作者：沈睿

关键词：差分约束，图论，函数相关

##题目简述

给你一个有$$n$$个车站的环形铁路，相邻两个车站之间的距离为正整数。再给你一些如以下形式的约束条件：

$$1.$$环上顺时针方向由S到T的一段距离大于一个给定的值L

$$2.$$环上顺时针方向由S到T的一段距离小于一个给定的值L

最后询问环形铁路的总长度共有几种不同的合法取值。（无穷取值方案输出$$-1$$）

数据范围：$$1\le n\le 50,1\le $$每种约束的个数$$\le 50$$

## 差分约束模型

我们不妨考虑按$$0-n$$顺序的前缀和，记作数组$$D$$。于是$$D[i]$$就表示环上按顺时针方向从$$0$$号车站到$$i$$号车站的距离总和。为了后面方便的推导，我们再假设环的总长度（也就是答案）为X，于是便可得到如下的不等式约束**（箭头后方是差分约束的标准形式）**：

由于相邻车站之间的距离是正整数，所以有：
$$
D[i]+1\le D[i+1] \rightarrow D[i]-D[i+1]\le -1
$$

不难发现$$D[0]=0,D[n]=X$$，所以我们又可以得到以下式子：
$$
D[0]+X=D[n] \rightarrow D[0]-D[n]<=-X,D[n]-D[0]<=X
$$


对于题目给的第一种条件，我们根据按照顺时针方向是否跨越过0号车站，分类讨论一下，也不难建立不等式关系：
$$
1.S<T,D[T]-D[S]\ge L \rightarrow D[S]-D[T]\le -L
$$

$$
2.S>T,X+D[T]-D[S]\ge L \rightarrow D[S]-D[T]\le X-L
$$

同理对于第二种条件，也可以获得以下不等式关系：
$$
1.S<T,D[T]-D[S]\le L \rightarrow D[T]-D[S]\le L
$$

$$
2.S>T,X+D[T]-D[S]\le L \rightarrow D[T]-D[S]\le -X+L
$$

这是一个经典的**差分约束**模型。所有不等式约束可以转化为图论中最短路的模型，如果出现**负环**则说明该不等式组无解。

在这道题中，我们由于设了一个未知数$$X$$，所以似乎无法直接求解。但是我们不难发现给定一个答案$$X$$，我们可以在转化的图上跑$$bellman-ford$$或者$$spfa$$来判断是否存在负环，从而判断该答案是否可行。但显然答案的范围可能很大，枚举验证的方法效率不高，我们不妨采用以下两种思路来解决问题。

##算法一

这也是$$TC$$上的题解给出的算法。

首先，不难发现最终的答案其实是在一个区间范围之内。于是我们如果设计出一个算法来判断一个不合法的X是低于下界还是高于上界，便可以进行二分求解出最终答案的区间。

对于一个不可行的答案，我们必然是可以在转化的图中找到一个负环的。于是我们不妨在求最短路的时候对于每一个值都记录下$$X$$的系数，那当我们找到一个负环的时候，我们也可以得到该负环数值中的X的系数。如果$$X$$的系数是正的话，那么显然我们只有将$$X$$调大，才能使该负环变成非负环，所以该X的值是低于答案的下界。同理，如果$$X$$的系数为负，可以得到该$$X$$高于答案的上界。值得注意的是，**如果存在一个负环$$X$$的系数为$$0$$便会无解**。

至此，我们可以使用**二分**算法，对上界和下界分别进行二分便可获得答案区间。时间复杂度为$$O(nmlogn)$$。

##代码一$$(from$$ $$topcoder's$$ $$std)$$

```C++
#include <vector>
#include <iostream>

using namespace std;

#define FOR(i,a,b) for (int i = a; i <= b; i++)
#define REP(i,a,b) for (int i = a; i < b; i++)
#define MP make_pair

typedef pair < long long, long long > PLL;

using namespace std;

long long INF = 100LL * 1000000000;

class YamanoteLine {

public:
	PLL sumPLL (PLL a, PLL b) {
        return  MP (a.first + b.first, a.second + b.second);
	}

	PLL d[111];
	vector < pair <int, PLL> > adj[111];
	//there is an edge from adj[i][k].first to i with the weight is adj[i][k].second

	pair <bool, long long> BellmanFord( long long length, int n, vector <int> s1, vector <int> t1, vector <int> l1, vector <int> s2, vector <int> t2, vector <int> l2) {

		//building the graph with the value length
		FOR (i, 0, n) adj[i].clear();

		FOR (i, 0, n - 1) adj[i].push_back(MP( i + 1, MP(-1, 0) ) );
		adj[n].push_back(MP(0, MP(length, 1)));
		adj[0].push_back(MP(n, MP(-length, -1)));

		REP (i, 0, (t1.size())) {
			if (s1[i] < t1[i]) adj[s1[i]].push_back(MP(t1[i], MP(-l1[i], 0)));
				else adj[s1[i]].push_back(MP(t1[i], MP(length - l1[i], 1)));
			}


		REP (i, 0, (t2.size()))
			if (s2[i] < t2[i]) adj[t2[i]].push_back(MP(s2[i], MP(l2[i], 0) ));
				else adj[t2[i]].push_back(MP(s2[i], MP( - length + l2[i], -1) ));

		FOR (i, 0, n) d[i] = MP(INF, 0);
		d[0] = MP(0, 0);

		PLL tmp, impt;
		bool update = false;

		//repeat n * n times instead of n times
		FOR (rep, 1, n * n) {
			update = false;
			FOR (i, 0, n)
				REP (k, 0, (adj[i].size()))
				if (d[adj[i][k].first].first < INF){
					tmp = sumPLL(adj[i][k].second, d[adj[i][k].first]);

					if (tmp.first < d[i].first) {
						d[i] = tmp;
						if (d[i].first < 0) return MP (false, d[i].second);
						update = true;
						//store the last value that you used to update
						impt = tmp;
					}
				}
			}


		if (!update) return MP(true, 0);
		else return MP(false, impt.second);
	}

	long long howMany(int n, vector <int> s1, vector <int> t1, vector <int> l1, vector <int> s2, vector <int> t2, vector <int> l2) {
		long long ub, lb, L, R;
		ub = INF; lb = -1;

		//finding the upper bound
		L = n; R = INF;
		while (L <= R) {
			long long M = (L + R) / 2;
			pair <bool, long long> res = BellmanFord(M, n, s1, t1, l1, s2, t2, l2);

			if (res.first || res.second > 0) {
				if (res.first) ub = M;
				L = M + 1;
			}
			else R = M - 1;
		}

		////finding the lower bound
		L = n; R = INF;
		while (L <= R) {
			long long M = (L + R) / 2;
			pair <bool, long long> res = BellmanFord(M, n, s1, t1, l1, s2, t2, l2);

			if (res.first || res.second < 0) {
				if (res.first) lb = M;
                R = M - 1;
			}
			else L = M + 1;
		}

        if (lb >= n && ub == INF) return -1;
		if (lb == -1) return 0;
			else return ub - lb + 1;

	}
};
```

##算法二

$$tc$$的提交界面上$$matthew99$$和$$xudyh$$使用的是该算法。
由于X的存在，我们不妨可以将每条路径的值都表示成$$AX+B$$的**一次函数**的形式。回顾一开始的建图过程，可以发现每条边中$$A$$的系数只有三种取值$$1,0,-1$$，所以路径长度$$AX+B$$的形式中$$A$$的取值不会超过$$O(m)$$个。那我们求出便可求出每两个点之间$$X$$系数为$$A$$的最短路。我们用$$f_{i,j,k}$$来表示$$i$$到$$j$$，$$X$$的系数为$$k$$的最小的$$B$$值，这是可以进行如下的$$floyd$$转移得到的：
$$
f_{i,j,a+b}=min\{f_{i,k,a}+f_{k,j,b}\}
$$

那么$$f_{i,i,s}$$里存的便是经过i号节点的系数为x的最小环的$$B$$值。不难发现我们只要让这样所有的环都**非负**即可满足所有约束，而且求得的环本身已经是最小值，约束已经达到最强，所以将所有约束整合便可得到最终的答案区间。

那我们不妨枚举所有的$$i$$和$$s$$，便可得到如下约束：
$$
s>0,X\le \frac{-f_{i,i,s}}{s}//s<0,X\ge \frac{-f_{i,i,s}}{s}
$$

分别对所有的约束上界取$$min$$，下界取$$max$$即可获得最终的答案区间。
**注意**，如果存在一个$$i$$使得$$f_{i,i,0}<0$$那么，最终答案无解。

该算法实现的复杂度为$$O(n^{3}m^{2})$$。

##代码二$$(from$$ $$SR)$$

```C++
#include<bits/stdc++.h>
#define FT first
#define SC second
#define PB push_back
#define MP make_pair
#define REP(i, l, r) for(int i = (l); i <= (r); i++)
#define PER(i, r, l) for(int i = (r); i >= (l); i--)
#define FOR(i, n) for(int i = 0; i < (n); i++)
#define ROF(i, n) for(int i = (n) - 1; i >= 0; i--)
#define VEP(i, x) for(int i = 0; i < x.size(); i++)
#define RUN(i, x) for(__typeof((x).begin()) i = (x).begin(); i != (x).end(); ++i)
#define DFOR(i, x, y) for(int i = hd[x], y = e[i].to; i; i = e[i].nxt, y = e[i].to)
#define MEM(a, b) memset(a, b, sizeof(a))
#define rint read<int>()
#define rll read<LL>()

using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PI;
const LL inf = 0x3f3f3f3f3f3f3f3fll;
const int MOD = 1000000007;

template <typename tn> inline void cmax(tn &a, tn b){ if (a < b) a = b; }
template <typename tn> inline void cmin(tn &a, tn b){ if (a > b) a = b; }
  
const int o = 51, N = 103;

LL f[o + 2][o + 2][N + 2];
void add(int x, int y, int p, int q){ cmin(f[x][y][o + q], (LL)p); }
class YamanoteLine  
{  
        public:  
        long long howMany(int n, vector <int> s1, vector <int> t1, vector <int> l1, vector <int> s2, vector <int> t2, vector <int> l2)  
        {  
			MEM(f, 0x3f);
        	REP(i, 0, n) f[i][i][o] = 0;
        	
			REP(i, 0, n - 1) add(i + 1, i, -1, 0); // d[i] + 1 <= d[i + 1]
			add(0, n, 0, 1), add(n, 0, 0, -1); // d[0] + w == d[n]
			
			VEP(i, s1) add(t1[i], s1[i], -l1[i], int(s1[i] > t1[i]));// d[t] - d[s] >= l | w + d[t] - d[s] >= l
			VEP(i, s2) add(s2[i], t2[i], l2[i], -int(s2[i] > t2[i]));// d[t] - d[s] <= l | w + d[t] - d[s] <= l
			
			//floyd
			REP(k, 0, n) REP(i, 0, n) REP(x, -o, o) if (f[i][k][o + x] < inf) 
					     REP(j, 0, n) REP(y, max(-o, -o - x), min(o, o - x)) if (f[k][j][o + y] < inf)
					     cmin(f[i][j][o + x + y], f[i][k][o + x] + f[k][j][o + y]);
			
			LL l = n, r = inf;
			
			//getans
			REP(i, 0, n) REP(j, -o, o){
				if (j == 0) if (f[i][i][o + j] < 0) return 0; else; else
				if (f[i][i][o + j] < inf)
					if (j > 0) cmax(l, (-f[i][i][o + j] - 1) / j + 1); 
					else cmin(r, f[i][i][o + j] / (-j));
			}
			return (r < l ? 0 : (r == inf ? -1 : r - l + 1));
        }  
};  
```
