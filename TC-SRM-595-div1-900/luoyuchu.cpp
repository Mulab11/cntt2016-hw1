#include <bits/stdc++.h>
using namespace std;

#define dig(...) fprintf(stderr, __VA_ARGS__)

template <class TAT>
void Ckmin(TAT &a, const TAT &b)
{
	if (a > b) a = b;
}
template <class TAT>

void Ckmax(TAT &a, const TAT &b)
{
	if (a < b) a = b;
}

typedef long long LL;

using namespace std;

const int maxn = 55;

int n, m;
double pro[maxn];
struct Point
{
	int x, y;
	Point() {}
	Point(int _x, int _y):x(_x), y(_y) {}
	Point operator + (const Point &b) const
	{
		return Point(x + b.x, y + b.y);
	}
	Point operator - (const Point &b) const
	{
		return Point(x - b.x, y - b.y);
	}
}dot[maxn];
double Dist(const Point &a)
{
	return sqrt(a.x * a.x + a.y * a.y);
}
int Cross(const Point &a, const Point &b)
{
	return a.x * b.y - a.y * b.x;
}
bool cmp_D(const Point &a, const Point &b)
{
	return a.y < b.y || (a.y == b.y && a.x < b.x);
}

double Solve()
{
	double P, Ans = 0;
	Point fr, to;
	double af, at;
	static double ang[maxn];
	for (int i = 1; i <= m; ++i) {
		ang[i] = atan2(dot[i].y, dot[i].x);
	}
	for (int i = 1; i <= m; ++i) {
		for (int j = i + 1; j <= m; ++j) {//对于其他任何两个点组成的线段，计算这条线段时凸包的一条边的概率
			P = pro[i] * pro[j];
			if (Cross(dot[i], dot[j]) > 0 || (Cross(dot[i], dot[j]) == 0 && Dist(dot[i]) < Dist(dot[j]))) {
				fr = dot[i], to = dot[j];
				af = ang[i], at = ang[j];
			}
			else {
				fr = dot[j], to = dot[i];
				af = ang[j], at = ang[i];
			}
			for (int k = 1; k <= m; ++k) {
				if (k == i || k == j) continue;
				if (Cross(dot[k] - fr, to - fr) > 0 || (Cross(dot[k] - fr, to - fr) == 0 && ang[k] >= af && ang[k] <= at)) {
					P *= (1 - pro[k]);
				}
			}
			Ans += Cross(fr, to) / 2.0 * P;//计算他对期望的贡献
		}
	}
	return Ans;//返回答案
}

class Constellation {
    public:
    double expectation(vector<int> x, vector<int> y, vector<int> prob) {
		static Point a[maxn];
		static double pr[maxn];
		double Ans = 0, P;
		n = x.size();
		for (int i = 0; i < n; ++i) {
			a[i + 1] = Point(x[i], y[i]);
		}
		sort(a + 1, a + 1 + n, cmp_D);
		for (int i = 0; i < n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (a[j].x == x[i] && a[j].y == y[i]) {
					pr[j] = prob[i] / 1000.0;
					break;
				}
			}
		}
		P = 1;
		for (int i = 1; i <= n; ++i) {//枚举将所有点按y为第一关键字升序，x为第二关键字升序排序出现的第一个点时哪一个
			m = 0;
			for (int j = i + 1; j <= n; ++j) {
				dot[++m] = a[j] - a[i];
				pro[m] = pr[j];
			}
			Ans += Solve() * P * pr[i];//这个点一定在凸包上，再计算其他点组成的线段对凸包面积的贡献
			P *= (1 - pr[i]);
		}
        return Ans;//返回答案
    }
};
