#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;

class StringWeight{
public:
	int dp[55][27][27], n, cnt[55], pf[55];
	inline void update(int &a, int b){if(a > b) a = b;}
	inline int down(int x, int d){return ((x + x - d + 1) * d) >> 1;}
	inline int up(int x, int d){return ((x + x + d - 1) * d) >> 1;}
	int getMinimum(vector <int> L){
		int i, j, k, a, b, cur, ext, mx, ans = INF;
		n = L.size();
		for(i = 1, pf[0] = 0; i <= n; ++ i){
			cnt[i] = L[i - 1];
			pf[i] = pf[i - 1] + cnt[i];
		}
		//dp[i][j][k]: processed the first i string, started j segments, among which k segments hadn't been close
		memset(dp, 0x3f, sizeof(dp));
		for(j = 0; j <= 26; ++ j){
			dp[1][max(min(cnt[1], 26), j)][j] = - down(cnt[1], j);
			if(cnt[1] > 26) dp[1][26][j] += cnt[1] - 26;
		}
		for(i = 1, mx = min(cnt[1], 26); i < n; mx = max(mx, min(cnt[++ i], 26))){
			for(j = mx; j <= 26; ++ j){
				for(k = 0; k <= j; ++ k){
					if((cur = dp[i][j][k]) == INF) continue;
					for(a = 0; a <= k; ++ a){ //Close a segments at i + 1
						for(b = 0; b + j <= 26; ++ b){ //Start b new segments at i + 1
							//In total, k - a + b segments covered i + 1
							ext = max(min(cnt[i + 1], 26) - (k + b), 0); //Need ext new segments for compensation
							if(b + j + ext > 26) continue;
							if(cnt[i + 1] > 26 && k == a)
								update(dp[i + 1][b + j + ext][k - a + b], cur + up(pf[i] + 1, a) - down(pf[i + 1], b) + cnt[i + 1] - 26);
							else update(dp[i + 1][b + j + ext][k - a + b], cur + up(pf[i] + 1, a) - down(pf[i + 1], b));
						}
					}
				}
			}
		}
		for(i = mx; i <= 26; ++ i)
			update(ans, dp[n][i][0]);
		return ans;
	}
};
