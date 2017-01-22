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
#define inf 1000000000000000000ll
using namespace std;
class SkiResorts
{
	int n,m,a[3000],b[150000],c[150000],d[150000],x[3000],g[5000000];
	long long f[3000];
	bool z[3000];
	inline void add(int i,int j,int k)
	{
		b[++m]=j;
		c[m]=k;
		d[m]=a[i];
		a[i]=m;
	}
	inline void spfa()
	{
		int i,j,k,t=1;
		for(i=1;i<=n*n+1;i++)
		  f[i]=inf;
		for(i=1;i<=t;i++)
		  {
		   for(j=a[g[i]];j>0;j=d[j])
		     if(f[b[j]]>f[g[i]]+c[j])
		       {
				f[b[j]]=f[g[i]]+c[j];
				if(!z[b[j]])
				  {
				   z[b[j]]=1;
				   g[++t]=b[j];
				  }
			   }
		   z[g[i]]=0;
		  }
	}
public:
	long long minCost(vector<string> s,vector<int> y)
	{
		int i,j,k;
		n=y.size();
		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		    if(y[i]>y[j])
		      x[i]++;
		sort(&y[0],&y[0]+n);
		//拆点+spfa 
		for(i=0;i<n;i++)
		  {
		   for(j=1;j<n;j++)
		     add(i*n+j+1,i*n+j,0);
		   for(j=0;j<n;j++)
		     if(s[i][j]=='Y')
		       for(k=0;k<n;k++)
		         add(i*n+k+1,j*n+k+1,abs(y[k]-y[x[j]]));
		  }
		for(i=0;i<n;i++)
		  {
		   add(0,i+1,abs(y[i]-y[x[0]]));
		   add((n-1)*n+i+1,n*n+1,0);
		  }
		spfa();
		if(f[n*n+1]==inf)
		  return -1;
		else
		  return f[n*n+1];
    }
};
