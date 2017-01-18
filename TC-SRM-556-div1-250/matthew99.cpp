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
const int maxw = 1024;

int n;
int w[maxn + 5];
vector<int> adj[maxn + 5];

int ans = 0;

bool vis[maxn + 5][maxw + 5];

void dfs(int x, int val)
{
	if (vis[x][val]) return;
	vis[x][val] = 1;
	chkmax(ans, val);
	for (auto y : adj[x]) dfs(y, val ^ w[y]);
}

class XorTravelingSalesman 
{
	public:
		int maxProfit(vector<int> cityValues, vector<string> roads) 
		{
			n = SZ(cityValues);
			REP(i, 0, n) w[i] = cityValues[i];
			REP(i, 0, n) adj[i].clear();
			REP(i, 0, n) REP(j, 0, n) if (roads[i][j] == 'Y') adj[i].pb(j);
			memset(vis, 0, sizeof vis);
			ans = 0;
			dfs(0, w[0]);
			return ans;
		}
};

// Powered by Greed 2.0-RC
