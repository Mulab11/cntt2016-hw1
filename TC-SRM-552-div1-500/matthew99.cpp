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

const int maxn = 32, maxdif = 910;

int n, m, K;
char g[maxn + 5][maxn + 5];

int sum[maxn + 5][maxn + 5];
int dif[maxn + 5][maxn + 5];

int up[maxn + 5][(maxdif << 1) + 5];
int le[maxn + 5][(maxdif << 1) + 5];
int dw[maxn + 5][(maxdif << 1) + 5];
int ri[maxn + 5][(maxdif << 1) + 5];

inline int get_sum(int x, int y, int u, int v) { return sum[u][v] - sum[x][v] - sum[u][y] + sum[x][y]; }
inline int get_dif(int x, int y, int u, int v) { return dif[u][v] - dif[x][v] - dif[u][y] + dif[x][y]; }

class FoxAndFlowerShopDivOne 
{
	public:
		int theMaxFlowers(vector<string> _g, int _K) 
		{
			n = SZ(_g), m = SZ(_g[0]);
			K = _K;
			REP(i, 0, n) REP(j, 0, m) g[i][j] = _g[i][j];
			REP(i, 0, n) REP(j, 0, m)
			{
				sum[i + 1][j + 1] = sum[i + 1][j] + sum[i][j + 1] - sum[i][j];
				dif[i + 1][j + 1] = dif[i + 1][j] + dif[i][j + 1] - dif[i][j];
				if (g[i][j] != '.') 
				{
					++sum[i + 1][j + 1];
					if (g[i][j] == 'L') --dif[i + 1][j + 1];
					else ++dif[i + 1][j + 1];
				}
			}
			memset(up, -oo, sizeof up);
			memset(le, -oo, sizeof le);
			memset(dw, -oo, sizeof dw);
			memset(ri, -oo, sizeof ri);
			REP(i, 0, n) REP(j, 0, m) REP(k, i + 1, n + 1) REP(l, j + 1, m + 1)
			{
				int s = get_sum(i, j, k, l);
				int d = get_dif(i, j, k, l);
				chkmax(up[k][d + maxdif], s);
				chkmax(le[l][d + maxdif], s);
				chkmax(dw[i][d + maxdif], s);
				chkmax(ri[j][d + maxdif], s);
			}
			REP(i, 0, n) REP(j, 0, maxdif << 1 | 1) chkmax(up[i + 1][j], up[i][j]);
			REP(i, 0, m) REP(j, 0, maxdif << 1 | 1) chkmax(le[i + 1][j], le[i][j]);
			int ret = -1;
			REP(i, 0, n + 1) REP(j, 0, maxdif << 1 | 1) REP(k, 0, maxdif << 1| 1) if (abs(j + k - (maxdif << 1)) <= K) chkmax(ret, up[i][j] + dw[i][k]);
			REP(i, 0, m + 1) REP(j, 0, maxdif << 1 | 1) REP(k, 0, maxdif << 1| 1) if (abs(j + k - (maxdif << 1)) <= K) chkmax(ret, le[i][j] + ri[i][k]);
			return ret;
		}
};

// Powered by Greed 2.0-RC
