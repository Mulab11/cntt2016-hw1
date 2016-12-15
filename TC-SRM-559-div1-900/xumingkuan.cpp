#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <cctype>
#include <queue>
#include <map>
using namespace std;

const double EPS = 1e-9, PI = acos(-1.0);
int cmp(double a, double b)//>_1   ==_0   <_-1
{
	return (a <= b + EPS && a >= b - EPS) ? 0 : ((a > b) ? 1 : -1);
}
int cmp(double a)
{
	return a > EPS ? 1 : a < -EPS ? -1 : 0;
}
double sqrt1(double a)
{
	if(a < 0)
		return 0;
	return sqrt(a);
}
class Point
{
	public:
		double x, y;
		Point(){}
		Point(double _x, double _y)
		{
			x = _x;
			y = _y;
		}
		Point operator +(const Point &b) const
		{
			return Point(x + b.x, y + b.y);
		}
		Point operator -(const Point &b) const
		{
			return Point(x - b.x, y - b.y);
		}
		Point operator *(double b) const
		{
			return Point(x * b, y * b);
		}
		Point operator /(double b) const
		{
			return Point(x / b, y / b);
		}
		Point& operator +=(const Point &b)
		{
			return *this = *this + b;
		}
		Point& operator -=(const Point &b)
		{
			return *this = *this - b;
		}
		Point& operator *=(double b)
		{
			return *this = *this * b;
		}
		Point& operator /=(double b)
		{
			return *this = *this / b;
		}
		bool operator <(const Point &b) const
		{
			return cmp(x, b.x) == 0 ? cmp(y, b.y) < 0 : cmp(x, b.x) < 0;//x == b.x ? y < b.y : x < b.x;
		}
		bool operator >(const Point &b) const
		{
			return b < *this;
		}
		bool operator ==(const Point &b) const
		{
			return cmp(x, b.x) == 0 && cmp(y, b.y) == 0;//x == b.x && y == b.y;
		}
		bool operator <=(const Point &b) const
		{
			return !(*this > b);
		}
		bool operator >=(const Point &b) const
		{
			return !(*this < b);
		}
		bool operator !=(const Point &b) const
		{
			return !(*this == b);
		}
		double len2() const
		{
			return x * x + y * y;
		}
		double len() const
		{
			return sqrt(len2());
		}
		void read()
		{
			scanf("%lf%lf", &x, &y);
		}
		void write2() const
		{
			printf("%.2lf %.2lf\n", x, y);
		}
		void write5() const
		{
			printf("%.5lf %.5lf\n", x, y);
		}
		Point unit() const
		{
			return *this / len();
		}
		Point& tounit()
		{
			return *this = *this / len();
		}
		Point normal() const
		{
			return Point(-y, x);
		}
		Point symmetry(const Point &b) const
		{
			return b + b - *this;
		}
		double angle() const
		{
			return atan2(y, x);
		}
};
Point operator *(double b, const Point &a)
{
	return Point(a.x * b, a.y * b);
}
Point middle(const Point &a, const Point &b)
{
	return (a + b) / 2;
}
double dot(const Point &a, const Point &b)
{
	return a.x * b.x + a.y * b.y;
}
double det(const Point &a, const Point &b)
{
	return a.x * b.y - a.y * b.x;
}
int intersection(const Point &a, const Point &b, const Point &c, const Point &d, Point &o)
{
	if(cmp(det(b - a, d - c)) == 0)
		return 0;
	double s1 = det(d - a, c - a);
	double s2 = det(c - b, d - b);
	o = a + (b - a) * s1 / (s1 + s2);
	return 1;
}
int line_segment_intersection(const Point &a, const Point &b, const Point &c, const Point &d, Point &o)
{
	if(intersection(a, b, c, d, o) == 0)
		return 0;
	return cmp(dot(o - a, o - b)) <= 0 && cmp(dot(o - c, o - d)) <= 0;
}
/*Point projection(const Point &a, const Point &b, const Point &p)
{
	Point h;
	double tmp = dot(p, b - a);
	if(cmp(b.y, a.y) != 0)
		intersection(a, b, p, Point(p.x + 1.0, (tmp - (p.x + 1.0) * (b.x - a.x)) / (b.y - a.y)), h);
	else
		intersection(a, b, p, Point((tmp - (p.y + 1.0) * (b.y - a.y)) / (b.x - a.x), p.y + 1.0), h);
	return h;
}*/
Point projection(const Point &a, const Point &b, const Point &p)
{
	return a + dot(p - a, (b - a).unit()) * (b - a).unit();
}
Point symmetry(const Point &a, const Point &b, const Point &p)
{
	return p.symmetry(projection(a, b, p));
}
bool in_triangle(const Point &a, const Point &b, const Point &c, const Point &p)
{
	return cmp(fabs(det(a - p, b - p)) + fabs(det(b - p, c - p)) + fabs(det(c - p, a - p)), fabs(det(a - b, c - b))) == 0;
}
bool convex_tetragon(const Point &a, const Point &b, const Point &c, const Point &d)
{
	return !in_triangle(a, b, c, d) && !in_triangle(b, c, d, a) && !in_triangle(c, d, a, b) && !in_triangle(d, a, b, c);
}
int circumcenter(const Point &a, const Point &b, const Point &c, Point &o)
{
	return intersection(middle(a, b), middle(a, b) + (a - b).normal(), middle(b, c), middle(b, c) + (b - c).normal(), o);
}
int circle_line_intersection(const Point &o, double r, const Point &a, const Point &b, Point &p1, Point &p2)
{
	Point h = projection(a, b, o);
	double tmp = r * r - (h - o).len2();
	int tmp1 = cmp(tmp);
	if(tmp1 == -1)
		return 0;
	else if(tmp1 == 0)
	{
		p1 = h;
		return 1;
	}
	else
	{
		p1 = a - b;
		p1 /= p1.len();
		p1 *= sqrt(tmp);
		p2 = h - p1;
		p1 += h;
		return 2;
	}
}
int circle_line_segment_intersection(const Point &o, double r, const Point &a, const Point &b, Point &p1, Point &p2)
{
	int tmp = circle_line_intersection(o, r, a, b, p1, p2);
	bool o1 = tmp >= 1 && cmp(dot(p1 - a, p1 - b)) <= 0;
	bool o2 = tmp == 2 && cmp(dot(p2 - a, p2 - b)) <= 0;
	if(o1 && o2)
		return 2;
	if(o1)
		return 1;
	if(o2)
	{
		p1 = p2;
		return 1;
	}
	return 0;
}
int circle_circle_intersection(const Point &o1, double r1, const Point &o2, double r2, Point &p1, Point &p2)
{
	if(o2 == o1)
		return 0;
	double tmp1 = ((o2 - o1).len2() + r1 * r1 - r2 * r2) / (2.0 * (o2 - o1).len());
	double tmp2 = r1 * r1 - tmp1 * tmp1;
	int tmp3 = cmp(tmp2);
	if(tmp3 == -1)
		return 0;
	else if(tmp3 == 0)
	{
		p1 = o1 + (o2 - o1).unit() * tmp1;
		return 1;
	}
	else
	{
		Point h = o1 + (o2 - o1).unit() * tmp1;
		p1 = (o2 - o1).unit().normal() * sqrt(tmp2);
		p2 = h - p1;
		p1 += h;
		return 2;
	}
}
double circle_point_tangent(const Point &o, double r, const Point &a, Point &p1, Point &p2)
{
	double tmp = (o - a).len2();
	if(cmp(tmp, r * r) == -1)
		return -1;
	Point h = o + (a - o) * (r * r / tmp);
	tmp = r * r - (h - o).len2();
	int tmp1 = cmp(tmp);
	if(tmp1 == -1)
		return -1;
	else if(tmp1 == 0)
	{
		p1 = h;
		return 0;
	}
	else
	{
		p1 = (a - o).unit().normal() * sqrt(tmp);
		p2 = h - p1;
		p1 += h;
		return (a - p1).len();
	}
}
double arc_length(const Point &tmp1, const Point &tmp2, double r)
{
	return acos(1.0 - (tmp1 - tmp2).len2() / (2.0 * r * r)) * r;
}
double fan_area(const Point &tmp1, const Point &tmp2, double r)
{
	return acos(1.0 - (tmp1 - tmp2).len2() / (2.0 * r * r)) * r * r / 2.0;
}
double bow_area(const Point &tmp1, const Point &tmp2, const Point &o, double r)
{
	return fan_area(tmp1, tmp2, r) - fabs(det(tmp2 - o, tmp1 - o) / 2.0);
}

class CircusTents
{
	private:
	int n;
	Point a[60], tp[60][2];//tangent point
	double r[60], cir/*circumference of the target circus tent*/, ml[60]/*min length*/, tl[60]/*length of tangent line*/, al[60]/*add length*/;
	vector <Point> now;//valid interval [x, y]
	void eraseInterval(double le, double ri)
	{
		if(le > ri)
		{
			eraseInterval(le, PI);
			eraseInterval(-PI, ri);
			return;
		}
		//printf("eraseInterval [%.5lf,%.5lf]\n", le, ri);
		int i = 0;
		while(i < now.size() && cmp(now[i].y, le) <= 0)
			i++;
		if(i == now.size())
			return;
		if(cmp(now[i].x, le) < 0 && cmp(now[i].y, ri) > 0)//split interval
		{
			now.insert(now.begin() + i + 1, Point(ri, now[i].y));
			now[i].y = le;
			return;
		}
		else if(cmp(now[i].x, le) < 0)
			now[i++].y = le;
		const int st = i;
		while(i < now.size() && cmp(now[i].y, ri) <= 0)
			i++;
		if(i < now.size() && cmp(now[i].x, ri) < 0)
			now[i].x = ri;
		now.erase(now.begin() + st, now.begin() + i);//covered intervals
	}
	bool checkValid(double ans)
	{
		//printf("checkValid %.15lf\n", ans);
		now.assign(1, Point(-PI, PI));
		for(int i = 1; i < n; i++)
		{
			if(cmp(ans, ml[i]) <= 0)
				continue;
			if(cmp(ans, tl[i] + al[i]) > 0)
				return false;
			if(cmp(ans, tl[i]) <= 0)
			{
				Point p1, p2;
				int tmp = circle_circle_intersection(a[0], r[0], a[i], ans + r[i], p1, p2);
				if(tmp == 2)
				{
					if(det(p1 - a[0], p2 - a[0]) < 0)
						swap(p1, p2);
					eraseInterval((p1 - a[0]).angle(), (p2 - a[0]).angle());
					/*printf("after circle #%d((%.0lf,%.0lf),r=%.0lf):", i, a[i].x, a[i].y, r[i]);
					for(int i = 0; i < now.size(); i++)
						printf(" [%.5lf,%.5lf]", now[i].x, now[i].y);
					printf("\n");*/
					if(now.empty())
						return false;
				}
				continue;
			}
			double tmp = (ans - tl[i]) / cir * PI * 2;
			double st = (tp[i][0] - a[0]).angle() - tmp;
			double ed = (tp[i][1] - a[0]).angle() + tmp;
			if(st < -PI)
				st += PI * 2;
			if(ed > PI)
				ed -= PI * 2;
			eraseInterval(st, ed);
			/*printf("tmp %.5lf st %.5lf ed %.5lf\n", tmp, (tp[i][0] - a[0]).angle(), (tp[i][1] - a[0]).angle());
			printf("after circle #%d((%.0lf,%.0lf),r=%.0lf):", i, a[i].x, a[i].y, r[i]);
			for(int i = 0; i < now.size(); i++)
				printf(" [%.5lf,%.5lf]", now[i].x, now[i].y);
			printf("\n");*/
			if(now.empty())
				return false;
		}
		return true;
	}
	public:
	double findMaximumDistance(vector<int> x, vector<int> y, vector<int> r)
	{
		n = x.size();
		for(int i = 0; i < n; i++)
		{
			a[i] = Point(x[i], y[i]);
			this->r[i] = r[i];
		}
		cir = r[0] * PI * 2;
		double le = 1e8, ri = 1e8;
		for(int i = 1; i < n; i++)
		{
			ml[i] = (a[i] - a[0]).len() - r[i] - r[0];
			tl[i] = circle_point_tangent(a[0], r[0], a[i], tp[i][0], tp[i][1]) - r[i];
			if(det(tp[i][0] - a[0], tp[i][1] - a[0]) < 0)
				swap(tp[i][0], tp[i][1]);
			al[i] = (cir - arc_length(tp[i][0], tp[i][1], r[0])) / 2;
			if(ml[i] < le)
				le = ml[i];
			if(tl[i] + al[i] < ri)
				ri = tl[i] + al[i];
			//printf("circle #%d((%.0lf,%.0lf),r=%d): ml=%.5lf, tl=%.5lf, al=%.5lf\n", i, a[i].x, a[i].y, r[i], ml[i], tl[i], al[i]);
		}
		while(cmp(le, ri) < 0)//er fen da an
		{
			double mi = (le + ri) / 2;
			if(checkValid(mi))
				le = mi;
			else
				ri = mi;
		}
		return le;
	}
};

