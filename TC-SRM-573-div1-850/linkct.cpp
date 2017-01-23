#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int MAXN = 100005;
const LL MOD = 1000000007LL;

class WolfPack{
public:
	LL f[MAXN], inv[MAXN]; int n, m; vector <int> x, y;
	inline LL C(int a, int b){return (f[a] * inv[b] % MOD) * inv[a - b] % MOD;}
	LL solve(vector <int> &pos){
		int i, j, mn, mx; LL ans = 0, cur;
		for(mn = mx = pos[0], i = 1; i < n; ++ i){
			mn = min(mn, pos[i]), mx = max(mx, pos[i]);
			if((pos[i] ^ pos[0]) & 1) return 0LL;
		}
		for(i = mx - m; i <= mn + m; i += 2){
			for(j = 0, cur = 1; j < n; ++ j)
				(cur *= C(m, (m + abs(i - pos[j])) / 2)) %= MOD;
			if((ans += cur) >= MOD) ans -= MOD;
		} return ans;
	}
	int calc(vector <int> x_, vector <int> y_, int m_){
		int i; n = x_.size(), m = m_;
		f[0] = f[1] = inv[0] = inv[1] = 1;
		for(i = 2; i <= m; ++ i){
			f[i] = f[i - 1] * i % MOD;
			inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
		}
		for(i = 2; i <= m; ++ i)
			(inv[i] *= inv[i - 1]) %= MOD;
		for(i = 0; i < n; ++ i){
			x.push_back(x_[i] - y_[i]);
			y.push_back(x_[i] + y_[i]);
		} return solve(x) * solve(y) % MOD;
	}
};
