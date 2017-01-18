#line 2 "DeerInZooDivOne.cpp"
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
#include<queue>
#define cl(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define oo 0x3f3f3f3f
#define maxn 60 
typedef long long ll;
using namespace std;
/* 对于两棵有根树，要从中取出最大的以各自的树根为根的同构子树，可以用km算法来做：对于两个树根的每个儿子，两两之间求出最大同构子树的大小，再求一个最大权匹配。
   对于题目中的情况，将无根树转为有根树，答案选出的两个连通块中，一定能找到一个连通块，将它深度最浅的点u和父亲断开后，两个连通块恰好位于断开后原树的不同部分。
   枚举u，断开它和父亲，再从父亲所在的树中枚举一个和它对应的点v，转化成之前的问题求解。
*/
bool del[maxn]; // del[i]标记第i条边是否被断开
int n, g[maxn], ei, pree[maxn]; // n是点数，g[], ei是边表，pree[i]是i点指向父亲边的编号。
struct edge{ 
	int t, nxt;
}e[maxn * 2];
void ae(int a, int b) {
	e[++ei].t = b; e[ei].nxt = g[a]; g[a] = ei;
}
void dfs1(int x, int fa) { // 把给出的无根树变成有根树
	for (int i = g[x]; i; i = e[i].nxt)
		if (e[i].t != fa) {
			pree[e[i].t] = (i ^ 1);
			dfs1(e[i].t, x);
		}
}
bool in[maxn];
void mark(int x, int fa) { // 标记x子树中的所有点
	in[x] = 1;
	for (int i = g[x]; i; i = e[i].nxt)
		if (e[i].t != fa)
			mark(e[i].t, x);
}
struct graph { // km
	queue<int> q;
	int G[maxn][maxn];
	int link[maxn], pre[maxn], ans[maxn];
	int nx, ny, m, n, u, v, w, wx[maxn], wy[maxn], slk[maxn];
	bool vx[maxn], vy[maxn], del[maxn];
	void aug(int y) {
		if (ans[pre[y]]) aug(ans[pre[y]]);
		link[y] = pre[y];
		ans[link[y]] = y;
	}
	void bfs(int s) {
		while (! q.empty()) q.pop();
		int x; q.push(s);
		for (int i = 1; i <= n; ++i) slk[i] = oo;
		for (int i = 1; i <= n; ++i) vx[i] = vy[i] = 0;
		while (1) {
			while (!q.empty()) {
				x = q.front(); q.pop(); vx[x] = 1;
				for (int y = 1; y <= n; ++y) {
					if (!vy[y]) {
						int t = wx[x] + wy[y] - G[x][y];
						if (!t) {
							pre[y] = x; vy[y] = 1;
							if (!link[y]) {aug(y); return;}
							q.push(link[y]);
						} else {
							if (t < slk[y])
								slk[y] = t, pre[y] = x;
						}
					}
				}
			}
			int d = oo;
			for (int i = 1; i <= n; ++i)
				if (!vy[i]) d = min(d, slk[i]);
			for (int i = 1; i <= n; ++i) {
				if (vx[i]) wx[i] -= d;
				if (vy[i]) wy[i] += d; else slk[i] -= d;
			}
			for (int i = 1; i <= n; ++i)
				if (!vy[i] && !slk[i]) {
					if (!link[i]) { aug(i); return;}
					vy[i] = 1; q.push(link[i]);
				}
		}
	}
	int km(int N) {
		n = N;
		cl(link); cl(pre); cl(ans);
		for (int i = 1; i <= n; ++i) wx[i] = -oo;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				wx[i] = max(wx[i], G[i][j]);
		for (int i = 1; i <= n; ++i) bfs(i);
		int sum = 0;
		for (int i = 1; i <= n; ++i)
			sum += G[i][ans[i]];
		return sum;
	}
}gra;
int calc(int u, int uf, int v, int vf) { // 计算u为根的树和v为根的树中，分别以u,v为根的最大同构子树大小。uf, vf是u,v在各自树上的父亲
	int su[maxn], ut = 0; // 存u的儿子
	int sv[maxn], vt = 0;
	int tg[maxn][maxn]; // tg[i][j]表示u的第i个儿子和v的第j个儿子匹配所能得到的最大同构子树大小
	for (int i = g[u]; i; i = e[i].nxt)
		if (!del[i >> 1] && e[i].t != uf)
			su[++ut] = e[i].t;
	for (int i = g[v]; i; i = e[i].nxt)
		if (!del[i >> 1] && e[i].t != vf)
			sv[++vt] = e[i].t;
	cl(tg);
	for (int i = 1; i <= ut; ++i)
		for (int j = 1; j <= vt; ++j)
			tg[i][j] = calc(su[i], u, sv[j], v); // 计算最大同构子树大小
	for (int i = 1; i <= max(ut, vt); ++i)
		for (int j = 1; j <= max(ut, vt); ++j)
			gra.G[i][j] = tg[i][j];
	int ret = 1 + gra.km(max(ut, vt)); // 答案 = 儿子配对的最大权 + 1
	return ret;
}
class DeerInZooDivOne {
	public:
		int getmax(vector <int> a, vector <int> b) {
			cl(pree); cl(g); ei = 1;
			n = a.size() + 1;
			for (int i = 0; i < n - 1; ++i) 
				ae(a[i] + 1, b[i] + 1), ae(b[i] + 1, a[i] + 1);
			dfs1(1, -1);
			int ans = 1;
			for (int u = 1; u <= n; ++u) { // 枚举一个连通块中最浅的点u
				cl(in); mark(u, e[pree[u]].t); // 标记u子树里的点
				cl(del); del[pree[u] >> 1] = 1; // 断开与父亲的边
				for (int v = 1; v <= n; ++v)
					if (!in[v])  // 枚举子树外一点v，与u对应
						ans = max(ans, calc(u, -1, v, -1));
			}
			return ans;
		}
};
