#line 2 "BoardPainting.cpp"
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
#define maxn 3010
typedef long long ll;
using namespace std;
/*
   把矩形分成横竖两类，画一个横矩形，会产生两条和竖矩形/边界之间的交界边。画竖矩形同理。 于是，只要计算出这样交界边的个数，就能知道矩形的个数。
   把点分成横竖两类，相邻的点如果横竖情况不同，就产生一条交界边，上方有障碍的点若属于竖矩形，也产生一条交界边。如此，跑一个最小割即可。
*/
const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0}; // 四个相邻方向
int s, t, n, m, cur[maxn], g[maxn], ei, dis[maxn], q[maxn], qh, qt; // 以下为网络流部分
struct edge {
	int t, c, nxt;
}e[maxn * 16];
void init() {
	memset(g, 0, sizeof(g)); ei = 1;
}
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
			d = dfs(e[i].t, min(f - u, e[i].c));
			e[i].c -= d; e[i ^ 1].c += d; u += d;
			if (u == f) return u;
		}
	if (! u) dis[x] = -42;
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
class BoardPainting {
	public:
		int minimalSteps(vector <string> tar) {
			init();
			n = tar.size(); m = tar[0].size();
			s = n * m + 1; t = s + 1;
			int cnth, cntv, x, y;
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < m; ++j)
					if (tar[i][j] == '#') { // 一个需要涂色的点
						cnth = cntv = 0;
						if (j == 0 || tar[i][j - 1] == '.') ++cnth; // 左端是障碍，它若作为横点，产生一个边界
						if (j == m - 1 || tar[i][j + 1] == '.') ++cnth; // 右端是障碍，它若作为横点，产生一个边界
						if (i == 0 || tar[i - 1][j] == '.') ++cntv; // 上端是障碍，它若作为竖点，产生一个边界
						if (i == n - 1 || tar[i + 1][j] == '.') ++cntv; // 上端是障碍，它若作为竖点，产生一个边界
						ae(s, i * m + j + 1, cnth);
						ae(i * m + j + 1, t, cntv);
						for (int d = 0; d < 4; ++d) {
							x = i + dx[d]; y = j + dy[d];
							if (x >= 0 && x < n && y >= 0 && y < m && tar[x][y] == '#')
								ae(i * m + j + 1, x * m + y + 1, 1); // 与相邻的点若横竖情况不同，产生一个边界
						}
					}
			return dinic() / 2; // 矩形个数 = 边界个数 / 2
		}
};
