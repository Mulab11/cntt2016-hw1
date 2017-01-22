/*
	Math
	Expected value
	Inclusion-exclusion
	State-compressed dp
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MAXN = 23;
int a[MAXN][MAXN], s[MAXN];
int dp[MAXN * 100];
class RandomPaintingOnABoard {
	public:
	double expectedSteps(vector <string> prob) {
		int n = prob.size(), m = prob[0].size(), S = 0; long double ret = 0;
		rep(i, 0, n - 1) rep(j, 0, m - 1) S += (n < m ? a[i][j] : a[j][i]) = (prob[i][j] - '0');
		if (n > m) swap(n, m); // let n be the smaller one
		rep(i, 0, (1 << n) - 1){
			int s0 = 0; rep(j, 0, n - 1) if (i >> j & 1) rep(k, 0, m - 1) s0 += a[j][k]; // get row sum
			memset(dp, 0, sizeof dp); dp[s0] = __builtin_popcount(i) & 1 ? 1 : -1; // initial value
			rep(j, 0, m - 1){ // go over columns
				int ss = 0; rep(k, 0, n - 1) if (~i >> k & 1) ss += a[k][j]; // get sum of this column
				red(k, S, ss) dp[k] -= dp[k - ss]; // inclusion-exclusion knap-sack dp
			}
			rep(j, 1, S) ret += (long double) dp[j] * S / j; // magic formula
		}
		return ret;
	}
};

/*
	short and shorter
*/
