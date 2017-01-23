#include <bits/stdc++.h>
using namespace std;
typedef vector <int> vi;

class KeyDungeonDiv1{
public:
	int n, N, dp[4105][265];
	inline void update(int &a, int b){if(a < b) a = b;}
	int maxKeys(vi dr, vi dg, vi rr, vi rg, vi rw, vi init){
		int i, j, k, l, ans = 0, cur;
		memset(dp, -1, sizeof(dp));
		for(i = 0; i <= init[2]; ++ i)
			dp[0][init[0] + i] = init[1] + init[2] - i;
		n = dr.size(), N = 1 << n;
		for(i = 0; i < N; ++ i){
			for(j = 0; j <= (n + 1) * 20; ++ j){
				if((cur = dp[i][j]) == -1) continue;
				ans = max(ans, j + cur);
				for(k = 0; k < n; ++ k){
					if(i & (1 << k)) continue;
					if(j < dr[k] || cur < dg[k]) continue;
					for(l = 0; l <= rw[k]; ++ l)
						update(dp[i | (1 << k)][j - dr[k] + rr[k] + l], cur - dg[k] + rg[k] + rw[k] - l);
				}
			}
		} return ans;
	}
};
