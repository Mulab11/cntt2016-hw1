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

inline int fpm(LL b, int e, int m)
{
	b %= m;
	LL t = 1;
	for ( ; e; e >>= 1, (b *= b) %= m)
		if (e & 1) (t *= b) %= m;
	return t;
}

const int Mod = 1e9 + 9;

const int maxn = 1300;
const int maxc = 2750;

int n;
int a[maxn + 5];

inline int get(const char &x)
{
	if (x >= 'a') return x - 'a';
	return x - 'A' + 26;
}

int inv[maxn + 5];

class ColorfulBuilding 
{
	public:
		int count(vector<string> color1, vector<string> color2, int L) 
		{
			string c1 = accumulate(ALL(color1), string());
			string c2 = accumulate(ALL(color2), string());
			n = SZ(c1);
			REP(i, 1, n) inv[i] = fpm(i, Mod - 2, Mod);
			REP(i, 0, n) a[i] = get(c1[i]) * 52 + get(c2[i]);
			static int dp[maxn + 5][maxn + 5];
			memset(dp, 0, sizeof dp);
			int tmp = 1;
			REP(i, 1, n) tmp = (LL)tmp * i % Mod;
			static int num[maxn + 5][maxc + 5];
			memset(num, 0, sizeof num);
			dp[n - 1][1] = tmp;
			(num[1][a[n - 1]] += tmp) %= Mod;
			(num[1][maxc] += tmp) %= Mod;
			for (int i = n - 2; i >= 0; --i) REP(j, 1, n - i + 1)
			{
				dp[i][j] = ((LL)num[j - 1][maxc] - num[j - 1][a[i]] + num[j][a[i]]) * inv[n - i - 1] % Mod;
				(num[j][a[i]] += dp[i][j]) %= Mod;
				(num[j][maxc] += dp[i][j]) %= Mod;
			}
			int ret = 0;
			REP(i, 0, n) (ret += dp[i][L]) %= Mod;
			(ret += Mod) %= Mod;
			return ret;
		}
};

// Powered by Greed 2.0-RC
