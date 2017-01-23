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
class EqualSums
{
	int n,m,a[110],b[5010],c[5010],d[5010],f[110],p,q=1000000007;
	bool x[110];
	inline void add(int i,int j,int k)
	{
		b[++m]=j;
		c[m]=k;
		d[m]=a[i];
		a[i]=m;
	}
	inline void dfs2(int i)
	{
		int j;
		x[i]=1;
		for(j=a[i];j>0;j=d[j])
		  if(!x[b[j]])
		    dfs2(b[j]);
	}
	inline void dfs(int i,int l)
	{
		int j;
		if(i<n && f[i]<l || f[i]<0)
		  {
		   p=1;
		   return;
		  }
		for(j=a[i];j>0;j=d[j])
		  if(f[b[j]]!=-100 && f[b[j]]!=c[j]-f[i])
		    {
			 p=1;
			 return;
			}
		  else if(f[b[j]]==-100)
		    {
			 f[b[j]]=c[j]-f[i];
		     dfs(b[j],l);
		     if(p)
		       return;
			}
	}
	inline int count(int l)
	{
		int i,j,k,u,ans=1;
		for(i=0;i<n;i++)
		  if(!x[i])
		    {
			 dfs2(i);
			 u=0;
		     for(j=l;j<10;j++)
		       {
			    p=0;
			    for(k=0;k<2*n;k++)
			      f[k]=-100;
			    f[i]=j;
			    dfs(i,l);
			    if(!p)
			      u++;
			   }
			 ans=(L)ans*u%q;
			}
		for(i=0;i<2*n;i++)
		  x[i]=0;
		return ans;
	}
public:
	int count(vector<string> s)
	{
		int i,j;
		n=s.size();
		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		    if(s[i][j]!='-')
		      {
			   add(i,j+n,s[i][j]-'0');
			   add(j+n,i,s[i][j]-'0');
			  }
		//容斥 
		return (count(0)-count(1)+q)%q;
    }
};
