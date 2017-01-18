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

const int maxn = 40;

int n;
vector<int> adj[maxn + 5];
LL dp[maxn + 5][(maxn << 1) + 5][2];

void dfs(int x, int f = -1)
{
	dp[x][maxn][0] = 1;
	dp[x][maxn + 1][1] = 1;
	for (auto y : adj[x]) if (y != f)
	{
		dfs(y, x);
		static LL tmp[(maxn << 1) + 5];
		memset(tmp, 0, sizeof tmp);
		REP(i, 0, maxn << 1) if (dp[x][i][0])
		{
			REP(j, 0, maxn << 1)
			{ 
				if (dp[y][j][0]) tmp[i + j - maxn] += dp[x][i][0] * dp[y][j][0];
				if (dp[y][j][1]) tmp[i + j - maxn] += dp[x][i][0] * dp[y][j][1];
			}
		}
		REP(i, 0, maxn << 1) dp[x][i][0] = tmp[i];
		memset(tmp, 0, sizeof tmp);
		REP(i, 0, maxn << 1) if (dp[x][i][1])
		{
			REP(j, 0, maxn << 1)
			{ 
				if (dp[y][j][0]) tmp[i + j - maxn] += (LL)dp[x][i][1] * dp[y][j][0];
				if (dp[y][j][1]) tmp[i + j - 2 - maxn] += (LL)dp[x][i][1] * dp[y][j][1];
			}
		}
		REP(i, 0, maxn << 1) dp[x][i][1] = tmp[i];
	}
}

class CentaurCompany 
{
	public:
		double getvalue(vector<int> a, vector<int> b) 
		{
			n = SZ(a) + 1;
			REP(i, 0, n) adj[i].clear();
			REP(i, 0, n - 1) --a[i], --b[i], adj[a[i]].pb(b[i]), adj[b[i]].pb(a[i]);
			memset(dp, 0, sizeof dp);
			dfs(0);
			LL ret = 0;
			REP(i, maxn + 3, maxn << 1) ret += (dp[0][i][0] + dp[0][i][1]) * (i - maxn - 2);
			ret <<= 1;
			return (double)ret / (1LL << n);
		}
};

// Powered by Greed 2.0-RC
