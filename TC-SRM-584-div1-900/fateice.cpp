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
class FoxTheLinguist
{
	int n,m,a[10000],b[1000000],c[1000000],d[1000000],x[10000],y[10000],p,f[10000],g[10000];
	inline int get(char a,char b)
	{
		return (a-'A')*10+(b-'0')+1;
	}
	inline void add(int i,int j,int k)
	{
		if(i==j)
		  return;
		b[++m]=j;
		c[m]=k;
		d[m]=a[i];
		a[i]=m;
	}
	inline void dfs(int i)
	{
		int k;
		p++;
		f[i]=1;
		for(k=a[i];k>0;k=d[k])
		  if(!f[b[k]])
		    dfs(b[k]);
	}
	inline void zl()
	{
		int i,j,k;
		for(i=0;i<=n;i++)
		  {
		   x[i]=10000;
		   g[i]=0;
		  }
		for(i=0;i<=n;i++)
		  if(!f[i])
		    for(j=a[i];j>0;j=d[j])
		      if(c[j]<x[b[j]])
		        {
				 x[b[j]]=c[j];
				 y[b[j]]=i;
				}
		g[0]=1;
		for(i=1;i<=n;i++)
		  if(!f[i] && !g[i])
		    {
			 g[i]=3;
			 for(j=y[i];j!=i && g[j]==0;j=y[j])
			   g[j]=3;
			 if(g[j]==1)
			   for(j=i;g[j]!=1;j=y[j])
				 g[j]=1;
			 else
			   {
			    i=j;
			    break;
			   }
			}
		if(i>n)
		  {
		   for(i=1;i<=n;i++)
		     if(!f[i])
		       p+=x[i];
		  }
		else
		  {
		   n++;
		   g[i]=2;
		   for(j=y[i];j!=i;j=y[j])
		     g[j]=2;
		   for(j=0;j<=n;j++)
		     if(!f[j])
		       for(k=a[j];k>0;k=d[k])
		         if(!f[b[k]])
				  if(g[j]!=2 && g[b[k]]==2)
				    {
				     c[k]-=x[b[k]];
				     b[k]=n;
				    }
				  else if(g[j]==2 && g[b[k]]!=2)
				    add(n,b[k],c[k]);
		   p+=x[i];
		   f[i]=1;
		   for(j=y[i];j!=i;j=y[j])
		     {
			  p+=x[j];
			  f[j]=1;
			 }
		   zl();
		  }
	}
public:
	int minimalHours(int nn,vector<string> a)
	{
		int i;
		string b;
		b.clear();
		n=nn*10;
		//建图 
		for(i=0;i<a.size();i++)
		  b+=a[i];
		for(i=0;i<b.size();i+=12)
		  add(get(b[i],b[i+1]),get(b[i+4],b[i+5]),(b[i+7]-'0')*1000+(b[i+8]-'0')*100+(b[i+9]-'0')*10+(b[i+10]-'0'));
		for(i=1;i<=n;i++)
		  if(i%10!=1)
		    add(i,i-1,0);
		for(i=1;i<=nn;i++)
		  add(0,(i-1)*10+1,0);
		//求是否有解 
		dfs(0);
		if(p!=n+1)
		  return -1;
		p=0;
		for(i=0;i<=n;i++)
		  f[i]=0;
		//最小树形图 
		zl();
		return p;
    }
};
