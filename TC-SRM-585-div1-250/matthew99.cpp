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

const int Mod = 1e9 + 7;

const int maxn = 1000100;

int dp[maxn + 5][2];

class TrafficCongestion 
{
	public:
		int theMinCars(int n) 
		{
			memset(dp, oo, sizeof dp);
			dp[0][0] = dp[0][1] = 1;
			REP(i, 1, n + 1)
			{
				dp[i][0] = ((dp[i - 1][1] << 1) - 1) % Mod,
				dp[i][1] = (dp[i - 1][0] + dp[i - 1][1]) % Mod;
			}
			return (dp[n][0] + Mod) % Mod;
		}
};

// Powered by Greed 2.0-RC
