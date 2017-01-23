#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55, dx[4] = {0, 1}, dy[4] = {1, 0};

class GameInDarknessDiv1{
public:
	int d1[MAXN * MAXN], d2[MAXN * MAXN], *d, g[MAXN * MAXN];
	int edgeSize, nxt[MAXN * MAXN * 2], to[MAXN * MAXN * 2];
	int id[MAXN][MAXN], r, c, n, dep[MAXN * MAXN * 2];
	int dfs(int x, int fe){
		if(~dep[fe]) return dep[fe];
		dep[fe] = 0;
		for(int p = g[x]; p; p = nxt[p]){
			if((p ^ 1) == fe) continue;
			dep[fe] = max(dep[fe], dfs(to[p], p) + 1);
		} return dep[fe];
	}
	void getDist(int x, int fa, int len){
		d[x] = len;
		for(int p = g[x]; p; p = nxt[p])
			if(to[p] != fa) getDist(to[p], x, len + 1);
	}
	inline bool inMap(int i, int j){return i >= 0 && i < r && j >= 0 && j < c;}
	void addEdge(int u, int v){
		nxt[++ edgeSize] = g[u];
		to[g[u] = edgeSize] = v;
	}
	string check(vector <string> field){
		int i, j, k, x, y, st = 0, ed = 0;
		r = field.size(), c = field[0].length();
		memset(id, 0, sizeof(id));
		for(i = n = 0; i < r; ++ i)
			for(j = 0; j < c; ++ j)
				if(field[i][j] != '#')
					id[i][j] = ++ n;
		memset(g, 0, sizeof(g));
		edgeSize = 1;
		for(i = 0; i < r; ++ i)
			for(j = 0; j < c; ++ j){
				if(id[i][j] == 0) continue;
				if(field[i][j] == 'A') st = id[i][j];
				else if(field[i][j] == 'B') ed = id[i][j];
				for(k = 0; k < 2; ++ k){
					x = i + dx[k], y = j + dy[k];
					if(inMap(x, y) && id[x][y]){
						addEdge(id[i][j], id[x][y]);
						addEdge(id[x][y], id[i][j]);
					}
				}
			}
		d = d1, getDist(st, 0, 0);
		d = d2, getDist(ed, 0, 0);
		memset(dep, -1, sizeof(dep));
		for(i = 1; i <= n; ++ i)
			if(d1[i] >= d2[i] + 2){
				for(j = g[i], k = 0; j; j = nxt[j])
					if(dfs(to[j], j) >= 2) ++ k;
				if(k >= 3) return "Bob wins";
			}
		return "Alice wins";
	}
};
