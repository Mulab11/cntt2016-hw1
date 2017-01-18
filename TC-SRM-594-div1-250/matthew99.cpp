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

const int maxn = 52;

class AstronomicalRecords 
{
	public:
		int minimalPlanets(vector<int> a, vector<int> b) 
		{
			static int dp[maxn + 5][maxn + 5][maxn + 5][maxn + 5];
			int n = SZ(a), m = SZ(b);
			a.pb(0), b.pb(0);
			rotate(a.begin(), a.end() - 1, a.end());
			rotate(b.begin(), b.end() - 1, b.end());
			memset(dp, oo, sizeof dp);
			dp[0][0][0][0] = 0;
			int ret = oo;
			REP(i, 0, n + 1) REP(j, 0, m + 1) REP(k, 0, i + 1) REP(l, 0, j + 1)
			{
				if (i == n && j == m) chkmin(ret, dp[i][j][k][l]);
				else
				{
					if (i < n) chkmin(dp[i + 1][j][k][l], dp[i][j][k][l] + 1);
					if (j < m) chkmin(dp[i][j + 1][k][l], dp[i][j][k][l] + 1);
					if (i < n && j < m && (LL)a[i + 1] * b[l] == (LL)b[j + 1] * a[k]) chkmin(dp[i + 1][j + 1][i + 1][j + 1], dp[i][j][k][l] + 1);
				}
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
