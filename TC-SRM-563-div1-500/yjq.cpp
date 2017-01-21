#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55;

int dp[MAXN] ; 

class SpellCards {
		public:

				int maxDamage(vector<int> level, vector<int> damage) {
						int n = level.size() ; 
						for(int i = 0;i < n;i ++) for(int j = n;j >= level[i];j --) dp[j] = max(dp[j], dp[j - level[i]] + damage[i]);
						int ans = 0;
						for(int i = 0;i <= n;i ++) ans = max(ans, dp[i]);
						return ans;
				}
};
