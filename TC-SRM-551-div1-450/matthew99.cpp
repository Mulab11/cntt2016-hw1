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

const int maxn = 60;

int n;
bool g[maxn + 5][maxn + 5];

int dis[maxn + 5];
bool vis[maxn + 5];

class ColorfulWolves 
{
	public:
		int getmin(vector<string> _g) 
		{
			n = SZ(_g);
			REP(i, 0, n) REP(j, 0, n) g[i][j] = _g[i][j] == 'Y';
			memset(dis, oo, sizeof dis);
			dis[0] = 0;
			memset(vis, 0, sizeof vis);
			while (1)
			{
				int u = -1;
				REP(i, 0, n) if (!vis[i] && (!~u || dis[i] < dis[u])) u = i;
				if (!~u || dis[u] >= oo) break;
				vis[u] = 1;
				int cnt = 0;
				REP(i, 0, n) if (g[u][i]) chkmin(dis[i], dis[u] + (cnt++));
			}
			if (dis[n - 1] >= oo) return -1;
			return dis[n - 1];
		}
};

// Powered by Greed 2.0-RC
