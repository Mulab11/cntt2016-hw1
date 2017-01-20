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

const int maxn = 55;
const int maxm = 3e5+155;

int n, N;
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
}dot[maxn], r[maxm];
LL seg[maxm * 4], ad[maxm * 4], sl[maxm * 4];//线段树及其标记
int Rb[maxm], Lb[maxm];

LL Cross(const Point &a, const Point &b)
{
    return (LL)a.x * b.y - (LL)a.y * b.x;
}

void Pd(int p)
{
    if (ad[p] != 0) {
        ad[p << 1] += ad[p];
        ad[p << 1 | 1] += ad[p];
        seg[p << 1] += ad[p] * sl[p << 1];
        seg[p << 1 | 1] += ad[p] * sl[p << 1 | 1];
        ad[p] = 0;
    }
}

void Build(int l, int r, int p)//线段树初始化
{
    int mid = (l + r) / 2;
    seg[p] = 0;
    ad[p] = 0;
    sl[p] = r - l + 1;
    if (l == r) {
        return;
    }
    Build(l, mid, p << 1);
    Build(mid + 1, r, p << 1 | 1);
}

void Add(int l, int r, int L, int R, int val, int p)//区间加
{
    int mid = (l + r) / 2;
    if (L <= l && R >= r) {
        seg[p] += sl[p] * val;
        ad[p] += val;
        return;
    }
    if (ad[p]) Pd(p);
    if (L <= mid) Add(l, mid, L, R, val, p << 1);
    if (R > mid) Add(mid + 1, r, L, R, val, p << 1 | 1);
    seg[p] = seg[p << 1] + seg[p << 1 | 1];
}

LL Query(int l, int r, int L, int R, int p)//区间询问
{
    int mid = (l + r) / 2;
    if (L <= l && R >= r) {
        return seg[p];
    }
    if (ad[p]) Pd(p);
    if (R <= mid) return Query(l, mid, L, R, p << 1);
    else if (L > mid) return Query(mid + 1, r, L, R, p << 1 | 1);
    return (LL)Query(l, mid, L, R, p << 1) + Query(mid + 1, r, L, R, p << 1 | 1);
}

void Prepare()//考虑对于三角形的底边的两个店，如果边界上第i个作为底边的左/右边界，顶点一定是一段后缀/前缀和，预先求出来
{
    int p = 1, np;
    bool ok;
    for (int i = 0; i < N; ++i) {//右边界
        while (1) {
            ok = 1;
            np = (p + 1) % N;
            for (int j = 1; j <= n; ++j) {
                if (Cross(r[np] - r[i], dot[j] - r[i]) < 0) {
                    ok = 0;
                    break;
                }
            }
            if (ok) p = np;
            else break;
        }
        Rb[i] = p;
    }
    p = N - 2;
    for (int i = N - 1; i >= 0; --i) {//左边界
        while (1) {
            ok = 1;
            np = (p - 1 + N) % N;
            for (int j = 1; j <= n; ++j) {
                if (Cross(r[np] - r[i], dot[j] - r[i]) > 0) {
                    ok = 0;
                    break;
                }
            }
            if (ok) p = np;
            else break;
        }
        Lb[i] = p;
    }
}

void Change_R(int x, int val)//将这个点的能取到的顶点区间加一/减一
{
    if (x == N - 1) {
        Add(1, N, N, N, val, 1);
        Add(1, N, 1, Rb[x] + 1, val, 1);
    }
    else if (Rb[x] >= x) {
        Add(1, N, x + 2, Rb[x] + 1, val, 1);
        //dig("+ %d %d\n", x + 1, Rb[x]);
    }
    else {
        Add(1, N, x + 2, N, val, 1);
        //dig("+ %d %d\n", x + 1, N - 1);
        Add(1, N, 1, Rb[x] + 1, val, 1);
        //dig("+ %d %d\n", 0, Rb[x]);
    }
}

LL Query_L(int x)//询问这个点能取到的顶点区间
{
    if (x == 0) {
        return Query(1, N, Lb[x] + 1, N, 1);
    }
    else if (Lb[x] <= x) {
        return Query(1, N, Lb[x] + 1, x, 1);
    }
    else {
        return Query(1, N, 1, x, 1) + Query(1, N, Lb[x] + 1, N, 1);
    }
}

LL Solve()
{
    LL Ans = 0;
    int p, np;
    bool ok;
    Build(1, N, 1);
    Change_R(0, 1);
    Change_R(1, 1);
    p = 1;
    for (int i = 0; i < N; ++i) {//扫描底边的左端点，用线段树维护这个左端点能取到的右端点的顶点情况之和
        Change_R(i, -1);
        while (1) {
            ok = 1;
            np = (p + 1) % N;
            for (int j = 1; j <= n; ++j) {
                if (Cross(r[np] - r[i], dot[j] - r[i]) < 0) {
                    ok = 0;
                    break;
                }
            }
            if (ok) {
                p = np;
                Change_R(p, 1);
            }
            else break;
        }
        Ans += Query_L(i);
    }
    return Ans;//返回答案
}

class EnclosingTriangle {
    public:
    long long getNumber(int m, vector<int> x, vector<int> y) {
        N = 0;
        n = x.size();
        for (int i = 1; i <= n; ++i) dot[i] = Point(x[i - 1], y[i - 1]);
        for (int i = 0; i <= m; ++i) r[N++] = Point(i, 0);
        for (int i = 1; i <= m; ++i) r[N++] = Point(m, i);
        for (int i = m - 1; i >= 0; --i) r[N++] = Point(i, m);
        for (int i = m - 1; i >= 1; --i) r[N++] = Point(0, i);
        Prepare();
        return Solve() / 3;//由于一个三角形会被三条边作为底边计算3次，所以除以3
    }
};
