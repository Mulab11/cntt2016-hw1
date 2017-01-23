#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55;

class TravellingPurchasingMan{
public:
	int g[MAXN][MAXN], dp[1 << 16][16], n, N;
	int dur[MAXN], st[MAXN], ed[MAXN], bitc[1 << 16];
	inline void update(int &a, int b){if(a == -1 || a > b) a = b;}
	int maxStores(int m, vector <string> buyPeriod, vector <string> roads){
		int i, j, k, u, v, w, ans = 0, cur;
		memset(g, 0x3f, sizeof(g));
		for(i = 0; i < int(roads.size()); ++ i){
			stringstream readin(roads[i]);
			readin >> u >> v >> w;
			g[u][v] = g[v][u] = w;
		}
		n = buyPeriod.size();
		for(i = 0; i < n; ++ i){
			stringstream readin(buyPeriod[i]);
			readin >> st[i] >> ed[i] >> dur[i];
		}
		for(i = 0; i < m; ++ i) g[i][i] = 0;
		for(k = 0; k < m; ++ k)
			for(i = 0; i < m; ++ i)
				for(j = 0; j < m; ++ j)
					if(g[i][k] + g[k][j] < g[i][j])
						g[i][j] = g[i][k] + g[k][j];
		memset(dp, -1, sizeof(dp));
		for(i = 0; i < n; ++ i)
			if(g[m - 1][i] <= ed[i])
				dp[1 << i][i] = max(st[i], g[m - 1][i]) + dur[i];
		for(i = 1, N = 1 << n; i < N; ++ i){
			bitc[i] = bitc[i >> 1] + (i & 1);
			for(j = 0; j < n; ++ j){
				if((cur = dp[i][j]) == -1)
					continue;
				ans = max(ans, bitc[i]);
				for(k = 0; k < n; ++ k){
					if(i & (1 << k)) continue;
					if(cur + g[j][k] <= ed[k])
						update(dp[i | (1 << k)][k], max(st[k], cur + g[j][k]) + dur[k]);
				}
			}
		} return ans;
	}
};
