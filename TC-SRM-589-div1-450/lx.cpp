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
const int N = 1e5 + 10;

class Network {
private : 
	struct edge { 
		int to, c, n;
	} e[N * 20];
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
};

char Col[3] = {'R', 'G', 'B'};

inline int inmod(int x, int mo) {
	if (x < 0)   x += mo;
	if (x >= mo) x -= mo;
	return x;
}

class GearsDiv1 {
private :
	Network my;
public :
	// 二分图，最大独立集
	int getmin(string col, vector<string> mat) {
		int n = col.size();
		int ans = n;
		int tot = n + 2;
		int s = n, t = s + 1;
		rep (i, 0, 2) {			//枚举与另外两种颜色不同的那个颜色
			char a = Col[inmod(i+1, 3)];
			char b = Col[inmod(i+2, 3)];
			my.init(tot);
			rep (i, 0, n-1) {
				if (col[i] == a) {
					my.addEdge(s, i, 1);
				} else if (col[i] == b) {
					my.addEdge(i, t, 1);
				}
			}
			rep (i, 0, n-1) if (col[i] == a) {
				rep (j, 0, n-1) if (col[j] == b && mat[i][j] == 'Y') {
					my.addEdge(i, j, 1);
				}
			}
			upmin(ans, my.Run(s, t));
		}
		return ans;
	}
};
