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
	bool visit[60];
	int n;//number of disks
	Point o[60], s, t;
	queue<int> q;
	vector<pair<long double, long double> > temp;
	int getpos(const Point &s, const Point &o, long double l, long double r)
	{
		long double tmp = (s - o).len();
		return tmp < l + EPS ? -1 : tmp > r - EPS ? 1 : 0;
	}
public:
	string ableToAchieve(vector<int> x, vector<int> y, vector<int> r, int sx, int sy, int tx, int ty)
	{
		n = x.size();
		for(int i = 0; i < n; i++)
			o[i] = Point(x[i], y[i]);
		s = Point(sx, sy), t = Point(tx, ty);
		if(cmp((s - t).len2()) == 0)//s == t
			return "YES";
		for(int i = 0; i < n; i++)
			if(cmp((s - o[i]).len2() - (long double)r[i] * r[i]) <= 0 && cmp((s - o[i]).len2() - (t - o[i]).len2()) == 0)//achievable using only 1 disk
				return "YES";
		for(int i = 0; i < n; i++)
		{
			temp.clear();
			for(int j = 0; j < n; j++)
				if(cmp((o[i] - o[j]).len2()) != 0)//concentric circles are useless
					temp.push_back(make_pair((o[i] - o[j]).len() - r[j], (o[i] - o[j]).len() + r[j]));//<min, max> distance between disk #j's edge and disk #i's center
			temp.push_back(make_pair(r[i], r[i]));
			sort(temp.begin(), temp.end());
			long double nowmax = 0;
			for(int j = 0; j < temp.size(); j++)
			{
				if(cmp(temp[j].first - nowmax) > 0)//unreachable area (nowmax, temp[j].first)
					if(getpos(s, o[i], nowmax, temp[j].first) * getpos(t, o[i], nowmax, temp[j].first) <= 0)
						return "NO";
				if(temp[j].second > nowmax)
					nowmax = temp[j].second;
				if(cmp(nowmax - r[i]) >= 0)
					break;
			}
		}
		memset(visit, false, sizeof(visit));
		for(int i = 0; i < n; i++)
			if(cmp((s - o[i]).len2() - (long double)r[i] * r[i]) <= 0)//S is in disk #i
				visit[i] = true, q.push(i);
		while(!q.empty())//bfs
		{
			int now = q.front();
			q.pop();
			for(int i = 0; i < n; i++)
				if(!visit[i] && cmp((o[now] - o[i]).len2() - (long double)(r[i] + r[now]) * (r[i] + r[now])) <= 0)//intersect or contain
					visit[i] = true, q.push(i);
		}
		for(int i = 0; i < n; i++)
			if(visit[i] && cmp((t - o[i]).len2() - (long double)r[i] * r[i]) <= 0)//T is in disk #i
				return "YES";
		return "NO";
	}
};

