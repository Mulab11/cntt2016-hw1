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
class PenguinEmperor
{
	int n,f[360][360],g[360][360],u[360][360],v[360][360],w[360][360],q=1000000007;
	inline void clear(int u[360][360])
	{
		int i,j;
		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		    u[i][j]=0;
	}
	inline void init(int u[360][360])
	{
		int i;
		clear(u);
		for(i=0;i<n;i++)
		  u[i][i]=1;
	}
	inline void cheng(int v[360][360])
	{
		int i,j,k;
		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		    if(i==0)
		      for(k=0;k<n;k++)
			    w[i][j]=(w[i][j]+(L)u[i][k]*v[k][j])%q;
			else
			  w[i][j]=w[0][(j-i+n)%n];
		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		    {
			 u[i][j]=w[i][j];
			 w[i][j]=0;
			}
	}
	inline void orz(int m)
	{
		int i,j,k;
		clear(f);
		for(i=0;i<n;i++)
		  f[i][i]=1;
		for(k=1;k<=m;k++)
		  {
		   clear(g);
		   for(i=0;i<n;i++)
		     {
			  for(j=0;j<n;j++)
			    g[i][j]=(g[i][j]+f[(i+k)%n][j])%q;
			  if((i+k)%n!=(i-k+n)%n)
			    for(j=0;j<n;j++)
			      g[i][j]=(g[i][j]+f[(i-k+n)%n][j])%q;
			 }
		   for(i=0;i<n;i++)
		     for(j=0;j<n;j++)
		       f[i][j]=g[i][j];
		  }
		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		    v[i][j]=f[j][i];
	}
public:
	int countJourneys(int nn,long long m)
	{
		long long i;
		n=nn;
		orz(n);
		init(u);
		//矩乘 
		for(i=1;i<=m/n;i<<=1);
		for(i>>=1;i>0;i>>=1)
		  {
		   cheng(u);
		   if(m/n&i)
		     cheng(v);
		  }
		orz(m%n);
		cheng(v);
		return u[0][0];
    }
};
