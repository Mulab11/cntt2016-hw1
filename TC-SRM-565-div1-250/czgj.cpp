/*
	Easy knapsack dp.
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
class MonstersValley {
	public:
	int minimumPrice(vector<long long> dread, vector <int> price) {
		LL dp[128]; memset(dp, 0, sizeof dp); // dp[i] = maximum sum with cost i
		int n = dread.size();
		for (int i = 0; i < n; ++i)
			for (int j = (i + 1) * 2; j >= 0; --j){
				if (dp[j] < dread[i]) dp[j] = -1e18; // Can't ignore that monster
				if (j >= price[i] && dp[j] < dp[j - price[i]] + dread[i]) // Buy that monster
					dp[j] = dp[j - price[i]] + dread[i];
			}
		for (int i = 0; i <= n * 2; ++i) if (dp[i] >= 0) return i;
		return -1;
	}
};

/*
	Don't let the bunny distract you!
		- osu!
*/
