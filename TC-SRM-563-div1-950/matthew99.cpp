#line 5 "CoinsGame.cpp"
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

const int Mod = 1e9 + 9;

const int walk[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

const int maxn = 50, maxm = 50;

int n, m;
bool g[maxn + 5][maxm + 5];

int col[maxn + 5][maxm + 5];

inline bool in(int x, int y) { return (x >= 0 && x < n && y >= 0 && y < m); }

inline int calc(int x, int y, int go)
{
	if (!in(x + walk[go][0], y + walk[go][1])) return -1;
	if (!g[x + walk[go][0]][y + walk[go][1]]) return col[x + walk[go][0]][y + walk[go][1]];
	return col[x][y];
}

int pw[maxn * maxm + 5];

class CoinsGame
{
	public:
		int ways(vector <string> board)
		{
			n = SZ(board), m = SZ(board[0]);
			REP(i, 0, n) REP(j, 0, m) g[i][j] = board[i][j] == '#';
			pw[0] = 1;
			REP(i, 0, n * m) pw[i + 1] = (pw[i] << 1) % Mod;
			int ret = 1;
			REP(i, 0, n) REP(j, 0, m) if (!g[i][j]) (ret <<= 1) %= Mod;
			(--ret) %= Mod;
			int lst = -1;
			int tot = 0;
			memset(col, 0, sizeof col);
			while (1)
			{
				lst = tot;
				tot = 0;
				map<pair<pair<int, int>, pair<int, int> >, int> id;
				static int nxt[maxn + 5][maxm + 5];
				REP(i, 0, n) REP(j, 0, m) if (!g[i][j]) { auto tmp = mp(mp(calc(i, j, 0), calc(i, j, 1)), mp(calc(i, j, 2), calc(i, j, 3))); if (!id.count(tmp)) id[tmp] = tot++; nxt[i][j] = id[tmp]; }
				if (tot == lst) break;
				memcpy(col, nxt, sizeof col);
			}
			static int cnt[maxn * maxm + 5];
			REP(i, 0, tot) cnt[i] = 0;
			REP(i, 0, n) REP(j, 0, m) if (!g[i][j]) ++cnt[col[i][j]];
			REP(i, 0, tot) (ret -= pw[cnt[i]] - 1) %= Mod;
			(ret += Mod) %= Mod;
			return ret;
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
