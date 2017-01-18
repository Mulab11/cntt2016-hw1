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

#define ctz __builtin_ctz
#define bcnt __builtin_popcount

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int oo = 0x3f3f3f3f;

const int maxn = 14, maxN = 13, max0 = 1600000;

int n, m;
int N;

int row[maxn + 5], col[maxn + 5];
bool ok[(1 << maxN) + 5];

vector<pair<int, int> > all;

int dp[max0 + 5];
int pw[maxN + 5];

class MagicalHats 
{
	public:
		int findMaximumReward(vector<string> g, vector<int> a, int K) 
		{
			n = SZ(g), m = SZ(g[0]);
			memset(row, 0, sizeof row), memset(col, 0, sizeof col);
			all.clear();
			REP(i, 0, n) REP(j, 0, m) if (g[i][j] == 'H') row[i] ^= 1, col[j] ^= 1, all.pb(mp(i, j));
			N = SZ(all);
			pw[0] = 1;
			REP(i, 0, N) pw[i + 1] = pw[i] * 3;
			sort(ALL(a));
			memset(ok, 0, sizeof ok);
			REP(mask, 0, 1 << N) if (bcnt(mask) == SZ(a))
			{
				static bool trow[maxn + 5], tcol[maxn + 5];
				memset(trow, 0, sizeof trow), memset(tcol, 0, sizeof tcol);
				REP(i, 0, N) if (mask >> i & 1) trow[all[i].x] ^= 1, tcol[all[i].y] ^= 1;
				ok[mask] = 1;
				REP(i, 0, n) if (trow[i] != row[i]) ok[mask] = 0;
				REP(i, 0, m) if (tcol[i] != col[i]) ok[mask] = 0;
			}
			a.resize(N);
			memset(dp, -1, sizeof dp);
			REP(i, 0, pw[N])
			{
				static int sta[maxN + 5];
				int tmp = 0;
				REP(j, 0, N) sta[j] = i / pw[j] % 3, tmp += sta[j] != 2;
				if (tmp == N)
				{
					int mask = 0;
					REP(j, 0, N) if (sta[j]) mask |= 1 << j;
					if (ok[mask]) dp[i] = 0;
				}
				else
				{
					int cnt = 0;
					REP(j, 0, N) if (sta[j] == 1) ++cnt;
					dp[i] = -1;
					REP(j, 0, N) if (sta[j] == 2) 
					{
						int u = dp[i - (pw[j] << 1)], v = dp[i - pw[j]];
						if (~v) v += (tmp >= K ? 0 : a[cnt]);
						if (!~u && !~v) continue;
						else if (~u && !~v) chkmax(dp[i], u);
						else if (!~u && ~v) chkmax(dp[i], v);
						else chkmax(dp[i], min(u, v));
					}
				}
			}
			int ret = dp[pw[N] - 1];
			return ret;
		}
};

// Powered by Greed 2.0-RC
