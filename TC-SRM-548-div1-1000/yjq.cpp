#include <bits/stdc++.h>

#define MOD 1000000007

using namespace std;

const int MAXN = 60;


int dp[MAXN][3][MAXN], g[MAXN][3][MAXN], C[MAXN * MAXN][MAXN * MAXN];

struct KingdomAndCities
{
	int howMany( int N, int M, int K )
	{
		int Limit = 1300;
		for ( int i = 0; i <= Limit; i++ )
		{
			C[i][0] = C[i][i] = 1;
			for ( int j = 1; j < i; j++ )
				C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
		}
		for ( int i = 1; i <= N; i++ )
			for ( int j = 0; j <= M && j <= i; j++ )
				for ( int k = 0; k <= K; k++ )
				{
					int x = i * (i - 1) / 2;
					if ( j == 0 )
						dp[i][j][k] = C[x][k];
					if ( j == 1 && k >= 2 )
						dp[i][j][k] = 1LL * (C[x - i + 1][k - 2]) * C[i - 1][2] % MOD;
					if ( j == 2 )
					{
						if ( k >= 4 )
							dp[i][j][k] = 1LL * (C[x - 2 * i + 3][k - 4]) * C[i - 2][2] % MOD * C[i - 2][2] % MOD;
						if ( k >= 3 )
							dp[i][j][k] = (1LL * (C[x - 2 * i + 3][k - 3]) * (i - 2) % MOD * (i - 2) % MOD + dp[i][j][k]) % MOD;
					}
					g[i][j][k] = dp[i][j][k];

					for ( int x = 1; x < i; x++ )
						for ( int y = 0; y <= k; y++ )
						{
							if ( j == 0 )
								dp[i][0][k] = ( (-1LL * (dp[x][0][y]) * g[i - x][0][k - y] % MOD * C[i - 1][x - 1] + dp[i][0][k]) % MOD + MOD) % MOD;
							if ( j == 1 )
								dp[i][1][k] = ( (-1LL * (dp[x][1][y]) * g[i - x][0][k - y] % MOD * C[i - 1][x - 1] + dp[i][1][k]) % MOD + MOD) % MOD;
							if ( j == 2 )
							{
								if ( x >= 2 )
									dp[i][2][k] = ( (-1LL * (dp[x][2][y]) * g[i - x][0][k - y] % MOD * C[i - 2][x - 2] + dp[i][2][k]) % MOD + MOD) % MOD;
								dp[i][2][k] = ( (-1LL * (dp[x][1][y]) * g[i - x][1][k - y] % MOD * C[i - 2][x - 1] + dp[i][2][k]) % MOD + MOD) % MOD;
							}
						}
				}
		return(dp[N][M][K]);
	}
};

