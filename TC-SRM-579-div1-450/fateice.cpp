#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
class TravellingPurchasingMan
{
	int a[16],b[16],c[16],x[50][50],f[65536][16],p[65536];  //x记录最短路  f[i][j]表示在i表示的商店集合中买好东西，当前在j号商店的最小时间  p[i]记录i的集合大小 
public:
	void read(string s,int &a,int &b,int &c)
	{
		int n=s.size();
		int i;
		a=b=c=0;
		for(i=0;i<n && s[i]!=' ';i++)
		  a=(a<<3)+(a<<1)+s[i]-'0';
		for(i++;i<n && s[i]!=' ';i++)
		  b=(b<<3)+(b<<1)+s[i]-'0';
		for(i++;i<n && s[i]!=' ';i++)
		  c=(c<<3)+(c<<1)+s[i]-'0';
	}
	int maxStores(int n,vector<string> s,vector<string> t)
	{
		int m=s.size(),ans=0;
		int i,j,k,l;
		for(i=0;i<m;i++)
		  read(s[i],a[i],b[i],c[i]);
		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		    x[i][j]=i==j?0:1000000000;
		//建边+最短路 
		for(i=0;i<t.size();i++)
		  {
		   read(t[i],j,k,l);
		   x[j][k]=x[k][j]=l;
		  }
		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		    for(k=0;k<n;k++)
		      x[j][k]=min(x[j][k],x[j][i]+x[i][k]);
		//状压dp 
		for(i=0;i<(1<<m);i++)
		  for(j=0;j<m;j++)
		    f[i][j]=1000000000;
		for(i=1;i<(1<<m);i++)
		  p[i]=p[i>>1]+(i&1);
		for(i=1;i<(1<<m);i++)
		  for(j=0;j<m;j++)
		    if((i^(1<<j))<i)
		      {
			   if((i^(1<<j))==0)
			     f[i][j]=x[j][n-1];
			   for(k=0;k<m;k++)
			     if((i^(1<<k))<i && j!=k)
			       f[i][j]=min(f[i][j],f[i^(1<<j)][k]+x[j][k]);
			   f[i][j]=max(f[i][j],a[j]);
			   if(f[i][j]<=b[j])
			     {
			      f[i][j]+=c[j];
			      ans=max(ans,p[i]);
				 }
			   else
			     f[i][j]=1000000000;
			  }
		return ans;
	}
};
