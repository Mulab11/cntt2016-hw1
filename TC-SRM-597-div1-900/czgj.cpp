/*
	Combinatorics
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MAXN = 1001100;
const int MOD = 1e9 + 7;
int inv[MAXN], fac[MAXN], ifac[MAXN], pow2[MAXN];
int C(int n, int m){
	return (LL)fac[n] * ifac[m] % MOD * ifac[n - m] % MOD;
}
LL calc(int n, int a, int b){ // Magic formula
	LL ret = 0;
	rep(i, 0, min(n, a)){
		int k = i + b - a, j = n - i - k, r = a - i - j;
		if (k < 0 || j < 0 || r < 0) continue;
		ret = (ret + (LL)C(n, i) * C(n - i, k) % MOD * pow2[j] % MOD * C(n + r - 1, n - 1)) % MOD;
	}
	return ret;
}
class LittleElephantAndBoard {
	public:
	int getNumber(int M, int R, int G, int B) {
		fac[0] = ifac[0] = pow2[0] = 1;
		rep(i, 1, M){
			inv[i] = i == 1 ? 1 : (LL)(MOD - MOD / i) * inv[MOD % i] % MOD;
			fac[i] = (LL)fac[i - 1] * i % MOD;
			ifac[i] = (LL)ifac[i - 1] * inv[i] % MOD;
			pow2[i] = pow2[i - 1] * 2 % MOD;
		}
		R = M - R; G = M - G; B = M - B;
		if (R < 0 || G < 0 || B < 0) return 0;
		return 2 * (calc(R, G, B) + calc(R - 1, G, B) + calc(B, R, G) + calc(B - 1, R, G) + calc(G, B, R) + calc(G - 1, B, R)) % MOD;
	}
};

/*
	Math can be very hard...
*/
