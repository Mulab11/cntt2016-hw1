#line 5 "ThreeColorability.cpp"
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

inline bool add(int x, int y)
{
	REP(i, 0, n) REP(j, 0, m) if (i != x && j != y)
	{
		int tmp = !!(~g[i][y]) + !!(~g[x][j]) + !!(~g[i][j]);
		if (tmp == 2)
		{
			bool tmp = 1;
			if (!~g[i][y]) g[i][y] = g[x][y] ^ g[x][j] ^ g[i][j], tmp = add(i, y);
			if (!~g[x][j]) g[x][j] = g[i][y] ^ g[x][y] ^ g[i][j], tmp = add(x, j);
			if (!~g[i][j]) g[i][j] = g[i][y] ^ g[x][j] ^ g[x][y], tmp = add(i, j);
			if (!tmp) return 0;
		}
		else if (tmp == 3 && (g[x][y] ^ g[i][y] ^ g[x][j] ^ g[i][j])) return 0;
	}
	return 1;
}

class ThreeColorability
{
	public:
		vector <string> lexSmallest(vector <string> cells)
		{
			n = SZ(cells), m = SZ(cells[0]);
			REP(i, 0, n) REP(j, 0, m) g[i][j] = cells[i][j] == '?' ? -1 : cells[i][j] == 'Z';
			REP(i, 0, n) REP(j, 0, m) if (~g[i][j]) if (!add(i, j)) return vector<string>();
			REP(i, 0, n) REP(j, 0, m) if (!~g[i][j]) g[i][j] = 0, add(i, j);
			vector<string> ret;
			REP(i, 0, n) { string tmp; REP(j, 0, m) if (g[i][j]) tmp += 'Z'; else tmp += 'N'; ret.pb(tmp); }
			return ret;
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
