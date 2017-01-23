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
class FoxAndGo3
{
	int n,m,a[3000],b[20000],c[20000],d[20000],f[3000],g[3000],x[3000],y[60][60],p,q;
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
	int maxEmptyCells(vector<string> x)
	{
		int w=x.size();
		int i,j;
		//建图 
		for(i=0;i<w;i++)
		  for(j=0;j<w;j++)
		    if(x[i][j]!='x')
		      y[i][j]=++n;
		for(i=0;i<w;i++)
		  for(j=0;j<w;j++)
		    if(x[i][j]=='.')
		      add(y[i][j],n+1,1);
		    else if(x[i][j]=='o')
		      {
			   add(0,y[i][j],1);
			   if(i>0 && x[i-1][j]=='.')
			     add(y[i][j],y[i-1][j],1);
			   if(j>0 && x[i][j-1]=='.')
			     add(y[i][j],y[i][j-1],1);
			   if(i<w-1 && x[i+1][j]=='.')
			     add(y[i][j],y[i+1][j],1);
			   if(j<w-1 && x[i][j+1]=='.')
			     add(y[i][j],y[i][j+1],1);
			  }
		//最小割 
		while(bfs())
		  p+=dfs(0,10000);
		return n-p;
    }
};
