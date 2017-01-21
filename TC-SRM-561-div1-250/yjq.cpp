#include <bits/stdc++.h>

using namespace std ; 

const int MAXN = 60  ;  
void chMin(int &a,  int b) {
		if (b < a) a = b  ;  
}


vector<int> tmpa, tmpb ; 
int dp[2][MAXN][MAXN][MAXN * MAXN / 2] ; 

class ICPCBalloons {
		public:
				int minRepaintings(vector <int> a,  string bs,  vector <int> ma) {

						sort(ma.begin(), ma.end()) ; 
						reverse(tmpa.begin(), tmpa.end()),  reverse(tmpb.begin(), tmpb.end()), reverse(ma.begin(), ma.end()) ;  
						tmpa.clear(), tmpb.clear() ; 

						for(int i = 0 ; i < a.size() ; i ++)
								if (bs[i] == 'L') tmpa.push_back(a[i]) ;  
								else tmpb.push_back(a[i]) ; 

						for( ; tmpa.size() < ma.size() ; ) tmpa.push_back(0) ; 
						for( ; tmpb.size() < ma.size() ; ) tmpb.push_back(0) ;  
						sort(tmpa.begin(), tmpa.end()) ; 
						sort(tmpb.begin(), tmpb.end()) ; 

						memset(dp,  60,  sizeof dp) ; 

						int INF = dp[0][0][0][0]  ;  
						int sum = 0,  p = 0 ; 
						dp[0][0][0][0] = 0 ; 
						for(int i = 0 ; i < ma.size() ; i ++) {
								p ^= 1 ; 
								int v = ma[i] ; 
								memset(dp[p], 60, sizeof dp[p]) ; 
								for(int j = 0 ; j <= tmpa.size() ; j ++)
										for(int k = 0 ; k <= tmpb.size() ; k ++)
												for(int s = 0 ; s <= sum ; s ++)
														if (dp[p ^ 1][j][k][s] != INF) {
																int val = dp[p ^ 1][j][k][s] ; 
																if (j < tmpa.size()) {
																		chMin(dp[p][j + 1][k][s + v], val + max(0, v - tmpa[j])) ; 
																}
																if (k < tmpb.size()) {
																		chMin(dp[p][j][k + 1][s], val + max(0, v - tmpb[k])) ; 
																}
														}
								sum += v ; 
						}
						int ans = INF, sa = 0, sb = 0 ; 
						for(int j = 0 ; j < tmpa.size() ; j ++) sa += tmpa[j] ; 
						for(int j = 0 ; j < tmpb.size() ; j ++) sb += tmpb[j] ; 
						for(int j = 0 ; j <= tmpa.size() ; j ++)
								for(int k = 0 ; k <= tmpb.size() ; k ++)
										for(int s = 0 ; s <= sum ; s ++)
												if (s <= sa && sum - s <= sb) chMin(ans, dp[p][j][k][s]) ;  
						if (ans == INF) return -1 ; 
						return ans ; 
				}
} ; 
