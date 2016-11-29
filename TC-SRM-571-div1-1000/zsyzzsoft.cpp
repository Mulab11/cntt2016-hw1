#include <algorithm>
#include <queue>
using namespace std;
const double eps = 1.0e-6;
class CandyOnDisk
{
public:
	int n;
	queue<int> que;
	double l[50], h[50];
	double Dist(int ax, int ay, int bx, int by)
	{
		return sqrt((double)(ax - bx) * (ax - bx) + (double)(ay - by) * (ay - by));
	}
	string ableToAchieve(vector<int> x, vector<int> y, vector<int> r, int sx, int sy, int tx, int ty)
	{
		if(sx == tx && sy == ty)
			return "YES";
		n = r.size();
		for(int i = 0; i < n; i++)
			l[i] = 1.0e10, h[i] = -1.0;
		bool vis[50] = {0};
		for(int i = 0; i < n; i++)
		{
			double d = Dist(sx, sy, x[i], y[i]);
			if(d <= r[i])
			{
				l[i] = h[i] = d;
				que.push(i);
				vis[i] = true;
			}
		}
		while(!que.empty())
		{
			int cur = que.front();
			que.pop();
			for(int i = 0; i < n; i++)
			{
				double d = Dist(x[cur], y[cur], x[i], y[i]);
				if(d > h[cur] + r[i])
					continue;
				if(l[cur] > d + r[i] || r[cur] < d - r[i])
					continue;
				double lo = max(d - r[cur], 0.0), hi = min(d + r[cur], (double)r[i]); //走到下一个圆的半径区间 
				if(x[cur] == x[i] && y[cur] == y[i])
					lo = l[cur], hi = min(h[cur], (double)r[i]);
				if(lo > hi)
					continue;
				if(lo <= l[i] - eps || hi >= h[i] + eps)
				{
					l[i] = min(l[i], lo), h[i] = max(h[i], hi); //更新半径区间 
					if(!vis[i])
						que.push(i), vis[i] = true;
				}
			}
			vis[cur] = false;
		}
		for(int i = 0; i < n; i++)
		{
			double d = Dist(tx, ty, x[i], y[i]);
			if(l[i] == h[i])
			{
				if(abs(sx - x[i]) == abs(tx - x[i]) && abs(sy - y[i]) == abs(ty - y[i]))
					return "YES";
			}
			else if(d >= l[i] && d <= h[i])
				return "YES";
		}
		return "NO";
	}
};