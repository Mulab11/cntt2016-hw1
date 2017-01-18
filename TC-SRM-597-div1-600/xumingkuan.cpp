#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <cctype>
#include <cassert>
using namespace std;
class Point
{
public:
	int x, y;
	Point(){}
	Point(int x, int y): x(x), y(y) {}
	Point operator -(const Point &b) const
	{
		return Point(x - b.x, y - b.y);
	}
	void write() const
	{
		printf("(%d,%d)\n", x, y);
	}
};
long long dot(const Point &a, const Point &b)
{
	return (long long)a.x * b.x + (long long)a.y * b.y;
}
long long det(const Point &a, const Point &b)
{
	return (long long)a.x * b.y - (long long)a.y * b.x;
}
class ConvexPolygonGame
{
private:
	int n, upn, downn, inn;
	Point up[55], down[55];//convex hull
	Point in1, in2;
	bool add(const Point &p)
	{
		if(inn < 2)
		{
			(inn++ ? in2 : in1) = p;
			return true;
		}
		return !det(p - in1, p - in2);
	}
public:
	string winner(vector<int> X, vector<int> Y)
	{
		n = X.size();
		int now = 0;
		for(int i = 1; i < n; i++)//get min X
			if(X[i] < X[now])
				now = i;
		if(X[(now + 1) % n] == X[now])
			now = (now + 1) % n;
		int minx = X[now];
		down[downn = 1] = Point(X[now], Y[now]);
		while(X[(now + 1) % n] > X[now])
		{
			now = (now + 1) % n;
			down[++downn] = Point(X[now], Y[now]);
		}
		if(X[(now + 1) % n] == X[now])
			now = (now + 1) % n;
		int maxx = X[now];
		up[upn = 1] = Point(X[now], Y[now]);
		while(X[(now + 1) % n] < X[now])
		{
			now = (now + 1) % n;
			up[++upn] = Point(X[now], Y[now]);
		}
		reverse(up + 1, up + upn + 1);
		inn = 0;
		int upptr = 1, downptr = 1;//two pointers
		for(int i = minx; i <= maxx; i++)//enum x
		{
			if(up[upptr + 1].x < i)
				upptr++;
			if(down[downptr + 1].x < i)
				downptr++;
			Point p1 = up[upptr], p2 = up[upptr + 1];
			if(p1.y > p2.y)
				swap(p1, p2);
			int upy = p1.y + (long long)(p2.y - p1.y) * abs(i - p1.x) / abs(p2.x - p1.x) - (i == p1.x || i == p2.x);
			p1 = down[downptr], p2 = down[downptr + 1];
			if(p1.y < p2.y)
				swap(p1, p2);
			int downy = p1.y - (long long)(p1.y - p2.y) * abs(i - p1.x) / abs(p2.x - p1.x) + (i == p1.x || i == p2.x);
			for(int j = downy; j <= upy; j++)//enum y
				if(!add(Point(i, j)))
					return "Masha";
		}
		return "Petya";
	}
};

