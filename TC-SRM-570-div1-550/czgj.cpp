/*
	Expected value
	Tree dp
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MAXN = 127;
int hd[MAXN], to[MAXN], nxt[MAXN], tl;
void ae(int u, int v){
	++tl; to[tl] = v; nxt[tl] = hd[u]; hd[u] = tl;
}
int n;
LL dp[40][40][40][2];
class CentaurCompany {
	public:
	void dfs(int p, int f = 0){
		dp[p][0][0][0] = dp[p][1][1][1] = 1;
		for (int i = hd[p]; i; i = nxt[i])
			if (to[i] != f){
				dfs(to[i], p);
				red(j, n, 0) red(k, n, 0){
					LL r0 = 0, r1  = 0;
					red(l, j, 0) red(m, k, 0){
						r0 += (dp[to[i]][j - l][k - m][0] + dp[to[i]][j - l][k - m][1]) * dp[p][l][m][0];
						r1 += (dp[to[i]][j - l][k - m][0] + dp[to[i]][j - l + 1][k - m][1]) * dp[p][l][m][1];
					}
					dp[p][j][k][0] = r0; dp[p][j][k][1] = r1;
				}
			}
	}
	double getvalue(vector <int> a, vector <int> b) {
		n = a.size() + 1; LL ret = 0;
		memset(hd, 0, sizeof hd); tl = 0;
		rep(i, 0, n - 2) ae(a[i], b[i]), ae(b[i], a[i]);
		memset(dp, 0, sizeof dp); dfs(1);
		rep(i, 0, n) rep(j, 0, n) ret += max(0, i * 2 - j - 2) * (dp[1][i][j][0] + dp[1][i][j][1]);
		return 2.0 * ret / (1ll << n);
	}
};

/*
	Look to the sky, way up on high
	There in the night stars now are right
	They will return
		- The Carol of the Old Ones
*/
