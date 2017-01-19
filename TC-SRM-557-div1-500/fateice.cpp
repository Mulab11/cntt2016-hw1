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
class Incubator
{
    int n,m,a[110],b[6000],c[6000],d[6000],f[110],g[110],w[60][60],q,p;
    bool x[110];
    inline void add(int i,int j,int k)
    {
		b[++m]=j;
		c[m]=k;
		d[m]=a[i];
		a[i]=m;
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
	int maxMagicalGirls(vector<string> x)
	{
		int i,j,k;
		n=x.size();
		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		    if(x[i][j]=='Y')
		      w[i][j]=1;
		for(i=0;i<n;i++)      //求出可到达性 
		  for(j=0;j<n;j++)
		    for(k=0;k<n;k++)
		      w[j][k]|=w[j][i]&w[i][k];
		for(i=0;i<n;i++)     //如果i可以到j，那么i1向j2连边 
		  for(j=0;j<n;j++)
		    if(w[i][j])
		      {
			   add(i+1,j+n+1,1);
			   add(j+n+1,i+1,0);
			  }
		//二分图最大匹配 
		for(i=1;i<=n;i++)
		  {
		   add(0,i,1);
		   add(i,0,0);
		   add(i+n,2*n+1,1);
		   add(2*n+1,i+n,0);
		  }
		n*=2;
		while(bfs())
		  p+=dfs(0,10000);
		return n/2-p;
    }
};
