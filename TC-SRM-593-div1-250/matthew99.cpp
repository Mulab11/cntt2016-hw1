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

const int maxn = 60;

int n, m;
int c[maxn + 5][maxn + 5];

char g[maxn + 5][maxn + 5];

int ret;

int walk[6][2] = {{0, -1}, {0, 1}, {-1, 0}, {-1, 1}, {1, -1}, {1, 0}};

void dfs(int x, int y)
{
	REP(i, 0, 6)
	{
		int u = x + walk[i][0], v = y + walk[i][1];
		if (u < 0 || u >= n || v < 0 || v >= m || g[u][v] != 'X') continue;
		chkmax(ret, 2);
		if (!~c[u][v]) c[u][v] = !c[x][y], dfs(u, v);
		else if (c[u][v] == c[x][y]) chkmax(ret, 3);
	}
}

class HexagonalBoard 
{
	public:
		int minColors(vector<string> _g) 
		{
			n = SZ(_g), m = SZ(_g[0]);
			REP(i, 0, n) REP(j, 0, m) g[i][j] = _g[i][j];
			memset(c, -1, sizeof c);
			ret = 0;
			REP(i, 0, n) REP(j, 0, m) if (g[i][j] == 'X' && !~c[i][j])
			{
				chkmax(ret, 1);
				dfs(i, j);
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
