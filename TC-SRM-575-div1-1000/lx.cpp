#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define LX_JUDGE

using namespace std;
typedef long long LL;

const int inf = 0x3f3f3f3f;
const int N = 4343;

class netWork
{
private : 
	struct edge
	{
		int to, c, n;
	} e[N * 13];

	int cur[N], head[N], tot = 1;
	int d[N], S, T;

	bool Bfs() {
		queue<int> Q;
		memset(d, -1, sizeof(d));
		d[S] = 0;
		Q.push(S);
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			cur[u] = head[u];
			for (int p = head[u]; p; p = e[p].n) {
				if (e[p].c && d[e[p].to] == -1) {
					d[e[p].to] = d[u] + 1;
					Q.push(e[p].to);
				}
			}
		}
		return d[T] >= 0;
	}
	int Dfs(int x, int f) {
		if (x == T)  return f;
		int a = f;
		for (int & p = cur[x]; p; p = e[p].n) {
			if (e[p].c && d[e[p].to] == d[x] + 1) {
				int t = Dfs(e[p].to, min(e[p].c, a));
				e[p].c -= t;
				e[p ^ 1].c += t;
				a -= t;
				if (!a)  return f;
			}
		}
		d[x] = -1;
		return f - a;
	}
public :
	void init(int s, int t) {
		S = s, T = t;
		tot = 1;
	}
	inline void addEdge(int x, int y, int c, int d = 0) {
		e[++tot] = (edge) {y, c, head[x]}, head[x] = tot;
		e[++tot] = (edge) {x, d, head[y]}, head[y] = tot;
	}
	int Run() {
		int ans = 0;
		while (Bfs())
			ans += Dfs(S, inf);
		return ans;
	}
} net ;

class TheTilesDivOne
{
public : 
	int id[55][55], tot, n, m;

	int find(vector<string> board) {
		n = board.size(), m = board[0].size();
		int s = N - 2, t = s + 1;
		net.init(s, t);
		rep (i, 0, n - 1) rep (j, 0, m - 1) {
			if (board[i][j] != 'X') {
				id[i][j] = ++tot;
				if ((i + j) & 1) {
					if (i & 1) {
						net.addEdge(s, id[i][j], 1);
						if (i > 0 && id[i - 1][j]) {
							net.addEdge(id[i][j], id[i - 1][j], 1);
						}
						if (j > 0 && id[i][j - 1]) {
							net.addEdge(id[i][j], id[i][j - 1], 1);
						}
					} else {
						net.addEdge(id[i][j], t, 1);
						if (i > 0 && id[i - 1][j]) {
							net.addEdge(id[i - 1][j] + 1, id[i][j], 1);
						}
						if (j > 0 && id[i][j - 1]) {
							net.addEdge(id[i][j - 1] + 1, id[i][j], 1);
						}
					}
				} else {
					++tot;
					net.addEdge(id[i][j], tot, 1);
					if (i > 0 && id[i - 1][j]) { 
						if ((i - 1) & 1) {
							net.addEdge(id[i - 1][j], id[i][j], 1);
						} else {
							net.addEdge(id[i][j] + 1, id[i - 1][j], 1);
						}
					}
					if (j > 0 && id[i][j - 1]) {
						if (i & 1) {
							net.addEdge(id[i][j - 1], id[i][j], 1);
						} else {
							net.addEdge(id[i][j] + 1, id[i][j - 1], 1);
						}
					}
				}
			}
		}
		int ans = net.Run();
		return ans;
	}
};
