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

const int maxn = 12, max0 = 130;

int n;
int dp[(1 << maxn) + 5][max0 + 5];

class KeyDungeonDiv1 
{
	public:
		int maxKeys(vector<int> a, vector<int> b, vector<int> wa, vector<int> wb, vector<int> wc, vector<int> num) 
		{
			n = SZ(a);
			int ret = 0;
			memset(dp, oo, sizeof dp);
			dp[0][0] = 0;
			REP(i, 0, 1 << n) REP(j, 0, max0 + 1) if (dp[i][j] < oo)
			{
				int na = num[0], nb = num[1], nc = num[2];
				int tot = 0;
				REP(k, 0, n) if (i >> k & 1) na += wa[k], nb += wb[k], nc += wc[k], tot += a[k] + b[k];
				na -= j;
				nb -= tot - (dp[i][j] + j);
				nc -= dp[i][j];
				chkmax(ret, na + nb + nc);
				REP(k, 0, n) if (!(i >> k & 1))
				{
					int need = max(0, a[k] - na) + max(0, b[k] - nb);
					if (nc >= need) chkmin(dp[i | (1 << k)][j + min(na, a[k])], dp[i][j] + need);
				}
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
