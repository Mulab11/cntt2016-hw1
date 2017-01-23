#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const LL MOD = 1000000007LL;

class DefectiveAddition{
public:
	int count(vector <int> a, int m){
		int i, j, lo, bit, ans = 0, n, s;
		LL f[55][2], g[55][2]; n = a.size();
		for(i = 29; i >= 0; -- i){
			f[0][0] = f[0][1] = g[0][0] = g[0][1] = 0;
			if(a[0] & (1 << i)) //f[j][k]: Considering first j numbers, all reach maximum in digit i, xor sum of digit i is k
				f[0][1] = (a[0] & ((1 << i) - 1)) + 1, g[0][0] = s = 1;
			else f[0][0] = (a[0] & ((1 << i) - 1)) + 1, s = 0;
			for(j = 1; j < n; ++ j){ //g[j][k]: Considering first j numbers, at least one of them didn't reach maximum in digit i
				lo = (a[j] & ((1 << i) - 1)) + 1;
				if(a[j] & (1 << i)){
					f[j][0] = f[j - 1][1] * lo % MOD;
					f[j][1] = f[j - 1][0] * lo % MOD;
					g[j][0] = (g[j - 1][0] * (1 << i) + g[j - 1][1] * lo + f[j - 1][0]) % MOD;
					g[j][1] = (g[j - 1][1] * (1 << i) + g[j - 1][0] * lo + f[j - 1][1]) % MOD;
					s ^= 1;
				}else{
					f[j][0] = f[j - 1][0] * lo % MOD;
					f[j][1] = f[j - 1][1] * lo % MOD;
					g[j][0] = g[j - 1][0] * lo % MOD;
					g[j][1] = g[j - 1][1] * lo % MOD;
				}
			} bit = (m & (1 << i)) ? 1 : 0;
			(ans += g[n - 1][bit]) %= MOD;
			if(i == 0) (ans += f[n - 1][bit]) %= MOD;
			if(s != bit) break;
		} return ans;
	}
};
