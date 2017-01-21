#include <bits/stdc++.h>

using namespace std;

const int MAXN = 22; 
int n , m , a[MAXN][MAXN] ;

int S = 0 ; 
int dp[MAXN][1 << 11][2], cnt = 0;

double ans = 0 ; 

class RandomPaintingOnABoard {
		public:
				double expectedSteps(vector<string> prob) {
						n = prob.size(), m = prob[0].size() ; 
						for (int i = 0; i < n; i ++) for (int j = 0; j < m; j ++) {
								if (n < m) a[i][j] = prob[i][j] - '0', S += a[i][j] ; 
								else a[j][i] = prob[i][j] - '0', S += a[j][i] ; 
						}
						for(int i = 1; i < (1 << n); i++) {
								cnt = __builtin_popcount(i) ; 
								dp[0][0][(n + m + cnt) & 1] = 1;
								for(int j = 0; j < m; j++) {
										int s = 0;
										for(int k = 0; k < n; k++) {
												if((i >> k) & 1)
														s += a[k][j];
										}
										for(int k = 0; k <= S; k++) {
												for(int t = 0; t < 2; t++) {
														if(dp[j][k][t]) {
																dp[j + 1][k][t] += dp[j][k][t];
																dp[j + 1][k + s][t ^ 1] += dp[j][k][t];
														}
												}
										}
								}
								for(int j = 0; j < S; j++) ans += 1.0 * j / S / (1.0 - 1.0 * j / S) * (dp[m][j][1] - dp[m][j][0]);
						}
						return ans + 1.0;
				}
};
