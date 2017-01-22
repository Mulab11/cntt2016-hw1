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

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

const int inf = 0x3f3f3f3f;
const int N = 115;

class DirectedSpanningTree {
private :
	struct edge {
		int x, y, v;
	} e[N * N];
	int win[N], pre[N];
	int vis[N], id[N];
	int n, m;
	int Work(int Root) {
		int ans = 0;
		while (1) {
			memset(win, 0x3f, sizeof(int) * n);
			rep (i, 0, m - 1) {
				if (win[e[i].y] > e[i].v) {
					win[e[i].y] = e[i].v;
					pre[e[i].y] = e[i].x;
				}
			}
			rep (i, 0, n - 1) {
				if (i != Root && win[i] == inf) {
					return -1;
				}
			}
			memset(vis, -1, sizeof(int) * n);
			memset(id, -1, sizeof(int) * n);
			win[Root] = id[Root] = 0;
			int tn = 1;
			rep (i, 0, n - 1) {
				ans += win[i];
				int u = i;
				while (vis[u] != i && id[u] == -1) {
					vis[u] = i;
					u = pre[u];
				}
				if (id[u] == -1) {
					int v = u;
					do {
						id[v] = tn;
						v = pre[v];
					} while (u != v);
					tn++;
				}
			}
			if (tn == 1)  break ;
			rep (i, 0, n - 1) {
				if (id[i] == -1)
					id[i] = tn++;
			}
			for (int i = 0; i < m; ++i) {
				if (id[e[i].x] == id[e[i].y]) {
					swap(e[i--], e[--m]);
				} else {
					e[i].v -= win[e[i].y];
					e[i].x = id[e[i].x];
					e[i].y = id[e[i].y];
				}
			}
			n = tn;
			Root = 0;
		}
		return ans;
	}
public :
	void init(int n) {
		this->n = n, m = 0;
	}
	void ins(int x, int y, int v) {
		e[m++] = (edge){x, y, v};
	}
	int Run(int R) {
		return Work(R);
	}
};

class FoxTheLinguist {
private :
	DirectedSpanningTree my;
	void Add(const string & s) {
		int x = (s[0] - 'A') * 10 + (s[1] - '0');
		int y = (s[4] - 'A') * 10 + (s[5] - '0');
		int v = (((s[7]-'0')*10 + s[8]-'0')*10 + s[9]-'0') * 10 + s[10]-'0';
		my.ins(x, y, v);
	}
public :
	int minimalHours(int n, vector<string> Info) {
		int root = n * 10;
		my.init(root + 1);
		stringstream ss;
		string A;
		rep (i, 0, Info.size() - 1)  ss << Info[i];
		while (ss >> A)  Add(A);
		rep (i, 0, n - 1) {
			int v = i * 10;
			my.ins(root, v, 0);
			rep (j, 1, 9) {
				my.ins(v + j, v + j - 1, 0);
			}
		}
		int ans = my.Run(root);
		return ans;
	}
};
