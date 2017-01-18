#line 5 "YamanoteLine.cpp"
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

const LL OO = 0x3f3f3f3f3f3f3f3fLL;

const int maxn = 50, maxm = 100;

LL f[maxn + 5][maxn + 5][(maxn << 1) + 5];

inline LL ceil(LL a, LL b);
inline LL floor(LL a, LL b);

inline LL ceil(LL a, LL b)
{
	if (b < 0) a = -a, b = -b;
	if (a < 0) return -floor(-a, b);
	return (a + b - 1) / b;
}

inline LL floor(LL a, LL b)
{
	if (b < 0) a = -a, b = -b;
	if (a < 0) return -ceil(-a, b);
	return a / b;
}

class YamanoteLine
{
	public:
		long long howMany(int n, vector <int> s1, vector <int> t1, vector <int> l1, vector <int> s2, vector <int> t2, vector <int> l2)
		{
			memset(f, 0x3f, sizeof f);
			REP(i, 0, n + 1) f[i][i][n] = 0;
			REP(i, 0, n) s1.pb(i), t1.pb((i + 1) % n), l1.pb(1);
			REP(i, 0, SZ(s1))
			{
				int x = s1[i], y = t1[i];
				LL z = l1[i];
				if (x < y) chkmin(f[y][x][n], -z);
				else chkmin(f[y][x][n + 1], -z);
			}
			REP(i, 0, SZ(s2))
			{
				int x = s2[i], y = t2[i];
				LL z = l2[i];
				if (x < y) chkmin(f[x][y][n], z);
				else chkmin(f[x][y][n - 1], z);
			}
			chkmin(f[n][0][n - 1], 0LL);
			chkmin(f[0][n][n + 1], 0LL);
			REP(k, 0, n + 1) REP(i, 0, n + 1) REP(a, -n, n + 1) if (f[i][k][a + n] < OO) REP(j, 0, n + 1) REP(b, max(-n, -n - a), min(n, n - a) + 1) if (f[k][j][b + n] < OO) chkmin(f[i][j][a + b + n], f[i][k][a + n] + f[k][j][b + n]);
			LL l = -OO, r = OO;
			REP(i, 0, n + 1) REP(j, 0, i + 1) REP(x, -n, n + 1) if (f[i][j][x + n] < OO) REP(y, max(-n, -n - x), min(n, n - x) + 1) if (f[j][i][y + n] < OO)
			{
				LL k = x + y, b = f[i][j][x + n] + f[j][i][y + n];
				if (!k)
				{
					if (b < 0) return 0;
				}
				else if (k > 0) chkmax(l, ceil(-b, k));
				else chkmin(r, floor(b, -k) + 1);
			}
			if (l >= r) return 0;
			if (r - l > 1e12) return -1;
			return r - l;
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
