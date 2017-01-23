#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int MAXN = 1505;
const LL MOD = 1000000007LL;

class LISNumber{
public:
	LL f[MAXN * 2], inv[MAXN * 2], ans[MAXN];
	inline LL C(int n, int m){return (f[n] * inv[m] % MOD) * inv[n - m] % MOD;}
	int count(vector <int> cnt, int k){
		int i, j, sum = 0, mx = 0, n;
		n = cnt.size();
		for(i = 0; i < n; ++ i){
			sum += cnt[i];
			mx = max(mx, cnt[i]);
		}
		f[0] = inv[0] = f[1] = inv[1] = 1;
		for(i = 2; i <= sum + k; ++ i){
			f[i] = f[i - 1] * i % MOD;
			inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
		}
		for(i = 2; i <= sum + k; ++ i)
			(inv[i] *= inv[i - 1]) %= MOD;
		memset(ans, 0, sizeof(ans));
		for(i = mx; i <= k; ++ i){
			ans[i] = 1LL;
			for(j = 0; j < n; ++ j)
				(ans[i] *= C(i, cnt[j])) %= MOD;
			for(j = mx; j < i; ++ j)
				ans[i] = (((ans[i] - ans[j] * C(sum + i - j, sum)) % MOD) + MOD) % MOD;
		} return ans[k];
	}
};
