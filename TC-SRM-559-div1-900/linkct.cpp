#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef vector <int> vi;
typedef pair <double, double> Range;
const double PI = acos(-1.0);
const int MAXN = 55;

class CircusTents{
public:
	struct Point{
		double x, y;
		Point(){}
		Point(double a, double b) :x(a), y(b) {}
		Point operator - (const Point &rhs) const{
			return Point(x - rhs.x, y - rhs.y);
		}
	}p[MAXN];
	typedef Point Vector;
	int n; vector <int> rd; vector <Range> rg;
	double pd[MAXN], pa[MAXN], td[MAXN], ta[MAXN];
	double Dot(Vector &a, Vector &b){return a.x * b.x + a.y * b.y;}
	double Length(Vector x){return sqrt(Dot(x, x));}
	double Angle(Vector a, Vector b){return acos(Dot(a, b) / Length(a) / Length(b));}
	double Cross(Vector a, Vector b){return a.x * b.y - a.y * b.x;}
	inline int dcmp(double x){return (fabs(x) <= 1e-10) ? 0 : ((x > 0.0) ? 1 : -1);}
	bool check(double dist){
		int i; double l, r, delta;
		rg.clear();
		for(i = 1; i < n; ++ i){
			if(dcmp(pd[i] - rd[i] - rd[0] - dist) >= 0) continue; //不相交
			if(dcmp(td[i] - rd[i] - dist) >= 0) //只沿直线走
				delta = acos((rd[0] * rd[0] + pd[i] * pd[i] - (dist + rd[i]) * (dist + rd[i])) / (2 * rd[0] * pd[i]));
			else delta = ta[i] + (dist - td[i] + rd[i]) / rd[0]; //走切线+一段弧
			l = pa[i] - delta, r = pa[i] + delta;
			if(l < 0) rg.push_back(Range(2 * PI + l, 2 * PI)), l = 0;
			if(r > 2 * PI) rg.push_back(Range(0, r - 2 * PI)), r = 2 * PI;
			if(l <= r) rg.push_back(Range(l, r));
		} sort(rg.begin(), rg.end());
		for(i = r = 0; i < int(rg.size()); ++ i){
			if(dcmp(rg[i].fi - r) > 0) return true;
			r = max(r, rg[i].se);
		} return dcmp(r - 2 * PI) < 0;
	}
	double findMaximumDistance(vi x, vi y, vi rd_){
		int i; double l = 0.0, r = 1e5, mid;
		n = x.size(), rd = rd_;
		for(i = 0; i < n; ++ i){
			p[i] = Point(x[i], y[i]);
			if(i){
				pd[i] = Length(p[i] - p[0]);
				pa[i] = Angle(Vector(1.0, 0.0), p[i] - p[0]); //连线的圆心角
				if(dcmp(Cross(Vector(1.0, 0.0), p[i] - p[0])) < 0) pa[i] = 2 * PI - pa[i];
				td[i] = sqrt(pd[i] * pd[i] - rd[0] * rd[0]); //切线长
				ta[i] = acos(rd[0] / pd[i]); //切线的偏移量
				r = min(r, (PI - ta[i]) * rd[0] + td[i] - rd[i]);
			}
		} cout << r << endl;
		for(i = 1; i <= 55; ++ i){
			mid = (l + r) / 2.0;
			if(check(mid)) l = mid;
			else r = mid;
		} return r;
	}
};
