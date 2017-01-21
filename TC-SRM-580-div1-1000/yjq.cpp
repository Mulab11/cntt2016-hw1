#include <bits/stdc++.h>

#define INF 1000000007 

using namespace std;

int n, m ;

const int MAXN = 60;

int a[MAXN][MAXN] ;

int S[MAXN][MAXN] ; 

int dp[MAXN][MAXN][MAXN][2] ; 

int Dodp(int x, int l, int r, int typ) {
		if (x == n - 1) return a[x][l];
		if (dp[x][l][r][typ] > 1000000000) {
				int p = typ ? r : l; 
				dp[x][l][r][typ] = a[x][p] + Dodp(x + 1, p, p, 0);
				if (l == 0 && r == m - 1) return dp[x][l][r][typ]; 
				int tmp = INF;
				if (r + 1 < m) tmp = min(tmp, Dodp(x, l, r + 1, 1) + S[x][r + 1] - S[x][p]);
				if (l) tmp = min(tmp, Dodp(x, l - 1, r, 0) + S[x][p + 1] - S[x][l]);
				if (tmp > dp[x][l][r][typ]) dp[x][l][r][typ] = tmp ; 
		}
		return dp[x][l][r][typ];
}
class WallGameDiv1 {
		public:
				int play(vector<string> s) {

						n = s.size(), m = s[0].length();
						
						memset(dp, 0x3f, sizeof dp) ; 
						for (int i = 0; i < n; i ++) for (int j = 0; j < m; j ++) a[i][j] = s[i][j] - '0';
						for (int i = 0; i < n; i ++) for (int j = 0; j < m; j ++) S[i][j + 1] = S[i][j] + a[i][j];
						int ans = INF;
						for (int i = 0; i < m; i ++) ans = min(ans, Dodp(0, i, i, 0));
						return ans ; 
				}
};
