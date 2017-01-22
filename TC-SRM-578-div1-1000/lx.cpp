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

class BiGraph {			//二分图类，简单封装KM算法
private :
	int cost[52][52], n;
	int lx[52], ly[52], mat[52];
	int slk[52], pre[52];
	bool vy[52];

	void augment(int root) {
		rep (i, 1, n) {
			vy[i] = false;
			slk[i] = inf;
		}
		int py = 0;
		mat[0] = root;
		do {
			vy[py] = 1;
			int x = mat[py], det = inf, yy = -1;
			rep (y, 1, n) if (!vy[y]) {
				int tmp = lx[x] + ly[y] - cost[x][y];
				if (tmp < slk[y]) {
					slk[y] = tmp;
					pre[y] = py;
				}
				if (slk[y] < det) {
					det = slk[y];
					yy = y;
				}
			}
			rep (y, 0, n) {
				if (vy[y]) {
					ly[y] += det;
					lx[mat[y]] -= det;
				} else {
					slk[y] -= det;
				}
			}
			py = yy;
		} while (mat[py] != -1);
		do {
			int p = pre[py];
			mat[py] = mat[p];
			py = p;
		} while (py);
	}
public :
	inline void init(int n) {
		this->n = n;
		rep (i, 1, n) rep (j, 1, n) {
			cost[i][j] = 0;
		}
	}
	inline void add(int x, int y, int v) {
		cost[x][y] = v;
	}
	int Run() {
		rep (i, 1, n) {
			mat[i] = -1;
			lx[i] = ly[i] = 0;
			rep (j, 1, n) {
				upmax(lx[i], cost[i][j]);
			}
		}
		int res = 0;
		rep (x, 1, n)  augment(x);
		rep (i, 1, n)  res += lx[i] + ly[i];
		return res;
	}
} my;

class DeerInZooDivOne {
private :
	int f[52][52][52][52];
	vector<int> adj[52];
	int n;

	int color[52];
	void Dfs(int x, int fa, int c) {
		color[x] = c;
		for (int to : adj[x]) {
			if (to != fa) {
				Dfs(to, x, c);
			}
		}
	}

	int rec(int x, int fx, int y, int fy) {
		int &res = f[x][fx][y][fy];
		if (res == -1) {
			rep (i, 0, adj[x].size()-1) if (adj[x][i] != fx) {
				rep (j, 0, adj[y].size()-1) if (adj[y][j] != fy) {
					rec(adj[x][i], x, adj[y][j], y);
				}
			}
			my.init(max(adj[x].size(), adj[y].size()));
			rep (i, 0, adj[x].size()-1) if (adj[x][i] != fx) {
				rep (j, 0, adj[y].size()-1) if (adj[y][j] != fy) {
					my.add(i + 1, j + 1, f[adj[x][i]][x][adj[y][j]][y]);
				}
			}
			res = my.Run() + 1;
		}
		return res;
	}

	int calc() {
		rep (i, 1, n) rep (j, 1, n) {
			f[i][0][j][0] = -1;
			for (int a : adj[i]) for (int b : adj[j]) {
				f[i][a][j][b] = -1;
			}
		}
		int res = 0;
		rep (i, 1, n) if (color[i] == 1) {
			rep (j, 1, n) if (color[j] == 2) {
				upmax(res, rec(i, 0, j, 0));
			}
		}
		return res;
	}
public :
	//DP, KM, 树的同构
	//时间复杂度 O(n) * O(n^2) * O(n^3) = O(n^6)
	//n 枚举边 * n^2 个状态 * n^3 KM算法转移
	int getmax(vector<int> e1, vector<int> e2) {
		int ans = 0;
		n = e1.size() + 1;
		rep (i, 0, n-2)  e1[i]++, e2[i]++;
		rep (i, 0, n-2) {			//为了确保点集不相交，枚举断开一条边
			rep (j, 1, n)  adj[j].clear();
			rep (j, 0, n-2) if (i != j) {
				adj[e1[j]].pb(e2[j]);
				adj[e2[j]].pb(e1[j]);
			}
			Dfs(e1[i], e2[i], 1);
			Dfs(e2[i], e1[i], 2);
			upmax(ans, calc());
		}
		return ans;
	}
};
