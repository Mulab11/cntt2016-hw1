#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
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

const int maxn = 60, max0 = 64;

int n;
int fa[maxn + 5];
vector<int> adj[maxn + 5];

vector<int> sub[maxn + 5];

int sg[maxn + 5];

int sum[maxn + 5];

void dfs(int x)
{
	sub[x] = {x};
	sum[x] = 0;
	for (auto y : adj[x])
	{
		dfs(y);
		sum[x] ^= sg[y];
		copy(ALL(sub[y]), back_inserter(sub[x]));
	}
	static bool vis[max0 + 5];
	memset(vis, 0, sizeof vis);
	for (auto u : sub[x]) if (u != n)
	{
		int tmp = sum[x];
		while (u != x) tmp ^= sum[u] ^ sg[u], u = fa[u];
		vis[tmp] = 1;
	}
	for (sg[x] = 0; vis[sg[x]]; ++sg[x]);
}

class CirclesGame 
{
	public:
		string whoCanWin(vector<int> x, vector<int> y, vector<int> r) 
		{
			n = SZ(x);
			REP(i, 0, n + 1) adj[i].clear();
			REP(i, 0, n) 
			{
				fa[i] = n;
				REP(j, 0, n) if ((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]) < (r[i] - r[j]) * (r[i] - r[j]) && r[i] < r[j] && (fa[i] == n || r[j] < r[fa[i]])) fa[i] = j;
				adj[fa[i]].pb(i);
			}
			dfs(n);
			return sg[n] ? "Alice" : "Bob";
		}
};

// Powered by Greed 2.0-RC
