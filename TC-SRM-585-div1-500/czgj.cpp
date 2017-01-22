/*
	Combinatorics
	(Knapsack?) dp
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MOD = 1000000007;
const int MAXN = 3333;
int dp[MAXN], inv[MAXN], ifac[MAXN], fac[MAXN], sum[MAXN];
int C(int n, int k){
	return n < k ? 0 : (LL)fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
}
class LISNumber {
	public:
	int count(vector <int> cardsnum, int K) {
		int n = cardsnum.size(), m = 0;
		rep(i, 0, n - 1) m += cardsnum[i], sum[i + 1] = sum[i] + cardsnum[i]; // prefix sum
		inv[1] = ifac[0] = ifac[1] = fac[0] = fac[1] = 1;
		rep(i, 2, m){ // Linear inversion
			inv[i] = (LL)(MOD - MOD / i) * inv[MOD % i] % MOD;
			fac[i] = (LL)fac[i - 1] * i % MOD;
			ifac[i] = (LL)ifac[i - 1] * inv[i] % MOD;
		}
		memset(dp, 0, sizeof dp);
		dp[0] = 1;
		rep(i, 0, n - 1) red(j, m, 0) if (dp[j]){ // now at i, has j seqs
			int tmp = dp[j]; // tmp
			rep(k, 0, cardsnum[i]){ // put k numbers at the end of k seqs
				int t = (LL)C(j, k) * C(sum[i] + cardsnum[i] - j, cardsnum[i] - k) % MOD * dp[j] % MOD;
				if (t) (dp[j + (cardsnum[i] - k)] += t) %= MOD;
			}
			dp[j] = (MOD + dp[j] - tmp) % MOD; // clear dp[j] in this way, because rep(k) modified dp[j]
		}
		return dp[K];
	}
};

/*
	Mata ka....
	Ii kagen ni shinasai yo...
*/
