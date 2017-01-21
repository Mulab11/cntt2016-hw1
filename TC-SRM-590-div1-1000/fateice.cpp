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
#define inf 1000000000
using namespace std;
class FoxAndCity
{
	int n,m,a[3000],b[150000],c[150000],d[150000],f[3000],g[3000],p,q;
	bool x[3000];
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
		add_(j,i,0);
	}
	inline bool bfs()
	{
		int i,j;
		for(i=1;i<=n+1;i++)
		  f[i]=x[i]=0;
		q=1;
		f[0]=1;
		for(i=1;i<=q;i++)
		  for(j=a[g[i]];j>0;j=d[j])
		    if(c[j] && !f[b[j]])
		      {
			   f[b[j]]=f[g[i]]+1;
			   g[++q]=b[j];
			   if(b[j]==n+1)
			     return 1;
			  }
		return 0;
	}
	inline int dfs(int i,int k)
	{
		int j,l=0,u;
		if(i==n+1)
		  return k;
		x[i]=1;
		for(j=a[i];j>0;j=d[j])
		  if(c[j] && !x[b[j]] && f[b[j]]==f[i]+1)
		    {
			 u=dfs(b[j],min(k-l,c[j]));
			 l+=u;
			 c[j]-=u;
			 c[(j-1^1)+1]+=u;
			 if(l==k)
			   {
				x[i]=0;
				return l;
			   }
			}
		return l;
	}
public:
	int minimalCost(vector<string> a,vector<int> b)
	{
		int w=a.size();
		int i,j,k;
		n=w*w;
		//每个点按距离拆点 
		for(i=1;i<w;i++)
		  add(i,i+1,inf);
		add(w,n+1,inf);
		for(i=1;i<w;i++)
		  {
		   add(0,i*w+1,inf);
		   for(j=1;j<w;j++)
		     add(i*w+j,i*w+j+1,(j-b[i])*(j-b[i]));
		   add(i*w+w,n+1,(w-b[i])*(w-b[i]));
		  }
		for(i=0;i<w;i++)
		  for(j=0;j<w;j++)
		    if(a[i][j]=='Y')
		      for(k=2;k<=w;k++)
		        add(i*w+k,j*w+k-1,inf);
		//最小割 
		while(bfs())
		  p+=dfs(0,inf);
		return p;
    }
};
