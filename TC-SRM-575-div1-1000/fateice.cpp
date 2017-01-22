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
class TheTilesDivOne
{
	int n,m,a[6000],b[300000],c[300000],d[300000],f[6000],g[6000],t[60][60],p,q;
	bool x[6000];
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
	int find(vector<string> s)
	{
		int w=s.size(),h=s[0].size();
		int i,j;
		for(i=0;i<w;i++)
		  for(j=0;j<h;j++)
		    if(s[i][j]=='.')
		      t[i][j]=++n;
		for(i=0;i<w;i++)
		  for(j=0;j<h;j++)
		    if(t[i][j])
		    if(!(i+j&1))
		      if(i&1)
		        {
				 if(j && t[i][j-1])
				   add(t[i][j-1],t[i][j],1);
				 if(j<h-1 && t[i][j+1])
				   add(t[i][j+1],t[i][j],1);
				 if(i && t[i-1][j])
				   add(t[i][j]+n,t[i-1][j],1);
				 if(i<w-1 && t[i+1][j])
				   add(t[i][j]+n,t[i+1][j],1);
				 add(t[i][j],t[i][j]+n,1);
				}
			  else
		        {
				 if(j && t[i][j-1])
				   add(t[i][j]+n,t[i][j-1],1);
				 if(j<h-1 && t[i][j+1])
				   add(t[i][j]+n,t[i][j+1],1);
				 if(i && t[i-1][j])
				   add(t[i-1][j],t[i][j],1);
				 if(i<w-1 && t[i+1][j])
				   add(t[i+1][j],t[i][j],1);
				 add(t[i][j],t[i][j]+n,1);
				}
		    else if(i&1)
		      add(0,t[i][j],1);
		    else
		      add(t[i][j],2*n+1,1);
		n*=2;
		while(bfs())
		  p+=dfs(0,10000);
		return p;
    }
};
