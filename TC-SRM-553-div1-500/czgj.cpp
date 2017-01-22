/*
	Dp && simple inclusion-exclusion
*/

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;
class TwoConvexShapes {
	public:
	int n, m;
	int L[233], R[233];
	long long dp[233][233][3];
	vector<string> reverse(vector<string> grid){ // B -> W; W -> B
		vector<string> ret(grid);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				if (grid[i][j] != '?') grid[i][j] = 'B' + 'W' - grid[i][j];
		return grid;
	}
	int count(vector<string> grid){
		for (int i = 0; i < n; ++i){
			L[i] = 0, R[i] = m;
			for (int j = 0; j < m; ++j) if (grid[i][j] == 'B') L[i] = j + 1;
			for (int j = m - 1; j >= 0; --j) if (grid[i][j] == 'W') R[i] = j;
		}
		memset(dp, 0, sizeof dp); // 0: equ; 1: inc; 2: dec;
		for (int i = 0; i < n; ++i){
			for (int j = L[i]; j <= R[i]; ++j) for (int k = 0; k < 3; ++k)
				dp[i][j][k] = i ? dp[i - 1][j][k] : 1;
			for (int j = 1; j <= m; ++j) (dp[i][j][1] += dp[i][j - 1][1]) %= MOD;
			for (int j = m - 1; j >= 0; --j) (dp[i][j][2] += dp[i][j + 1][2]) %= MOD;
		}
		int rowL = 1, rowR = n;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j){
				if (grid[i][j] == 'W') rowL = max(rowL, i + 1);
				if (grid[i][j] == 'B') rowR = min(rowR, i);
			}
		// ret = inc + dec - equ - row
		long long s = 0;
		for (int i = 0; i <= m; ++i) (s += dp[n - 1][i][0]) %= MOD;
		return (dp[n - 1][m][1] + dp[n - 1][0][2] - s - max(0, rowR - rowL + 1)) % MOD;
	}
	
	int countWays(vector <string> grid) {
		n = grid.size(); m = grid[0].length();
		return (count(grid) + count(reverse(grid))) % MOD;
	}
};

/*
	Anata wa kono gakkou ga suki desuka?
	Watashi wa totemo totemo suki desu...
		- Furukawa Nagisa
*/
