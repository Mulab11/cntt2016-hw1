/*
	First sort the songs by their tones.
	Then do some knapsack dp.
*/

#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PI;
const int MAXN = 60;
class GUMIAndSongsDiv1 {
	public:
	int maxSongs(vector <int> duration, vector <int> tone, int T) {
		PI a[MAXN]; int n = duration.size(), dp[60][60], ret = 0; // dp[i][j] = sing j songs among the first i songs, the least cost
		for (int i = 0; i < n; ++i) for (int j = 0; j <= n; ++j) dp[i][j] = 12345678; // init
		for (int i = 0; i < n; ++i) a[i] = PI(tone[i], duration[i]); // mp
		sort(a, a + n); 
		for (int i = 0; i < n; ++i){
			dp[i][1] = a[i].second; 
			if (dp[i][1] <= T) ret = max(1, ret);
			for (int j = 2; j <= i + 1; ++j)
				for (int k = 0; k < i; ++k){
					dp[i][j] = min(dp[i][j], dp[k][j - 1] + a[i].second + a[i].first - a[k].first); // ***
					if (dp[i][j] <= T) ret = max(ret, j);
				}
		}
		return ret;
	}
};

/*
	Is 'GUMI' that one in Vocaloid? I'm not sure.
*/
