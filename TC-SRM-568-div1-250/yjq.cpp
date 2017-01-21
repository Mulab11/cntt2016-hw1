#include <bits/stdc++.h>

using namespace std;

const int MAXN = 60 ; 

int dp[MAXN][1 << 3];

class BallsSeparating {
		public:
				int minOperations(vector <int> r, vector <int> g, vector <int> b) {
						int n = r.size() ; 
						memset(dp, 0x3f, sizeof dp) ; 
						dp[0][0] = 0 ; 
						for (int i = 0; i < n; i ++) { 
								for (int j = 0; j < 8; j ++) { 
										dp[i + 1][j | 1] = min(dp[i + 1][j | 1], dp[i + 1][j] + g[i] + b[i]) ; 
										dp[i + 1][j | 2] = min(dp[i + 1][j | 2], dp[i + 1][j] + r[i] + b[i]) ; 
										dp[i + 1][j | 4] = min(dp[i + 1][j | 4], dp[i + 1][j] + r[i] + g[i]) ; 
								}
						}
						if (dp[n][7] > 1000000000) return -1 ;
						return dp[n][7] ; 
				}
};
