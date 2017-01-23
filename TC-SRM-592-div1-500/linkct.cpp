#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int MOD = 1000000007, MAXN = 55;

class LittleElephantAndPermutationDiv1{
public:
	int f[MAXN][MAXN][MAXN * MAXN];
	inline void update(int &a, int b){if((a += b) >= MOD) a -= MOD;}
	int getNumber(int n, int m){
		int i, j, k, ans = 0; LL cur;
		f[0][0][0] = 1;
		for(i = 0; i < n; ++ i)
			for(j = 0; j <= i; ++ j)
				for(k = 0; k <= i * i; ++ k){
					if((cur = f[i][j][k]) == 0) continue;
					//Place i at i
					update(f[i + 1][j][k + i + 1], cur);
					//Place i before i, and some larger number at i
					if(j) update(f[i + 1][j][k + i + 1], cur * j % MOD);
					//Place i before i, and some smaller number at i
					if(j) update(f[i + 1][j - 1][k + 2 * (i + 1)], cur * j * j % MOD);
					//Place i after i, and some larger number at i
					update(f[i + 1][j + 1][k], cur);
					//Place i after i, and some smaller number at i
					if(j) update(f[i + 1][j][k + i + 1], cur * j % MOD);
				}
		for(i = m; i <= n * n; ++ i)
			update(ans, f[n][0][i]);
		for(i = 1; i <= n; ++ i)
			ans = LL(ans) * i % MOD;
		return ans;
	}
};
