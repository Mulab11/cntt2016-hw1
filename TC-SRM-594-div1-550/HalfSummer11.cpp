#line 2 "FoxAndGo3.cpp"
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
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};
int s, t, g[maxn * maxn], cur[maxn * maxn], ei;
int dis[maxn * maxn], q[maxn * maxn], qh, qt;
struct edge {
	int t, c, nxt;
} e[maxn * maxn * 10];
void ae(int a, int b, int c) {
	e[++ei].t = b; e[ei].nxt = g[a]; g[a] = ei; e[ei].c = c;
	e[++ei].t = a; e[ei].nxt = g[b]; g[b] = ei; e[ei].c = 0;
}
bool bfs() {
	memset(dis, -1, sizeof(dis));
	q[qh = qt = 1] = s; dis[s] = 0;
	int x;
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
	if (u == 0) dis[x] = -42;
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
class FoxAndGo3 {
	public:
		int maxEmptyCells(vector <string> board) {
			cl(g); ei = 1;
			int n = board.size();
			s = n * n; t = s + 1;
			int all = 0;
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j) {
					if (board[i][j] == '.') {
						++all;
						ae(s, i * n + j, 1);
						for (int d = 0; d < 4; ++d) {
							int x = i + dx[d], y = j + dy[d];
							if (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == 'o')
								ae(i * n + j, x * n + y, oo);
						}
					}
					if (board[i][j] == 'o') {
						++all;
						ae(i * n + j, t, 1);
					}
				}
			return all - dinic();
		}
};
