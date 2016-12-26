/*
首先二分答案d，对于每个圆i，我们可以知道圆0中到圆i"距离"超过d的点是在哪个区间，最后看看区间有没有交集就好了。
怎么求这个区间？每个圆i继续二分相对角度(0~π)，显然越大距离越远，求距离就分类讨论下在不在切线内就好了。
*/
#include <bits/stdc++.h>

using namespace std;

const double pi = acos(-1);

struct node
{
	double x,y;

	node(void){}
	node(double a,double b) : x(a),y(b){}

	double len()
	{
		return sqrt(x * x + y * y);
	}
};

node operator -(const node &a,const node &b) {return node(a.x - b.x,a.y - b.y);}

struct circ
{
	node p;double r;

	circ(void){}
	circ(node p_a,double r_a) : p(p_a),r(r_a){}
};

class CircusTents
{
public:
	double ang[105],len[105];
	circ c[105];
	int n;

	double normal(double ang)
	{
		for(;ang < 0;ang += 2 * pi);
		for(;ang > 2 * pi;ang -= 2 * pi);
		return ang;
	}

	double dis(double ang,int u) //求距离，注意过了切点要先在圆弧到切点再走直线
	{
		ang = normal(ang);
		if (ang > pi) ang = 2 * pi - ang;
		double l = len[u],l1 = l * l - c[0].r * c[0].r;
		double theta = acos((c[0].r * c[0].r + l * l - l1) / (2 * l * c[0].r));
		if (ang <= theta)
		{
			return sqrt(c[0].r * c[0].r + len[u] * len[u] - 2 * len[u] * c[0].r * cos(ang)) - c[u].r;
		} else
		{
			double dis = sqrt(c[0].r * c[0].r + len[u] * len[u] - 2 * len[u] * c[0].r * cos(theta)) - c[u].r;
			return dis + (ang - theta) * c[0].r;
		}
	}

	bool test(double d)
	{
		vector<double> ava;
		ava.clear();
		for(int i = 1;i < n;i ++)
		{
			ang[i] = atan2(c[i].p.y,c[i].p.x);
			len[i] = c[i].p.len();
			double l = 0,r = pi,tmp = pi + 1;
			for(int j = 1;j <= 100;j ++) //可以二分来求可行范围，角度越大，距离越大
			{
				double mid = (l + r) / 2;
				if (dis(mid,i) >= d) tmp = mid,r = mid; else l = mid;
			}
			if (tmp > pi + 0.5) return 0;
			ava.push_back(normal(tmp + ang[i])),ava.push_back(normal(ang[i] - tmp));
		}
		sort(ava.begin(),ava.end());
		ava.push_back(*ava.begin() + 2 * pi);
		//交集必然包含某个端点，枚举端点，判断是否存在一个端点合法
		for(int i = 0;i < ava.size() - 1;i ++)
		{
			double ref = (ava[i] + ava[i + 1]) / 2;
			bool ok = 1;
			for(int j = 1;j < n;j ++)
				if (dis(ref - ang[j],j) < d) {ok = 0;break;}
			if (ok) return 1; 
		}
		return 0;
	}

	double findMaximumDistance(vector<int> x, vector<int> y, vector<int> r)
	{
		n = x.size();
		for(int i = 0;i < n;i ++) c[i] = circ(node(x[i],y[i]),r[i]);
		for(int i = 1;i < n;i ++)
			c[i].p = c[i].p - c[0].p;
		double l = 0,rr = 50000,tmp = 0;
		for(int i = 1;i <= 100;i ++)
		{
			double mid = (l + rr) / 2;
			if (test(mid)) tmp = mid,l = mid; else rr = mid;
		}
		return tmp;
	}
};
