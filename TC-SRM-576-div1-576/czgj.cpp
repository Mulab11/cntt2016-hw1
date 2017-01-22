/*
	dp
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const LL MOD = 1e9 + 9;
const int MAXN = 330;
int a[MAXN], sum[MAXN], n;
LL f[MAXN][MAXN], sf[MAXN][MAXN], g[MAXN][MAXN]; 
class TheExperiment {
	public:
	int countPlacements(vector <string> intensity, int m, int L, int A, int B) {
		memset(sf, 0, sizeof sf); memset(f, 0, sizeof f); memset(g, 0, sizeof g); n = 0; // all.clear()
		rep(i, 0, (int)intensity.size() - 1)
			rep(j, 0, (int)intensity[i].size() - 1)
				a[++n] = intensity[i][j] - '0'; // read
		rep(i, 1, n) sum[i] = sum[i - 1] + a[i];
		rep(i, 0, n) sf[i][0] = 1;
		rep(i, 1, n) rep(j, 1, m){ // dp
			rep(k, 1, L - 1) if (k <= i && A <= sum[i] - sum[i - k] && sum[i] - sum[i - k] <= B){ // length < L
				f[i][j] = (f[i][j] + f[i - k][j - 1]) % MOD;
				g[i][j] = (g[i][j] + g[i - k][j - 1] + (i > k ? sf[i - k - 1][j - 1] : j == 1)) % MOD;
			}
			if (i >= L && A <= sum[i] - sum[i - L] && sum[i] - sum[i - L] <= B) // length = L
				f[i][j] = (f[i][j] + sf[i - L][j - 1] + g[i - L][j - 1]) % MOD;
			sf[i][j] = (sf[i - 1][j] + f[i][j]) % MOD;
		}
		return sf[n][m];
	}
};

/*
	IOSYS - Pointsettia
*/
