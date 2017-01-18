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

const int maxn = 360;

int n;
int dp[maxn + 5][maxn + 5];

inline void mul(int *a, int *b)
{
	static int ans[maxn + 5];
	memset(ans, 0, sizeof ans);
	REP(i, 0, n) if (a[i]) REP(j, 0, n) (ans[(i + j) % n] += (LL)a[i] * b[j] % Mod) %= Mod;
	memcpy(a, ans, sizeof ans);
}

class PenguinEmperor 
{
	public:
		int countJourneys(int _n, LL K) 
		{
			n = _n;
			memset(dp, 0, sizeof dp);
			dp[0][0] = 1;
			for (int i = 1; i <= n; ++i)
			{
				int u = i % n, v = n - i;
				REP(j, 0, n) if (dp[i - 1][j])
				{
					(dp[i][(j + u) % n] += dp[i - 1][j]) %= Mod;
					if (u != v) (dp[i][(j + v) % n] += dp[i - 1][j]) %= Mod;
				}
			}
			static int res[maxn + 5], tmp[maxn + 5];
			memset(res, 0, sizeof res);
			memcpy(tmp, dp[n], sizeof tmp);
			res[0] = 1;
			LL tmp0 = K / n;
			for ( ; tmp0; tmp0 >>= 1, mul(tmp, tmp)) if (tmp0 & 1) mul(res, tmp);
			mul(res, dp[K % n]);
			int ret = res[0];
			(ret += Mod) %= Mod;
			return ret;
		}
};

// Powered by Greed 2.0-RC
