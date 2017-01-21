#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int MAXN = 60 ;

LL dp[MAXN][MAXN << 1];

class MonstersValley {
		public:
				int minimump(vector<LL> d, vector <int> p) {
						memset(dp, 0, sizeof dp);
						int n = d.size();
						for (int i = 0; i < n ; i ++) {
								for (int j = 0 ; j <= (n << 1) ; j ++) dp[i + 1][j] = -(1LL << 53);
								for (int j = 0 ; j <= (n << 1) ; j ++) {
										if (dp[i][j] >= d[i]) dp[i + 1][j] = max(dp[i + 1][j],dp[i][j]);
										dp[i + 1][j + p[i]] = max(dp[i + 1][j + p[i]],dp[i][j] + d[i]);
								}
						}
						for (int j = 0 ; j <= (n << 1) ;j ++) if (dp[n][j] >= 0) return j;
				}
};
