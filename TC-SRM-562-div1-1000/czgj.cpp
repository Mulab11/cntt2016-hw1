/*
	Combinatorics
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for(int _r = r, i = l; i <= _r; ++i)
#define red(i, r, l) for(int _l = l, i = r; i >= _l; --i)
#define debug(x) cerr << #x << " = " << x << endl
#define MEM(x, y) memset(x, y, sizeof(x))
#define X first
#define Y second

using namespace std;
typedef long long LL;
typedef pair<int, int> PI;
typedef vector<int> VI;
const LL MOD = 1e9 + 9;
const int MAXN = 52;
vector<int> E[MAXN];
LL fac[MAXN], ifac[MAXN];
LL a[MAXN][MAXN], sz[MAXN][MAXN], t[MAXN][MAXN];
int dp[MAXN][MAXN][MAXN][MAXN];
bool vis[MAXN][MAXN];
int dis[MAXN][MAXN];
int n;
void dfs(int x, int fa){
	if (a[fa][x]) return;
	a[fa][x] = sz[fa][x] = 1;
	for (int y : E[x]) if (fa != y){
		dfs(y, x);
		sz[fa][x] += sz[x][y];
		a[fa][x] = a[fa][x] * a[x][y] % MOD * ifac[sz[x][y]] % MOD;
	}
	a[fa][x] = a[fa][x] * fac[sz[fa][x] - 1] % MOD;
}
void work(int x, int fa){
	if (vis[fa][x]) return;
	dp[fa][x][0][0] = vis[fa][x] = 1;
	int ss = 0;
	for (int y : E[x]) if (y != fa){
		work(y, x);
		MEM(t, 0);
		rep(i, 0, sz[x][y]) rep(j, 0, sz[x][y]) rep(k, 0, ss) rep(l, 0, ss)
			(t[i + k][j + l] += (LL)dp[x][y][i][j] * dp[fa][x][k][l] % MOD * ifac[i] % MOD * ifac[j] % MOD) %= MOD;
		ss += sz[x][y];
		rep(i, 0, ss) rep(j, 0, ss) dp[fa][x][i][j] = t[i][j];
	}
	rep(i, 0, sz[fa][x]) rep(j, 0, sz[fa][x])
		dp[fa][x][i][j] = (LL)dp[fa][x][i][j] * fac[i] % MOD * fac[j] % MOD;
	dp[fa][x][0][sz[fa][x]] = dp[fa][x][sz[fa][x]][0] = a[fa][x];
}
class InducedSubgraphs{
	public:
	InducedSubgraphs(){
		fac[0] = ifac[0] = ifac[1] = 1;
		rep(i, 2, 50) ifac[i] = (MOD - MOD / i) * ifac[MOD % i] % MOD;
		rep(i, 2, 50) ifac[i] = ifac[i - 1] * ifac[i] % MOD;
		rep(i, 1, 50) fac[i] = fac[i - 1] * i % MOD;
	}
	int getCount(VI e1, VI e2, int k){
		LL ret = 0;
		n = e1.size() + 1;
		if (k == 1) return fac[n]; // spj
		rep(i, 0, n - 2) E[e1[i]].push_back(e2[i]), E[e2[i]].push_back(e1[i]);
		rep(i, 0, n - 1) rep(j, 0, n - 1) dis[i][j] = i == j ? 0 : 23333;
		rep(i, 0, n - 1) for (int j : E[i]) dis[i][j] = 1;
		rep(i, 0, n - 1) dfs(i, n);
		rep(k, 0, n - 1) rep(i, 0, n - 1) rep(j, 0, n - 1) // floyd
			dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
		if (n >= 2 * k){ // case 1
			rep(i, 0, n - 1) rep(j, 0, n - 1)
				if (dis[i][j] == n - 2 * k + 1){
					int x, y;
					for (int k : E[i]) if (dis[k][j] < dis[i][j]) {x = k; break;}
					for (int k : E[j]) if (dis[k][i] < dis[j][i]) {y = k; break;}
					if (sz[x][i] == k && sz[y][j] == k) ret = (ret + a[x][i] * a[y][j]) % MOD;
				}
			return ret;
		}
		else{ // case 2
			rep(i, 0, n - 1) work(i, n);
			rep(i, 0, n - 1) ret = (ret + dp[n][i][n - k][n - k]) % MOD;
			ret = ret * fac[2 * k - n - 1] % MOD;
			return ret;
		}
	}
};

