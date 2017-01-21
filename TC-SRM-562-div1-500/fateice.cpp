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
#define pi 3.1415926535897932
using namespace std;
struct orz
{
	double w;
	int p;
}a[600];
inline bool cmp(orz a,orz b)
{
	return a.w<b.w;
}
class CheckerFreeness
{
	int n,m,x[300],y[300],xx[300],yy[300];
	double t[300];
	long long p;
	inline void get(vector<string> a,int x[],int &n)
	{
		int i;
		string b;
		b.clear();
		for(i=0;i<a.size();i++)
		  b+=a[i];
		n=0;
		for(i=0;i<b.size();i++)
		  {
		   x[++n]=0;
		   for(;i<b.size() && b[i]>='0' && b[i]<='9';i++)
		     x[n]=x[n]*10+b[i]-'0';
		  }
	}
public:
	string isFree(vector<string> x1,vector<string> y1,vector<string> x2,vector<string> y2)
	{
		int i,j,k,l;
		get(x1,x,n);
		get(y1,y,n);
		get(x2,xx,m);
		get(y2,yy,m);
		//统计黑点在白点两侧的四边形个数 
		for(i=1;i<n;i++)
		  for(j=i+1;j<=n;j++)
		    {
			 for(k=1,l=0;k<=m;k++)
			   if((L)(x[i]-xx[k])*(y[j]-yy[k])-(L)(x[j]-xx[k])*(y[i]-yy[k])>0)
			     l++;
			 p+=l*(m-l);
			}
		//减去某个白点内角>180度的四边形个数 
		for(i=1;i<=n;i++)
		  {
		   for(j=1;j<=m;j++)
		     {
		      t[j]=atan2(yy[j]-y[i],xx[j]-x[i]);
		      t[j]=(t[j]>0?(t[j]-pi):(t[j]+pi));
			 }
		   sort(t+1,t+m+1);
		   for(j=1;j<=m;j++)
		     {
			  a[j].w=t[j];
			  a[j].p=0;
			  for(k=1;k<j;k++)
			    if(t[j]-t[k]<pi)
			      a[j].p++;
			    else
			      {
				   a[j].p--;
				   p-=n-1;
				  }
			  for(k=j+1;k<=m;k++)
			    if(t[k]-t[j]<pi)
			      a[j].p--;
			    else
				  a[j].p++;
			 }
		   for(j=1;j<=n;j++)
		     if(i!=j)
		       {
			    a[m+j-(j>i)].w=atan2(y[j]-y[i],x[j]-x[i]);
			    a[m+j-(j>i)].p=10000;
			   }
		   sort(a+1,a+n+m,cmp);
		   for(j=1,k=0;j<n+m;j++)
		     if(a[j].p==10000)
		       k++;
		     else
		       p-=k*a[j].p;
		  }
		if(!p)
		  return "YES";
		else
		  return "NO";
    }
};
