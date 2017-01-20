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

int n;
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
};
vector<Point> Up, Down;

LL Cross(const Point &a, const Point &b)
{
	return (LL)a.x * b.y - (LL)a.y * b.x;
}

string Solve()
{
	Point sta[3];
	int st = 0;
	int p1 = 0, p2 = 0;
	int l, r;
	for (int i = Down[0].x, _end_ = Down.back().x; i <= _end_; ++i) {//由于所有的合法凸包形成的是树形结构，所以第一次就可以直接取到叶子结点，只需判断masha能否操作即可
		if (i >= Up[p1 + 1].x) ++p1;
		if (i >= Down[p2 + 1].x) ++p2;
		if (i == Up[p1].x) r = Up[p1].y - 1;
		else {
			r = Up[p1].y + floor((long double)(Up[p1 + 1].y - Up[p1].y) * (i - Up[p1].x) / (Up[p1 + 1].x - Up[p1].x));
		}
		if (i == Down[p2].x) l = Down[p2].y + 1;
		else {
			l = Down[p2].y + ceil((long double)(Down[p2 + 1].y - Down[p2].y) * (i - Down[p2].x) / (Down[p2 + 1].x - Down[p2].x));
		}
		for (int j = l; j <= r; ++j) {//暴力判断是否存在3点不共线
			if (st < 2) {
				sta[++st] = Point(i, j);
			}
			else {
				if (Cross(Point(i, j) - sta[1], sta[2] - sta[1]) != 0) {
					return "Masha";
				}
			}
		}
	}
	return "Petya";
}

class ConvexPolygonGame {
    public:
    string winner(vector<int> X, vector<int> Y) {
		n = X.size();
		int Min = 2e9, Max = -2e9;
		for (int i = 0; i < n; ++i) {
			Ckmin(Min, X[i]);
			Ckmax(Max, X[i]);
		}
		for (int i = 0; i < n; ++i) {//取出上凸壳与下凸壳
			if (X[i] == Min && X[(i + 1) % n] != Min) {
				for (int j = i; ; j = (j + 1) % n) {
					Down.push_back(Point(X[j], Y[j]));
					if (X[j] == Max) break;
				}
				break;
			}
		}
		for (int i = 0; i < n; ++i) {
			if (X[i] == Max && X[(i + 1) % n] != Max) {
				for (int j = i; ; j = (j + 1) % n) {
					Up.push_back(Point(X[j], Y[j]));
					if (X[j] == Min) break;
				}
				break;
			}
		}
		reverse(Up.begin(), Up.end());
		return Solve();
    }
};
