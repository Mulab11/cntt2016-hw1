#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define L long long
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
double pi=3.1415926535897932;
struct line
{
	double l,r;
}a[200];
inline bool cmp(line a,line b)
{
	return a.l<b.l;
}
class CircusTents
{
	int n,x[100],y[100],r[100];
	inline double sqr(double x)
	{
		return x*x;
	}
	inline double dis(int i,int j)
	{
		return sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j]));
	}
	inline bool pd(double p)
	{
		int i,m;
		double j,k;
		m=1;
		a[1].l=2*pi;
		a[1].r=100;
		//计算每个圆对应的不可行区间 
		for(i=2;i<=n;i++)
		  {
		   if(p<dis(1,i)-r[1]-r[i])
		     continue;
		   j=sqrt(sqr(dis(1,i))-sqr(r[1]));
		   if(p<j-r[i])
		     k=acos((sqr(r[1])+sqr(dis(1,i))-sqr(r[i]+p))/(2*r[1]*dis(1,i)));
		   else
		     {
		      k=acos(r[1]/dis(1,i))+(p+r[i]-j)/r[1];
		      if(k>pi)
		        return 0;
			 }
		   j=-k+atan2(y[i]-y[1],x[i]-x[1]);
		   k+=atan2(y[i]-y[1],x[i]-x[1]);
		   if(j<0)
		     j+=2*pi;
		   if(k<0)
		     k+=2*pi;
		   if(j<k)
		     {
			  a[++m].l=j;
			  a[m].r=k;
			 }
		   else
		     {
			  a[++m].l=j;
			  a[m].r=2*pi;
			  a[++m].l=0;
			  a[m].r=k;
			 }
		  }
		//求区间并判断是否是全集 
		sort(a+1,a+m+1,cmp);
		for(i=1,k=0;i<=m;i++)
		  if(a[i].l<k+1e-11)
		    k=max(k,a[i].r);
		return !(k>99);
	}
public:
	double findMaximumDistance(vector<int> xx,vector<int> yy,vector<int> rr)
	{
		int i;
		double a,b;
		n=xx.size();
		for(i=1;i<=n;i++)
		  {
		   x[i]=xx[i-1];
		   y[i]=yy[i-1];
		   r[i]=rr[i-1];
		  }
		//二分答案 
		for(a=0,b=100000;b-a>1e-10;)
		  if(pd((a+b)/2))
		    a=(a+b)/2;
		  else
		    b=(a+b)/2;
		return a;
    }
};
