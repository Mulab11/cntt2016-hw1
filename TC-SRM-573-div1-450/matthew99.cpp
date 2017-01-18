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
const LL OO = 0x3f3f3f3f3f3f3f3fLL;

const int maxn = 60;

int n;
int a[maxn + 5];
vector<int> adj[maxn + 5];

LL dis[maxn + 5];

class SkiResorts 
{
	public:
		long long minCost(vector<string> g, vector<int> _a) 
		{
			n = SZ(g);
			REP(i, 0, n) a[i] = _a[i];
			REP(i, 0, n)
			{
				adj[i].clear();
				REP(j, 0, n) if (g[i][j] == 'Y') adj[i].pb(j);
			}
			vector<int> v(_a);
			sort(ALL(v), greater<int>());
			memset(dis, oo, sizeof dis);
			for (auto u : v)
			{
				static bool vis[maxn + 5];
				memset(vis, 0, sizeof vis);
				chkmin(dis[0], (LL)abs(a[0] - u));
				while (1)
				{
					int x = -1;
					REP(i, 0, n) if (!vis[i] && dis[i] < OO && (!~x || dis[i] < dis[x])) x = i;
					if (!~x) break;
					vis[x] = 1;
					for (auto y : adj[x]) chkmin(dis[y], dis[x] + abs(a[y] - u));
				}
			}
			if (dis[n - 1] >= OO) return -1;
			return dis[n - 1];
		}
};

// Powered by Greed 2.0-RC
