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

const int maxn = 54;

int n;
bool dp[maxn + 5][maxn + 5][maxn * maxn + 5];

int d[maxn + 5];

class KingdomAndDice 
{
	public:
		double newFairness(vector<int> a, vector<int> b, int X) 
		{
			REP(i, 0, SZ(a)) if (!a[i]) a[i] = -1;
			sort(ALL(a)), sort(ALL(b));
			n = SZ(b);
			b.pb(X + 1);
			int lst = 0;
			REP(i, 0, n + 1)
			{
				d[i] = b[i] - lst - (lower_bound(ALL(a), b[i]) - lower_bound(ALL(a), lst)) - 1;
				lst = b[i];
			}
			int sum = 0, cnt = 0;
			REP(i, 0, n) if (~a[i]) ++cnt, sum += lower_bound(ALL(b), a[i]) - b.begin();
			memset(dp, 0, sizeof dp);
			dp[0][cnt][sum] = 1;
			int sqrn = n * n;
			REP(i, 0, n + 1) REP(j, 0, n + 1) REP(k, 0, sqrn + 1) if (dp[i][j][k]) REP(l, 0, min(n - j, d[i]) + 1) dp[i + 1][j + l][k + i * l] = 1;
			int ret = -1;
			int Min = oo;
			REP(i, 0, n + 1) REP(j, 0, sqrn + 1) if (dp[n + 1][i][j])
			{
				int tmp = abs((j << 1) - sqrn);
				if (chkmin(Min, tmp)) ret = j;
				else if (Min == tmp) chkmin(ret, j);
			}
			return ret / (double)sqrn;
		}
};

// Powered by Greed 2.0-RC
