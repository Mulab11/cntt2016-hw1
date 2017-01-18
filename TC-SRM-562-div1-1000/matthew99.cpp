#line 5 "InducedSubgraphs.cpp"
#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), _end_ = (b); i < _end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int oo = 0x3f3f3f3f;

const int Mod = 1e9 + 9;

const int maxn = 50;

int fac[maxn + 5], ifac[maxn + 5];

inline int fpm(LL b, int v, int m)
{
	b %= m;
	LL t = 1;
	for ( ; v; v >>= 1, (b *= b) %= m)
		if (v & 1) (t *= b) %= m;
	return t;
}

inline void prepare()
{
	fac[0] = 1;
	REP(i, 0, maxn) fac[i + 1] = (LL)fac[i] * (i + 1) % Mod;
	ifac[maxn] = fpm(fac[maxn], Mod - 2, Mod);
	for (int i = maxn - 1; i >= 0; --i) ifac[i] = (LL)ifac[i + 1] * (i + 1) % Mod;
}

int n, K;
vector<int> v[maxn + 5];

int dp[maxn + 5];

int sz[maxn + 5];
int Max[maxn + 5];

void pre_dfs(int x, int f = -1)
{
	sz[x] = 1;
	Max[x] = 0;
	for (auto y : v[x])
	{
		if (y == f) continue;
		pre_dfs(y, x);
		sz[x] += sz[y];
		chkmax(Max[x], sz[y]);
	}
}

inline void dfs(int x, int f = -1)
{
	sz[x] = 0, dp[x] = 1;
	for (auto y : v[x])
	{
		if (y == f) continue;
		dfs(y, x);
		dp[x] = (LL)dp[x] * dp[y] % Mod * ifac[sz[y]] % Mod;
		sz[x] += sz[y];
	}
	dp[x] = (LL)dp[x] * fac[sz[x]++] % Mod;
	if (sz[x] > K && SZ(v[x]) > 2) dp[x] = 0;
}

inline int work0()
{
	assert((K << 1) <= n);
	pre_dfs(0);
	vector<int> rt;
	REP(i, 0, n) 
	{
		chkmax(Max[i], n - sz[i]);
		if ((Max[i] << 1) <= n) rt.pb(i);
	}
	if (SZ(rt) == 1 && SZ(v[rt[0]]) > 2) return 0;
	if (SZ(rt) == 1)
	{
		assert(SZ(v[rt[0]]) == 2);
		int a = v[rt[0]][0], b = v[rt[0]][1], mid = rt[0];
		dfs(a, mid);
		dfs(b, mid);
		return ((LL)dp[a] * dp[b] << 1) % Mod;
	}
	assert(SZ(rt) == 2);
	int a = rt[0], b = rt[1];
	dfs(a, b), dfs(b, a);
	return ((LL)dp[a] * dp[b] << 1) % Mod;
}

int dp0[maxn + 5][maxn + 5][maxn + 5];

void dfs0(int x, int f = -1)
{
	memset(dp0[x], 0, sizeof dp0[x]);
	sz[x] = 1;
	dp0[x][0][0] = 1;
	for (auto y : v[x])
	{
		if (y == f) continue;
		dfs0(y, x);
		sz[x] += sz[y];
		static int tmp[maxn + 5][maxn + 5];
		memset(tmp, 0, sizeof tmp);
		REP(a, 0, K + 1) REP(b, 0, K + 1) if (dp0[x][a][b]) REP(c, 0, K - a + 1) REP(d, 0, K - b + 1) if (dp0[y][c][d])
			(tmp[a + c][b + d] += (LL)dp0[x][a][b] * dp0[y][c][d] % Mod * fac[a + c] % Mod * fac[b + d] % Mod * ifac[a] % Mod * ifac[b] % Mod * ifac[c] % Mod * ifac[d] % Mod) %= Mod;
		memcpy(dp0[x], tmp, sizeof dp0[x]);
	}
	if (sz[x] <= K) dp0[x][sz[x]][0] = dp0[x][0][sz[x]] = dp[x];
}

inline int work1() 
{
	assert((K << 1) > n);
	pre_dfs(0);
	int rt = -1;
	REP(i, 0, n) 
	{
		chkmax(Max[i], n - sz[i]);
		if ((Max[i] << 1) <= n) rt = i;
	} 
	assert(rt >= 0);
	dfs(rt);
	K = n - K;
	dfs0(rt);
	return (LL)dp0[rt][K][K] * fac[n - (K << 1)] % Mod;
}

class InducedSubgraphs
{
	public:
		int getCount(vector <int> edge1, vector <int> edge2, int k)
		{
			K = k;
			prepare();
			n = SZ(edge1) + 1;
			REP(i, 0, n) v[i].clear();
			REP(i, 0, n - 1) v[edge1[i]].pb(edge2[i]), v[edge2[i]].pb(edge1[i]);
			if (K == 1 || K == n) return fac[n];
			int ret = (K << 1) <= n ? work0() : work1();
			(ret += Mod) %= Mod;
			return ret;
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor


// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
