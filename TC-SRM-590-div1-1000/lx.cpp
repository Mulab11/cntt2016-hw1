#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define bin(x) (1<<(x))
#define LX_JUDGE

using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

template<typename T> inline void upmax(T &x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T &x, T y) { x > y ? x = y : 0; }

const int inf = 0x3f3f3f3f;
const int N = 1e4 + 10;

class Network {
private : 
	struct edge { 
		int to, c, n;
	} e[N * 51];
	int head[N], tot;
	int cur[N], d[N], S, T;
	bool Bfs() {
		queue<int> Q;
		memset(d, -1, sizeof(int) * (T+1));
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
		for (int &p = cur[x]; p; p = e[p].n) {
			if (e[p].c && d[e[p].to] == d[x] + 1) {
				int t = Dfs(e[p].to, min(e[p].c, a));
				e[p].c -= t;
				e[p ^ 1].c += t;
				if (!(a -= t))  return f;
			}
		}
		d[x] = -1;
		return f - a;
	}
public :
	void init(int n) {
		memset(head, 0, sizeof(int) * (n+1));
		tot = 1;
	}
	inline void addEdge(int x, int y, int c, int d = 0) {
		e[++tot] = (edge) {y, c, head[x]}, head[x] = tot;
		e[++tot] = (edge) {x, d, head[y]}, head[y] = tot;
	}
	int Run(int s, int t) {
		S = s, T = t;
		int ans = 0;
		while (Bfs())
			ans += Dfs(S, inf);
		return ans;
	}
} my;

inline int sqr(int x) {
	return x * x;
}

class FoxAndCity {
private :
	int id[53][53], tot;
	int n;
public :
	int minimalCost(vector<string> link, vector<int> want) {
		n = link.size();
		rep (i, 0, n-1) rep (j, 0, n-1) {
			id[i][j] = tot++;
		}
		int s = tot++, t = tot++;
		my.init(0);
		rep (i, 0, n - 1) {
			my.addEdge(s, id[i][0], (i == 0) ? 0 : inf);
			rep (j, 1, n - 1) {
				int cost = i > 0 ? sqr(want[i] - j) : inf;
				my.addEdge(id[i][j - 1], id[i][j], cost);
			}
			my.addEdge(id[i][n - 1], t, inf);
		}
		rep (i, 0, n - 1) rep (j, 0, n - 1) {
			if (link[i][j] == 'Y') {
				rep (k, 1, n - 1) {
					my.addEdge(id[i][k], id[j][k - 1], inf);
				}
			}
		}
		int ans = my.Run(s, t);
		return ans;
	}
};
