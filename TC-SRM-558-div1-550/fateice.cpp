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
class Ear
{
	int n,m,w[310],x[310],y[310];
	long long p;
	inline void get(vector<string> a,int &n,int x[])
	{
		int i,j,k;
		string s;
		s.clear();
		for(i=0;i<a.size();i++)
		  s+=a[i];
		n=0;
		for(i=0;i<s.size();i=j+1)
		  {
		   for(j=i,k=0;j<s.size() && s[j]!=' ';j++)
		     k=(k<<3)+(k<<1)+s[j]-'0';
		   x[++n]=k;
		  }
	}
	inline long long C(int n,int m)
	{
		int i;
		long long p=1;
		for(i=n;i>n-m;i--)
		  p*=i;
		for(i=1;i<=m;i++)
		  p/=i;
		return p;
	}
public:
	long long getCount(vector<string> a,vector<string> b,vector<string> c)
	{
		int i,j,k,l1,r1,l2,r2;
		double t;
		get(a,n,w);
		get(b,m,x);
		get(c,m,y);
		sort(w+1,w+n+1);
		for(i=1;i<=m;i++)
		  for(j=1;j<=m;j++)
		    if(y[i]>y[j])
		      {
			   //查找斜线位置 
			   t=x[i]+double(x[j]-x[i])/(y[i]-y[j])*y[i];
			   for(k=1;k<=n;k++)
			     if(w[k]>=t-1e-6)
			       break;
			   if(x[i]<x[j])
			     r1=n-k+(fabs(w[k]-t)>1e-6);
			   else
			     l1=k-1;
			   //查找垂直位置 
			   for(k=1;k<=n;k++)
			     if(w[k]>=x[i])
			       break;
			   if(x[i]<x[j])
			     l1=k-1;
			   else
			     r1=n-k+(w[k]!=x[i]);
			   for(k=1;k<=n;k++)
			     if(w[k]>=x[j])
			       break;
			   l2=k-1;
			   r2=n-k+(w[k]!=x[j]);
			   p+=(C(l2,2)-C(l2-l1,2))*(C(r2,2)-C(r2-r1,2));
		  	  }
		return p;
    }
};
