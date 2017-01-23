#include <bits/stdc++.h>
using namespace std;
const int MAXN = 305, MOD = 1000000009;

class TheExperiment{
public:
	int n, pf[MAXN], f[MAXN][MAXN], g[MAXN][MAXN], dp[MAXN][MAXN];
	inline void update(int &a, int b){if((a += b) >= MOD) a -= MOD;}
	int countPlacements(vector <string> drops, int m, int L, int a, int b){
		int i, j, k; string drop;
		for(i = 0; i < int(drops.size()); ++ i)
			drop += drops[i];
		n = drop.length();
		for(pf[0] = i = 0; i < n; ++ i)
			pf[i + 1] = pf[i] + drop[i] - '0';
		memset(f, 0, sizeof(f));
		memset(g, 0, sizeof(g));
		memset(dp, 0, sizeof(dp));
		for(i = 0; i <= n; ++ i) dp[0][i] = 1;
		for(i = 1; i <= m; ++ i)
			for(j = 1; j <= n; ++ j){
				if((dp[i][j] = g[i][j - 1] + dp[i][j - 1]) >= MOD)
					dp[i][j] -= MOD;
				for(k = 1; k <= j; ++ k)
					if(pf[j] - pf[k - 1] >= a && pf[j] - pf[k - 1] <= b && j - k + 1 <= L){
						update(g[i][j], g[i - 1][k - 1]);
						if(j - k + 1 == L){
							update(g[i][j], f[i - 1][k - 1]);
							update(g[i][j], dp[i - 1][k - 1]);
						}else{
							update(f[i][j], f[i - 1][k - 1]);
							update(f[i][j], dp[i - 1][k - 1]);
						}
					}
			}
		return (g[m][n] + dp[m][n]) % MOD;
	}
};
