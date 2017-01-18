#line 5 "Constellation.cpp"
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

const double eps = 1e-8;

inline int dcmp(double x) { return x < -eps ? -1 : x > eps; }

struct point
{
	int x, y;

	point() { }
	point(const int &_x, const int &_y): x(_x), y(_y) { }

	friend point operator+(const point &x, const point &y) { return point(x.x + y.x, x.y + y.y); }
	friend point &operator+=(point &x, const point &y) { x.x += y.x, x.y += y.y; return x; }
	friend point operator-(const point &x, const point &y) { return point(x.x - y.x, x.y - y.y); }
	friend point &operator-=(point &x, const point &y) { x.x -= y.x, x.y -= y.y; return x; }
	friend bool operator<(const point &x, const point &y) { if (!dcmp(x.x - y.x)) return dcmp(x.y - y.y) < 0; return x.x < y.x; }
	friend int operator*(const point &x, const point &y) { return x.x * y.x + x.y * y.y; }
	friend int operator^(const point &x, const point &y) { return x.x * y.y - x.y * y.x; }

};

const int maxn = 50;

int n;
point a[maxn + 5];

double P[maxn + 5];

class Constellation
{
	public:
		double expectation(vector <int> x, vector <int> y, vector <int> prob)
		{
			n = SZ(x);
			REP(i, 0, n) P[i] = prob[i] / 1000., a[i] = point(x[i], y[i]);
			double ret = 0; 
			REP(i, 0, n) REP(j, 0, n) if (i != j)
			{
				double tmp = P[i] * P[j];
				REP(k, 0, n) if (k != i && k != j)
				{
					int foo = ((a[k] - a[i]) ^ (a[j] - a[i]));
					if (foo > 0) tmp *= 1 - P[k];
					else if (!foo && (a[k] - a[i]) * (a[k] - a[j]) < 0) tmp *= 1 - P[k];
				}
				ret += tmp * (a[i] ^ a[j]);
			}
			return ret / 2;
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
