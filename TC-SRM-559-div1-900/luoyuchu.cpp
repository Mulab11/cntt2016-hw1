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

const double pi = acos(-1.0);
const int maxn = 55;

int n;
int X[maxn], Y[maxn], R[maxn];//每个圆的坐标半径
double la[maxn], ra[maxn], C;//la,ra为每个圆心对于0号圆的切线的弧度区间，区间之内的最短弧线长度都是单峰的
double stop[maxn * 2];//所有切点
int st = 0;

double Dist(double x, double y)//求距离
{
	return sqrt(x * x + y * y);
}

double Adist(int p, double ang)//求出0号圆上一个弧度为ang的点到p号圆的距离
{
	double x, y;
	x = cos(ang) * R[0];
	y = sin(ang) * R[0];
	return Dist(x - X[p], y - Y[p]) - R[p];
}

double Standardizing(double a)//将a这个弧度转化带(-pi,pi)区间中
{
	while (a > pi) a -= pi * 2;
	while (a < -pi) a += pi * 2;
	return a;
}

void Getpoint()//求出所有切点的弧度
{
	stop[++st] = -pi;
	stop[++st] = pi;
	for (int i = 1; i < n; ++i) {
		ra[i] = stop[++st] = Standardizing(pi / 2 - (pi / 2 - acos(R[0] / Dist(X[i], Y[i])) - atan2(Y[i], X[i])));
		la[i] = stop[++st] = Standardizing(-pi / 2 + (atan2(Y[i], X[i]) - (-pi / 2) - acos(R[0] / Dist(X[i], Y[i]))));
	}
}

bool Isin(int x, double ang)//是否在弧度区间内
{
	if (la[x] < ra[x]) return (ang >= la[x] && ang <= ra[x]);
	else return (ang >= la[x] || ang <= ra[x]);
}

double Nearest(int p, double ang)//求出与ang最近的p号圆心与0号圆的切点
{
	double det = 2e9;
	Ckmin(det, fabs(ang - la[p]));
	Ckmin(det, fabs(ang - la[p] + pi * 2));
	Ckmin(det, fabs(ang - la[p] - pi * 2));
	Ckmin(det, fabs(ang - ra[p]));
	Ckmin(det, fabs(ang - ra[p] + pi * 2));
	Ckmin(det, fabs(ang - ra[p] - pi * 2));
	return det;
}

double Shortest(double ang)//求出如果将售票机设在0号圆弧度为ang的点处，最短曲线是多少
{
	double ans = 2e9;
	for (int i = 1; i < n; ++i) {
		if (Isin(i, ang)) {
			Ckmin(ans, Adist(i, ang));
		}
		else {
			Ckmin(ans, Adist(i, la[i]) + C / pi / 2 * Nearest(i, ang));
		}
	}
	return ans;
}

double Solve()//对于每个区间，由于最短曲线单峰，所以可以三分
{
	double ans = 0;
	double l, r, mid1, mid2;
	sort(stop + 1, stop + 1 + st);
	for (int i = 1; i < st; ++i) {
		l = stop[i];
		r = stop[i + 1];
		while (r - l > 1e-14) {
			mid1 = l + (r - l) / 3;
			mid2 = l + (r - l) / 3 * 2;
			if (Shortest(mid1) < Shortest(mid2)) l = mid1;
			else r = mid2;
		}
		Ckmax(ans, Shortest(l));
	}
	return ans;
}

class CircusTents {
    public:
    double findMaximumDistance(vector<int> _x, vector<int> _y, vector<int> _r) {
		n = _x.size();
		for (int i = 0; i < n; ++i) {
			X[i] = _x[i];
			Y[i] = _y[i];
			R[i] = _r[i];
		}
		for (int i = 1; i < n; ++i) X[i] -= X[0], Y[i] -= Y[0];//以0号圆心为坐标原点
		C = pi * 2 * R[0];//0号圆周长
		Getpoint();//求切点
        return Solve();//分段三分求答案
    }
};

