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

const int maxn = 52;

bool g[maxn + 5][maxn + 5];

const int walk[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

int n, m;

inline bool check(int x, int y)
{
	return x >= 0 && x < n && y >= 0 && y < m && !g[x][y];
}

class RotatingBot 
{
	public:
		int minArea(vector<int> moves) 
		{
			if (SZ(moves) == 1) return moves[0] + 1;
			int x = moves[0], y = moves[1];
			int ret = oo;
			for (n = x + 1; n <= maxn; ++n) for (m = y + 1; m <= maxn; ++m)
			{
				memset(g, 0, sizeof g);
				int u = x, v = y;
				int cur = 0;
				g[u][v] = 1;
				bool failed = 0;
				int lst = -1;
				for (auto step : moves)
				{
					if (~lst && check(u + walk[lst][0], v + walk[lst][1])) { failed = 1; break; }
					REP(i, 0, step)
					{
						u += walk[cur][0], v += walk[cur][1];
						if (!check(u, v)) { failed = 1; break; }
						g[u][v] = 1;
					}
					if (failed) break;
					lst = cur, (cur += 1) &= 3;
				}
				if (!failed) chkmin(ret, n * m);
			}
			if (ret == oo) return -1;
			return ret;
		}
};

// Powered by Greed 2.0-RC
