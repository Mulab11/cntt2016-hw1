/*
	Combinatorics
	f[i][j] = first i buildings, j color blocks
	sum[j] = prefix sum
	g[i][j] = prefix sum for color i
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MAXN = 2333;
const int MOD = 1e9 + 9;
int col[MAXN], v[MAXN], sum[MAXN], inv[MAXN], fac[MAXN], ifac[MAXN];
int f[MAXN][MAXN], g[MAXN][MAXN];
class ColorfulBuilding {
	public:
	string splay(vector<string> &a){
		string ret;
		rep(i, 0, (int)a.size() - 1) ret += a[i];
		return ret;
	}
	int count(vector <string> color1, vector <string> color2, int L) {
		string st1 = splay(color1), st2 = splay(color2);
		int n = st1.size();
		rep(i, 1, n) col[i] = v[i] = st1[i - 1] * 256 + st2[i - 1];
		sort(v + 1, v + n + 1); int vn = unique(v + 1, v + n + 1) - v - 1;
		rep(i, 1, n) col[i] = lower_bound(v + 1, v + vn + 1, col[i]) - v;
		
		inv[1] = fac[0] = ifac[0] = fac[1] = ifac[1] = 1;
		rep(i, 2, n){
			inv[i] = (LL)(MOD - MOD / i) * inv[MOD % i] % MOD;
			fac[i] = (LL)fac[i - 1] * i % MOD;
			ifac[i] = (LL)ifac[i - 1] * inv[i] % MOD;
		}
		
		memset(f, 0, sizeof f);
		memset(sum, 0, sizeof sum);
		memset(g, 0, sizeof g);
		
		f[0][0] = 1; g[0][0] = sum[0] = fac[n - 1];
		rep(i, 1, n) red(j, min(i, L), 1){
			f[i][j] = ((LL)sum[j - 1] - g[col[i]][j - 1] + g[col[i]][j] + MOD) * ifac[n - i] % MOD;
			sum[j] = (sum[j] + (LL)f[i][j] * fac[n - i - 1]) % MOD;
			g[col[i]][j] = (g[col[i]][j] + (LL)f[i][j] * fac[n - i - 1]) % MOD;
		}
		return f[n][L];
	}
};

/*
	Chotto... Muzukashii kamo
*/
