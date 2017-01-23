#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55, MOD = 1000000007;

class twoConvexShapes{
public:
	int n, m, f[MAXN][MAXN], ans; char g[MAXN][MAXN];
	inline void update(int &a, int b){if((a += b) >= MOD) a -= MOD;}
	int solve(){
		int i, j, k, ed, ret = 0;
		memset(f, 0, sizeof(f));
		for(j = 1; j <= m; ++ j)
			if(g[1][j] == 'B') break;
		ed = j - 1;
		for(j = m; j; -- j)
			if(g[1][j] == 'W') break;
		for(; j <= ed; ++ j) f[1][j] = 1;
		for(i = 2; i <= n; ++ i){
			for(j = 1; j <= m; ++ j)
				if(g[i][j] == 'B') break;
			ed = j - 1;
			for(j = m; j; -- j)
				if(g[i][j] == 'W') break;
			for(; j <= ed; ++ j)
				for(k = j; k <= m; ++ k)
					update(f[i][j], f[i - 1][k]);
		}
		for(j = 0; j <= m; ++ j) update(ret, f[n][j]);
		return ret;
	}
	int vert(){
		int i, j, ed;
		for(i = 1; i <= m; ++ i){
			for(j = 1; j <= n; ++ j)
				if(g[j][i] == 'B') break;
			if(j <= n) break;
		} ed = i - 1;
		for(i = m; i; -- i){
			for(j = 1; j <= n; ++ j)
				if(g[j][i] == 'W') break;
			if(j <= n) break;
		} return max(ed - i + 1, 0);
	}
	int hori(){
		int i, j, ed;
		for(i = 1; i <= n; ++ i){
			for(j = 1; j <= m; ++ j)
				if(g[i][j] == 'B') break;
			if(j <= m) break;
		} ed = i - 1;
		for(i = n; i; -- i){
			for(j = 1; j <= m; ++ j)
				if(g[i][j] == 'W') break;
			if(j <= m) break;
		} return max(ed - i + 1, 0);
	}
	int countWays(vector <string> grid){
		int i, j;
		n = grid.size(), m = grid[0].length();
		for(i = 0; i < n; ++ i)
			for(j = 0; j < m; ++ j)
				g[i + 1][j + 1] = grid[i][j];
		update(ans, solve());
		update(ans, MOD - vert());
		update(ans, MOD - hori());
		for(i = 1; i <= n; ++ i)
			for(j = 1; j <= m / 2; ++ j)
				swap(g[i][j], g[i][m - j + 1]);
		update(ans, solve());
		update(ans, MOD - vert());
		for(i = 1; i <= m; ++ i)
			for(j = 1; j <= n / 2; ++ j)
				swap(g[j][i], g[n - j + 1][i]);
		update(ans, solve());
		update(ans, MOD - hori());
		for(i = 1; i <= n; ++ i)
			for(j = 1; j <= m / 2; ++ j)
				swap(g[i][j], g[i][m - j + 1]);
		update(ans, solve());
		for(i = 1; i <= n; ++ i){
			for(j = 1; j <= m; ++ j)
				if(g[i][j] == 'W') break;
			if(j <= m) break;
		} if(i > n) update(ans, 1);
		for(i = 1; i <= n; ++ i){
			for(j = 1; j <= m; ++ j)
				if(g[i][j] == 'B') break;
			if(j <= m) break;
		} if(i > n) update(ans, 1);
		return ans;
	}
};
