#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<iomanip>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<queue>
#include<stack>
using namespace std;
#define MAXN 1010
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
const double pi=acos(-1);
struct pt
{
	double x;
	double y;
	pt()
	{
		
	}
	pt(double _x,double _y)
	{
		x=_x;
		y=_y;
	}
	friend pt operator -(pt x,pt y)
	{
		return pt(x.x-y.x,x.y-y.y);
	}
};
struct itv
{
	double l;
	double r;
	itv()
	{
		
	}
	itv(double _l,double _r)
	{
		l=_l;
		r=_r;
	}
	friend bool operator <(itv x,itv y)
	{
		return x.l<y.l;
	}
};
itv b[MAXN];
int n;
pt a[MAXN];
double r[MAXN];
int tot;
double sq(double x)
{
	return x*x;
}
double dis(pt x,pt y)
{
	return sqrt(sq(x.x-y.x)+sq(x.y-y.y));
}
double cal(double x)
{
	return x/r[1];
}
bool OK(double X)
{
	int i;
	tot=0;
	for(i=2;i<=n;i++)
	{
		double diso=dis(a[1],a[i]);
		if(r[1]+r[i]+X>diso)
		{//计算不合法的区间 
			double angj=100;
			double len=sqrt(sq(diso)-sq(r[1]));
			if(r[1]+diso>r[i]+X)
			{
				angj=acos((sq(r[1])+sq(diso)-sq(r[i]+X))/(2*r[1]*diso));
			}
			double angq=acos((sq(r[1])+sq(diso)-sq(len))/(2*r[1]*diso));//计算交点连成的圆心角和切点连成的圆心角 
			if(angj>angq)
			{
				angj=angq+cal(r[i]+X-len);
			}
			if(angj>=pi)
			{
				return 0;
			}
			double mid=atan2((a[i]-a[1]).y,(a[i]-a[1]).x);
			double l=mid-angj;
			double r=mid+angj;
			if(l<=-pi)
			{
				b[++tot]=itv(-pi,r);
				b[++tot]=itv(l+2*pi,pi);
			}
			else if(r>pi)
			{
				b[++tot]=itv(l,pi);
				b[++tot]=itv(-pi,r-2*pi);
			}
			else
			{
				b[++tot]=itv(l,r);
			}
		}
	}
	sort(b+1,b+tot+1);
	double now=-pi;
	for(i=1;i<=tot;i++)
	{//判断是否有一个合法的点 
		if(b[i].l>now)
		{
			return 1;
		}
		now=max(now,b[i].r);
	}
	if(now>=pi-eps)
	{
		return 0;
	}
	return 1;
}
struct CircusTents
{
	double findMaximumDistance(vector<int>_x,vector<int>_y,vector<int>_r)
	{
		int i;
		n=_x.size();
		for(i=1;i<=n;i++)
		{
			a[i]=pt(_x[i-1],_y[i-1]);
			r[i]=_r[i-1];
		}
		double l=0;
		double r=200000;
		double ans;
		int tmp=200;
		while(tmp--)
		{//二分答案 
			double mid=(l+r)/2;
			if(OK(mid))
			{
				ans=mid;
				l=mid+1;
			}
			else
			{
				r=mid-1;
			}
		}
		return ans;
	}
};

/*

*/