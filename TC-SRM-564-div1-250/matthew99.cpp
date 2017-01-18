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

vector<vector<bool> > vis;

int n, m, cnt;

void dfs(int x, int y)
{
	if (x < 0 || x >= n || y < 0 || y >= m) return;
	if (vis[x][y]) return;
	vis[x][y] = 1;
	++cnt;
	dfs(x - 1, y - 2);
	dfs(x - 1, y + 2);
	dfs(x + 1, y - 2);
	dfs(x + 1, y + 2);
	dfs(x + 2, y + 1);
	dfs(x - 2, y + 1);
	dfs(x + 2, y - 1);
	dfs(x - 2, y - 1);
}

class KnightCircuit2 
{
	public:
		int maxSize(int w, int h) 
		{
			n = w, m = h;
			if (w >= 4 && h >= 4) return w * h;
			vis.resize(w);
			REP(i, 0, w) vis[i] = vector<bool>(h, 0);
			int ret = 0;
			REP(i, 0, w) REP(j, 0, h) if (!vis[i][j])
			{
				cnt = 0;
				dfs(i, j);
				chkmax(ret, cnt);
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
