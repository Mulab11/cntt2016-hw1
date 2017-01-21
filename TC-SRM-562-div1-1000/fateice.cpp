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
class InducedSubgraphs
{
	int n,m,a[50],b[100],c[100],C[50][50],f[50][50][50],g[50],h[50],w[50],p,q=1000000009;
	inline int power(int a,int b)
	{
		if(!b)
		  return 1;
		int c=power(a,b>>1);
		c=(L)c*c%q;
		if(b&1)
		  c=(L)c*a%q;
		return c;
	}
	inline void dp(int i,int k)
	{
		int j,l=0;
		w[i]=1;
		for(j=a[i];j>0;j=c[j])
		  if(b[j]!=k)
		    {
			 h[b[j]]=h[i]+1;
			 dp(b[j],i);
			 w[i]+=w[b[j]];
			 if(w[b[j]]>n/2)
			   l=1;
			}
		if(!m && !l && n-w[i]<=n/2)
		  m=i;
	}
	inline void dp2(int i,int k)
	{
		int j,l=w[i]-1;
		g[i]=1;
		for(j=a[i];j>0;j=c[j])
		  if(b[j]!=k)
		    {
			 dp2(b[j],i);
			 g[i]=(L)g[i]*g[b[j]]%q*C[l][w[b[j]]]%q;
			 l-=w[b[j]];
			}
	}
	inline void dp3(int i,int k)
	{
		int j,l=1,x,y,z,t;
		f[i][0][0]=1;
		for(j=a[i];j>0;j=c[j])
		  if(b[j]!=k)
		    {
			 dp3(b[j],i);
			 for(x=0;x<=l;x++)
			   for(y=0;x+y<=l;y++)
			     for(z=0;z<=w[b[j]];z++)
			       for(t=0;z+t<=w[b[j]];t++)
			         f[0][x+z][y+t]=(f[0][x+z][y+t]+(L)f[i][x][y]*f[b[j]][z][t]%q*C[x+z][x]%q*C[y+t][y])%q;
			 for(x=0;x<=l+w[b[j]];x++)
			   for(y=0;x+y<=l+w[b[j]];y++)
			     {
				  f[i][x][y]=f[0][x][y];
			      f[0][x][y]=0;
			     }
			 l+=w[b[j]];
			}
		f[i][w[i]][0]=f[i][w[i]-1][0];
		f[i][0][w[i]]=f[i][0][w[i]-1];
	}
public:
	int getCount(vector<int> x,vector<int> y,int k)
	{
		int i,j;
		n=x.size()+1;
		for(i=0;i<n-1;i++)
		  {
		   b[2*i+1]=y[i]+1;
		   c[2*i+1]=a[x[i]+1];
		   a[x[i]+1]=2*i+1;
		   b[2*i+2]=x[i]+1;
		   c[2*i+2]=a[y[i]+1];
		   a[y[i]+1]=2*i+2;
		  }
		dp(1,0);
		h[m]=0;
		dp(m,0);
		for(i=0;i<=n;i++)
		  {
		   C[i][0]=1;
		   for(j=1;j<=i;j++)
		     C[i][j]=(C[i-1][j]+C[i-1][j-1])%q;
		  }
		//k=1时任意编号 
		if(k==1)
		  {
		   p=1;
		   for(i=1;i<=n;i++)
		     p=(L)p*i%q;
		  }
		//2k<=n时是一条长度为n-2*k+2，两个端点子树大小为k的链 
		else if(2*k<=n)
		  {
		   dp2(m,0);
		   if(2*k==n)
		     {
		      for(i=1;i<=n;i++)
		        if(w[i]==k && h[i]==1)
		          p=(L)2*g[m]*power(C[2*k-1][k],q-2)%q;
			 }
		   else
		     for(i=1;i<n;i++)
		       for(j=i+1;j<=n;j++)
		         if(w[i]==k && w[j]==k && h[i]+h[j]==n-2*k+1)
		           p=(L)2*g[i]*g[j]%q;
		  }
		//2k>n时是一个大小为2*k-n的连通块，挂若干个大小和为k的子树和另外若干个大小和为k的子树 
		else
		  {
		   dp3(m,0);
		   p=f[m][n-k][n-k];
		   for(i=1;i<=2*k-n;i++)
		     p=(L)p*i%q;
		  }
		return p;
    }
};
