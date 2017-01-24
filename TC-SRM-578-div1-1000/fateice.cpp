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
int n,m,a[20000],b[1000000],c[1000000],d[1000000],e[1000000],f[20000],x[20000],y[20000],g[4000000],p,q;
bool z[20000];
int t,aa[600],bb[1100],cc[1100],fa[600],fb[600],ff[600][600],del,w[600][600],ans;
class DeerInZooDivOne
{
	inline void add_(int i,int j,int k,int l)
    {
		b[++m]=j;
		c[m]=k;
		d[m]=l;
		e[m]=a[i];
		a[i]=m;
	}
    inline void add(int i,int j,int k,int l)
    {
		add_(i,j,k,l);
		add_(j,i,0,-l);
	}
	inline void spfa()
	{
		int i,j,k,t=1;
		for(i=1;i<=n+1;i++)
		  f[i]=-1000000000;
		for(i=1;i<=t;i++)
		  {
		   for(j=a[g[i]];j>0;j=e[j])
		     if(c[j] && f[b[j]]<f[g[i]]+d[j])
		       {
				f[b[j]]=f[g[i]]+d[j];
				x[b[j]]=j;
				y[b[j]]=g[i];
				if(!z[b[j]])
				  {
				   z[b[j]]=1;
				   g[++t]=b[j];
				  }
			   }
		   z[g[i]]=0;
		  }
		if(f[n+1]>0)
		  {
		   p++;
		   q+=f[n+1];
		   for(i=n+1;i>0;i=y[i])
		     {
			  c[x[i]]--;
			  c[(x[i]-1^1)+1]++;
			 }
		   spfa();
		  }
	}
	inline void dfs(int i)
	{
		int j,k;
		ff[i][i]=1;
		for(j=aa[i];j>0;j=cc[j])
		  if(fa[bb[j]]==-1)
		    {
			 fa[bb[j]]=i;
			 fb[bb[j]]=j;
			 dfs(bb[j]);
			 for(k=0;k<t;k++)
			   if(ff[bb[j]][k])
			     ff[i][k]=1;
			}
	}
	inline void dp(int u,int fu,int v,int fv)
	{
		int i,j,k,l,r;
		for(i=aa[u],k=0;i>0;i=cc[i])
		  if(i!=del && i!=(del-1^1)+1 && bb[i]!=fu)
		    {
			 k++;
			 for(j=aa[v];j>0;j=cc[j])
			   if(j!=del && j!=(del-1^1)+1 && bb[j]!=fv)
			     dp(bb[i],u,bb[j],v);
			}
		for(j=aa[v],l=0;j>0;j=cc[j])
		  if(j!=del && j!=(del-1^1)+1 && bb[j]!=fv)
			l++;
		for(i=aa[u],r=0;i>0;i=cc[i])
		  if(i!=del && i!=(del-1^1)+1 && bb[i]!=fu)
		    {
			 r++;
			 add(0,r,1,0);
			 for(j=aa[v],l=0;j>0;j=cc[j])
			   if(j!=del && j!=(del-1^1)+1 && bb[j]!=fv)
			     {
			 	  l++;
			 	  if(w[bb[i]][bb[j]])
				    add(r,l+k,1,w[bb[i]][bb[j]]);
				 }
			}
		n=k+l;
		for(j=aa[v],l=0;j>0;j=cc[j])
		  if(j!=del && j!=(del-1^1)+1 && bb[j]!=fv)
			{
			 l++;
			 add(l+k,n+1,1,0);
			}
		spfa();
		w[u][v]=q+1;
		for(i=0;i<=n+1;i++)
		  a[i]=0;
		for(i=1;i<=m;i++)
		  b[i]=c[i]=d[i]=e[i]=0;
		m=0;
		p=q=0;
	}
public:
	int getmax(vector<int> x,vector<int> y)
	{
		int i,j;
		t=x.size()+1;
		for(i=0;i<t-1;i++)
		  {
		   bb[2*i+1]=y[i];
		   cc[2*i+1]=aa[x[i]];
		   aa[x[i]]=2*i+1;
		   bb[2*i+2]=x[i];
		   cc[2*i+2]=aa[y[i]];
		   aa[y[i]]=2*i+2;
		  }
		for(i=1;i<t;i++)
		  fa[i]=-1;
		dfs(0);
		for(i=1;i<t;i++)    //把树劈成两半，dp+费用流 
		  {
		   del=fb[i];
		   for(j=0;j<t;j++)
		     if(!ff[i][j])
		       {
				dp(i,-1,j,-1);
				ans=max(ans,w[i][j]);
			   }
		  }
		return ans;
    }
};
