#line 5 "GameInDarknessDiv1.cpp"
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

const int walk[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

const int maxn = 50;

int n, m;
int ax, ay, bx, by;

int a[maxn + 5][maxn + 5];

int disA[maxn + 5][maxn + 5], disB[maxn + 5][maxn + 5];
bool vis[maxn + 5][maxn + 5];

void dfs(int x, int y, int now, int dis[maxn + 5][maxn + 5])
{
	vis[x][y] = 1, dis[x][y] = now;
	REP(i, 0, 4) { int u = x + walk[i][0], v = y + walk[i][1]; if (u >= 0 && u < n && v >= 0 && v < m && !a[u][v] && !vis[u][v]) dfs(u, v, now + 1, dis); }
}

int Max[maxn + 5][maxn + 5];

int cnt = 0;

void dfs0(int x, int y, int dep = 0)
{
	vis[x][y] = 1, Max[x][y] = dep;
	REP(i, 0, 4) { int u = x + walk[i][0], v = y + walk[i][1]; if (u >= 0 && u < n && v >= 0 && v < m && !a[u][v] && !vis[u][v]) dfs0(u, v, dep + 1), chkmax(Max[x][y], Max[u][v]); }
	if (dep == 1 && Max[x][y] >= 3) ++cnt;
}

class GameInDarknessDiv1
{
	public:
		string check(vector <string> field)
		{
			n = SZ(field), m = SZ(field[0]);
			REP(i, 0, n) REP(j, 0, m) 
			{
				a[i][j] = field[i][j] == '#';
				if (field[i][j] == 'A') ax = i, ay = j;
				if (field[i][j] == 'B') bx = i, by = j;
			}
			memset(vis, 0, sizeof vis);
			dfs(bx, by, 0, disB);
			memset(vis, 0, sizeof vis);
			dfs(ax, ay, 0, disA);
			memset(Max, 0, sizeof Max);
			REP(i, 0, n) REP(j, 0, m) if (!a[i][j] && disA[i][j] > disB[i][j] + 1)
			{
				memset(vis, 0, sizeof vis), cnt = 0;
				dfs0(i, j, 0);
				if (cnt >= 3) return "Bob wins";
			}
			return "Alice wins";
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
