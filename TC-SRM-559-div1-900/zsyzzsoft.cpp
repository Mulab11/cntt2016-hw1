#include <algorithm>
#include <math.h>
using namespace std;
class CircusTents
{
public:
	int n;
	double x[50], y[50], r[50];
	vector<pair<double, int> > evt;
	double Pow(double t)
	{
		return t * t;
	}
	double Dist(int i)
	{
		return sqrt(Pow(x[i] - x[0]) + Pow(y[i] - y[0]));
	}
	double DistP(int i)
	{
		return Pow(x[i] - x[0]) + Pow(y[i] - y[0]);
	}
	double MinDist(int i) //最短距离 
	{
		return Dist(i) - r[i] - r[0];
	}
	double DirectDist(int i) //切线距离 
	{
		return sqrt(DistP(i) - Pow(r[0]));
	}
	double CalcAngle(double a, double b, double c) //余弦定理 
	{
		return (a * a + b * b - c * c) / (a * b * 2.0);
	}
	void Event(double l, double r)
	{
		evt.push_back(make_pair(l, -1));
		evt.push_back(make_pair(r, 1));
	}
	void Cover(double l, double r) //覆盖角度[l, r] 
	{
		if(l < 0.0)
			Event(l + M_PI * 2.0, M_PI * 2.0), Event(0.0, r);
		else if(r > M_PI * 2.0)
			Event(l, M_PI * 2.0), Event(0.0, r - M_PI * 2.0);
		else
			Event(l, r);
	}
	bool Check(double d)
	{
		evt.clear();
		for(int i = 1; i < n; i++) //枚举每个圆，处理出与当前圆最短路不超过d的角度区间 
		{
			if(MinDist(i) >= d)
				continue;
			double rest = d - (DirectDist(i) - r[i]);
			double field_angle = acos(r[0] / Dist(i)); //可直达的角度范围 
			if(rest < 0)
				field_angle = acos(CalcAngle(r[0], Dist(i), d + r[i]));
			else
			{
				field_angle += rest / r[0]; //需要绕一段圆弧才能直达 
				if(field_angle >= M_PI)
					return false;
			}
			double center_angle = acos((x[i] - x[0]) / Dist(i)); //连心线的倾斜角 
			if(y[i] < y[0])
				center_angle = M_PI * 2.0 - center_angle;
			Cover(center_angle - field_angle, center_angle + field_angle); //覆盖不可行的角度区间 
		}
		if(!evt.size())
			return true;
		sort(evt.begin(), evt.end()); //扫描角度区间，判断是否有未被覆盖的点 
		for(int i = 0, j = 0; i < evt.size() && evt[i].first < M_PI * 2.0; i++)
		{
			if((j -= evt[i].second) == 0)
				return true;
		}
		return false;
	}
	double findMaximumDistance(vector<int> _x, vector<int> _y, vector<int> _r)
	{
		n = _x.size();
		for(int i = 0; i < n; i++)
			x[i] = _x[i], y[i] = _y[i], r[i] = _r[i];
		double l = 0.0, r = 1.0e4;
		while(r - l >= 1e-10) //二分答案 
		{
			double mid = (l + r) / 2.0;
			if(Check(mid))
				l = mid;
			else
				r = mid;
		}
		return l;
	}
};
