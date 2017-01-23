#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int MAXN = 39;

class CentaurCompany{
public:
	LL f[MAXN][MAXN][MAXN], g[MAXN][MAXN][MAXN], tf[MAXN][MAXN], tg[MAXN][MAXN];
	int n, G[MAXN], to[MAXN << 1], nxt[MAXN << 1], edgeSize, size[MAXN];
	void solve(int x, int fa){
		int p, i, j, u, v;
		f[x][1][1] = g[x][0][0] = size[x] = 1;
		for(p = G[x]; p; p = nxt[p]){
			if(to[p] == fa) continue;
			solve(to[p], x);
			memset(tf, 0, sizeof(tf));
			memset(tg, 0, sizeof(tg));
			for(i = 0; i <= size[x]; ++ i)
				for(j = 0; j <= size[x]; ++ j)
					for(u = 0; u <= size[to[p]]; ++ u)
						for(v = 0; v <= size[to[p]]; ++ v){
							if(j + v) tf[i + u][j + v - 1] += f[x][i][j] * f[to[p]][u][v];
							tg[i + u][j + v] += g[x][i][j] * g[to[p]][u][v];
							tf[i + u][j + v] += f[x][i][j] * g[to[p]][u][v];
							tg[i + u][j + v] += g[x][i][j] * f[to[p]][u][v];
						}
			size[x] += size[to[p]];
			for(i = 0; i <= size[x]; ++ i)
				for(j = 0; j <= size[x]; ++ j)
					f[x][i][j] = tf[i][j], g[x][i][j] = tg[i][j];
		}
	}
	void addEdge(int u, int v){
		nxt[++ edgeSize] = G[u];
		to[G[u] = edgeSize] = v;
	}
	double getvalue(vector <int> u, vector <int> v){
		int i, j; LL ans = 0LL;
		memset(f, 0, sizeof(f));
		memset(g, 0, sizeof(g));
		memset(G, 0, sizeof(G));
		edgeSize = 0;
		n = u.size() + 1;
		for(i = 0; i < n - 1; ++ i)
			addEdge(u[i], v[i]), addEdge(v[i], u[i]);
		solve(1, -1);
		for(i = 1; i <= n; ++ i)
			for(j = 1; j <= n; ++ j)
				ans += f[1][i][j] * max(2 * j - i - 2, 0);
		for(i = 0; i < n; ++ i)
			for(j = 0; j < n; ++ j)
				ans += g[1][i][j] * max(2 * j - i - 2, 0);
		return ans * 2.0 / (1LL << n);
	}
};
