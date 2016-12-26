#include <bits/stdc++.h>
 
using namespace std;
 
#define eprintf printf
#define pb push_back
#define mp make_pair
#define sz(x) ((int)(x).size())
#define sqr(x) ((x) * (x))

typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;
 
const int INF = 1e9;
 
struct Stamp {
	int getMinimumCost(string desiredColor, int stampCost, int pushCost) {
		int n = sz(desiredColor);
		// 配色
		vi msks(n);
		for (int i = 0; i < n; i++) {
			switch (desiredColor[i]) {
				case 'R': msks[i] = 1; break;
				case 'G': msks[i] = 2; break;
				case 'B': msks[i] = 4; break;
				case '*': msks[i] = 7; break;
			}
		}
		int ans = INF;
		// 枚举印章长度
		for (int len = 1; len <= n; len++) {
			// dp[i]表示刷完前缀i的代价
			vi dp(n + 1, INF);
			dp[0] = 0;
			for (int i = 0; i < n; i++) {
				int ccol = 7;
				for (int ne = i; ne < n; ne++) {
					// 迄今是否可以涂成同一种颜色
					ccol = ccol & msks[ne];
					if (!ccol) break;

					int clen = (ne - i + 1);
					if (clen < len) continue;
					// 涂色代价
					int cops = (clen + len - 1) / len;
					dp[ne + 1] = min(dp[ne + 1], dp[i] + cops * pushCost);
				}
			}
			ans = min(ans, dp[n] + len * stampCost);
		}
		return ans;
	}
};