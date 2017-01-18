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
LL dp[maxn + 5][(maxn << 1) + 5];

class MonstersValley 
{
	public:
		int minimumPrice(vector<long long> a, vector<int> b) 
		{
			n = SZ(a);
			memset(dp, -1, sizeof dp);
			dp[0][0] = 0;
			REP(i, 0, n)
			{
				REP(j, 0, i << 1 | 1) if (dp[i][j] >= 0)
				{
					chkmax(dp[i + 1][j + b[i]], dp[i][j] + a[i]);
					if (dp[i][j] >= a[i]) chkmax(dp[i + 1][j], dp[i][j]);
				}
			}
			REP(i, 0, n << 1 | 1) if (dp[n][i] >= 0) return i;
			return -1;
		}
};

// Powered by Greed 2.0-RC
