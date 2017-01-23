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
class CentaurCompany
{
	int n,a[50],b[100],c[100];
	double f[50][50][50],g[50][50][50],p;
	inline void add(int i,int j,int k)
	{
		b[k]=j;
		c[k]=a[i];
		a[i]=k;
	}
	inline void dp(int i,int j)
	{
		int k,l,u,v,w;
		f[i][1][1]=g[i][0][0]=0.5;
		for(k=a[i];k>0;k=c[k])
		  if(b[k]!=j)
		    {
			 dp(b[k],i);
			 for(l=n;l>=0;l--)
			   for(u=n;u>=0;u--)
			     {
				  f[i][l][u]*=g[b[k]][0][0];
				  g[i][l][u]*=g[b[k]][0][0];
				  for(v=1;v<=l;v++)
				    for(w=1;w<=u;w++)
				      {
					   f[i][l][u]+=f[i][l-v][u-w]*g[b[k]][v][w]+f[i][l-v][u-w+1]*f[b[k]][v][w];
					   g[i][l][u]+=g[i][l-v][u-w]*g[b[k]][v][w]+g[i][l-v][u-w]*f[b[k]][v][w];
					  }
				 }
			}
	}
public:
	double getvalue(vector<int> x,vector<int> y)
	{
		int i,j;
		n=x.size()+1;
		for(i=0;i<n-1;i++)
		  {
		   add(x[i],y[i],2*i+1);
		   add(y[i],x[i],2*i+2);
		  }
		//计算一个人的贡献*2 
		dp(1,0);
		for(i=0;i<=n;i++)
		  for(j=0;j<=n;j++)
		    p+=max(2*j-i-2,0)*(f[1][i][j]+g[1][i][j]);
		return 2*p;
    }
};
