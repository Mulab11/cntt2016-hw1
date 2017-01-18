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
vector<int> adj[maxn + 5];

int a[maxn + 5], b[maxn + 5];

int dp[maxn + 5][2];

void dfs(int x)
{
	dp[x][0] = 0, dp[x][1] = 1;
	for (auto y : adj[x]) 
	{
		dfs(y);
		int nxt[2] = {oo, oo};
		REP(i, 0, 2) REP(j, 0, 2) chkmin(nxt[i ^ j], dp[x][i] + dp[y][j]);
		memcpy(dp[x], nxt, sizeof dp[x]);
	}
	if (b[x]) dp[x][a[x]] = oo;
}

class TurnOnLamps 
{
	public:
		int minimize(vector<int> roads, string initState, string isImportant) 
		{
			n = SZ(roads) + 1;
			REP(i, 0, n) adj[i].clear();
			b[0] = 1, a[0] = 1;
			REP(i, 1, n) adj[roads[i - 1]].pb(i), a[i] = initState[i - 1] - '0', b[i] = isImportant[i - 1] - '0';
			dfs(0);
			return min(dp[0][0], dp[0][1]) >> 1;
		}
};

// Powered by Greed 2.0-RC
