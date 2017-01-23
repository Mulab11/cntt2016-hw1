#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int MOD = 555555555;

class XorBoard{
public:
	int n, m, rc, cc, C[3005][3005];
	int solve(int i, int j){
		return (LL(C[n][i]) * C[m][j] % MOD) * (LL(C[(rc - i) / 2 + n - 1][n - 1]) * C[(cc - j) / 2 + m - 1][m - 1] % MOD) % MOD;
	}
	int count(int n_, int m_, int rc_, int cc_, int tot){
		int i, j, ans = 0;
		n = n_, m = m_, rc = rc_, cc = cc_;
		for(i = 0; i <= max(rc / 2 + n, cc / 2 + m); ++ i)
			for(j = C[i][0] = 1; j <= i; ++ j)
				if((C[i][j] = C[i - 1][j] + C[i - 1][j - 1]) >= MOD)
					C[i][j] -= MOD;
		for(i = rc & 1; i <= rc && i <= n; i += 2){ //Enumerate the number of rows which are selected odd times
			//For j as the number of columns, i * m + n * j - 2 * i * j = tot holds, leading to j = (tot - i * m) / (n - 2 * i)
			if(n == 2 * i && tot == i * m){
				for(j = cc & 1; j <= cc && j <= m; j += 2) //Enumerate all possible j
					if((ans += solve(i, j)) >= MOD)
						ans -= MOD;
			}else if(n != 2 * i && (tot - i * m) % (n - 2 * i) == 0){ //j subject to the constraint of tot is unique
				j = (tot - i * m) / (n - 2 * i);
				if(j < 0 || j > m || j > cc || (j & 1) != (cc & 1))
					continue;
				if((ans += solve(i, j)) >= MOD)
					ans -= MOD;
			}
		} return ans;
	}
};
