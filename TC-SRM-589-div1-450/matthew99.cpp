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

const int maxn = 60;

int n;
int a[maxn + 5];

int X, Y;
int lk[maxn + 5];

bool vis[maxn + 5];
bool g[maxn + 5][maxn + 5];

bool find(int x)
{
	REP(y, 0, n) if (a[y] == Y && g[x][y] && !vis[y])
	{ 
		vis[y] = 1;
		if (!~lk[y] || find(lk[y])) { lk[y] = x; return 1; }
	}
	return 0;
}

class GearsDiv1 
{
	public:
		int getmin(string w, vector<string> _g) 
		{
			n = SZ(w);
			REP(i, 0, n) REP(j, 0, n) g[i][j] = _g[i][j] == 'Y';
			REP(i, 0, n) a[i] = w[i] == 'R' ? 2 : w[i] == 'G';
			int ret = oo;
			REP(i, 0, 3)
			{
				X = (i + 1) % 3;
				Y = (i + 2) % 3;
				memset(lk, -1, sizeof lk);
				int tmp = 0;
				REP(j, 0, n) if (a[j] == X)
				{
					memset(vis, 0, sizeof vis);
					tmp += find(j);
				}
				chkmin(ret, tmp);
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
