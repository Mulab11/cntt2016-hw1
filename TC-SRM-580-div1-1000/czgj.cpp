/*
	Only block the position when Rabbit is there.
	Dp
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MAXN = 60;
int a[MAXN][MAXN], sum[MAXN][MAXN];
int f[MAXN][MAXN][MAXN][2];
bool vis[MAXN][MAXN][MAXN][2];
int n, m;
int dfs(int x, int l, int r, int pos){
	bool p = pos == l;
	if (x == n - 1) return a[x][pos]; // exit
	if (vis[x][l][r][p]) return f[x][l][r][p]; // memory
	vis[x][l][r][p] = 1;
	int f1 = dfs(x + 1, pos, pos, pos); // let it go
	if (l == 1 && r == m) return f[x][l][r][p] = f1 + a[x][pos]; // no more choice
	// block this position, Then it's Rabbit's turn to choose left or right
	int f2 = l > 1 ? dfs(x, l - 1, r, l - 1) + sum[x][pos - 1] - sum[x][l - 1] : 1e9; // left
	int f3 = r < m ? dfs(x, l, r + 1, r + 1) + sum[x][r] - sum[x][pos] : 1e9; // right
	return f[x][l][r][p] = a[x][pos] + max(f1, min(f2, f3));
}
class WallGameDiv1 {
	public:
	int play(vector <string> costs) {
		memset(vis, 0, sizeof vis);
		n = costs.size(); m = costs[0].size();
		rep(i, 0, n - 1) rep(j, 1, m) a[i][j] = costs[i][j - 1] - '0';
		rep(i, 0, n - 1) rep(j, 1, m) sum[i][j] = sum[i][j - 1] + a[i][j];
		int ret = 1e9;
		rep(i, 1, m) ret = min(ret, dfs(0, i, i, i));
		return ret;
	}
};

/*
	Gochuumon wa usagi desuka?
*/
