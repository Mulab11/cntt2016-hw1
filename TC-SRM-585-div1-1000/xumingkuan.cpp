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
const int MAXN = 242424;
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

class EnclosingTriangle
{
private:
	int n;//number of black points
	Point a[MAXN];//red points
	Point b[25];//black points
	int f[MAXN], g[MAXN];//f[i]: max j: edge i->j is valid; g[i]: min j>i: edge j->i is valid
	long long sum[MAXN];//sum[i]: sum(j=1~i) f[i] 
	bool checkedge(const Point &u, const Point &v)
	{
		for(int i = 1; i <= n; i++)
			if(det(v - u, b[i] - u) < 0)
				return false;
		return true;
	}
public:
	long long getNumber(int m, vector<int> x, vector<int> y)
	{
		n = x.size();
		for(int i = 1; i <= n; i++)
			b[i] = Point(x[i - 1], y[i - 1]);
		for(int i = 0; i < m; i++)//counter-clockwise order
			a[i + 1] = Point(i, 0);
		for(int i = 0; i < m; i++)
			a[m + i + 1] = Point(m, i);
		for(int i = 0; i < m; i++)
			a[m * 2 + i + 1] = Point(m - i, m);
		for(int i = 0; i < m; i++)
			a[m * 3 + i + 1] = Point(0, m - i);
		f[0] = g[0] = 1;
		sum[0] = 0;
		for(int i = 1; i <= m * 4; i++)
		{
			f[i] = f[i - 1];
			while(f[i] < m * 4 && checkedge(a[i], a[f[i] + 1]))
				f[i]++;
			g[i] = g[i - 1] + (g[i - 1] == i);
			while(g[i] <= m * 4 && !checkedge(a[g[i]], a[i]))
				g[i]++;
			sum[i] = sum[i - 1] + f[i];
		}
		long long ans = 0;
		int ptr = 1;//min b > i: f[b] >= g[i]
		for(int i = 1; i <= m * 4; i++)
		{
			while(ptr <= i || (ptr <= f[i] && f[ptr] < g[i]))
				ptr++;
			ans += sum[f[i]] - sum[ptr - 1] - (long long)(g[i] - 1) * (f[i] - ptr + 1) - (f[i] == g[i]);
		}
		return ans;
	}
};

