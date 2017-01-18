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
int a[maxn + 5], b[maxn + 5];

class SpellCards 
{
	public:
		int maxDamage(vector<int> level, vector<int> damage) 
		{
			n = SZ(level);
			REP(i, 0, n) a[i] = level[i], --a[i], b[i] = damage[i];
			reverse(a, a + n);
			reverse(b, b + n);
			int ret = 0;
			REP(t, 0, n)
			{
				static int dp[maxn + 5][maxn + 5];
				memset(dp, -oo, sizeof dp);
				dp[0][0] = 0;
				REP(i, 0, n) REP(j, 0, i + 1) if (dp[i][j] >= 0)
				{
					chkmax(dp[i + 1][j + 1], dp[i][j]);
					if (j >= a[i]) chkmax(dp[i + 1][j - a[i]], dp[i][j] + b[i]);
				}
				REP(i, 0, n + 1) chkmax(ret, dp[n][i]);
				rotate(a, a + 1, a + n);
				rotate(b, b + 1, b + n);
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
