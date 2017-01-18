#line 5 "CandyOnDisk.cpp"
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

const int maxn = 50;

const long double pi = acos(-1.0);
const long double eps = 1e-8;

inline int dcmp(long double x) { return x < -eps ? -1 : x > eps; }

struct point
{
	long double x, y;

	point() { }
	point(const long double &_x, const long double &_y): x(_x), y(_y) { }

	friend point operator+(const point &x, const point &y) { return point(x.x + y.x, x.y + y.y); }
	friend point &operator+=(point &x, const point &y) { x.x += y.x, x.y += y.y; return x; }
	friend point operator-(const point &x, const point &y) { return point(x.x - y.x, x.y - y.y); }
	friend point &operator-=(point &x, const point &y) { x.x -= y.x, x.y -= y.y; return x; }
	friend point operator*(const point &x, const long double &y) { return point(x.x * y, x.y * y); }
	friend point operator/(const point &x, const long double &y) { return point(x.x / y, x.y / y); }
	friend bool operator<(const point &x, const point &y) { if (!dcmp(x.x - y.x)) return dcmp(x.y - y.y) < 0; return dcmp(x.x - y.x) < 0; }
	friend long double operator*(const point &x, const point &y) { return x.x * y.x + x.y * y.y; }
	friend long double operator^(const point &x, const point &y) { return x.x * y.y - x.y * y.x; }

	long double angle() const{ return atan2(y, x); }

};

int n;

long double low[maxn + 5], high[maxn + 5];

point a[maxn + 5];
long double r[maxn + 5];

map<point, int> Max;

point S, T;

long double dis[maxn + 5][maxn + 5];

bool vis[maxn + 5];
bool done[maxn + 5][maxn + 5];

inline long double get_dis(const point &x, const point &y)
{
	return sqrt((x - y) * (x - y));
}

inline bool intersect(const long double &l0, const long double &r0, const long double &l1, const long double &r1)
{
	if (l0 > r1 || l1 > r0) return 0;
	return 1;
}

class CandyOnDisk
{
	public:
		string ableToAchieve(vector <int> x, vector <int> y, vector <int> r, int sx, int sy, int tx, int ty)
		{
			if (sx == tx && sy == ty) return "YES";
			Max.clear();
			REP(i, 0, SZ(x)) chkmax(Max[point(x[i], y[i])], r[i]);
			S = point(sx, sy), T = point(tx, ty);
			n = 0;
			for (auto x : Max) a[n] = x.x, r[n++] = x.y;
			REP(i, 0, n) low[i] = 1e100, high[i] = -1e100;
			REP(i, 0, n) REP(j, 0, i) dis[i][j] = dis[j][i] = get_dis(a[i], a[j]);
			memset(vis, 0, sizeof vis);
			memset(done, 0, sizeof done);
			REP(i, 0, n)
			{
				long double tmp = get_dis(a[i], S);
				if (tmp < r[i]) low[i] = high[i] = tmp, vis[i] = 1;
			}
			while (1)
			{
				bool flag = 0;
				REP(i, 0, n)
					if (vis[i])
					{
						REP(j, 0, n)
							if (j != i && !done[i][j] && intersect(low[i], high[i], dis[i][j] - r[j], dis[i][j] + r[j]))
							{
								done[i][j] = done[j][i] = vis[j] = 1;
								chkmin(low[i], max((long double)0, dis[i][j] - r[j]));
								chkmax(high[i], min((long double)r[i], dis[i][j] + r[j]));
								chkmin(low[j], max((long double)0, dis[j][i] - r[i]));
								chkmax(high[j], min((long double)r[j], dis[j][i] + r[i]));
								flag = 1;
							}
					}
				if (!flag) break;
			}
			REP(i, 0, n)
			{
				long double tmp = get_dis(a[i], T);
				if (vis[i] && low[i] <= tmp && tmp <= high[i]) return "YES";
			}
			return "NO";
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
