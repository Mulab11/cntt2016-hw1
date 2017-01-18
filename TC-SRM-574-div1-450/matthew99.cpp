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

const int maxn = 18;

int n;
LL dp[(1 << maxn) + 5][maxn + 5];

class PolygonTraversal 
{
	public:
		long long count(int _n, vector<int> a) 
		{
			n = _n;
			int S = 0;
			for (auto &u : a) --u, S |= 1 << u;
			int s = a[0], t = a.back();
			memset(dp, 0, sizeof dp);
			dp[S][t] = 1;
			REP(i, 0, 1 << n) REP(j, 0, n) if (dp[i][j])
				REP(k, 0, n) if ((i == (1 << n) - 1 && k == s) || !(i >> k & 1))
				{
					int u = j, mask = i;
					while (u != k) mask &= ~(1 << u), (++u) %= n;
					(mask |= (1 << j) | (1 << k)) &= i;
					if (mask == i) continue;
					mask &= ~(1 << j) & ~(1 << k);
					if (!mask) continue;
					dp[i | (1 << k)][k] += dp[i][j];
				}
			return dp[(1 << n) - 1][s];
		}
};

// Powered by Greed 2.0-RC
