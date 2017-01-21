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
class Orienteering
{
	int n,m,q,a[3000],b[12000],c[12000],x[60][60],y[3000],f[3000],d[310][310];
	double C[310][310],p;
	inline void add_(int i,int j)
	{
		b[++q]=j;
		c[q]=a[i];
		a[i]=q;
	}
	inline void add(int i,int j)
	{
		add_(i,j);
		add_(j,i);
	}
	inline void dfs(int i,int j)
	{
		int k;
		for(k=a[i];k>0;k=c[k])
		  if(b[k]!=j)
		    {
		     dfs(b[k],i);
		     f[i]+=f[b[k]];
			}
	}
	inline void dfs(int i,int j,int l,int p)
	{
		int k;
		if(y[i])
		  d[l][y[i]]=p;
		for(k=a[i];k>0;k=c[k])
		  if(b[k]!=j)
		    dfs(b[k],i,l,p+1);
	}
public:
	double expectedLength(vector<string> s,int t)
	{
		int i,j,k,l;
		int w=s.size(),h=s[0].size();
		//建树 
		for(i=0;i<w;i++)
		  for(j=0;j<h;j++)
		    if(s[i][j]=='.' || s[i][j]=='*')
		      {
			   x[i][j]=++n;
			   if(s[i][j]=='*')
			     {
			      y[n]=++m;
			      f[n]=1;
				 }
			   if(i && x[i-1][j])
			     add(x[i-1][j],n);
			   if(j && x[i][j-1])
			     add(x[i][j-1],n);
			  }
		//预处理组合数 
		for(i=0;i<=m;i++)
		  {
		   C[i][0]=1;
		   for(j=1;j<=i;j++)
		     C[i][j]=C[i-1][j]+C[i-1][j-1];
		  }
		//树形dp求出i的子树中有多少个特殊点 
		dfs(1,0);
		//求出虚树期望 
		for(i=2;i<=n;i++)
		  p+=C[m][t]-C[f[i]][t]-C[m-f[i]][t];
		p*=2;
		//求出特殊点之间的距离 
		for(i=1;i<=n;i++)
		  if(y[i])
		    dfs(i,0,y[i],0);
		//求出最远点对期望 
		for(i=1;i<m;i++)
		  for(j=i+1;j<=m;j++)
		    {
		     for(k=0,l=1;l<=m;l++)
		       if(l!=i && l!=j && (d[i][l]<d[i][j] || d[i][l]==d[i][j] && l>j) && (d[j][l]<d[i][j] || d[j][l]==d[i][j] && l>i))
		         k++;
		     p-=C[k][t-2]*d[i][j];
			}
		p/=C[m][t];
		return p;
    }
};
