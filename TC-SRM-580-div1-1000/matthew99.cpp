#line 5 "WallGameDiv1.cpp"
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

const int maxn = 50, maxm = 50;

int n, m;
int g[maxn + 5][maxm + 5];
int sum[maxn + 5][maxm + 5];

int dp[maxn + 5][maxm + 5][maxm + 5][2];

inline int go(int x, int from, int to) { if (from < to) return sum[x][to + 1] - sum[x][from + 1]; return sum[x][from] - sum[x][to]; }

class WallGameDiv1
{
	public:
		int play(vector <string> costs)
		{
			n = SZ(costs), m = SZ(costs[0]);
			REP(i, 0, n) 
			{
				sum[i][0] = 0;
				REP(j, 0, m) g[i][j] = costs[i][j] - '0', sum[i][j + 1] = sum[i][j] + g[i][j];
			}
			memset(dp, oo, sizeof dp);
			REP(i, 0, m) dp[n - 1][i][i][1] = 0;
			for (int i = n - 2; i >= 0; --i) for (int j = m - 1; j >= 0; --j) REP(k, 0, min(m, m - j + 1)) REP(u, 0, 2)
			{
				int l = k, r = k + j;
				if (!l && !u) continue;
				if (r == m && u) continue;
				if (u == 0) dp[i][l][r][u] = dp[i + 1][l - 1][l - 1][1] + g[i + 1][l - 1];
				else dp[i][l][r][u] = dp[i + 1][r][r][1] + g[i + 1][r];
				if (j < m - 1)
				{
					int now = u ? r : l - 1;
					int newl = l, newr = r;
					if (!u) --newl;
					else ++newr;
					int gol = !l ? oo : dp[i][newl][newr][0] + go(i, now, newl - 1);
					int gor = r == m ? oo : dp[i][newl][newr][1] + go(i, now, newr);
					chkmax(dp[i][l][r][u], min(gol, gor));
				}
			}
			int ret = oo;
			REP(i, 0, m) chkmin(ret, dp[0][i][i][1] + g[0][i]);
			return ret;
		}


};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
