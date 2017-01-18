#line 5 "TheTilesDivOne.cpp"
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

const int walk[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

const int maxn = 47;

const int max0 = 10000, max1 = 100000;

struct edge
{
	int id, nxt;

	edge() { }
	edge(int _id, int _nxt): id(_id), nxt(_nxt) { }

};

int st[max0 + 5], en = 0;
edge e[max1 + 5];

inline void add_edge(int x, int y) { e[en] = edge(y, st[x]), st[x] = en++; }
inline void add_biedge(int x, int y) { add_edge(x, y), add_edge(y, x); }

int lk[max0 + 5];

int N;

int n, m;

bool g[maxn + 5][maxn + 5];

bool vis[max0 + 5];

bool go(int x)
{
	for (int i = st[x]; ~i; i = e[i].nxt)
	{
		int y = e[i].id;
		if (!vis[y])
		{
			vis[y] = 1;
			if (!~lk[y] || go(lk[y]))
			{
				lk[lk[y] = x] = y;
				return 1;
			}
		}
	}
	return 0;
}

class TheTilesDivOne
{
	public:
		int find(vector <string> board)
		{
			n = SZ(board), m = SZ(board[0]);
			REP(i, 0, n) REP(j, 0, m) g[i][j] = board[i][j] == 'X';
			N = n * m << 1;
			memset(st, -1, sizeof st), en = 0;
			int tot = 0;
			REP(i, 0, n) REP(j, 0, m) if (!g[i][j] && !((i ^ j) & 1))
			{
				++tot;
				add_biedge((i * m + j) << 1, (i * m + j) << 1 | 1);
				REP(k, 0, 4)
				{
					int u = i + walk[k][0], v = j + walk[k][1];
					if (u >= 0 && u < n && v >= 0 && v < m && !g[u][v])
						add_biedge((i * m + j) << 1 | (k & 1), (u * m + v) << 1);
				}
			}
			memset(lk, -1, sizeof lk);
			int ans = 0;
			REP(i, 0, N) if (!~lk[i]) 
			{
				memset(vis, 0, sizeof vis);
				ans += go(i);
			}
			return ans - tot;
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
