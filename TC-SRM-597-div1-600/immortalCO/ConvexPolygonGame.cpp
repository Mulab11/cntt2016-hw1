#include <bits/stdc++.h>
using namespace std;

#ifdef assert
#undef assert
#define assert(x) ((x) ? (void) 1 : (fprintf(stderr, "Assertion \"%s\" failed on line %d.\n", #x, __LINE__), exit(6)))
#endif

const int MaxN = 55;
int N, X;
struct Point
{
	int x, y;
	bool operator < (const Point& p) const
	{
		return x < p.x || (x == p.x && y < p.y);
	}
	bool operator == (const Point& p) const
	{
		return x == p.x && y == p.y;
	}
} p[MaxN];
struct Line
{
	long double k, b; int l, r; bool d;
	bool cross() {return l <= X && X <= r;}
	long double f() const {return k * X + b;}
	bool operator < (const Line& l) const
	{
		if(fabs(f() - l.f()) > 1e-9)
			return f() < l.f();
		return d > l.d;
	}
	void make(const Point& p, const Point& q)
	{
		if((d = p.x < q.x))	l = p.x, r = q.x;
		else				l = q.x, r = p.x;
		k = (long double) (p.y - q.y) / (p.x - q.x);
		b = p.y - k * p.x;
		assert(fabs(q.y - k * q.x - b) < 1e-9);
	}
} ln[MaxN], cur[MaxN];

class ConvexPolygonGame
{
public:
	string winner(vector<int> px, vector<int> py)
	{
		N = px.size();
		int min_x = 1e9, max_x = -1e9;
		for(int i = 0; i != N; ++i)
		{
			p[i] = (Point) {px[i], py[i]};
			if(px[i] < min_x) min_x = px[i];
			if(px[i] > max_x) max_x = px[i];
		}
		p[N] = p[0];
		int L = 0;
		for(int i = 0; i != N; ++i)
			if(p[i].x != p[i + 1].x)
				ln[L++].make(p[i], p[i + 1]);
		std::sort(p, p + N);
		Point A, B;
		int count = 0;
		for(X = min_x; X <= max_x; ++X)
		{
			int Cur = 0;
			for(int i = 0; i != L; ++i)
				if(ln[i].cross()) cur[Cur++] = ln[i];
			std::sort(cur, cur + Cur);
			for(int i = 0; i < Cur; ++i)
			{
				if(!cur[i].d || (i != Cur && cur[i + 1].d)) continue;
				for(int Y = ceill(cur[i].f()), YE = floorl(cur[i + 1].f()); Y <= YE; ++Y)
				{
					if(find(p, p + N, (Point) {X, Y}) != p + N) continue;
					++count;
					if(count == 1) A = (Point) {X, Y};
					else if(count == 2) B = (Point) {X, Y};
					else
					{
						int a = A.x - X, b = A.y - Y;
						int c = B.x - X, d = B.y - Y;
						if((long long) a * d != (long long) b * c) return "Masha";
					}
				}
			}
		}
		return "Petya";
	}
}	user;
