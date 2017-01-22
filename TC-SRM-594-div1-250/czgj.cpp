/*
	answer = n + m - max{LCS}
	Fix the ratio, and then do the LCS.
*/

#include <bits/stdc++.h>
using namespace std;

class AstronomicalRecords {
	public:
	int minimalPlanets(vector <int> A, vector <int> B) {
		int n = A.size(), m = B.size(), ret = 0;
		int dp[63][63]; memset(dp, 0, sizeof dp);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j){
				int a0 = A[i], b0 = B[j]; // Ratio = a0 : b0
				for (int k = 1; k <= n; ++k) // LCS dp
					for (int l = 1; l <= m; ++l){
						dp[k][l] = max(dp[k - 1][l], dp[k][l - 1]);
						if ((long long)a0 * B[l - 1] == (long long)b0 * A[k - 1]) dp[k][l] = max(dp[k - 1][l - 1] + 1, dp[k][l]);
					}
				if (ret < dp[n][m]) ret = dp[n][m];
			}
		ret = n + m - ret;
		return ret;
	}
};

/*
	Tooku no tsuki sama ni, yowaki na kimi ga
	'Tatte yaru sa' to sakendeita
	...sukoshi kakkoiikana maa
		- otsukimi recital
*/
