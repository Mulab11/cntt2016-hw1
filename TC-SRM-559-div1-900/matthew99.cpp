#line 5 "CircusTents.cpp"
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

const double pi = acos(-1.0);
const double eps = 1e-8;

inline int dcmp(double x) { return x < -eps ? -1 : x > eps; }

struct point //define point
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

struct cir //define circle
{
	point O;
	double r;

	cir() { }
	cir(const point &_O, const double &_r): O(_O), r(_r) { }

};

inline bool cir_cir(const point &O0, const double &r0, const point &O1, const double &r1, double &x, double &y) //get the intersections of two circles
{
	point u = O1 - O0;
	double ang = u.angle();
	double tmp0 = u * u;
	double tmp1 = (tmp0 + r0 * r0 - r1 * r1) / (2 * sqrt(tmp0) * r0);
	if (tmp1 >= 1 || tmp1 <= -1) return 0;
	tmp1 = acos(tmp1);
	x = ang - tmp1;
	y = ang + tmp1;
	return 1;
}

inline double sqrdis(const point &x, const point &y) { return (y - x) * (y - x); } //for two vector x and y return (x - y) ^ 2

const int maxn = 50;

int n;
cir a[maxn + 5];

vector<pair<double, double> > all;

inline void add(double l, double r) //add an interval of angle
{
	if (l < -pi) all.pb(mp(l + 2 * pi, pi)), l = -pi;
	if (r > pi) all.pb(mp(-pi, r - 2 * pi)), r = pi;
	all.pb(mp(l, r));
}

inline bool work(double x)
{
	all.clear();
	REP(i, 1, n)
	{
		double d0 = sqrdis(a[0].O, a[i].O);
		double d1 = d0 - a[0].r * a[0].r;
		double d2 = x + a[i].r;
		if (d2 * d2 < d1) //go directly
		{
			double l, r;
			if (cir_cir(a[0].O, a[0].r, a[i].O, d2, l, r)) add(l, r);
		}
		else //first go along the circumference and then go directly
		{
			double l, r;
			assert(cir_cir(a[0].O, a[0].r, a[i].O, sqrt(d1), l, r));
			double ang = (d2 - sqrt(d1)) / a[0].r;
			if (r - l + ang * 2 >= 2 * pi) return 0;
			add(l - ang, r + ang);
		}
	}
	sort(ALL(all));
	double lst = -pi;
	for (auto x : all) //check whether all angles are covered
	{
		if (x.x > lst) return 1;
		chkmax(lst, x.y);
	}
	return lst < pi;
}

class CircusTents
{
	public:
		double findMaximumDistance(vector <int> x, vector <int> y, vector <int> R)
		{
			n = SZ(x);
			REP(i, 0, n) a[i] = cir(point(x[i], y[i]), R[i]);
			double l = 0, r = 1000000;
			REP(i, 0, 100) //binary search
			{
				double mid = (l + r) / 2;
				if (work(mid)) l = mid;
				else r = mid;
			}
			return l;
		}


};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
