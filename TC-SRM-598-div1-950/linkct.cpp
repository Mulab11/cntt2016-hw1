#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55;

class TPS{
public:
	int n, edgeSize, g[MAXN], nxt[MAXN << 1], to[MAXN << 1];
	int dfs(int x, int f){
		int ret = n, p, cur, chain = 0;
		for(p = g[x]; p; p = nxt[p]){
			if(to[p] == f) continue;
			cur = dfs(to[p], x);
			if(cur == 0) chain = 1, ++ ret;
			else ret += cur;
		} return ret - chain;
	}
	void addEdge(int u, int v){
		nxt[++ edgeSize] = g[u];
		to[g[u] = edgeSize] = v;
	}
	int minimalBeacons(vector <string> graph){
		int i, j, ans = n = graph.size();
		if(n == 1) return 0;
		memset(g, 0, sizeof(g));
		edgeSize = 0;
		for(i = 0; i < n; ++ i)
			for(j = 0; j < n; ++ j)
				if(graph[i][j] == 'Y')
					addEdge(i + 1, j + 1);
		for(i = 1; i <= n; ++ i)
			ans = min(ans, dfs(i, 0) + 1);
		return ans;
	}
};
