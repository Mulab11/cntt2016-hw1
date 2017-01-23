#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#include<map>
#define L long long
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define inf 1000000000000000000ll
#define eps 1e-6
using namespace std;
class SimilarNamesCustom
{
	int n,m,f[60][100000],g[100000],h[100000],w[60][60],a[100000],b[100000],p,r,q=1000000007;
    vector<int> z[100000];
    map<int,int> t;
	inline void dfs(int x)
	{
		int i,j,k;
		for(i=1;i<=w[x][0];i++)
		  dfs(w[x][i]);
		g[0]=1;
		for(i=1;i<(1<<p);i++)
		  g[i]=0;
		for(i=1;i<=w[x][0];i++)
		  {
		   for(j=1;j<=r;j++)
			 for(k=0;k<z[a[j]].size();k++)
				h[a[j]]=(h[a[j]]+(L)f[w[x][i]][z[a[j]][k]]*g[a[j]^z[a[j]][k]])%q;
		   for(j=0;j<(1<<p);j++)
		     {
			  g[j]=h[j];
		      h[j]=0;
			 }
		  }
		for(i=0;i<(1<<p);i++)
		  f[x][i]=g[i];
		if(x!=n)
		  for(i=r;i>=1;i--)
			for(j=0;j<p;j++)
			  if((a[i]>>j)&1)
			    f[x][a[i]]=(f[x][a[i]]+f[x][a[i]^(1<<j)])%q;
	}
public:
	int count(vector<string> s,vector<int> x,vector<int> y)
	{
		int i,j,k;
		n=s.size();
		m=x.size();
		//标记有要求的串 
		for(int i=0;i<m;i++)
		  {
		   if(!t[x[i]])
		     t[x[i]]=++p;
		   if(!t[y[i]])
		     t[y[i]]=++p;
		  }
		//建树 
		sort(&s[0],&s[0]+n);
		for(i=0;i<n;i++)
		  {
		   for(j=i-1;j>=0;--j)
		  	 if(s[i].substr(0,s[j].size())==s[j])
			   break;
		   if(j>=0)
		     w[j][++w[j][0]]=i;
		   else
		     w[n][++w[n][0]]=i;
		  }
		//找合法状态 
		for(i=0;i<(1<<p);i++)
		  {
		   for(j=0;j<m;j++)
			 if(((i>>t[x[j]]-1)&1) && !((i>>t[y[j]]-1)&1))
			   break;
		   if(j==m)
		     {
		      a[++r]=i;
			  b[i]=r;
			 }
		  }
		//找合法的a,b,a^b 
		for(i=0;i<(1<<p);i++)
		  if(b[i])
		    for(j=i;;j=(j-1&i))
			  {
			   if(b[j] && b[i^j])
			     z[i].push_back(j);
			   if(j==0)
			     break;
			  }
		dfs(n);
		for(i=1,k=f[n][(1<<p)-1];i<=n-p;i++)
		  k=(L)k*i%q;
		return k;
	}
};
