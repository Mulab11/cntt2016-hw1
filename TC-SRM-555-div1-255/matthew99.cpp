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

#define ctz __builtin_ctzll
#define clz __builtin_clzll
#define bcnt __builtin_popcountll

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int oo = 0x3f3f3f3f;

const int maxn = 50;

const int num = 26;

int n;

int len[30];
LL pw[30];

class CuttingBitString 
{
	public:
		int getmin(string S) 
		{
			pw[0] = 1;
			REP(i, 0, num) pw[i + 1] = pw[i] * 5;
			REP(i, 0, num) len[i] = 64 - clz(pw[i]);
			LL x = 0;
			REP(i, 0, SZ(S)) (x <<= 1) |= S[i] - '0';
			n = SZ(S);
			static int dp[maxn + 5];
			memset(dp, oo, sizeof dp);
			dp[0] = 0;
			REP(i, 0, n) if (dp[i] < oo) 
				REP(j, 0, num) if (((x >> i) & ((1LL << len[j]) - 1)) == pw[j]) chkmin(dp[i + len[j]], dp[i] + 1);
			if (dp[n] >= oo) return -1;
			return dp[n];
		}
};

// Powered by Greed 2.0-RC
