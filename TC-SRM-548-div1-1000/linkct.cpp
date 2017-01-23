#include <cstdio>
typedef long long int LL;
const int MAXN = 55, MOD = 1000000007;

inline void update(int &a, int b){if((a += b) >= MOD) a -= MOD;}
class KingdomAndCities{
	public:
		int C[MAXN * MAXN][MAXN * MAXN], e[MAXN], f[MAXN][MAXN * MAXN];
		int howMany(int n, int s, int m){
			int i, j, k, l, ans = 0;
			if(m < n - 1 || m > n * (n - 1) / 2) return 0;
			for(i = 1; i <= n; ++ i) e[i] = i * (i - 1) / 2;
			for(i = 0; i <= e[n]; ++ i)
				for(j = C[i][0] = 1; j <= i; ++ j)
					if((C[i][j] = C[i - 1][j] + C[i - 1][j - 1]) >= MOD)
						C[i][j] -= MOD;
			for(f[1][0] = 1, i = 2; i <= n; ++ i) //Number of connected graphs with i node(s) & j edge(s)
				for(j = i - 1; j <= m && j <= e[i]; ++ j){
					f[i][j] = C[e[i]][j];
					for(k = 1; k < i; ++ k)
						for(l = k - 1; l <= j && l <= e[k]; ++ l)
							if((f[i][j] = (f[i][j] - (LL(f[k][l]) * C[e[i - k]][j - l] % MOD) * C[i - 1][k - 1]) % MOD) < 0LL)
								f[i][j] += MOD;
				}
			if(!s) return f[n][m];
			else if(s == 1){
				n -= 1, m -= 2;
				if(n < 0 || m < 0) return 0;
				for(i = 1; i < n; ++ i)
					for(j = i - 1; j <= m && j <= e[i]; ++ j)
						update(ans, ((LL(C[n - 1][i - 1]) * f[i][j] % MOD) * f[n - i][m - j] % MOD) * (i * (n - i)) % MOD);
				return (ans + LL(f[n][m]) * C[n][2]) % MOD;
			}else{
				if(n >= 2 && m >= 4){ //Case 1: no edge between two special nodes
					n -= 2, m -= 4;
					update(ans, LL(f[n][m]) * e[n] * e[n] % MOD);
					for(i = 1; i < n; ++ i)
						for(j = i - 1; j <= m && j <= e[i]; ++ j)
							update(ans, ((LL(C[n - 1][i - 1]) * f[i][j] % MOD) * f[n - i][m - j] % MOD) * (i * (n - i) * (i * (n - i) + (e[i] + e[n - i]) * 2)) % MOD);
					for(i = 1; i < n - 1; ++ i)
						for(j = i - 1; j <= m && j <= e[i]; ++ j)
							for(k = 1; i + k < n; ++ k)
								for(l = k - 1; j + l <= m && l <= e[k]; ++ l)
									//Three components: (i, j), (k, l), (n-i-k, m-j-l)
									update(ans, ((((LL(C[n - 1][i - 1]) * C[n - i - 1][k - 1] % MOD) * f[i][j] % MOD) * f[k][l] % MOD) * f[n - i - k][m - j - l] % MOD) * (i * k * (n - i - k) * n * 2) % MOD);
					n += 2, m += 4;
				}
				if(n >= 2 && m >= 3){ //Case 2: one edge between two special nodes
					n -= 2, m -= 3;
					update(ans, (LL(f[n][m]) * n * n) % MOD);
					for(i = 1; i < n; ++ i)
						for(j = i - 1; j <= m && j <= e[i]; ++ j)
							update(ans, ((LL(C[n - 1][i - 1]) * f[i][j] % MOD) * f[n - i][m - j] % MOD) * (i * (n - i) * 2) % MOD);
					n += 2, m += 3;
				} return ans;
			}
		}
};
