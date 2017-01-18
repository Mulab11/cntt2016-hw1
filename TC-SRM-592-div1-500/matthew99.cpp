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

const int maxn = 50, maxk = 2500;

class LittleElephantAndPermutationDiv1 
{
	public:
		int getNumber(int n, int K) 
		{
			chkmax(K -= n, 0);
			static int dp[2][maxn + 5][maxk + 5];
			memset(dp, 0, sizeof dp);
			dp[0][0][0] = 1;
			REP(i, 0, n) 
			{
				int cur = i & 1;
				memset(dp[!cur], 0, sizeof dp[!cur]);
				REP(j, 0, i + 1) REP(k, 0, maxk + 1) if (dp[cur][j][k])
				{
					if (j) 
					{
						(dp[!cur][j - 1][k + (i << 1)] += (LL)dp[cur][j][k] * j % Mod * j % Mod) %= Mod;
						(dp[!cur][j][k + i] += (LL)dp[cur][j][k] * j % Mod) %= Mod;
					}
					(dp[!cur][j][k + i] += (LL)dp[cur][j][k] * (j + 1) % Mod) %= Mod;
					(dp[!cur][j + 1][k] += dp[cur][j][k]) %= Mod;
				}
			}
			int ret = 0;
			REP(i, K, maxk + 1) if (dp[n & 1][0][i]) (ret += dp[n & 1][0][i]) %= Mod;
			(ret += Mod) %= Mod;
			REP(i, 1, n + 1) ret = (LL)ret * i % Mod;
			return ret;
		}
};

// Powered by Greed 2.0-RC
