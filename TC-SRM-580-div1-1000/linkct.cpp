#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55, INF = 1e9;

class WallGameDiv1{
public:
	int cost[MAXN][MAXN], pf[MAXN][MAXN], dp[MAXN][MAXN];
	int f[MAXN][MAXN][MAXN], g[MAXN][MAXN][MAXN], n, m;
	inline int sum(int x, int l, int r){return pf[x][r] - pf[x][l - 1];}
	int solvef(int x, int l, int r){
		int &cur = f[x][l][r];
		if(~cur) return cur;
		if(l == 1) return cur = INF;
		if(l == 2 && r == m) return cur = solve(x + 1, 1) + cost[x][1];
		return cur = max(min(solvef(x, l - 1, r), solveg(x, l - 1, r) + sum(x, l, r)), solve(x + 1, l - 1)) + cost[x][l - 1];
	}
	int solveg(int x, int l, int r){
		int &cur = g[x][l][r];
		if(~cur) return cur;
		if(r == m) return cur = INF;
		if(l == 1 && r == m - 1) return cur = solve(x + 1, m) + cost[x][m];
		return cur = max(min(solveg(x, l, r + 1), solvef(x, l, r + 1) + sum(x, l, r)), solve(x + 1, r + 1)) + cost[x][r + 1];
	}
	int solve(int r, int c){
		int &cur = dp[r][c];
		if(~cur) return cur;
		return cur = max(min(solvef(r, c, c), solveg(r, c, c)), solve(r + 1, c)) + cost[r][c];
	}
	int play(vector <string> c){
		int i, j, ans = INF;
		n = c.size(), m = c[0].length();
		for(i = 0; i < n; ++ i)
			for(j = pf[i + 1][0] = 0; j < m; ++ j){
				cost[i + 1][j + 1] = c[i][j] - '0';
				pf[i + 1][j + 1] = pf[i + 1][j] + cost[i + 1][j + 1];
			}
		if(m == 1){
			int sum = 0;
			for(i = 1; i <= n; ++ i) sum += cost[i][1];
			return sum;
		}
		memset(dp, -1, sizeof(dp));
		memset(f, -1, sizeof(f));
		memset(g, -1, sizeof(g));
		for(i = 1; i <= m; ++ i)
			dp[n][i] = cost[n][i];
		for(i = 1; i <= m; ++ i)
			ans = min(ans, solve(1, i));
		return ans;
	}
};
