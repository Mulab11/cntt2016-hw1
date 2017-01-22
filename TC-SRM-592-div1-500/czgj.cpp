/*
	Combinatorics
	(a little) tricky dp
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const LL MOD = 1e9 + 7;
const int MAXN = 55;
LL dp[2][MAXN][MAXN * MAXN];
class LittleElephantAndPermutationDiv1 {
	public:
	int getNumber(int n, int m) {
		bool p = 0; memset(dp, 0, sizeof dp); dp[0][0][0] = 1;
		// put first i numbers into the grid.
		// dp[j][k] = 2 * j columns with one number, (determined) sum = k
		// (i - j) * full, (2 * j) * half, (n - i - j) * empty
		rep(i, 0, n - 1){
			rep(j, 0, n) rep(k, 0, n * n) dp[!p][j][k] = 0; // clear
			rep(j, 0, i) rep(k, 0, i * i) if (dp[p][j][k]){ // put (i + 1) into the grid
				if (j) (dp[!p][j - 1][k + 2 * i + 2] += dp[p][j][k] * j * j) %= MOD; // 2 halves
				(dp[!p][j][k + i + 1] += dp[p][j][k] * (2 * j + 1) * (n - i - j)) %= MOD; // 1 half
				(dp[!p][j + 1][k] += dp[p][j][k] * (n - i - j) * (n - i - j - 1)) %= MOD; // no half
			}
			p ^= 1; // roll
		}
		LL ret = 0; rep(i, m, n * n) ret = (ret + dp[p][0][i]) % MOD;
		return ret;
	}
};

/*
	[Musou Tensei]
*/
