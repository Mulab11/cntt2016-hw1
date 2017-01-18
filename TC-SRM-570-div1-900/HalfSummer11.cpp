#line 2 "CurvyonRails.cpp"
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
#define clear(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define son e[i].t
#define oo 0x3f3f3f3f
#define maxn 2010
typedef long long ll;
using namespace std;
// 以下为费用流部分
int tot, s, t, n, m, g[maxn], ei, dis[maxn], pre[maxn], q[maxn], qh, qt;
bool inq[maxn];
struct edge {
	int t, c, w, nxt;
}e[maxn * 16];
void ae(int a, int b, int c, int d) {
	e[++ei].t = b; e[ei].nxt = g[a]; g[a] = ei; e[ei].c = c; e[ei].w = d;
	e[++ei].t = a; e[ei].nxt = g[b]; g[b] = ei; e[ei].c = 0; e[ei].w = -d;
}
bool spfa() {
	memset(dis, 0x3f, sizeof(dis));
	qh = qt = 0; q[qt++] = s; dis[s] = 0; inq[s] = 1; int x;
	while (qh != qt){
		x = q[qh ++]; if (qh == maxn) qh = 0; inq[x] = 0;
		for (int i = g[x]; i; i = e[i].nxt)
			if (e[i].c && dis[e[i].t] > dis[x] + e[i].w) {
				dis[e[i].t] = dis[x] + e[i].w;
				pre[e[i].t] = i;
				if (! inq[e[i].t]) {
					inq[e[i].t] = 1;
					q[qt++] = e[i].t; if (qt == maxn) qt = 0;
				}
			}
	}
	return dis[t] != oo;
}
int mincost() {
	int cost = 0, flow, mf = 0;
	while (spfa()) {
		flow = oo;
		for (int i = t; i != s; i = e[pre[i] ^ 1].t) flow = min(flow, e[pre[i]].c);
		cost += flow * dis[t]; mf += flow;
		for (int i = t; i != s; i = e[pre[i] ^ 1].t) 
			e[pre[i]].c -= flow, e[pre[i] ^ 1].c += flow;
	}
	if (mf != tot) return -1;
	return cost;
}
class CurvyonRails {
	public:
		int getmin(vector <string> field) {
			memset(g, 0, sizeof(g)); ei = 1;
			n = field.size(); m = field[0].size();
			tot = 0;
			s = 2 * n * m + 1; t = s + 1;
			int v, h, w;
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < m; ++j)
					if (field[i][j] != 'w') {
						++ tot;
						v = i * m + j + 1; h = v + n * m;
					if ((i + j) % 2) { // 将棋盘黑白染色，黑色的点放在左边，白色的点放在右边。每个点又拆成横h竖v两种。每个黑色的点通过媒介v和h分别向竖直/水平方向的相邻白点的h与v连边。
							ae(s, v, 1, 0); ae(s, h, 1, 0); // 默认一条边是竖的，一条边是横的，形成curve
							if (j > 0 && field[i][j - 1] != 'w') ae(h, n * m + i * m + j - 1 + 1, 1, 0); // 向四周白点连边
							if (j < m - 1 && field[i][j + 1] != 'w') ae(h, n * m + i * m + j + 1 + 1, 1, 0);
							if (i > 0 && field[i - 1][j] != 'w') ae(v, (i - 1) * m + j + 1, 1, 0);
							if (i < n - 1 && field[i + 1][j] != 'w') ae(v, (i + 1) * m + j + 1, 1, 0);
						} else {
							ae(v, t, 1, 0); ae(h, t, 1, 0); // 白点，同样默认一横一竖
						}
						w = (field[i][j] == 'C'); 
						ae(v, h, 1, w); ae(h, v, 1, w); // 可以在v/h之间调整流量，变成一横一竖，此时若该点是C，就需要付出1的代价
					}
			return mincost();
		}
};
