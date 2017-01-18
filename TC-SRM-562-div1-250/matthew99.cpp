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

const int maxn = 200;

int n, m;

int a[maxn + 5][maxn + 5];

class PastingPaintingDivOne 
{
	public:
		vector<long long> countColors(vector<string> g, int T) 
		{
			n = SZ(g), m = SZ(g[0]);
			REP(i, 0, n) REP(j, 0, m)
			{
				if (g[i][j] == '.') a[i][j] = -1;
				else if (g[i][j] == 'R') a[i][j] = 0;
				else if (g[i][j] == 'G') a[i][j] = 1;
				else if (g[i][j] == 'B') a[i][j] = 2;
			}
			vector<LL> ret(3, 0);
			REP(i, 0, n) REP(j, 0, m) if (~a[i][j])
			{
				int cnt = T;
				REP(k, 1, min(T, min(i, j)) + 1)
					if (~a[i - k][j - k]) { cnt = k; break; }
				ret[a[i][j]] += cnt;
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
