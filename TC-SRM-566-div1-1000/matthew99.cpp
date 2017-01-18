#line 5 "FencingPenguins.cpp"
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

const int Mod = 100007;

const int maxn = 222, maxm = 50, maxty = 52;

const double pi = acos(-1.0);
const double eps = 1e-8;

inline int dcmp(double x) { return x < -eps ? -1 : x > eps; }

struct point
{
	double x, y;

	point() { }
	point(const double &_x, const double &_y): x(_x), y(_y) { }

	friend point operator+(const point &x, const point &y) { return point(x.x + y.x, x.y + y.y); }
	friend point &operator+=(point &x, const point &y) { x.x += y.x, x.y += y.y; return x; }
	friend point operator-(const point &x, const point &y) { return point(x.x - y.x, x.y - y.y); }
	friend point &operator-=(point &x, const point &y) { x.x -= y.x, x.y -= y.y; return x; }
	friend point operator*(const point &x, const double &y) { return point(x.x * y, x.y * y); }
	friend point operator/(const point &x, const double &y) { return point(x.x / y, x.y / y); }
	friend bool operator<(const point &x, const point &y) { if (!dcmp(x.x - y.x)) return dcmp(x.y - y.y) < 0; return x.x < y.x; }
	friend double operator*(const point &x, const point &y) { return x.x * y.x + x.y * y.y; }
	friend double operator^(const point &x, const point &y) { return x.x * y.y - x.y * y.x; }

	double angle() const{ return atan2(y, x); }

};

int n, m;
point a[maxn + 5], b[maxm + 5];

int ty[maxm + 5];

int dp[maxn + 5][maxn + 5];

bool ok[maxn + 5][maxn + 5];
int contain[maxn + 5][maxn + 5][maxn + 5];

class FencingPenguins
{
	public:
		int countWays(int numPosts, int radius, vector <int> x, vector <int> y, string color)
		{
			n = numPosts, m = SZ(x);
			REP(i, 0, n) a[i] = point(cos(double(i) / n * 2 * pi), sin(double(i) / n * 2 * pi)) * radius;
			REP(i, 0, m) b[i] = point(x[i], y[i]), ty[i] = (tolower(color[i]) - 'a') << 1 | (!!islower(color[i]));
			REP(i, 0, m) 
			{
				int lst = n - 1;
				REP(j, 0, n) 
				{
					if (((a[j] - a[lst]) ^ (b[i] - a[lst])) < 0) return 0;
					lst = j;
				}
			}
			memset(ok, 0, sizeof ok);
			memset(dp, 0, sizeof dp);
			memset(contain, 0, sizeof contain);
			static LL all[maxn + 5][maxn + 5];
			memset(all, 0, sizeof all);
			REP(i, 0, n) REP(j, 0, i)
			{
				static int lst[maxty + 5];
				memset(lst, -1, sizeof lst);
				ok[i][j] = 1;
				all[i][j] = 0;
				REP(k, 0, m)
				{
					bool tmp = ((a[j] - a[i]) ^ (b[k] - a[i])) > 0;
					if (tmp) all[i][j] |= 1LL << k;
					if ((~lst[ty[k]]) && tmp != lst[ty[k]]) ok[i][j] = 0;
					lst[ty[k]] = tmp;
				}
				all[j][i] = ((1LL << m) - 1) ^ all[i][j];
				ok[j][i] = ok[i][j];
			}
			REP(i, 0, n) REP(j, i + 1, n - 1) REP(k, j + 1, n) 
				contain[i][j][k] = !!(all[i][j] & all[j][k] & all[k][i]);
			static int conv[maxn + 5][maxn + 5][2];
			memset(conv, 0, sizeof conv);
			REP(i, 0, n) conv[i][i][0] = dp[i][i] = dp[i + 1][i] = 1;
			REP(l, 2, n + 1)
				REP(i, 0, n - l + 1)
				{
					int j = i + l - 1;
					if (!contain[i][i + 1][j]) (dp[i][j] += dp[i + 1][j]) %= Mod;
					REP(k, i, j) REP(u, 0, 2) 
					{
						if (conv[i][k][u] && ok[k][j])
						{
							if (contain[k][k + 1][j - 1] || contain[k][j - 1][j]) continue;
							(conv[i][j][u | contain[i][k][j]] += (LL)conv[i][k][u] * dp[k + 1][j - 1] % Mod) %= Mod;
						}
					}
					REP(k, i, j + 1)
					{
						if (conv[i][k][1] && ok[k][i] && (k == j || (!contain[i][k][k + 1] && !contain[i][k + 1][j])))
							(dp[i][j] += (LL)conv[i][k][1] * dp[k + 1][j] % Mod) %= Mod;
					}
				}
			return dp[0][n - 1];
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
