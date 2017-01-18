#line 5 "RockPaperScissors.cpp"
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

const double eps = 1e-15;

const int oo = 0x3f3f3f3f;

const int maxn = 50;

int n;

double dp[2][maxn + 5][maxn + 5][maxn + 5][4];

double C[maxn + 5][maxn + 5];

class RockPaperScissors
{
	public:
		double bestScore(vector <int> a, vector <int> b, vector <int> c)
		{
			static double P[maxn + 5][3];
			n = SZ(a);
			REP(i, 0, n + 1)
			{
				C[i][0] = 1;
				REP(j, 1, i + 1) C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
			}
			memset(dp, 0, sizeof dp);
			dp[0][0][0][0][3] = 1;
			double inv300 = 1.0 / 300;
			REP(i, 0, n) P[i][0] = a[i] * inv300, P[i][1] = b[i] * inv300, P[i][2] = c[i] * inv300;
			REP(x, 0, n)
			{
				int cur = x & 1, nxt = !cur;
				memset(dp[nxt], 0, sizeof dp[nxt]);
				REP(i, 0, n) REP(j, 0, n - i) REP(k, 0, n - i - j )
					if (dp[cur][i][j][k][3] > eps)
					{
						REP(l, 0, 4)
						{
							dp[nxt][i + 1][j][k][l] += dp[cur][i][j][k][l] * P[x][0];
							dp[nxt][i][j + 1][k][l] += dp[cur][i][j][k][l] * P[x][1];
							dp[nxt][i][j][k + 1][l] += dp[cur][i][j][k][l] * P[x][2];
						}
						dp[nxt][i][j][k][3] += dp[cur][i][j][k][3];
						REP(l, 0, 3) dp[nxt][i][j][k][l] += dp[cur][i][j][k][l] + dp[cur][i][j][k][3] * P[x][l];
					}
			}
			double ret = 0;
			REP(i, 0, n) REP(j, 0, n - i) REP(k, 0, n - i - j)
				if (dp[n & 1][i][j][k][3] > eps)
				{
					double *v = dp[n & 1][i][j][k];
					double tmp = 0;
					REP(l, 0, 3) chkmax(tmp, v[l] + v[(l + 2) % 3] * 3);
					tmp /= C[n][i + j + k];
					tmp /= (n - i - j - k);
					ret += tmp;
				}
			return ret;
		}


};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
