#line 5 "Tunnels.cpp"
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

const int maxn = 50;

const int walk[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int n, m;

bool g[maxn + 5][maxn + 5];

int N = 0;
int col[maxn + 5][maxn + 5];

int lstx, lsty;

void dfs(int x, int y, int c)
{
	if (col[x][y] == c) return;
	lstx = x, lsty = y;
	col[x][y] = c;
	REP(i, 0, 4)
	{
		int u = x + walk[i][0], v = y + walk[i][1];
		if (u < 0 || u >= n || v < 0 || v >= m || !g[u][v]) continue;
		dfs(u, v, c);
	}
}

int l[maxn + 5], r[maxn + 5];

int deg[maxn + 5][maxn + 5];

class Tunnels
{
	public:
		int minimumTunnels(vector <string> frame)
		{
			n = SZ(frame), m = SZ(frame[0]);
			REP(i, 0, n) REP(j, 0, m) g[i][j] = frame[i][j] == 'X';
			memset(col, -1, sizeof col);
			N = 0;
			memset(l, -1, sizeof l), memset(r, -1, sizeof r);
			REP(i, 0, n) REP(j, 0, m) if (g[i][j])
			{
				deg[i][j] = 0;
				REP(k, 0, 4)
				{
					int u = i + walk[k][0], v = j + walk[k][1];
					if (u < 0 || u >= n || v < 0 || v >= m || !g[u][v]) continue;
					++deg[i][j];
				}
			}
			REP(i, 0, n) REP(j, 0, m) if (g[i][j] && deg[i][j] < 2 && !~col[i][j]) 
			{
				dfs(i, j, N++);
				if (i == lstx)
				{
					if (!j && lsty == m - 1) l[i] = r[i] = 2;
					else 
					{
						if (!j) l[i] = !i;
						if (lsty == m - 1) r[i] = !i;
					}
				}
				else if (!i)
				{
					if (!lsty) l[lstx] = 1;
					if (lsty == m - 1) r[lstx] = 1;
				}
				else
				{
					if (!j) l[i] = 0;
					if (j == m - 1) r[i] = 0;
					if (!lsty && (i < lstx - 1 || j)) l[lstx] = 1;
					if (lsty == m - 1 && (i < lstx - 1 || j != m - 1)) r[lstx] = 1;
				}
			}
			if (m == 1) return !!N;
			static int dp[maxn + 5][maxn + 5][maxn + 5];
			memset(dp, -1, sizeof dp);
			dp[0][0][0] = 0;
			REP(i, 0, n) REP(j, 0, i + 1) REP(k, 0, i + 1) if (~dp[i][j][k])
			{
				if (l[i] == 2)
				{
					assert(r[i] == 2);
					chkmax(dp[i + 1][j + 1][max(0, k - 1)], dp[i][j][k] + (k > 0));
					chkmax(dp[i + 1][max(0, j - 1)][k + 1], dp[i][j][k] + (j > 0));
				}
				else
				{
					int delta = 0;
					int newj = j, newk = k;
					if (l[i] == 0) delta += newj > 0, newj = max(0, newj - 1);
					else if (l[i] == 1) ++newj;
					if (r[i] == 0) delta += newk > 0, newk = max(0, newk - 1);
					else if (r[i] == 1) ++newk;
					chkmax(dp[i + 1][newj][newk], dp[i][j][k] + delta);
				}
			}
			int ans = 0;
			REP(i, 0, n + 1) REP(j, 0, n + 1) chkmax(ans, dp[n][i][j]);
			return N - ans;
		}


};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
