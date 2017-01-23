#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55;

class RockPaperScissors{
public:
	double dp[MAXN][MAXN][MAXN][4], C[MAXN][MAXN], p[MAXN][4];
	double bestScore(vector <int> rock, vector <int> paper, vector <int> scissors){
		int i, j, a, b, c, col, n; double ans = 0.0;
		n = rock.size();
		for(i = 0; i <= n; ++ i)
			for(C[i][0] = j = 1; j <= i; ++ j)
				C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
		memset(dp, 0, sizeof(dp));
		for(i = 0; i < n; ++ i){
			p[i + 1][1] = rock[i] / 300.0;
			p[i + 1][2] = paper[i] / 300.0;
			p[i + 1][3] = scissors[i] / 300.0;
		} dp[0][0][0][0] = 1.0;
		for(i = 1; i <= n; ++ i)
			for(a = i; a >= 0; -- a)
				for(b = i - a; b >= 0; -- b)
					for(c = i - a - b; c >= 0; -- c)
						for(col = (a + b + c == i ? 0 : 3); col >= 0; -- col){
							//Case 1: dice i is not the coming dice; the coming dice's outcome doesn't change
							if(a) dp[a][b][c][col] += dp[a - 1][b][c][col] * p[i][1];
							if(b) dp[a][b][c][col] += dp[a][b - 1][c][col] * p[i][2];
							if(c) dp[a][b][c][col] += dp[a][b][c - 1][col] * p[i][3];
							//Case 2: dice i is the coming dice
							if(col) dp[a][b][c][col] += dp[a][b][c][0] * p[i][col];
						}
		for(a = 0; a < n; ++ a)
			for(b = 0; a + b < n; ++ b)
				for(c = 0; a + b + c < n; ++ c)
					ans += max(dp[a][b][c][1] + dp[a][b][c][3] * 3, max(dp[a][b][c][2] + dp[a][b][c][1] * 3, dp[a][b][c][3] + dp[a][b][c][2] * 3)) / (C[n][a + b + c] * (n - a - b - c));
		return ans;
	}
};
