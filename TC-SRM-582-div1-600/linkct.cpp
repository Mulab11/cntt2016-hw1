#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const LL MOD = 1000000009LL;
const int MAXN = 1505;

class ColorfulBuilding{
public:
	int col[MAXN], tmp[MAXN], n, dp[MAXN][MAXN];
	LL sum[MAXN], cur[MAXN], f[MAXN], inv[MAXN];
	int count(vector <string> c1, vector <string> c2, int L){
		int i, j, ans = 0;
		for(i = 0; i < int(c1.size()); ++ i)
			for(j = 0; j < int(c1[i].length()); ++ j)
				col[++ n] = c1[i][j] * 256 + c2[i][j];
		for(i = 1; i <= n; ++ i) tmp[i] = col[i];
		sort(tmp + 1, tmp + 1 + n);
		for(i = 1; i <= n; ++ i)
			col[i] = lower_bound(tmp + 1, tmp + 1 + n, col[i]) - tmp;
		reverse(col + 1, col + 1 + n);
		f[0] = inv[0] = f[1] = inv[1] = 1;
		for(i = 2; i <= n; ++ i){
			f[i] = f[i - 1] * i % MOD;
			inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
		}
		for(i = 2; i <= n; ++ i)
			inv[i] = inv[i] * inv[i - 1] % MOD;
		memset(dp, 0, sizeof(dp));
		memset(cur, 0, sizeof(cur));
		cur[col[1]] = dp[1][1] = 1;
		for(i = 2; i <= n; ++ i)
			if(col[i] == col[1]){
				dp[1][i] = cur[col[1]] * f[i - 2] % MOD;
				(cur[col[1]] += dp[1][i] * inv[i - 1]) %= MOD;
			}
		for(i = 2; i <= L; ++ i){
			memset(sum, 0, sizeof(sum));
			memset(cur, 0, sizeof(cur));
			sum[0] = sum[col[i - 1]] = dp[i - 1][i - 1] * inv[i - 2] % MOD;
			for(j = i; j <= n; ++ j){
				dp[i][j] = (sum[0] - sum[col[j]] + MOD + cur[col[j]]) * f[j - 2] % MOD;
				(sum[col[j]] += dp[i - 1][j] * inv[j - 1]) %= MOD;
				(sum[0] += dp[i - 1][j] * inv[j - 1]) %= MOD;
				(cur[col[j]] += dp[i][j] * inv[j - 1]) %= MOD;
			}
		}
		for(i = L; i <= n; ++ i)
			ans = (ans + (dp[L][i] * f[n - 1] % MOD) * inv[i - 1]) % MOD;
		return ans;
	}
};
