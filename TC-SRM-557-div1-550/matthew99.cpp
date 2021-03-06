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

const int maxn = 50;

int n;
bool g[maxn + 5][maxn + 5];

bool vis[maxn + 5];

int lk[maxn + 5];

int find(int x)
{
	REP(y, 0, n) if (g[x][y] && !vis[y])
	{
		vis[y] = 1;
		if (!~lk[y] || find(lk[y])) { lk[y] = x; return 1; }
	}
	return 0;
}

class Incubator 
{
	public:
		int maxMagicalGirls(vector<string> love) 
		{
			n = SZ(love);
			REP(i, 0, n) REP(j, 0, n) g[i][j] = love[i][j] == 'Y';
			REP(k, 0, n) REP(i, 0, n) REP(j, 0, n) g[i][j] |= g[i][k] & g[k][j];
			int ans = n;
			memset(lk, -1, sizeof lk);
			REP(i, 0, n) memset(vis, 0, sizeof vis), ans -= find(i);
			return ans;
		}
};

// Powered by Greed 2.0-RC
