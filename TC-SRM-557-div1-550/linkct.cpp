#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55;

class Incubator{
public:
	int g[MAXN][MAXN], g_[MAXN][MAXN], n, cnt, match[MAXN];
	int nid[MAXN]; bool vis[MAXN];
	int find(int x){
		for(int i = 1; i <= n; ++ i)
			if(g_[x][i] && !vis[i]){
				vis[i] = true;
				if(!match[i] || find(match[i])){
					match[i] = x;
					return true;
				}
			}
		return false;
	}
	int maxMagicalGirls(vector <string> graph){
        memset(g, 0, sizeof(g));
        memset(g_, 0, sizeof(g_));
        memset(match, 0, sizeof(match));
        memset(nid, 0, sizeof(nid));
		int i, j, k, ans = 0;
		n = graph.size();
		for(i = 0; i < n; ++ i)
			for(j = 0; j < n; ++ j)
				if(graph[i][j] == 'Y')
					g[i + 1][j + 1] = 1;
		for(k = 1; k <= n; ++ k) //Floyd just for connectivity
			for(i = 1; i <= n; ++ i)
				for(j = 1; j <= n; ++ j)
					g[i][j] |= g[i][k] & g[k][j];
		for(i = 1, cnt = 0; i <= n; ++ i){
			if(g[i][i]) continue; //Node i has a path leading back to itself, hence not qualified for constructing the final DAG
			nid[i] = ++ cnt;
		}
		for(i = 1; i <= n; ++ i){
			if(!nid[i]) continue;
			for(j = 1; j <= n; ++ j){
				if(!g[i][j] || !nid[j]) continue;
				g_[nid[i]][nid[j]] = 1;
			}
		}
		for(i = 1; i <= cnt; ++ i){
			memset(vis, false, sizeof(vis));
			if(find(i)) ++ ans;
		} return cnt - ans;
	}
};
