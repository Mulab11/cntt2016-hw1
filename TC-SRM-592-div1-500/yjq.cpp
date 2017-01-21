#include <bits/stdc++.h>

using namespace std ;

int MOD ;

const int MAXN = 81 ; 

int dp[2][MAXN * MAXN][MAXN] ; 

inline void update(int &a, int b) {
		 a += b ; 
		 if (a >= MOD) a -= MOD ;
}
class LittleElephantAndPermutationDiv1 {
		public :
				int getNumber(int N, int K) { 
						memset(dp, 0, sizeof dp) ; 
						int p = 0 ; 
						dp[0][0][0] = 1; 
						for (int i = 0; i < N; i ++) { 
								memset(dp[p ^ 1], 0, sizeof dp[p ^ 1]) ;  
								for (int j = 0; j <= (i + 1) * (i + 1); j ++) { 
										for (int k = 0; k <= i; k ++) { 
														if (dp[p][j][k]) { 
																update(dp[p ^ 1][j + i + 1][k], dp[p][j][k]) ; 
																update(dp[p ^ 1][j][k + 1], dp[p][j][k] ) ;
																update(dp[p ^ 1][j + i + 1][k], (int) (1LL * dp[p][j][k] * (k << 1) % MOD) ) ; 
																update(dp[p ^ 1][j + (i << 1) + 2][k - 1], (int) (1LL * dp[p][j][k] * k % MOD * k % MOD) ) ; 
														}
										}
								}
								p ^= 1 ; 
						}
						int ans =0  ;
						for (int k = K; k <= N * N; k ++) { 
								update(ans, dp[p][k][0]) ; 
						}
						for (int i = 1; i <= N; i ++) ans = 1LL * ans * i % MOD ; 
						return ans ; 
				}
} solution ; 

int main() {
#ifdef YJQ_LOCAL
		freopen(".in", "r", stdin)  ;
#endif
		int N, K;
		scanf("%d%d%d", &N, &K, &MOD) ;
		printf("%d\n", solution.getNumber(N, K)) ; 
}

