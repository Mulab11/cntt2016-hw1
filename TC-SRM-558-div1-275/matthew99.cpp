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

class Stamp 
{
	public:
		int getMinimumCost(string a, int b, int c) 
		{
			int n = SZ(a);
			static bool ok[maxn + 5][maxn + 5];
			memset(ok, 0, sizeof ok);
			REP(i, 0, n) REP(j, i + 1, n + 1)
			{
				ok[i][j] = 1;
				REP(u, i, j) if (a[u] != '*') REP(v, i, u) if (a[v] != '*' && a[u] != a[v]) ok[i][j] = 0;
			}
			int ret = oo;
			for (int i = 1; i <= n; ++i)
			{
				static int dp[maxn + 5];
				memset(dp, oo, sizeof dp);
				dp[0] = 0;
				REP(j, 0, n) if (dp[j] < oo)
					REP(k, j + i, n + 1) if (ok[j][k]) chkmin(dp[k], dp[j] + (k - j + i - 1) / i);
				if (dp[n] < oo) chkmin(ret, i * b + dp[n] * c);
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
