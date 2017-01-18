#line 2 "CosmicBlocks.cpp"
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#define cl(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define oo 0x3f3f3f3f
#define maxn 10
typedef long long ll;
using namespace std;
int n, ans, L, R, a[maxn]; //  n种颜色，第i种颜色有a[i]个，L/R为拆除方案数的上下界
int num[maxn], c[maxn][maxn]; // num[l]为第l层的颜色种数，具体颜色存在c[l][*]里
bool used[maxn]; // 搜颜色分配情况时的辅助数组
// 以下是网络流部分-------------------
int s, t, g[maxn], cur[maxn], ei;
struct edge {
	int t, c, nxt;
}e[maxn * maxn * 2];
void ae(int a, int b, int c) {
	e[++ei].t = b; e[ei].nxt = g[a]; g[a] = ei; e[ei].c = c;
	e[++ei].t = a; e[ei].nxt = g[b]; g[b] = ei; e[ei].c = 0;
}
int q[maxn], qh, qt, dis[maxn];
bool bfs() {
	memset(dis, -1, sizeof(dis));
	q[qh = qt = 1] = s; dis[s] = 0; int x;
	while (qh <= qt) {
		x = q[qh ++]; 
		for (int i = g[x]; i; i = e[i].nxt)
			if (e[i].c && dis[e[i].t] == -1) {
				dis[e[i].t] = dis[x] + 1;
				q[++ qt] = e[i].t;
			}
	}
	return dis[t] != -1;
}
int dfs(int x, int f) {
	if (x == t) return f;
	int d, u = 0;
	for (int &i = cur[x]; i; i = e[i].nxt)
		if (e[i].c && dis[e[i].t] == dis[x] + 1) {
			d = dfs(e[i].t, min(e[i].c, f - u));
			e[i].c -= d; e[i ^ 1].c += d; u += d;
			if (u == f) return f;
		}
	if (!u) dis[x] = -42;
	return u;
}
int dinic() {
	int ret = 0;
	while (bfs()) {
		memcpy(cur, g, sizeof(cur));
		ret += dfs(s, oo);
	}
	return ret;
}
//------------------------------------
int ecnt[maxn], edges[maxn][1 << 9]; // 记录每两层之间，所有合法的连边方案
bool con[maxn][maxn]; // 所有层之间连的边形成了一个DAG，con存它的传递闭包
int f[1 << 6]; // 计算DAG拓扑排序方案数的dp数组，f[s]表示已经使用了s内的点，这些点的拓扑排序方案数
void calc(int h) { // 对于一种颜色分配到层的方案，枚举它的所有层与层之间连边情况，对答案做相应贡献
	int last = oo, sum;
	for (int i = 1; i <= h; ++i) {
		sum = 0;
		for (int j = 1; j <= num[i]; ++j) sum += a[c[i][j]];
		if (sum > last) return; // 验证下面的层是否不小于上面的层
		last = sum;
	}
	int means = 1; // 可行的连边方案总数
	for (int l = 1; l < h; ++l) { // 由于层与层之间是相互独立的，对于每一层，枚举它的连边情况，并求出其中合法的那些
		int tot = num[l] * num[l + 1], tcnt[maxn]; 
		ecnt[l] = 0;
		sum = 0;
		for (int sta = 0; sta < (1 << tot); ++sta) { // 枚举各种边的存在性
			// 验证合法性的办法是：首先，每条边至少有一条，扣除这些基础边之后，不能有颜色的个数变为负的。然后，对于剩下的积木，做一个网络流来验证是否能够仅通过这几种边，让所有上一层的积木都能安放到某个下一层的积木上去
			cl(g); ei = 1; s = num[l] + num[l + 1] + 1; t = s + 1;
			cl(tcnt); // tcnt用来存每种颜色的积木在基础边里使用掉了多少
			for (int i = 1; i <= num[l]; ++i)
				for (int j = 1; j <= num[l + 1]; ++j)
					if (sta & (1 << ((i - 1) * num[l + 1] + j - 1)))
						ae(num[l] + j, i, oo), ++tcnt[c[l][i]], ++tcnt[c[l + 1][j]]; 
			bool flag = 0;
			for (int i = 1; i <= n; ++i)
				if (tcnt[i] > a[i]) { // 若积木个数不足以形成基础边，该连边方案不合法
					flag = 1; break;
				}
			if (flag) continue;
			int full = 0;
			for (int i = 1; i <= num[l + 1]; ++i)
				ae(s, num[l] + i, a[c[l + 1][i]] - tcnt[c[l + 1][i]]), full += a[c[l + 1][i]] - tcnt[c[l + 1][i]];
			for (int i = 1; i <= num[l]; ++i)
				ae(i, t, a[c[l][i]] - tcnt[c[l][i]]);
			int flow = dinic();
			if (flow == full) // 表示所有上一层的积木都有地方放 
				edges[l][++ecnt[l]] = sta;
		}
		means *= ecnt[l]; // 层间相互独立，合法连边方案数相乘
	}
	for (int s = 0; s < means; ++s) { // 枚举整体的合法连边方案。
		int tmp = s; cl(f); cl(con); f[0] = 1; 
		for (int l = 1; l < h; ++l) {
			int sta = edges[l][tmp % ecnt[l] + 1];
			for (int i = 1; i <= num[l]; ++i)
				for (int j = 1; j <= num[l + 1]; ++j)
					if (sta & (1 << ((i - 1) * num[l + 1] + j - 1))) 
						con[c[l + 1][j]][c[l][i]] = 1; // 连边
			tmp /= ecnt[l];
		}
		for (int k = 1; k <= n; ++k)
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= n; ++j)
					if (i != j && j != k && i != k)
						con[i][j] |= con[i][k] & con[k][j]; // 传递闭包
		for (int sta = 0; sta < (1 << n); ++sta) { // dp计算拓扑排序方案数
			if (! f[sta]) continue;
			for (int i = 0; i < n; ++i)
				if (! (sta & (1 << i))) { // 对于一个不在当前集合中的点i，若所有能到达它的点都在当前集合中，那么可以把它加入当前集合
					bool flag = 1;
					for (int j = 1; j <= n; ++j)
						if (j != i + 1 && con[j][i + 1] && ! (sta & (1 << (j - 1)))) {
							flag = 0; break;
						}
					if (flag) f[sta | (1 << i)] += f[sta];
				}
		}
		if (f[(1 << n) - 1] >= L && f[(1 << n) - 1] <= R) ++ans; // f[(1 << n) - 1]就是这个DAG的拓扑排序方案数，即拆除序列的种数
	}
}
void dfs(int h) { // 枚举颜色在层间的分配方案
	int tmp[maxn], cnt = 0;
	for (int i = 1; i <= n; ++i) 
		if (! used[i]) 
			tmp[++cnt] = i;
	if (!cnt) { // 颜色已经用完了
		calc(h - 1);
		return;
	}
	for (int sta = 1; sta < (1 << cnt); ++sta) { // 枚举当前层用的颜色集合
		num[h] = 0;
		for (int i = 0; i < cnt; ++i)
			if (sta & (1 << i)) {
				c[h][++num[h]] = tmp[i + 1];
				used[tmp[i + 1]] = 1;
			}
		dfs(h + 1);
		for (int i = 0; i < cnt; ++i)
			if (sta & (1 << i))
				used[tmp[i + 1]] = 0;
	}
}
class CosmicBlocks {
	public:
		int getNumOrders(vector <int> col, int Llim, int Rlim) {
			n = col.size(); L = Llim; R = Rlim; ans = 0;
			for (int i = 0; i < n; ++ i) a[i + 1] = col[i];
			cl(used); cl(num);
			dfs(1);
			return ans;
		}
};

