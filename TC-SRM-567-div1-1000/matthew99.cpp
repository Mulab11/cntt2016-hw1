#line 5 "Mountains.cpp"
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

const int maxn = 10, maxm = 50;

int n, m;
int h[maxn + 5];

bool g[maxn + 5][maxm + 5];

map<vector<int>, int> dp[maxn + 5];

int dfs(int x, vector<int> cur)
{
	if (x == n) return 1;
	if (dp[x].count(cur)) return dp[x][cur];
	int &ret = dp[x][cur];
	ret = 0;
	REP(i, 0, m)
	{
		bool flag = 1;
		REP(j, 0, m) if ((h[x] - abs(i - j) > cur[j]) ^ g[x][j]) { flag = 0; break; } 
		if (!flag) continue;
		vector<int> nxt(cur);
		REP(j, 0, m) chkmax(nxt[j], h[x] - abs(i - j));
		(ret += dfs(x + 1, nxt)) %= Mod;
	}
	return ret;
}

class Mountains
{
	public:
		int countPlacements(vector <int> heights, vector <string> visibility)
		{
			n = SZ(heights), m = SZ(visibility[0]);
			REP(i, 0, n) h[n - i - 1] = heights[i];
			REP(i, 0, n) REP(j, 0, m) g[n - i - 1][j] = visibility[i][j] == 'X';
			return dfs(0, vector<int>(m, 0));
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
