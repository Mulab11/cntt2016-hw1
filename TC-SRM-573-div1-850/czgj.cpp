/*
	rotate the axes
	easy combinatorics
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;

class WolfPack {
	public:
	static const LL MOD = 1000000007;
	static const int NN = 123456;
	LL fac[NN], ifac[NN];
	int n;
	LL C(int n, int k){
		if (k > n || k < 0) return 0;
		return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
	}
	WolfPack(){
		ifac[0] = ifac[1] = fac[0] = 1;
		rep(i, 2, NN - 1) ifac[i] = (MOD - MOD / i) * ifac[MOD % i] % MOD;
		rep(i, 1, NN - 1) ifac[i] = ifac[i] * ifac[i - 1] % MOD, fac[i] = fac[i - 1] * i % MOD;
	}
	LL calc(const vector<int> &x, int m){
		LL ret = 0;
		rep(x0, -200000, 200000){
			LL r0 = 1;
			rep(i, 0, n - 1){
				int k = m + x[i] - x0;
				if (k & 1) {r0 = 0; break;}
				r0 = r0 * C(m, k / 2) % MOD;
			}
			ret = (ret + r0) % MOD;
		}
		return ret;
	}
	int calc(vector <int> x, vector <int> y, int m) {
		n = x.size();
		rep(i, 0, n - 1) x[i] += y[i], y[i] = x[i] - 2 * y[i];
		return calc(x, m) * calc(y, m) % MOD;
	}
};

/*
	850???
*/
