#line 5 "ArcadeManao.cpp"
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

int n, m, sx, sy;

int g[maxn + 5][maxm + 5];

inline bool can(int L)
{
	static pair<int, int> q[maxn * maxm + 5];
	int head = 0, rear = 0;
	static bool vis[maxn + 1][maxm + 1];
	memset(vis, 0, sizeof vis);
	REP(i, 0, m) q[rear++] = mp(n - 1, i), vis[n - 1][i] = 1;
	while (head != rear)
	{
		auto x = q[head++];
		if (x.y > 0 && !vis[x.x][x.y - 1] && g[x.x][x.y - 1]) q[rear++] = mp(x.x, x.y - 1), vis[x.x][x.y - 1] = 1;
		if (x.y + 1 < m && !vis[x.x][x.y + 1] && g[x.x][x.y + 1]) q[rear++] = mp(x.x, x.y + 1), vis[x.x][x.y + 1] = 1;
		REP(i, -L, L + 1)
			if (x.x - i >= 0 && x.x - i < n && !vis[x.x - i][x.y] && g[x.x - i][x.y]) q[rear++] = mp(x.x - i, x.y), vis[x.x - i][x.y] = 1;
	}
	return vis[sx][sy];
}

class ArcadeManao
{
	public:
		int shortestLadder(vector <string> level, int coinRow, int coinColumn)
		{
			sx = coinRow - 1, sy = coinColumn - 1;
			n = SZ(level), m = SZ(level[0]);
			REP(i, 0, n) REP(j, 0, m) g[i][j] = level[i][j] == 'X';
			for (int i = 0; ; ++i) if (can(i)) return i;
			assert(0);
			return -1;
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
