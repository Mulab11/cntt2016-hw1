#include <bits/stdc++.h>

#define dig(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

template <class TAT>
void Ckmax(TAT &a, const TAT &b)
{
    if (a < b) a = b;
}
template <class TAT>
void Ckmin(TAT &a, const TAT &b)
{
    if (a > b) a = b;
}

typedef long long LL;

struct Point
{
    long double x, y;
    Point() {}
    Point(long double _x, long double _y):x(_x), y(_y) {}
    Point operator + (const Point &b) const
    {
        return Point(x + b.x, y + b.y);
    }
    Point operator - (const Point &b) const
    {
        return Point(x - b.x, y - b.y);
    }
    Point operator * (const double &b) const
    {
        return Point(x * b, y * b);
    }
};
struct Vector
{
    Point x, d;
    Vector() {}
    Vector(Point _x, Point _d):x(_x), d(_d) {}
};

long double Cross(const Point &a, const Point &b)//差积
{
    return a.x * b.y - a.y * b.x;
}

Point Inter(const Vector &a, const Vector &b)//求交点
{
    long double s = Cross(b.d, a.d);
    long double ks = Cross(a.d, b.x - a.x);
    return b.x + (b.d * (ks / s));
}

long double Solve(int W)
{
    long double Ans = 0;
    Vector lx, rx;
    Point lp, rp;
    lp = Point(0, 1);
    rp = Point(W, 1);
    lx = Vector(lp, Point(W, -1));
    rx = Vector(rp, Point(-W, -1));
    for (int i = 0; i < W; i += 2) {//对于中间部分的三角形，由于高是一样的可以一排一排的算
        Point ld, rd, sd, xd;
        ld = Inter(rx, Vector(lp, Point(i, -1)));
        rd = Inter(lx, Vector(rp, Point(-i, -1)));
        sd = Inter(rx, Vector(lp, Point(i + 1, -1)));
        Ans += (rd.x - ld.x) * (sd.y - rd.y) / 2;
        if (i + 1 == W) {
            Ans += (1 - sd.y) * W / 2;
        }
        if (i != 0) {
            xd = Inter(rx, Vector(lp, Point(i - 1, -1)));
            Ans += (rd.x - ld.x) * (rd.y - xd.y) / 2;
        }
    }
    for (int i = 1; i < W; i += 2) {//暴力计算两边的三角形
        Point sd, xd;
        sd = Inter(rx, Vector(lp, Point(i + 1, -1)));
        xd = Inter(rx, Vector(lp, Point(i, -1)));
        Ans += Cross(xd - lp, sd - lp);
    }
    return W - Ans;//由于计算的是答案的补集
}

class TriangleXor {
    public:
    int theArea(int W) {
        return floor(Solve(W));
    }
};
