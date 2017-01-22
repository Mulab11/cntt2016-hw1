/*
	Manhattan --> Chebyshev
	Then big force dp.
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;

int dp[20][20][20][20];
bool vis[20][20][20][20], a[20][20];
int DP(int x0, int y0, int x1, int y1){
	if (x0 == x1 && y0 == y1) return 0;
	if (vis[x0][y0][x1][y1]) return dp[x0][y0][x1][y1];
	vis[x0][y0][x1][y1] = 1;
	int ret = 23333333;
	if (x0 < x1){ // more than one row
		int t = DP(x0 + 1, y0, x1, y1); // up
		rep(i, y0, y1) if (a[x0][i]) t += max(max(i - y0, y1 - i), x1 - x0);
		if (ret > t) ret = t;
		t = DP(x0, y0, x1 - 1, y1); // down
		rep(i, y0, y1) if (a[x1][i]) t += max(max(i - y0, y1 - i), x1 - x0);
		if (ret > t) ret = t;
	}
	if (y0 < y1){ // more than one column
		int t = DP(x0, y0 + 1, x1, y1); // left
		rep(i, x0, x1) if (a[i][y0]) t += max(max(i - x0, x1 - i), y1 - y0);
		if (ret > t) ret = t;
		t = DP(x0, y0, x1, y1 - 1); // right
		rep(i, x0, x1) if (a[i][y1]) t += max(max(i - x0, x1 - i), y1 - y0);
		if (ret > t) ret = t;
	}
	return dp[x0][y0][x1][y1] = ret;
}
class EllysChessboard {
	public:
	int minCost(vector <string> board) {
		memset(a, 0, sizeof a);
		memset(vis, 0, sizeof vis);
		rep(i, 0, 7) rep(j, 0, 7)
			if (board[i][j] == '#')
				a[i + j][i - j + 7] = 1; // some magical transformation
		return DP(0, 0, 16, 16);
	}
};

/*
	Justice rains from above
*/
