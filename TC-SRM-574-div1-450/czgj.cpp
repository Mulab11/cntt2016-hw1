/*
	State-compressed dp
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
LL dp[1 << 18][20];
int lg2[1 << 18];
bool check(int mask, int i, int j){ // if i-j intersects some segment in mask.
	if (i > j) swap(i, j);
	bool m1 = (mask >> (i + 1)) & ((1 << (j - i - 1)) - 1); // mask between (i, j)
	bool m2 = (mask & ((1 << i) - 1)) || (mask >> (j + 1)); // mask of (1, i) && (j, n)
	return m1 && m2;
}
class PolygonTraversal {
	public:
	long long count(int n, vector <int> points) {
		int m = points.size(), mask = (1 << n) - 1, p0 = 0;
		memset(dp, 0, sizeof dp);
		rep(i, 0, m - 1) p0 |= 1 << (points[i] - 1);
		rep(i, 0, n - 1) lg2[1 << i] = i;
		dp[p0][points[m - 1] - 1] = 1;
		for (int i = (p0 + 1) | p0; i <= mask; i = (i + 1) | p0) // masks with subset p0
			for (int j = i; j; j ^= j & -j) // choose one
				for (int k = i ^ (j & -j); k; k ^= k & -k) // choose another one
					if (check(i, lg2[j & -j], lg2[k & -k])) // if ok
						dp[i][lg2[j & -j]] += dp[i ^ (j & -j)][lg2[k & -k]]; // upd
		LL ret = 0;
		rep(i, 0, n - 1) if (check(mask, i, points[0] - 1)) ret += dp[mask][i]; // judge the last one
		return ret;
	}
};

/*
	Boku wa
	Shinsekai no KAMI ni naru.
		- Yagami Light
*/

