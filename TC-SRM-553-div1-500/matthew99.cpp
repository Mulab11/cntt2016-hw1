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

const int Mod = 1e9 + 7;

const int oo = 0x3f3f3f3f;

const int maxn = 60;

int n, m;

int a[maxn + 5][maxn + 5];

inline int work()
{
	static int dp[maxn + 5][maxn + 5];
	memset(dp, 0, sizeof dp);
	dp[0][0] = 1;
	REP(i, 0, n)
	{
		int l = 0, r = m;
		REP(j, 0, m) if (a[i][j] == 1) chkmin(r, j); else if (!a[i][j]) chkmax(l, j + 1);
		REP(j, 0, m + 1) if (dp[i][j]) REP(k, max(j, l), r + 1) (dp[i + 1][k] += dp[i][j]) %= Mod;
	}
	int ret = 0;
	REP(i, 0, m + 1) (ret += dp[n][i]) %= Mod;
	return ret;
}

class TwoConvexShapes 
{
	public:
		int countWays(vector<string> g) 
		{
			n = SZ(g), m = SZ(g[0]);
			REP(i, 0, n) REP(j, 0, m)
			{
				if (g[i][j] == '?') a[i][j] = -1;
				else if (g[i][j] == 'W') a[i][j] = 0;
				else a[i][j] = 1;
			}
			int ans = work();
			REP(i, 0, n) reverse(a[i], a[i] + m);
			(ans += work()) %= Mod;
			REP(i, 0, n) REP(j, 0, m) if (~a[i][j]) a[i][j] = !a[i][j];
			(ans += work()) %= Mod;
			REP(i, 0, n) reverse(a[i], a[i] + m);
			(ans += work()) %= Mod;
			REP(i, 1, m) REP(le, 0, 2)
			{
				int ri = !le;
				bool failed = 0;
				REP(j, 0, n)
				{
					REP(k, 0, i) if (~a[j][k] && a[j][k] != le) failed = 1;
					REP(k, i, m) if (~a[j][k] && a[j][k] != ri) failed = 1;
				}
				if (!failed) (--ans) %= Mod;
			}
			REP(i, 1, n) REP(up, 0, 2)
			{
				int dw = !up;
				bool failed = 0;
				REP(j, 0, m)
				{
					REP(k, 0, i) if (~a[k][j] && a[k][j] != up) failed = 1;
					REP(k, i, n) if (~a[k][j] && a[k][j] != dw) failed = 1;
				}
				if (!failed) (--ans) %= Mod;
			}
			REP(col, 0, 2)
			{
				bool failed = 0;
				REP(i, 0, n) REP(j, 0, m) if (~a[i][j] && a[i][j] != col) failed = 1;
				if (!failed) (ans -= 3) %= Mod;
			}
			(ans += Mod) %= Mod;
			return ans;
		}
};

// Powered by Greed 2.0-RC
