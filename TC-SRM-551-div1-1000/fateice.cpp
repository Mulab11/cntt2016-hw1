#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define L long long
using namespace std;
struct orz
{
	int a,b;
}w[1050000];
inline bool cmp(int a,int b)
{
	return a>b;
}
inline bool cmp2(orz a,orz b)
{
	return a.a<b.a;
}
class SweetFruits
{
	int n,m,t,a[100],x[100][100],f[100],c[100][100],s[1050000],p,q,r;
	int y[1050000],z;
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
	inline void dfs(int i,int j,int k)
	{
		if(i>(t>>1))
		  {
		   w[++r].a=j;
		   w[r].b=k;
		   return;
		  }
		dfs(i+1,j,k);
		dfs(i+1,j+a[i],k+1);
	}
	inline int ef(int k)
	{
		int l=1,rr=r;
		while(l<r)
		  if(w[l+r+1>>1].a<=k)
		    l=(l+r+1>>1);
		  else
		    r=(l+r+1>>1)-1;
		r=rr;
		return l;
	}
	inline void dfs2(int i,int j,int k,int l)
	{
		if(i>t)
		  {
		   if(j<=m)
		     {
			  int u;
			  if(!y[++z])
			    {
			     u=ef(m-j);
			     y[z]=u+1;
				}
			  else
			    u=y[z]-1;
			  p=(p+(L)s[u]*f[l+k])%q;
			 }
		   return;
		  }
		dfs2(i+1,j,k,l);
		dfs2(i+1,j+a[i],k+1,l);
	} 
public:
	int countTrees(vector<int> aa,int mm)
	{
		int i,j,k,l,u;
		n=aa.size();
		m=mm;
		q=1000000007;
		for(i=1;i<=n;i++)
		  a[i]=aa[i-1];
		sort(a+1,a+n+1,cmp);
		for(t=1;t<=n && a[t]>=0;t++);
		t--;
		for(i=0;i<=t;i++)
		  {
		   c[i][0]=1;
		   for(j=1;j<=i;j++)
		     c[i][j]=(c[i-1][j]+c[i-1][j-1])%q;
		  }
		//matrix-tree求出真甜水果数<=i的方案数 
		for(i=0;i<=t;i++)
		  {
		   for(j=1;j<=n;j++)
		     for(k=1;k<=n;k++)
		       x[j][k]=0;
		   for(j=1;j<=i;j++)
		     {
			  x[j][j]=n-t+max(i-1,0);
			  for(k=1;k<=i;k++)
			    if(j!=k)
			      x[j][k]=-1;
			  for(k=t+1;k<=n;k++)
			    x[j][k]=-1;
			 }
		   for(;j<=t;j++)
		     {
			  x[j][j]=n-t;
			  for(k=t+1;k<=n;k++)
			    x[j][k]=-1;
			 }
		   for(;j<=n;j++)
		     {
			  x[j][j]=n-1;
			  for(k=1;k<=n;k++)
			    if(j!=k)
			      x[j][k]=-1;
			 }
		   f[i]=1;
		   for(j=1;j<n;j++)
		     {
			  for(k=j;k<=n;k++)
			    if(x[k][j])
			      break;
			  if(k>n)
			    {
				 f[i]=0;
				 break;
				}
			  if(j!=k)
			    f[i]=-f[i];
			  for(l=1;l<=n;l++)
			    swap(x[j][l],x[k][l]);
			  k=power(x[j][j],q-2);
			  f[i]=(L)f[i]*x[j][j]%q;
			  for(l=1;l<=n;l++)
			    x[j][l]=(L)x[j][l]*k%q;
			  for(k=j+1;k<=n;k++)
			    if(x[k][j])
			      for(l=n;l>=j;l--)
			        x[k][l]=(x[k][l]-(L)x[j][l]*x[k][j])%q;
			 }
		  }
		//计算真甜水果数=i的方案数 
		for(i=1;i<=t;i++)
		  for(j=0;j<i;j++)
		    f[i]=(f[i]-(L)c[i][j]*f[j])%q;
		//meet-in-the-middle
		dfs(1,0,0);
		sort(w+1,w+r+1,cmp2);
		for(j=0;j<=(t>>1);j++)
		  {
		   for(i=1;i<=r;i++)
		     s[i]=s[i-1]+(w[i].b==j);
		   z=0;
		   dfs2((t>>1)+1,0,0,j);
		  }
		return (p+q)%q;
	}
};
