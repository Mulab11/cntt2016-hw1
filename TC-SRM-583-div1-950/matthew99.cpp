#line 5 "RandomPaintingOnABoard.cpp"
#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), _end_ = (b); i < _end_; ++i)
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

const int maxn = 21, max0 = 1500;

int n, m;

int a[maxn + 5][maxn + 5];

int val[maxn + 5];

double dp[maxn + 1][max0 + 5];
double cnt[max0 + 5];

class RandomPaintingOnABoard
{
	public:
		double expectedSteps(vector <string> prob)
		{
			n = SZ(prob), m = SZ(prob[0]);
			if (n < m) { swap(n, m); REP(i, 0, n) REP(j, 0, m) a[i][j] = prob[j][i] - '0'; }
			else REP(i, 0, n) REP(j, 0, m) a[i][j] = prob[i][j] - '0';
			int tot = 0;
			REP(i, 0, n) REP(j, 0, m) tot += a[i][j];
			memset(cnt, 0, sizeof cnt);
			REP(i, 0, 1 << m)
			{
				memset(dp, 0, sizeof dp);
				memset(val, 0, sizeof val);
				dp[0][0] = (__builtin_popcount(((1 << m) - 1) ^ i) & 1) ? 1 : -1;
				REP(j, 0, n) REP(k, 0, m) if (i >> k & 1) val[j] += a[j][k];
				REP(j, 0, n) REP(k, 0, tot + 1) if (dp[j][k]) 
				{
					dp[j + 1][k] -= dp[j][k];
					if (k + val[j] <= tot) dp[j + 1][k + val[j]] += dp[j][k];
				}
				REP(j, 0, tot + 1) cnt[j] += dp[n][j];
			}
			double ret = 0;
			REP(i, 0, tot) if (cnt[i]) ret += cnt[i] * tot / (tot - i);
			return ret;
		}


};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
