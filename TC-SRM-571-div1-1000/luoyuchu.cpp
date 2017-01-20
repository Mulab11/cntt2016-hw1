#include <bits/stdc++.h>

#define dig(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

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

const int maxn = 55;
const long double eps = 1e-11;
const long double pi = acos(-1.0);

int n;
pair<long double, long double> bound[maxn];
struct Point
{
	long double x, y;
	Point() {}
	Point(double _x, double _y):x(_x), y(_y) {}
	Point operator - (const Point &b) const
	{
		return Point(x - b.x, y - b.y);
	}
	Point operator + (const Point &b) const
	{
		return Point(x + b.x, y + b.y);
	}
	Point operator * (const long double &b) const
	{
		return Point(x * b, y * b);
	}
};
struct Circle
{
	Point x;
	long double r;
}c[maxn];
int line[maxn + 5];
bool ever[maxn];
int h = 0, t = 0;

int dcmp(long double f)//比较函数
{
	if (fabs(f) < eps) {
		return 0;
	}
	return (f > 0) ? 1 : -1;
}

long double Dist(const Point &a)//求距离
{
	return sqrt(a.x * a.x + a.y * a.y);
}

void Addline(int p)//加入队列
{
	if (ever[p] == 0) {
		ever[p] = 1;
		line[h] = p;
		h = (h == maxn) ? 0 : (h + 1);
	}
}

void Update(int p, long double l, long double r)//更新一个圆盘的可达半径
{
	static bool ok;
	ok = 0;
	if (dcmp(l - bound[p].first) < 0) {
		bound[p].first = l;
		ok = 1;
	}
	if (dcmp(r - bound[p].second) > 0) {
		bound[p].second = r;
		ok = 1;
	}
	if (ok) Addline(p);
}

void Solve()
{
	int now;
	long double L, dis;
	while (h != t) {
		now = line[t];
		t = (t == maxn) ? 0 : (t + 1);
		ever[now] = 0;
		for (int i = 1; i <= n; ++i) {
			if (i == now) continue;
			if (dcmp(Dist(c[i].x - c[now].x) - (c[i].r + c[now].r)) > 0) continue;//两圆相离
			if (dcmp(c[i].x.x - c[now].x.x) == 0 && dcmp(c[i].x.y - c[now].x.y) == 0) {//如果时同心圆，要特殊处理
				Update(i, bound[now].first, bound[now].second);
				continue;
			}
			long double l, r, al, ar;
			l = bound[now].first;
			r = bound[now].second;
			al = 2e9; ar = -2e9;
			dis = Dist(c[i].x - c[now].x);
			if (dcmp(c[i].r - fabs(dis - l)) >= 0 || dcmp(c[i].r - fabs(dis - r)) >= 0) {//检查now这个圆是否能更新到i圆
				l = 0;
				r = c[now].r;
				if (dis < r) Ckmin(al, (long double)0), Ckmax(ar, (long double)0);//是否包含i的圆心
				L = fabs(dis - r); Ckmin(al, L); Ckmax(ar, L);//更新
				L = dis + r; Ckmin(al, L); Ckmax(ar, L);
				L = dis; Ckmin(al, L); Ckmax(ar, L);
				Ckmin(ar, c[i].r);
				Update(i, al, ar);
			}
		}
	}
}

class CandyOnDisk {
    public:
    string ableToAchieve(vector<int> x, vector<int> y, vector<int> r, int sx, int sy, int tx, int ty) {
		n = x.size();
		Point st = Point(sx, sy), ed = Point(tx, ty);
		for (int i = 1; i <= n; ++i) {
			c[i].x = Point(x[i - 1], y[i - 1]);
			c[i].r = r[i - 1];
			bound[i].first = 2e9;
			bound[i].second = -2e9;
		}
		for (int i = 1; i <= n; ++i) {//求出起点属于那些圆盘，以及所在的半径
			if (dcmp(Dist(st - c[i].x) - c[i].r) <= 0) {
				Update(i, Dist(st - c[i].x), Dist(st - c[i].x));
			}
		}
		Solve();//Spfa更新
		bool ok = 0;
		if (sx == tx && sy == ty) ok = 1;//起点终点重合
		for (int i = 1; i <= n; ++i) {//检查终点是否被一个圆盘的可达半径覆盖
			if (dcmp(Dist(ed - c[i].x) - bound[i].first) >= 0 && dcmp(Dist(ed - c[i].x) - bound[i].second) <= 0) {
				ok = 1;
			}
		}
		if (ok) return "YES";
        else return "NO";
    }
};
