#include <bits/stdc++.h>

#define MOD 1000000007  

using namespace std;

int n, m ;

const int MAXN = 100010 ; 

int  inv[MAXN], Fac[MAXN];

int Get(vector<int> x) {
		sort(x.begin(), x.end());
		int ans = 0;
		for (int i = x[n - 1] - m; i <= x[0] + m; i ++) {
				int mul = 1;
				for(int j = 0; j < n; j ++) {
						if((m + i - x[j]) & 1) mul = 0;
						else mul = 1LL * mul * Fac[(m + i - x[j]) / 2] % MOD;
				}
				ans = (ans + mul) % MOD;
		}
		return ans;
}
class WolfPack {
		public:
				int calc(vector<int> x, vector<int> y, int M) {
						n = x.size(), m = M;
						for(int i = 0; i < n; i ++) {
								int tx = x[i], ty = y[i];
								x[i] = tx + ty, y[i] = tx - ty;
						}
						inv[1] = 1;
						for(int i = 2; i <= m; i ++) {
								inv[i] = -1LL * (MOD / i) * inv[MOD % i] % MOD;
								if(inv[i] < 0) inv[i] += MOD;
						}
						Fac[0] = 1;
						for(int i = 1; i <= m; i++) Fac[i] = 1LL * Fac[i - 1] * (m - i + 1) % MOD * inv[i] % MOD;
						return 1LL * Get(x) * Get(y) % MOD; 
				}
};
