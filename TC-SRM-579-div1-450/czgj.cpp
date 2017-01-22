/*
	Shortest path
	State-compressed dp
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
int dp[1 << 16][16];
int l[60], r[60], t[60];
int g[60][60];
class TravellingPurchasingMan {
	public:
	int maxStores(int n, vector <string> stores, vector <string> roads) {
		int m = stores.size();
		rep(i, 0, m - 1){
			stringstream ss(stores[i]);
			ss >> l[i] >> r[i] >> t[i];
		}
		rep(i, 0, n - 1) rep(j, 0, n - 1) g[i][j] = i == j ? 0 : 1e9;
		rep(i, 0, (int)roads.size() - 1){
			int x, y, w;
			stringstream ss(roads[i]);
			ss >> x >> y >> w;
			g[x][y] = g[y][x] = w;
		}
		rep(k, 0, n - 1) rep(i, 0, n - 1) rep(j, 0, n - 1) // floyd
			g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
		memset(dp, 0x3f, sizeof dp); // fill with 1e9
		rep(i, 0, m - 1) if (g[n - 1][i] <= r[i]) dp[1 << i][i] = max(l[i], g[n - 1][i]) + t[i]; // init
		rep(i, 1, (1 << m) - 1) rep(j, 0, m - 1) rep(k, 0, m - 1) // dp
			if (dp[i][j] + g[j][k] <= r[k]) // j -> k && purchase at k
				dp[i | 1 << k][k] = min(dp[i | 1 << k][k], max(l[k], dp[i][j] + g[j][k]) + t[k]); // upd
		int ret = 0;
		rep(i, 0, (1 << m) - 1) rep(j, 0, m - 1) if (dp[i][j] < 1e9) ret = max(ret, __builtin_popcount(i)); // find ans
		return ret;
	}
};

/*
	Heian's Alien
	'Heian' is 'Peace' here... not 'Dark'...
*/
