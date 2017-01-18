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

const int maxn = 60, maxm = 16;

int n, m;
int dp[(1 << maxm) + 5][maxm + 1];

int f[maxn + 5][maxn + 5];

int s[maxm + 5], t[maxm + 5], d[maxm + 5];

class TravellingPurchasingMan 
{
	public:
		int maxStores(int _n, vector<string> _a, vector<string> _b) 
		{
			n = _n;
			m = SZ(_a);
			REP(i, 0, m)
			{
				istringstream in(_a[i]);
				in >> s[i] >> t[i] >> d[i];
			}
			memset(f, oo, sizeof f);
			REP(i, 0, n) f[i][i] = 0;
			for (auto u : _b)
			{
				istringstream in(u);
				int x, y, w;
				in >> x >> y >> w;
				f[x][y] = f[y][x] = w;
			}
			REP(k, 0, n) REP(i, 0, n) REP(j, 0, n) chkmin(f[i][j], f[i][k] + f[k][j]);
			int ret = 0;
			memset(dp, oo, sizeof dp);
			dp[0][m] = 0;
			REP(i, 0, 1 << m) REP(j, 0, m + 1) if (dp[i][j] < oo)
			{
				chkmax(ret, bcnt(i));
				int now = (j == m ? n - 1 : j);
				REP(k, 0, m) if (!(i >> k & 1))
				{
					int tmp = dp[i][j] + f[now][k];
					if (tmp > t[k]) continue;
					chkmax(tmp, s[k]);
					tmp += d[k];
					chkmin(dp[i | (1 << k)][k], tmp);
				}
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
