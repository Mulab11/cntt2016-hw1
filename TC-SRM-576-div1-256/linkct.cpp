#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55, INF = 0x3f3f3f3f, MAXM = MAXN * MAXN * MAXN;

class ArcadeManao{
public:
	int d[MAXN * MAXN], id[MAXN][MAXN], g[MAXN * MAXN], r, c, n;
	int edgeSize, nxt[MAXM * 2], to[MAXM * 2], val[MAXM * 2];
	bool vis[MAXN * MAXN];
	void addEdge(int u, int v, int w){
		nxt[++ edgeSize] = g[u];
		to[g[u] = edgeSize] = v;
		val[edgeSize] = w;
	}
	int shortestLadder(vector <string> gr, int tr, int tc){
		int i, j, k, mn, mp; -- tr, -- tc;
		r = gr.size(), c = gr[0].length();
		for(i = n = 0; i < r; ++ i)
			for(j = 0; j < c; ++ j){
				if(gr[i][j] != 'X') continue;
				if(j == 0 || gr[i][j - 1] != 'X')
					id[i][j] = ++ n;
				else id[i][j] = n;
			}
		for(i = 0; i < r; ++ i)
			for(j = 0; j < c; ++ j){
				if(gr[i][j] != 'X') continue;
				for(k = i - 1; k >= 0; -- k)
					if(gr[k][j] == 'X')
						addEdge(id[i][j], id[k][j], i - k);
				for(k = i + 1; k < r; ++ k)
					if(gr[k][j] == 'X')
						addEdge(id[i][j], id[k][j], k - i);
			}
		memset(d, 0x3f, sizeof(d));
		memset(vis, false, sizeof(vis));
		for(i = 1, d[n] = 0; i <= n; ++ i){
			for(j = 1, mn = INF; j <= n; ++ j)
				if(!vis[j] && d[j] < mn) mn = d[j], mp = j;
			vis[mp] = true; if(id[tr][tc] == mp) break;
			for(j = g[mp]; j; j = nxt[j])
				if(d[to[j]] > max(mn, val[j]))
					d[to[j]] = max(mn, val[j]);
		} return d[id[tr][tc]] == INF ? -1 : d[id[tr][tc]];
	}
};
