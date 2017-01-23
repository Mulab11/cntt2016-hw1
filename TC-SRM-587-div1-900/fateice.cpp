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
class ThreeColorability
{
	int n,m,f[100],g[100],a[100],b[3000],c[3000],p,q;
	inline int fa(int i)
	{
		return f[i]==i?i:f[i]=fa(f[i]);
	}
	inline void unit(int i,int j)
	{
		i=fa(i);
		j=fa(j);
		f[i]=j;
	}
	inline void add_(int i,int j)
	{
		b[++p]=j;
		c[p]=a[i];
		a[i]=p;
	}
	inline void add(int i,int j)
	{
		add_(i,j);
		add_(j,i);
	}
	inline void dfs(int i)
	{
		int j;
		for(j=a[i];j>0;j=c[j])
		  if(g[b[j]]==2)
		    {
			 g[b[j]]=g[i]^1;
			 dfs(b[j]);
			}
		  else if(g[b[j]]==g[i])
		    q=1;
	}
	inline bool pd(vector<string> x)  //判断是否有解 
	{
		int i,j,k;
		for(i=0;i<n;i++)
		  f[i]=i;
		for(j=0;j<m;j++)
		  {
		   for(i=0;i<n;i++)
		     if(x[i][j]=='N')
		       break;
		   for(k=i+1;k<n;k++)
		     if(x[k][j]=='N')
		       unit(i,k);
		   for(i=0;i<n;i++)
		     if(x[i][j]=='Z')
		       break;
		   for(k=i+1;k<n;k++)
		     if(x[k][j]=='Z')
		       unit(i,k);
		  }
		for(j=0;j<m;j++)
		  {
		   for(i=0;i<n;i++)
		     if(x[i][j]=='N')
		       break;
		   for(k=0;k<n;k++)
		     if(x[k][j]=='Z')
		       break;
		   if(i<n && k<n)
		     add(fa(i),fa(k));
		  }
		for(i=0;i<n;i++)
		  g[i]=2;
		q=0;
		for(i=0;i<n;i++)
		  if(f[i]==i && g[i]==2)
		    {
			 g[i]=0;
			 dfs(i);
			}
		for(i=0;i<n;i++)
		  a[i]=0;
		for(i=1;i<=p;i++)
		  b[i]=c[i]=0;
		p=0;
		return !q;
	}
public:
	vector<string> lexSmallest(vector<string> x)
	{
		int i,j;
		n=x.size();
		m=x[0].size();
		if(!pd(x))
		  {
		   x.clear();
		   return x;
		  }
		for(i=0;i<n;i++)
		  for(j=0;j<m;j++)
		    if(x[i][j]=='?')  //枚举填入N和Z判断是否有解 
		      {
			   x[i][j]='N';
			   if(!pd(x))
			     x[i][j]='Z';
			  }
		return x;
    }
};
