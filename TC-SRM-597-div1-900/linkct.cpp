#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const LL MOD = 1000000007LL, MAXN = 2000005;

class LittleElephantAndBoard{
public:
	LL f[MAXN], inv[MAXN];
	inline LL C(int n, int m){return (f[n] * inv[m] % MOD) * inv[n - m] % MOD;}
	int getNumber(int n, int r, int g, int b){
		r = n - r, g = n - g, b = n - b;
		if(r < 0 || g < 0 || b < 0) return 0;
		if(r > g) swap(r, g);
		if(r > b) swap(r, b);
		if(g > b) swap(g, b);
		if(r == 0){
			if(n & 1) return abs(g - b) == 1 ? 2 : 0;
			return g == b ? 4 : 0;
		} int i, j, ans = 0;
		f[0] = f[1] = inv[0] = inv[1] = 1;
		for(i = 2; i <= 2 * n; ++ i){
			f[i] = f[i - 1] * i % MOD;
			inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
		}
		for(i = 2; i <= 2 * n; ++ i)
			(inv[i] *= inv[i - 1]) %= MOD;
		for(i = 0; i < r; ++ i)
			for(j = 0; j <= 2 && i + j <= g; ++ j)
				if(i + j > 0 && b >= r - 1 - i + g - i - j)
					ans = (ans + (C(r - 1, i) * C(2, j) * C(g - 1, (i + j) - 1) % MOD) * C(r + g + 1 - (r - 1 - i + g - i - j), b - (r - 1 - i + g - i - j))) % MOD;
		return ans * 2 % MOD;
	}
};
