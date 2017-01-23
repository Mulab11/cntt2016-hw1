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
class DisjointSemicircles
{
	int n,m,a[110],b[5010],c[5010],d[5010],f[110],l[110],r[110],x[110],w[110],t,p,q;
	bool g[110];
	vector<int> s;
	inline void add_(int i,int j,int k)
	{
		b[++m]=j;
		c[m]=k;
		d[m]=a[i];
		a[i]=m;
	}
	inline void add(int i,int j,int k)
	{
		add_(i,j,k);
		add_(j,i,k);
	}
	inline void dfs2(int i)
	{
		int j;
	    g[i]=1;
	    for(j=a[i];j>0;j=d[j])
	      if(!g[b[j]])
	        {
			 f[b[j]]=f[i]^c[j];
			 dfs2(b[j]);
			}
		  else if(f[b[j]]!=f[i]^c[j])
		    q=1;
	}
	inline void pd()  //二分图染色 
	{
		int i,j,k,u;
		for(i=1;i<=t;i++)
		  {
		   for(j=l[i],u=0;j<=r[i];j++)
		     if(s[j-1]<0)
		       u++;
		   j=w[r[i]];
		   if(j<l[i])
		     continue;
		   k=w[l[i]];
		   if(x[i])
		     add(j,k,0);
		   else
		     add(j,k,u&1);
		  }
		j=w[n];
		add(0,j,0);
		for(i=0;i<=n;i++)
		  if(s[i-1]<0 && !g[i])
		    {
			 f[i]=0;
			 dfs2(i);
			}
		if(!q)
		  p=1;
		q=0;
		for(i=1;i<=m;i++)
		  b[i]=c[i]=d[i]=0;
		for(i=0;i<=n;i++)
		  a[i]=g[i]=0;
		m=0;
	}
	inline void dfs(int i)  //枚举每对已经匹配好的在上还是下 
	{
		if(i>t)
		  {
		   pd();
		   return;
		  }
		if(l[i]==r[i]-1)
		  {
		   dfs(i+1);
		   return;
		  }
		int j,k;
		for(j=0;j<=1;j++)
		  {
		   x[i]=j;
		   for(k=1;k<i;k++)
		     if(x[i]==x[k] && (l[i]>l[k] && l[i]<r[k] && r[i]>r[k] || l[i]<l[k] && l[k]<r[i] && r[i]<r[k]))
		       break;
		   if(k==i)
			 dfs(i+1);
		  }
	}
public:
	string getPossibility(vector<int> ss)
	{
		int i,j,k;
		s=ss;
		n=s.size();
		for(i=0;i<n/2;i++)
		  for(j=0,k=0;j<n;j++)
		    if(s[j]==i)
		      if(!k)
		        {
				 k=1;
				 l[++t]=j+1;
				}
			  else
			    r[t]=j+1;
		for(i=1;i<=n;i++)
		  {
		   for(j=i;j>0 && s[j-1]>=0;j--);
		   w[i]=j;
		  }
		dfs(1);
		if(p)
		  return "POSSIBLE";
		else
		  return "IMPOSSIBLE";
    }
};
