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
class OldBridges
{
    int n,m,a[100],b[3000],c[3000],d[3000],f[100],g[100],q,p;
    bool x[100];
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
	string isPossible(vector<string> x,int a1,int a2,int an,int b1,int b2,int bn)
	{
		int i,j;
		n=x.size();
		a1++;
		a2++;
		b1++;
		b2++;
		//从a1,b1到a2,b2的最大流 
		for(i=1;i<n;i++)
		  for(j=i+1;j<=n;j++)
		    if(x[i-1][j-1]=='N')
		      {
		       add(i,j,10000);
		       add(j,i,10000);
			  }
		    else if(x[i-1][j-1]=='O')
		      {
		       add(i,j,1);
		       add(j,i,1);
			  }
		add(0,a1,an);
		add(a1,0,0);
		add(0,b1,bn);
		add(b1,0,0);
		add(a2,n+1,an);
		add(n+1,a2,0);
		add(b2,n+1,bn);
		add(n+1,b2,0);
		while(bfs())
		  p+=dfs(0,10000);
		if(p!=an+bn)
		  return "No";
		//从a1,b2到a2,b1的最大流 
		for(i=0;i<=n+1;i++)
		  a[i]=0;
		for(i=1;i<=m;i++)
		  b[i]=c[i]=d[i]=0;
		m=0;
		for(i=1;i<n;i++)
		  for(j=i+1;j<=n;j++)
		    if(x[i-1][j-1]=='N')
		      {
		       add(i,j,10000);
		       add(j,i,10000);
			  }
		    else if(x[i-1][j-1]=='O')
		      {
		       add(i,j,1);
		       add(j,i,1);
			  }
		add(0,a1,an);
		add(a1,0,0);
		add(0,b2,bn);
		add(b2,0,0);
		add(a2,n+1,an);
		add(n+1,a2,0);
		add(b1,n+1,bn);
		add(n+1,b1,0);
		p=0;
		while(bfs())
		  p+=dfs(0,10000);
		if(p!=an+bn)
		  return "No";
		else
		  return "Yes";
    }
};
