#include <bits/stdc++.h>

using namespace std ;

const int MAXN = 60 ;

int cnt[MAXN][2] ; 

class TheDevice {
		public:
				inline int minimumAdditional(vector <string> mp) {
						int ans = 0 ;
						for (int i = 0; i < mp.size(); i ++) {
								for (int j = 0; j < mp[0].size(); j ++) { 
										cnt[j][mp[i][j] - '0'] ++ ; 
								}
						}
						for (int i = 0; i < mp[0].size(); i ++) ans = max(ans, max(1 - cnt[i][0], 0) + max(2 - cnt[i][1], 0)) ; 
						return ans ; 
				}
};
