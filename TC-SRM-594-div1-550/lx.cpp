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
const int N = 2555;

class Network {
private : 
	struct edge { 
		int to, c, n;
	} e[N * 20];
	int head[N], tot, n;
	int cur[N], d[N], S, T;
	bool Bfs() {
		queue<int> Q;
		memset(d, -1, sizeof(int) * (n+1));
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
		this->n = n;
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

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

class FoxAndGo3 {
private :
	int loc[51][51], tot;
	Network my;
	int n;
	inline bool inBoard(int x, int y) {
		return x >= 0 && x < n && y >= 0 && y < n;
	}
public :
	int maxEmptyCells(vector<string> board) {
		n = board.size();
		int s = tot++, t = tot++;
		rep (i, 0, n-1) rep (j, 0, n-1) {
			if (board[i][j] != 'x') {
				loc[i][j] = tot++;
			}
		}
		my.init(tot);
		rep (i, 0, n-1) rep (j, 0, n-1) {
			if (board[i][j] != 'x') {
				if (board[i][j] == 'o') {
					my.addEdge(s, loc[i][j], 1);
					rep (d, 0, 3) {
						int tx = i + dx[d], ty = j + dy[d];
						if (inBoard(tx, ty) && loc[tx][ty]) {
							my.addEdge(loc[i][j], loc[tx][ty], inf);
						}
					}
				} else {
					my.addEdge(loc[i][j], t, 1);
				}
			}
		}
		int ans = tot-2 - my.Run(s, t);
		return ans;
	};
};
