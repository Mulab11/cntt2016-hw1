#include <bits/stdc++.h>
using namespace std;
const int MAXN = 35;

class FoxAndFlowerShopDivOne{
public:
	int g[MAXN][MAXN], g_[MAXN][MAXN], c, cnt[MAXN][MAXN], ans, n, m;
	int mx[MAXN][MAXN * MAXN * 2], sum[MAXN][MAXN], cur[MAXN * MAXN * 2];
	inline void update(int &a, int b){if(a < b) a = b;}
	void solve(){
		int i, j, k, x, y;
		for(i = 1; i <= n; ++ i) //Preprocess prefix sum to support matrix sum & number of flowers query
			for(j = 1; j <= m; ++ j){
				sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + g[i][j];
				cnt[i][j] = cnt[i - 1][j] + cnt[i][j - 1] - cnt[i - 1][j - 1];
				if(g[i][j] != 0) cnt[i][j] ++;
			}
		memset(mx, 0xcf, sizeof(mx));
		for(i = n; i > 1; -- i){ //Preprocess all choices for the second matrix under the i-th borderline
			for(j = 0; j <= n * m * 2; ++ j)
				mx[i][j] = mx[i + 1][j];
			for(j = 1; j <= m; ++ j)
				for(x = i; x <= n; ++ x)
					for(y = j; y <= m; ++ y)
						update(mx[i][n * m + sum[x][y] - sum[i - 1][y] - sum[x][j - 1] + sum[i - 1][j - 1]], cnt[x][y] - cnt[i - 1][y] - cnt[x][j - 1] + cnt[i - 1][j - 1]);
		}
		memset(cur, 0xcf, sizeof(cur));
		for(i = 1; i < n; ++ i){
			for(j = 1; j <= m; ++ j) //Process the first matrix
				for(x = 1; x <= i; ++ x)
					for(y = 1; y <= j; ++ y)
						update(cur[n * m + sum[i][j] - sum[x - 1][j] - sum[i][y - 1] + sum[x - 1][y - 1]], cnt[i][j] - cnt[x - 1][j] - cnt[i][y - 1] + cnt[x - 1][y - 1]);
			for(j = 0; j <= 2 * n * m; ++ j) //Enumerate every legal combinations, update the answer
				for(k = max(2 * n * m - j - c, 0); k <= min(2 * n * m - j + c, 2 * n * m); ++ k)
					update(ans, cur[j] + mx[i + 1][k]);
		}
	}
	int theMaxFlowers(vector <string> inp, int k){
		int i, j; c = k, ans = -1;
		memset(g, 0, sizeof(g));
		n = inp.size(), m = inp[0].length();
		for(i = 0; i < n; ++ i)
			for(j = 0; j < m; ++ j)
				if(inp[i][j] == 'L') g[i + 1][j + 1] = 1;
				else if(inp[i][j] == 'P') g[i + 1][j + 1] = -1;
		solve(); //Enumerating horizontal borderlines
		for(i = 1; i <= n; ++ i)
			for(j = 1; j <= m; ++ j)
				g_[j][i] = g[i][j];
		swap(n, m); //Transpose the matrix to solve vertical scenario
		for(i = 1; i <= n; ++ i)
			for(j = 1; j <= m; ++ j)
				g[i][j] = g_[i][j];
		solve();
		return ans;
	}
};
