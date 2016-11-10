#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

const double pi = acos(-1);
const double eps = 1e-9;
const double pac = (sqrt(5) - 1) / 2;
struct Point
{
	double x, y;
	double length() {return sqrt(x * x + y * y);}
	Point operator - (const Point& p) {return (Point) {x - p.x, y - p.y};}
	double operator * (const Point& p) {return x * p.y - y * p.x;}
	double operator / (const Point& p) {return x * p.x + y * p.y;}
};

struct Circle
{
	Point p;
	int r;
	double pp, kk, ll, rr, pl, pr;
	bool type;
} cir[60];

double cut[160];

double ans = -1;
int N;
void cmax(double &a, const double& b) {if(a < b) a = b;}
void cmin(double &a, const double& b) {if(a > b) a = b;}
double circle_dist(double x)
{
	x = fmod(x, 2 * pi);
	while(x < 0) x += 2 * pi;
	return min(x, 2 * pi - x);
}
double calc(double a)
{
	Point p = (Point) {cir->r * cos(a), cir->r * sin(a)};
	double ans = 1.0 / 0.0;
	for(int i = 1; i != N; ++i)
		if(cir[i].type)
			cmin(ans, (cir[i].p - p).length() - cir[i].r);
		else
		{
			cmin(ans, cir[i].pl + cir->r * circle_dist(cir[i].ll - a));
			cmin(ans, cir[i].pr + cir->r * circle_dist(cir[i].rr - a));
		}
	cmax(::ans, ans);
	return ans;
}

class CircusTents
{
public:
	double findMaximumDistance(vector<int> cx, vector<int> cy, vector<int> cr)
	{
		N = cx.size();
		for(int i = 0; i != N; ++i) cir[i] = (Circle) {(Point) {cx[i], cy[i]}, cr[i]};
		// 把第 0 个圆的坐标弄成原点
		for(int i = N - 1; i; --i)
		{
			cir[i].p.x -= cir->p.x,
			cir[i].p.y -= cir->p.y;
		}
		// 求其他圆圆心和 0 圆的切点
		int C = 0;
		for(int i = 1; i != N; ++i)
		{
			double p = cir[i].pp = fmod(atan2(cir[i].p.y, cir[i].p.x) + pi + 10 * pi, 2 * pi);
			double k = cir[i].kk = fmod(pi - acos(cir->r / cir[i].p.length()) + 10 * pi, 2 * pi);
			cut[C++] = p;
			cir[i].pl = (((Point) {cir->r * cos(p - k), cir->r * sin(p - k)}) - cir[i].p).length() - cir[i].r;
			cir[i].pr = (((Point) {cir->r * cos(p + k), cir->r * sin(p + k)}) - cir[i].p).length() - cir[i].r;
			cir[i].ll = fmod(cir[i].pp - cir[i].kk + 10 * pi, 2 * pi);
			cir[i].rr = fmod(cir[i].pp + cir[i].kk + 10 * pi, 2 * pi);
			cut[C++] = fmod(cir[i].ll, 2 * pi);
			cut[C++] = fmod(cir[i].rr, 2 * pi);
		}
		cut[C++] = 0;
		cut[C++] = 2 * pi;
		sort(cut, cut + C);
		// 每一段内是取切线还是取直线距离是确定的了
		// 每一种距离函数的单调性也都确定了
		// 似乎就可以暴力三分了
		for(int _ = 1; _ != C; ++_)
		{
			double l = cut[_ - 1], r = cut[_];
			if(r - l < eps) continue;
			// 判断每一个圆的类型
			double v = fmod((l + r) / 2 + 10 * pi, 2 * pi);
			// 如果中点和圆心的连线和圆没有交，就是直线距离，否则是切线长度+弧长
			for(int i = 1; i != N; ++i)
			{
				double &l = cir[i].ll, &r = cir[i].rr;
				if(l <= r) cir[i].type = !(l <= v && v <= r);
				else cir[i].type = !(v <= r || l <= v);
			}
			// 开始三分！
			while(r - l > eps)
			{
				double a = l + (r - l) * (1 - pac);
				double b = l + (r - l) * pac;
				if(calc(a) > calc(b))
					r = b; else l = a;
			}
		}
		return ans;
	}
}   user;
