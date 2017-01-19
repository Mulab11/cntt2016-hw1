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
class HatRack
{
	int n,a[60],b[120],c[120],f[60],h[60];
	long long p,g[60];
	inline void dp(int i,int j)
	{
		int k,l=0,r=0;
		for(k=a[i];k>0;k=c[k])
		  if(b[k]!=j)
		    {
			 dp(b[k],i);
			 if(!l)
			   l=b[k];
			 else if(!r)
			   r=b[k];
			 else
			   return;
			}
		if(h[l]<h[r])
		  swap(l,r);
		if(h[l]==h[r] && !f[l] && !f[r])
		  {
		   g[i]=g[l]*g[r]*(1+(l>0));
		   h[i]=h[l]+1;
		  }
		else if(h[l]==h[r] && f[l]+f[r]==1 || h[l]==h[r]+1 && !f[r])
		  {
		   f[i]=1;
		   g[i]=g[l]*g[r];
		   h[i]=h[l]+1;
		  }
	}
	inline void js(int x)
	{
		int i;
		for(i=1;i<=n;i++)
		  f[i]=g[i]=h[i]=0;
		g[0]=1;
		dp(x,0);
		p+=g[x];
	}
public:
	long long countWays(vector<int> x,vector<int> y)
	{
		int i,j;
		n=x.size()+1;
		for(i=1;i<n;i++)
		  {
		   b[2*i-1]=y[i-1];
		   c[2*i-1]=a[x[i-1]];
		   a[x[i-1]]=2*i-1;
		   b[2*i]=x[i-1];
		   c[2*i]=a[y[i-1]];
		   a[y[i-1]]=2*i;
		  }
		for(i=1;i<=n;i++)
		  js(i);
		return p;
    }
};
