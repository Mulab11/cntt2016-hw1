#include <algorithm>
using namespace std;
struct Point
{
	int x, y;
	Point() {x = y = 0; }
	Point(int _x, int _y) {x = _x, y = _y; }
	Point operator - (const Point &_pt) const
	{
		return Point(x - _pt.x, y - _pt.y);
	}
	long long operator * (const Point &_pt) const
	{
		return (long long)x * _pt.y - (long long)y * _pt.x;
	}
};
int n, m, que[300000];
long long sum[300000];
Point bd[300000], pt[20];
class EnclosingTriangle
{
public:
	bool Valid(Point a, Point b)
	{
		for(int i = 0; i < m; i++)
		{
			if((b - a) * (pt[i] - a) > 0)
				return false;
		}
		return true;
	}
	long long getNumber(int _m, vector<int> x, vector<int> y)
	{
		m = _m;
		for(int i = 0; i < m; i++)
			bd[n++] = Point(0, i);
		for(int i = 0; i < m; i++)
			bd[n++] = Point(i, m);
		for(int i = 0; i < m; i++)
			bd[n++] = Point(m, m - i);
		for(int i = 0; i < m; i++)
			bd[n++] = Point(m - i, 0);
		m = x.size();
		for(int i = 0; i < m; i++)
			pt[i] = Point(x[i], y[i]);
		long long ans = 0;
		for(int i = 0, j = 0, k = 1, l = 0, r = 1; i < n; i++) //枚举一个点 
		{
			while(k < n && !Valid(bd[k], bd[i])) //最后一个点的最小值 
				k++;
			while(j < n && Valid(bd[i], bd[j])) //扫描第二个点 
			{
				for(que[r] = que[r - 1]; que[r] < n && Valid(bd[j], bd[que[r]]); que[r]++);
				sum[r] = sum[r - 1] + que[r]; //加入队列并维护前缀和 
				r++, j++;
			}
			while(l < r && k >= que[l]) //在队列中找到对应区间 
				l++;
			l = max(l, i + 2);
			ans += sum[r - 1] - sum[l - 1] - (long long)k * (r - l); //统计答案 
			if(r - 1 == k + 1) //端点不能重合 
				ans--;
		}
		return ans;
	}
};