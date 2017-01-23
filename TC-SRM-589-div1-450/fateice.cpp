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
class GearsDiv1
{
	int n,m,a[60],b[10000],c[10000],d[10000],f[60],g[60],p,q,ans=100;
	bool x[60];
	string w="RGB";
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
	int getmin(string aa,vector<string> bb)
	{
		int i,j,k;
		n=aa.size();
		for(k=0;k<=2;k++)  //枚举三种颜色的方向 
		  {
		   //最大点独立集 
		   for(i=0;i<n;i++)
		     for(j=0;j<n;j++)
		       if(bb[i][j]=='Y' && aa[i]==w[k] && aa[j]==w[(k+1)%3])
		         add(i+1,j+1,1);
		   for(i=0;i<n;i++)
		     if(aa[i]==w[k])
		       add(0,i+1,1);
		     else if(aa[i]==w[(k+1)%3])
		       add(i+1,n+1,1);
		   p=0;
		   while(bfs())
		     p+=dfs(0,10000);
		   ans=min(ans,p);
		   for(i=0;i<=n+1;i++)
		     a[i]=0;
		   for(i=1;i<=m;i++)
		     b[i]=c[i]=d[i]=0;
		   m=0;
		  }
		return ans;
    }
};
