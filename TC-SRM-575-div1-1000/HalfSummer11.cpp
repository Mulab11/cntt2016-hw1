#line 2 "TheTilesDivOne.cpp"
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
#define maxn 5010
typedef long long ll;
using namespace std;
/*
   将棋盘黑白染色后，再把白色格子灰白染色。一个L形正好覆盖了三个不同颜色的方块，需要做一个类似最大匹配的东西。
   把所有的黑色格子放在中间，把灰色格子放在一侧，白色格子放在另一侧，跑最大流即可。
*/
const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0}; // 四个相邻方向
// 以下为网络流部分
int s, t, n, m, cur[maxn], g[maxn], ei, dis[maxn], q[maxn], qh, qt; 
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
	while (qh <= qt){
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
			d = dfs(e[i].t, min(f - u, e[i].c));
			e[i].c -= d; e[i ^ 1].c += d; u += d;
			if (u == f) return u;
		}
	if (!u) dis[x] = -42;
	return u;
}
int dinic() {
	int ret = 0;
	while (bfs()){
		memcpy(cur, g, sizeof(g));
		ret += dfs(s, oo);
	}
	return ret;
}
class TheTilesDivOne
{
	public:
		int find(vector <string> board) {
			init();
			n = board.size(); m = board[0].size();
			s = 2 * n * m + 1; t = s + 1;
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < m; ++j)
					if (board[i][j] == '.') {
						int x = i * m + j + 1;
						if ((i + j) % 2 == 0) { // 黑色格子
							ae(x, x + n * m, 1); // 拆成两个点，中间容量为1.
							if (i % 2 == 0) {
								if (j > 0 && board[i][j - 1] == '.') ae(x + n * m, i * m + j - 1 + 1, 1); // 与相邻的白格子连边
								if (j < m - 1 && board[i][j + 1] == '.') ae(x + n * m, i * m + j + 1 + 1, 1);
							} else {
								if (i > 0 && board[i - 1][j] == '.') ae(x + n * m, (i - 1) * m + j + 1, 1); 
								if (i < n - 1 && board[i + 1][j] == '.') ae(x + n * m, (i + 1) * m + j + 1, 1);
							}
						} else {
							if (i % 2 == 0) // 白格子
								ae(x, t, 1);
							else {
								ae(s, x, 1); // 灰格子
								for (int d = 0; d < 4; ++d) {
									int nx = i + dx[d], ny = j + dy[d];
									if (nx >= 0 && nx < n && ny >= 0 && ny < m && board[nx][ny] == '.')
										ae(x, nx * m + ny + 1, 1); // 与相邻的黑格子连边
								}
							}
						}
					}
			return dinic();
		}
};
