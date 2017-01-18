#line 5 "TPS.cpp"
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

const int maxn = 50;

int n;

bool f[maxn + 5][maxn + 5];
int deg[maxn + 5];

int fa[maxn + 5];

bool vis[maxn + 5];

void dfs(int x)
{
	REP(y, 0, n) if (y != fa[x] && f[x][y]) fa[y] = x, dfs(y);
}

class TPS
{
	public:
		int minimalBeacons(vector <string> linked)
		{
			n = SZ(linked);
			if (n == 1) return 0;
			memset(deg, 0, sizeof deg);
			memset(f, 0, sizeof f);
			REP(i, 0, n) REP(j, 0, n) if (linked[i][j] == 'Y') f[i][j] = 1, ++deg[i];
			int p = -1;
			REP(i, 0, n) if (deg[i] > 2) p = i;
			if (!~p) return 1;
			fa[p] = -1, dfs(p);
			int ret = 0;
			memset(vis, 0, sizeof vis);
			REP(i, 0, n) if (deg[i] == 1)
			{
				++ret;
				int u = i;
				while (~fa[u] && deg[u] <= 2) u = fa[u];
				if (!vis[u]) --ret, vis[u] = 1;
			}
			return ret;
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
