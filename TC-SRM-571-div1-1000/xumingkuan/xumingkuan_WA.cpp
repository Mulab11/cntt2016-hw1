//反正能过System Test，不删了
//Challenge succeeded by wangyurzee
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
const long double EPS = 1e-6;
int cmp(long double x)
{
	return x > EPS ? 1 : x < -EPS ? -1 : 0;
}
class Point
{
public:
	long double x, y;
	Point(){}
	Point(long double x, long double y): x(x), y(y) {}
	Point operator -(const Point &b) const
	{
		return Point(x - b.x, y - b.y);
	}
	long double len2() const
	{
		return x * x + y * y;
	}
	long double len() const
	{
		return sqrt(len2());
	}
};
class CandyOnDisk
{
private:
	long double f[60];//f[i]: min radius achievable on disk #i
	bool visit[60];
	int n;//number of disks
	Point o[60], s, t;
	queue<int> q;
public:
	string ableToAchieve(vector<int> x, vector<int> y, vector<int> r, int sx, int sy, int tx, int ty)
	{
		n = x.size();
		for(int i = 0; i < n; i++)
			o[i] = Point(x[i], y[i]);
		s = Point(sx, sy);
		t = Point(tx, ty);
		if(cmp((s - t).len2()) == 0)//s == t
			return "YES";
		memset(visit, false, sizeof(visit));
		for(int i = 0; i < n; i++)
			if(cmp((s - o[i]).len2() - (long double)r[i] * r[i]) <= 0 && cmp((s - o[i]).len2() - (t - o[i]).len2()) == 0)//achievable using only 1 disk
				return "YES";
		for(int i = 0; i < n; i++)
		{
			f[i] = r[i];
			for(int j = 0; j < n; j++)
				if(cmp((o[i] - o[j]).len2()) != 0)//concentric circles are useless
					f[i] = min(f[i], max((long double)0, (o[i] - o[j]).len() - r[j]));
		}
		for(int i = 0; i < n; i++)
			if(cmp((s - o[i]).len2() - (long double)r[i] * r[i]) <= 0 && cmp((s - o[i]).len2() - f[i] * f[i]) >= 0)//able to achieve the edge of disk #i
				visit[i] = true, q.push(i);
		while(!q.empty())//bfs
		{
			int now = q.front();
			q.pop();
			for(int i = 0; i < n; i++)
				if(!visit[i] && cmp((o[i] - o[now]).len2()) != 0 && cmp((o[now] - o[i]).len2() - (long double)(r[i] + r[now]) * (r[i] + r[now])) <= 0)//intersect or contain but not concentric
					visit[i] = true, q.push(i);
		}
		for(int i = 0; i < n; i++)
			if(visit[i] && cmp((t - o[i]).len2() - (long double)r[i] * r[i]) <= 0 && cmp((t - o[i]).len2() - f[i] * f[i]) >= 0)//able to achieve the edge of disk #i
				return "YES";
		return "NO";
	}
};

