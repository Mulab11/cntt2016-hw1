/*
	Geometry
	Binary search
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for(int _r = r, i = l; i <= _r; ++i)
#define red(i, r, l) for(int _l = l, i = r; i >= _l; --i)
#define debug(x) cerr << #x << " = " << x << endl
#define MEM(x, y) memset(x, y, sizeof(x))
#define X first
#define Y second

using namespace std;
typedef long long LL;
typedef vector<int> VI;
typedef pair<int, int> PI;
typedef pair<double, double> PD;
const double pi = acos(-1);
const double eps = 1e-10;
VI x, y, r;
PD a[233];
int n;
double sqr(double x){return x * x;}
double dist(int i, int j){
	return sqrt(sqr(x[i] - x[j]) + sqr(y[i] - y[j]));
}
bool check(double t){
	a[1] = PD(2 * pi, 666);
	int m = 1;
	rep(i, 1, n - 1){
		if (t + r[0] + r[i] < dist(0, i)) continue; // not intersect
		double l0 = sqrt(sqr(dist(0, i)) - sqr(r[0])), theta; // the length of the tangent line 
		if (t + r[i] < l0)
			theta = acos((sqr(r[0]) + sqr(dist(0, i)) - sqr(r[i] + t)) / (2 * r[0] * dist(0, i))); // Law of Cosines
		else{
			theta = acos(r[0] / dist(0, i)) + (t + r[i] - l0) / r[0];
			if (theta > pi) return 0; // included
		}
		double t0 = atan2(y[i] - y[0], x[i] - x[0]);
		double L = t0 - theta, R = t0 + theta;
		if (L < 0) L += 2 * pi;
		if (R < 0) R += 2 * pi;
		if (L < R) a[++m] = PD(L, R);
		else a[++m] = PD(L, 2 * pi), a[++m] = PD(0, R);
	}
	sort(a + 1, a + m + 1);
	double mx = 0;
	rep(i, 1, m) if (a[i].first < mx + eps) mx = max(mx, a[i].second);
	return mx < 666;
}
class CircusTents{
	public:
	double findMaximumDistance(VI _x, VI _y, VI _r){
		n = _x.size();
		x = _x; y = _y; r = _r;
		double l = 0, r = 233333;
		while (l + eps < r){
			double m = (l + r) / 2;
			(check(m) ? l : r) = m;
		}
		return l;
	}
};

