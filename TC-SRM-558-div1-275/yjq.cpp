#include <bits/stdc++.h>

using namespace std; 

const int MAXN = 60 ; 

int dp[MAXN] ;  

class Stamp {
		public:
				int getMinimumCost(string s, int c1, int c2) {

						int ans = (1 << 30); 
						int n = s.length() ;  

						for(int l = 1; l <= n; l ++) {
								int cur = l * c1; 
								memset(dp, 60, sizeof dp); 
								dp[0] = 0 ;  
								for(int j = 1; j <= n; j ++) {
										int cnt = -1; 
										for(int i = j; i; i --) {
												if (s[i - 1] != '*') {
														if (cnt != -1 && cnt != s[i - 1]) break; 
														cnt = s[i - 1]; 
												}
												int len = j - i + 1; 
												if (len < l) continue ; 
												dp[j] = min(dp[j], dp[i - 1] + (len / l + (bool) (len % l)) * c2);  
										}
								}
								ans = min(ans, cur + dp[n]); 
						}
						return ans; 
				}
}; 
