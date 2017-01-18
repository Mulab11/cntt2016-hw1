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
};
long long det(const Point &a, const Point &b)
{
	return (long long)a.x * b.y - (long long)a.y * b.x;
}
long long dot(const Point &a, const Point &b)
{
	return (long long)a.x * b.x + (long long)a.y * b.y;
}
class Constellation
{
private:
	int n;
	Point a[55];//star
	double p[55];//prob
public:
	double expectation(vector<int> x, vector<int> y, vector<int> prob)
	{
		n = x.size();
		for(int i = 0; i < n; i++)
			a[i] = Point(x[i], y[i]), p[i] = prob[i] / 1000.0;
		double ans = 0.0;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				if(i != j)//i -> j is on the convex hull
				{
					double now = p[i] * p[j];
					for(int k = 0; k < n; k++)
						if(k != i && k != j)
						{
							long long tmp = det(a[k] - a[i], a[j] - a[i]);
							if(tmp > 0 || (tmp == 0 && dot(a[k] - a[i], a[k] - a[j]) < 0))
								now *= 1 - p[k];
						}
					ans += now * det(a[i], a[j]);// / 2
				}
		return ans / 2;
	}
};

