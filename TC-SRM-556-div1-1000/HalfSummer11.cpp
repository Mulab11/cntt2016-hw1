#line 2 "OldBridges.cpp"
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
#define maxn 60
typedef long long ll;
using namespace std;
// 以下为网络流部分
int g[maxn], ei, cur[maxn];
struct edge {
	int t, c, nxt;
}e[maxn * maxn * 4];
int n, s, t, q[maxn], qh, qt, dis[maxn];
void ae(int a, int b, int c) {
	e[++ei].t = b; e[ei].nxt = g[a]; g[a] = ei; e[ei].c = c;
	e[++ei].t = a; e[ei].nxt = g[b]; g[b] = ei; e[ei].c = 0;
}
bool bfs() {
	memset(dis, -1, sizeof(dis)); 
	q[qh = qt = 1] = s; dis[s] = 0; int x;
	while (qh <= qt) {
		x = q[qh++];
		for (int i = g[x]; i; i = e[i].nxt)
			if (e[i].c && dis[e[i].t] == -1) {
				dis[e[i].t] = dis[x] + 1;
				q[++qt] = e[i].t;
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
			u += d; e[i].c -= d; e[i ^ 1].c += d;
			if (u == f) return u;
		}
	if (!u) dis[x] = -42;
	return u;
}
int dinic() {
	int ret = 0;
	while (bfs()) {
		memcpy(cur, g, sizeof(g));
		ret += dfs(s, oo);
	}
	return ret;
}
//-------------------
bool check(vector <string> G, int a1, int a2, int an, int b1, int b2, int bn) { // 检查以a1,b1为源，a2,b2为汇，能否满流
	cl(g); ei = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j) { // 建图
			if (G[i - 1][j - 1] == 'O') 
				ae(i, j, 2), ae(j, i, 2); // 只能走两遍
			if (G[i - 1][j - 1] == 'N')
				ae(i, j, oo), ae(j, i, oo); // 不限
		}
	s = n + 1; t = s + 1;
	ae(s, a1, an * 2);
	ae(s, b1, bn * 2);
	ae(a2, t, an * 2);
	ae(b2, t, bn * 2);
	return dinic() == an * 2 + bn * 2;
}
class OldBridges {
	public:
		string isPossible(vector <string> G, int a1, int a2, int an, int b1, int b2, int bn) {
			++a1; ++a2; ++b1; ++b2; n = G.size();
			if (check(G, a1, a2, an, b1, b2, bn) && check(G, a1, a2, an, b2, b1, bn)) // 两种都能满流 等价于Alice和Bob都可以完成任务
				return "Yes";
			else
				return "No";
		}
};

