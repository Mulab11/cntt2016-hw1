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
class CurvyonRails
{
	int n,m,t[30][30],a[2000],b[100000],c[100000],d[100000],e[100000],f[2000],x[2000],y[2000],g[4000000],p,q;
	bool z[2000];
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
		for(i=1;i<=2*n+1;i++)
		  f[i]=1000000000;
		for(i=1;i<=t;i++)
		  {
		   for(j=a[g[i]];j>0;j=e[j])
		     if(c[j] && f[b[j]]>f[g[i]]+d[j])
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
		if(f[2*n+1]<1000000000)
		  {
		   p++;
		   q+=f[2*n+1];
		   for(i=2*n+1;i>0;i=y[i])
		     {
			  c[x[i]]--;
			  c[(x[i]-1^1)+1]++;
			 }
		   spfa();
		  }
	}
public:
	long long getmin(vector<string> s)
	{
		int w=s.size(),r=s[0].size();
		int i,j;
		for(i=0;i<w;i++)
		  for(j=0;j<r;j++)
		    if(s[i][j]!='w')
		      t[i][j]=++n;
		//拆点建边 
		for(i=0;i<w;i++)
		  for(j=0;j<r;j++)
		    if(s[i][j]!='w')
		      if(i+j&1)
		        {
				 add(0,t[i][j],1,0);
				 add(0,t[i][j]+n,1,0);
				 add(t[i][j],t[i][j]+n,1,s[i][j]=='C');
				 add(t[i][j]+n,t[i][j],1,s[i][j]=='C');
				 if(i>0 && t[i-1][j])
				   add(t[i][j],t[i-1][j],1,0);
				 if(i<w-1 && t[i+1][j])
				   add(t[i][j],t[i+1][j],1,0);
				 if(j>0 && t[i][j-1])
				   add(t[i][j]+n,t[i][j-1]+n,1,0);
				 if(j<r-1 && t[i][j+1])
				   add(t[i][j]+n,t[i][j+1]+n,1,0);
				}
			  else
			    {
				 add(t[i][j],2*n+1,1,0);
				 add(t[i][j]+n,2*n+1,1,0);
				 add(t[i][j],t[i][j]+n,1,s[i][j]=='C');
				 add(t[i][j]+n,t[i][j],1,s[i][j]=='C');
				}
		//费用流 
		spfa();
		if(p==n)
		  return q;
		else
		  return -1;
    }
};
