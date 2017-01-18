#line 5 "Orienteering.cpp"
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

const int maxn = 50, maxm = 50, maxk = 300, max0 = 2500;

int n, m, K;
int g[maxn + 5][maxm + 5];

int dis[max0 + 5][max0 + 5];

vector<int> all;

int tot = 0;
int id[maxn + 5][maxn + 5];

int fa[max0 + 5], sz[max0 + 5], dep[max0 + 5];

void dfs(int x, int y, int f = -1)
{
	fa[tot] = f;
	if (f == -1) dep[tot] = 0;
	else dep[tot] = dep[f] + 1;
	if (g[x][y]) all.pb(tot);
	sz[tot] = g[x][y];
	id[x][y] = tot++;
	REP(i, 0, 4)
	{
		int u = x + walk[i][0], v = y + walk[i][1];
		if (u < 0 || u >= n || v < 0 || v >= m || g[u][v] == -1 || id[u][v] != -1) continue;
		dfs(u, v, id[x][y]);
		sz[id[x][y]] += sz[id[u][v]];
	}
}

double C[maxk + 5][maxk + 5];

inline void prepare()
{
	double Max = 0;
	REP(i, 0, maxk + 1)
	{
		C[i][0] = 1;
		REP(j, 1, i + 1) C[i][j] = C[i - 1][j - 1] + C[i - 1][j], chkmax(Max, C[i][j]);
	}
}

class Orienteering
{
	public:
		double expectedLength(vector <string> field, int __K)
		{
			K = __K;
			prepare();
			n = SZ(field), m = SZ(field[0]);
			REP(i, 0, n) REP(j, 0, m) g[i][j] = field[i][j] == '#' ? -1: field[i][j] == '*';
			memset(id, -1, sizeof id), tot = 0;
			all.clear();
			REP(i, 0, n) REP(j, 0, m) if (g[i][j] != -1) { dfs(i, j); goto lyc; }
lyc:;
			double ret = tot * C[sz[0]][K];
			REP(i, 0, tot) ret -= C[sz[i]][K] + C[sz[0] - sz[i]][K];
			ret *= 2;
			REP(i, 0, tot) REP(j, 0, tot)
				if (i == j) dis[i][j] = 0;
				else
				{
					if (dep[i] > dep[j]) dis[i][j] = dis[fa[i]][j] + 1;
					else dis[i][j] = dis[i][fa[j]] + 1;
				}
			int N = SZ(all);
			REP(a, 0, N) REP(b, a + 1, N)
			{
				int i = all[a], j = all[b];
				int ban = 0;
				REP(c, 0, N)
				{
					int k = all[c];
					if (k == i || k == j) continue;
					if (dis[i][k] > dis[i][j] || (k < j && dis[i][k] == dis[i][j])) ++ban;
					else if (dis[k][j] > dis[i][j] || (k < i && dis[k][j] == dis[i][j])) ++ban;
				}
				ret -= C[N - 2 - ban][K - 2] * dis[i][j];
			}
			return ret / C[sz[0]][K];
		}


};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
