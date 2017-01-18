#line 5 "CosmicBlocks.cpp"
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

const int maxn = 6;

int n, m;
int L, R;

int ans = 0;

int a[maxn + 1];

int all[maxn + 1];

vector<int> v[maxn + 1];
int mask[maxn + 1];

int tot = 0;

int deg[maxn + 1];
bool vis[maxn + 1];

void dfs(int x)
{
	if (tot > R) return;
	if (x == n)
	{
		++tot;
		return;
	}
	REP(i, 0, n) if (!deg[i] && !vis[i])
	{
		vis[i] = 1;
		for (auto j : v[i]) --deg[j];
		dfs(x + 1);
		for (auto j : v[i]) ++deg[j];
		vis[i] = 0;
	}
}

inline void doit()
{
	REP(i, 0, n) deg[i] = 0;
	REP(i, 0, n) for (auto j : v[i]) ++deg[j];
	REP(i, 0, n) if (a[i] < max(deg[i], SZ(v[i]))) return;
	REP(i, 0, m - 1)
	{
		for (int j = all[i]; j > 0; j = (j - 1) & all[i])
		{
			int tmp = 0;
			int need = 0;
			REP(k, 0, n) if (j >> k & 1) tmp |= mask[k], need += a[k] - SZ(v[k]);
			REP(k, 0, n) if (tmp >> k & 1) need -= a[k] - deg[k];
			if (need > 0) return;
		}
	}
	tot = 0;
	memset(vis, 0, sizeof vis);
	dfs(0);
	if (tot <= R && tot >= L) ++ans;
}

inline void work()
{
	vector<pair<int, int> > ed;
	REP(i, 0, m - 1) REP(j, 0, n) if (all[i] >> j & 1) REP(k, 0, n) if (all[i + 1] >> k & 1) ed.pb(mp(j, k));
	REP(i, 0, 1 << SZ(ed))
	{
		REP(j, 0, n) v[j].clear(), mask[j] = 0;
		REP(j, 0, SZ(ed)) if (i >> j & 1) v[ed[j].x].pb(ed[j].y), mask[ed[j].x] |= 1 << ed[j].y;
		bool flag = 1;
		REP(j, 0, n) if (!(all[m - 1] >> j & 1) && v[j].empty()) { flag = 0; break; }
		if (!flag) continue;
		doit();
	}
}

inline void go(int x, int res)
{
	if (!res)
	{
		m = x;
		work();
		return;
	}
	for (all[x] = res; all[x] > 0; all[x] = res & (all[x] - 1)) go(x + 1, res ^ all[x]);
}

class CosmicBlocks
{
	public:
		int getNumOrders(vector <int> blockTypes, int minWays, int maxWays)
		{
			n = SZ(blockTypes);
			REP(i, 0, n) a[i] = blockTypes[i];
			L = minWays, R = maxWays;
			ans = 0;
			go(0, (1 << n) - 1);
			return ans;
		}


};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
