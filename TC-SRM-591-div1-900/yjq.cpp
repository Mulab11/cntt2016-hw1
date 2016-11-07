#include <bits/stdc++.h>
#define MOD 1000000009

using namespace std ;

int dp[2][1 << 16] ; 
int pos[10][10] ;
pair<int, int> seq[20] ; 

inline void update(int &a, int b) {
		a += b ;
		if (a >= MOD) a -= MOD ; 
}

int n, m ;

string A, B ; 

class StringPath {
		public :
				int countBoards(int n, int m, string A, string B) {
						int p = 0 ;
						if (A[0] != B[0]) return 0 ; 
						dp[p][3] = 1; 
						memset(pos, -1, sizeof pos) ; 	
						pos[1][1] = 0 ; //pos数组记录该格子是当前轮廓线上的第几个格子 
						int now = 1 ; 
						seq[0] = make_pair(1, 1) ; //seq数组记录当前轮廓线上的格子。

						for (int tot = 3; tot <= n + m; tot ++) { // tot表示当前枚举的格子于(1,1)的距离
								int ca = A[tot - 2], cb = B[tot - 2] ; 
								for (int i = 1; i <= tot;i ++) {
										int j = tot - i ; 
										if (i < 1 || i > n || j < 1 || j > m) continue ; 
										memset(dp[p ^ 1], 0, sizeof dp[p ^ 1]) ; 
										for (int S = 0; S < (1 << (now << 1)); S ++) { 
												if (dp[p][S]) { 
														if (ca == cb) { //如果两个字符串的当前字符相同
																// trans表示转移到的状态， to是求trans的辅助变量
																int trans = S , to = 0 ; 
																//枚举两种情况， 填的字符是需要的字符， 或者不是
																if (pos[i][j - 1] >= 0) to |= ((S >> (pos[i][j - 1] << 1)) & 3) ; 
																if (pos[i - 1][j] >= 0) to |= ((S >> (pos[i - 1][j] << 1)) & 3) ; 
																if (pos[i - 1][j] >= 0) 
																		trans = ((((S >> ((pos[i - 1][j] + 1) << 1)) << 2) | to) << (pos[i - 1][j] << 1)) + (S & ((1 << (pos[i - 1][j] << 1)) - 1 )) ; 
																else trans = (S << 2) + to ; 
																update(dp[p ^ 1][trans] , dp[p][S]) ;

																if (pos[i - 1][j] >= 0) trans = ((S >> (((pos[i - 1][j] + 1)) << 1)) << ((pos[i - 1][j] + 1) << 1)) + (S & ((1 << (pos[i - 1][j] << 1)) - 1 )) ; 
																else trans = S << 2 ;  
																update(dp[p ^ 1][trans], (int) (1LL * dp[p][S] * 25 % MOD)) ;
														}
														else {
																int trans = S, to = 0 ;

																//基本与两个字符串当前位置字符相同的情况一样。 只不过需要多枚举一种情况（填的字符到底是第一个字符串的还是第二个字符串的
																if (pos[i][j - 1] >= 0) to |= ((S >> (pos[i][j - 1] << 1)) & 1) ; 
																if (pos[i - 1][j] >= 0) to |= ((S >> (pos[i - 1][j] << 1)) & 1) ; 
																if (pos[i - 1][j] >= 0) 
																		trans = ((((S >> ((pos[i - 1][j] + 1) << 1)) << 2) | to) << (pos[i - 1][j] << 1)) + (S & ((1 << (pos[i - 1][j] << 1)) - 1 )) ; 
																else trans = (S << 2) + to ; 
																update(dp[p ^ 1][trans] , dp[p][S]) ;
																to = 0 ; 
																if (pos[i][j - 1] >= 0) to |= ((S >> (pos[i][j - 1] << 1)) & 2) ; 
																if (pos[i - 1][j] >= 0) to |= ((S >> (pos[i - 1][j] << 1)) & 2) ; 
																if (pos[i - 1][j] >= 0) 
																		trans = ((((S >> ((pos[i - 1][j] + 1) << 1)) << 2) | to) << (pos[i - 1][j] << 1)) + (S & ((1 << (pos[i - 1][j] << 1)) - 1 )) ; 
																else trans = (S << 2) + to ; 
																update(dp[p ^ 1][trans] , dp[p][S]) ;
																if (pos[i - 1][j] >= 0) trans = ((S >> ((pos[i - 1][j] + 1) << 1)) << ((pos[i - 1][j] + 1) << 1) )+ (S & ((1 << (pos[i - 1][j] << 1)) - 1 )) ; 
																else trans = S << 2 ;  
																update(dp[p ^ 1][trans], (int) (1LL * dp[p][S] * 24 % MOD)) ;
														}		
												}
										}
										if (pos[i - 1][j] < 0) {
												for (int k = now ; k ; k --) {
														seq[k] = seq[k - 1] ; 
														pos[seq[k].first][seq[k].second] = k ; 
												}
												seq[0] = make_pair(i, j) ; 
												pos[i][j] = 0 ; 
												now ++ ; 
										}
										else {
												seq[pos[i - 1][j]] = make_pair(i, j) ;
												pos[i][j] = pos[i - 1][j] ; 
												pos[i - 1][j] = - 1 ; 
										}	
										p ^= 1 ; 
								}
								if (seq[now - 1].first + seq[now - 1].second < tot) { 
										for (int S = 0; S < (1 << (now << 1)); S ++) {
												if (S >> ((now - 1) << 1)) update(dp[p][S & ((1 << ((now - 1) << 1)) - 1)] , dp[p][S]) ; 
										}
										pos[seq[now - 1].first][seq[now - 1].second] = -1 ; 
										now -- ; 
								}
						}
						return dp[p][3] ; 
	}
} ;

