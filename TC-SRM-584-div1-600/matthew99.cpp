#line 5 "Excavations.cpp"
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

int n;

bool in[maxn + 5];

vector<int> all[maxn + 5];

LL f[maxn + 5][maxn + 5][maxn + 5];
LL g[maxn + 5][maxn + 5][maxn + 5];

class Excavations
{
	public:
		long long count(vector <int> kind, vector <int> depth, vector <int> found, int K)
		{
			memset(in, 0, sizeof in);
			REP(i, 0, maxn) all[i].clear();
			for (auto x : found) in[x - 1] = 1;
			n = SZ(kind);
			vector<int> v(depth);
			sort(ALL(v));
			REP(i, 0, n) all[kind[i] - 1].pb(lower_bound(ALL(v), depth[i]) - v.begin());
			memset(f, 0, sizeof f);
			f[0][0][n] = 1;
			REP(i, 0, maxn)
			{
				if (in[i])
				{
					sort(ALL(all[i]));
					memset(g, 0, sizeof g);
					for (auto x : all[i])
					{
						for (int a = K - 1; a >= 0; --a) REP(b, 0, n) REP(c, b + 1, n + 1) if (f[a][b][c] + g[a][b][c])
						{
							g[a + 1][max(b, x)][c] += f[a][b][c];
							g[a + 1][b][c] += g[a][b][c];
						}
					}
					memcpy(f, g, sizeof f);
				}
				else
				{
					for (auto x : all[i])
					{
						for (int a = K - 1; a >= 0; --a) REP(b, 0, n) REP(c, b + 1, n + 1)
							f[a + 1][b][min(c, x)] += f[a][b][c];
					}
				}
			}
			LL ret = 0;
			REP(i, 0, n) REP(j, i + 1, n + 1) ret += f[K][i][j];
			return ret;
		}


};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
