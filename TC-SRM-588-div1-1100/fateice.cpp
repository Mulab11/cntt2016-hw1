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
class GameInDarknessDiv1
{
	int n,m,w[60][60],f[3000],g[3000],a[3000],b[30000],c[30000],s,t,p;
	inline void add_(int i,int j)
	{
		b[++m]=j;
		c[m]=a[i];
		a[i]=m;
	}
	inline void add(int i,int j)
	{
		add_(i,j);
		add_(j,i);
	}
	inline int dfs(int i,int j)
	{
		int k,l=0;
		g[i]=1;
		for(k=a[i];k>0;k=c[k])
		  if(b[k]!=j)
		    {
			 f[b[k]]=f[i]+1;
			 dfs(b[k],i);
			 g[i]=max(g[i],g[b[k]]+1);
			 if(!j && g[b[k]]>=3)
			   l++;
			}
		if(l>=3)
		  p=1;
	}
public:
	string check(vector<string> x)
	{
		int i,j;
		for(i=0;i<x.size();i++)
		  for(j=0;j<x[0].size();j++)
		    if(x[i][j]!='#')
		      {
		       w[i][j]=++n;
		       if(x[i][j]=='A')
		         s=n;
		       if(x[i][j]=='B')
		         t=n;
		       if(i && w[i-1][j])
		         add(w[i-1][j],n);
		       if(j && w[i][j-1])
		         add(w[i][j-1],n);
			  }
		for(i=1;i<=n;i++)
		  {
		   //判断dis(s,i)>=dis(t,i)+2且i有至少3个深度>=3的子树 
		   f[i]=0;
		   p=0;
		   dfs(i,0);
		   if(f[s]>=f[t]+2 && p)
		     return "Bob wins";
		  }
		return "Alice wins";
    }
};
