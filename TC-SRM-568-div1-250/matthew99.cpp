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

class BallsSeparating 
{
	public:
		int minOperations(vector<int> r, vector<int> g, vector<int> b) 
		{
			int n = SZ(r);
			bool has[3] = {0};
			REP(i, 0, n) if (r[i]) has[0] = 1;
			REP(i, 0, n) if (g[i]) has[1] = 1;
			REP(i, 0, n) if (b[i]) has[2] = 1;
			const int maxn = 60;
			static int dp[maxn + 5][8];
			memset(dp, oo, sizeof dp);
			dp[0][0] = 0;
			REP(i, 0, n) REP(j, 0, 8) if (dp[i][j] < oo)
			{
				chkmin(dp[i + 1][j | 1], dp[i][j] + g[i] + b[i]);
				chkmin(dp[i + 1][j | 2], dp[i][j] + r[i] + b[i]);
				chkmin(dp[i + 1][j | 4], dp[i][j] + r[i] + g[i]);
			}
			int ret = dp[n][has[0] | (has[1] << 1) | (has[2] << 2)];
			if (ret >= oo) return -1;
			return ret;
		}
};

// Powered by Greed 2.0-RC
