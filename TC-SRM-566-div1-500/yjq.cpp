#include <bits/stdc++.h>

#define MOD 1000000007 

typedef long long LL ; 

using namespace std;

int n ;

const int MAXN = 350 ; 

int dp[MAXN][MAXN] ; 

struct Matrix {
		int a[MAXN];
		Matrix() {
				memset(a, 0, sizeof(a));
		}
		Matrix operator * (const Matrix &ano) const {
				Matrix c;
				for(int i = 0; i < n; i ++) {
						for(int j = 0; j < n; j ++)
								c.a[(i + j) % n] = (c.a[(i + j) % n] + 1LL * a[i] * ano.a[j] % MOD) % MOD ; 
				}
				return c;
		}
};
class PenguinEmperor {
		public:
				int countJourneys(int N, LL m) {

						n = N;

						memset(dp, 0, sizeof dp) ; 

						dp[0][0] = 1;

						for(int i = 1; i <= n; i ++) {
								for(int j = 0; j < n; j ++)
										dp[i][j] = (i == n || (i << 1) == n ? dp[i - 1][(j + i) % n] : (dp[i - 1][(j + i) % n] + dp[i - 1][(j + n - i) % n]) % MOD);
						}
						Matrix ans, a;
						for(int i = 0; i < n; i ++) ans.a[i] = dp[m % n][i];
						for(int i = 0; i < n; i ++) a.a[i] = dp[n][i];
						m /= n;
						while (m) {
								if(m & 1) ans = ans * a;
								a = a * a;
								m >>= 1;
						}
						return ans.a[0];
				}
};
