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

const int maxn = 310;

template<typename T> inline void extract(const vector<string> &s, vector<T> &a)
{
	istringstream tmp(accumulate(ALL(s), string()));
	T x;
	a.clear();
	while (tmp >> x) a.pb(x);
}

int n, m;
vector<int> L, R;

class WolfInZooDivOne 
{
	public:
		int count(int _N, vector<string> _L, vector<string> _R) 
		{
			n = _N;
			extract(_L, L);
			extract(_R, R);
			m = SZ(L);
			static int Min[maxn + 5];
			REP(i, 0, n) Min[i] = i;
			REP(i, 0, m) REP(j, L[i], R[i] + 1) chkmin(Min[j], L[i]);
			static int dp[maxn + 5][maxn + 5];
			memset(dp, 0, sizeof dp);
			dp[0][0] = 1;
			REP(i, 0, n)
			{
				static int nxt[maxn + 5][maxn + 5];
				memset(nxt, 0, sizeof nxt);
				REP(j, 0, i + 1) REP(k, 0, j + 1) if (dp[j][k])
				{
					(nxt[j][k] += dp[j][k]) %= Mod;
					if (k <= Min[i]) (nxt[i + 1][j] += dp[j][k]) %= Mod;
				}
				memcpy(dp, nxt, sizeof dp);
			}
			int ret = 0;
			REP(i, 0, n + 1) REP(j, 0, i + 1) (ret += dp[i][j]) %= Mod;
			(ret += Mod) %= Mod;
			return ret;
		}
};

// Powered by Greed 2.0-RC
