#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55, dx[3] = {0, 0, 1}, dy[3] = {-1, 1, 0};

class Tunnels{
public:
	int cnt, id[MAXN][MAXN], up[MAXN * MAXN], dw[MAXN * MAXN];
	int f[MAXN][MAXN][MAXN], n, m; bool g[MAXN][MAXN];
	bool full[MAXN], lup[MAXN], ldw[MAXN], rup[MAXN], rdw[MAXN];
	inline bool inmap(int x, int y){return x >= 0 && x < n && y >= 0 && y < m;}
	inline void update(int &a, int b){if(a < b) a = b;}
	void dfs(int x, int y){
		id[x][y] = cnt;
		dw[cnt] = max(dw[cnt], x);
		for(int i = 0; i < 3; ++ i){
			x += dx[i], y += dy[i];
			if(inmap(x, y) && g[x][y] && id[x][y] == -1)
				dfs(x, y);
			x -= dx[i], y -= dy[i];
		}
	}
	int minimumTunnels(vector <string> g_){
		int i, j, k, cur; cnt = 0;
		n = g_.size(), m = g_[0].length();
		memset(id, -1, sizeof(id));
		memset(full, false, sizeof(full));
		memset(ldw, false, sizeof(ldw));
		memset(rdw, false, sizeof(rdw));
		memset(lup, false, sizeof(lup));
		memset(rup, false, sizeof(rup));
		memset(g, false, sizeof(g));
		for(i = 0; i < n; ++ i)
			for(j = 0; j < m; ++ j)
				g[i][j] = (g_[i][j] == 'X');
		for(i = 0; i < n; ++ i)
			for(j = 0; j < m; ++ j){
				if((~id[i][j]) || !g[i][j])
					continue;
				++ cnt; up[cnt] = dw[cnt] = i;
				dfs(i, j);
			}
		if(cnt == 0) return 0;
		if(m == 1) return 1;
		if(n == 1) return cnt;
		for(i = 0; i < n; ++ i){
			for(j = 0; j < m; ++ j)
				if(!g[i][j]) break;
			if(j == m) full[i] = true;
			if(i && g[i][0] && up[id[i][0]] == i && !(g[i][1] && g[i + 1][0]))
				lup[i] = true;
			if(g[i][0] && dw[id[i][0]] == i)
				ldw[i] = (i == 0) || !((g[i - 1][0] && g[i][1]) || lup[i - 1]);
			if(i && g[i][m - 1] && up[id[i][m - 1]] == i && !(g[i][m - 2] && g[i + 1][m - 1]))
				rup[i] = true;
			if(g[i][m - 1] && dw[id[i][m - 1]] == i)
				rdw[i] = (i == 0) || !((g[i - 1][m - 1] && g[i][m - 2]) || rup[i - 1]);
		}
		memset(f, -1, sizeof(f));
		f[0][0][0] = 0;
		for(i = 0; i < n; ++ i){
			for(j = 0; j <= i; ++ j)
				for(k = 0; k <= i; ++ k){
					if((cur = f[i][j][k]) < 0) continue;
					if(full[i] && lup[i] && rup[i]){
						update(f[i + 1][j][max(k - 1, 0)], cur);
						update(f[i + 1][j + 1][max(k - 1, 0)], cur + 1);
						update(f[i + 1][max(j - 1, 0)][k], cur);
						update(f[i + 1][max(j - 1, 0)][k + 1], cur + 1);
					}else{
						if(lup[i]){
							if(rup[i]) update(f[i + 1][max(j - 1, 0)][max(k - 1, 0)], cur);
							else{
								update(f[i + 1][max(j - 1, 0)][k], cur);
								if(rdw[i]) update(f[i + 1][max(j - 1, 0)][k + 1], cur + 1);
							}
						}else{
							if(rup[i]) update(f[i + 1][j][max(k - 1, 0)], cur);
							else{
								update(f[i + 1][j][k], cur);
								if(rdw[i]) update(f[i + 1][j][k + 1], cur + 1);
							}
							if(ldw[i]){
								if(rup[i]) update(f[i + 1][j + 1][max(k - 1, 0)], cur + 1);
								else{
									update(f[i + 1][j + 1][k], cur + 1);
									if(rdw[i] && !full[i]) update(f[i + 1][j + 1][k + 1], cur + 2);
								}
							}
						}
					}
				}
		} return cnt - f[n][0][0];
	}
};
