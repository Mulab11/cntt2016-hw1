#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
using namespace std;
class CosmicBlocks
{
	int n,l,r,p,ans;
	int t[10],x[10][10],w[10],a[10][600],b[10],f[10][10],s[10],c[10],d[10],cc,dd,z[1000][10];
	bool y[10];
	bool pd(int i,int j)    //判断层与层之间的某种连边方式是否可行 
	{
		int k,l,u,v,p=0;
		for(k=1;k<=n;k++)
		  s[k]=t[k];
		cc=x[i+1][0];
		for(k=1;k<=cc;k++)
		  c[k]=x[i+1][k];
		dd=x[i][0];
		for(k=1;k<=dd;k++)
		  d[k]=x[i][k];
		for(k=1;k<=cc;k++)
		  for(l=1;l<=dd;l++)
		    {
			 f[k][l]=(j&1);
			 j>>=1;
			}
		for(k=1;k<=cc;k++)
		  for(l=1;l<=dd;l++)
		    if(f[k][l])
		      {
			   s[c[k]]--;
			   s[d[l]]--;
			   if(s[c[k]]<0 || s[d[l]]<0)
			     p=1;
			  }
		if(p)
		  return 0;
		for(k=1;k<=cc;k++)
		  {
		   for(l=1,u=0;l<=dd;l++)
		     u+=f[k][l];
		   if(u==0)
		     return 0;
		   if(u==1)
		     {
			  for(l=1;l<=dd;l++)
			    if(f[k][l])
			      break;
			  s[d[l]]-=s[c[k]];
			  if(s[d[l]]<0)
			    return 0;
			  for(l=1;l<=dd;l++)
			    f[k][l]=f[cc][l];
			  c[k]=c[cc];
			  cc--;
			  k--;
			 }
		   else if(u==dd)
		     {
			  for(l=1;l<=dd;l++)
			    f[k][l]=f[cc][l];
			  c[k]=c[cc];
			  cc--;
			  k--;
			 }
	      }
	    for(k=1;k<cc;k++)
	      {
		   for(l=k+1;l<=cc;l++)
		     {
			  for(u=1;u<=dd;u++)
			    if(f[k][u]!=f[l][u])
			      break;
			  if(u>dd)
			    {
				 s[c[k]]+=s[c[l]];
				 for(u=1;u<=dd;u++)
				   f[l][u]=f[cc][u];
				 c[l]=c[cc];
				 cc--;
				 l--;
				}
			 }
		  }
	    if(cc==0)
	      return 1;
		if(cc==1)
		  {
		   for(k=1,l=0;k<=dd;k++)
		     if(f[1][k])
		       l+=s[d[k]];
		   return s[c[1]]<=l;
		  }
		if(cc==2)
		  {
		   for(k=1,l=u=v=0;k<=dd;k++)
		     if(f[1][k] && f[2][k])
		       l+=s[d[k]];
		     else if(f[1][k])
		       u+=s[d[k]];
		     else if(f[2][k])
		       v+=s[d[k]];
		   return max(s[c[1]]-u,0)+max(s[c[2]]-v,0)<=l;
		  }
		if(dd==2)
		  {
		   for(k=1,l=u=v=0;k<=cc;k++)
		     if(f[k][1] && f[k][2])
		       l+=s[c[k]];
		     else if(f[k][1])
		       u+=s[c[k]];
		     else if(f[k][2])
		       v+=s[c[k]];
		   return max(u-s[d[1]],0)+max(v-s[d[2]],0)<=l;
		  }
		for(k=1;k<=3;k++)
		  {
		   for(l=1,u=0;l<=3;l++)
		     if(f[k][l])
		       u+=s[d[l]];
		   if(s[c[k]]>u)
		     return 0;
		  }
		return 1;
	}
	void dfs2(int i,int m) 
	{
		//计算有多少种排列可行 
		int j,k,u,v,p;
		if(i==m)
		  {
		   k=1;
		   z[1][1]=1;
		   for(i=2;i<=n;i++)
		     {
			  for(j=1;j<=k;j++)
			    for(u=0;u<i;u++)
			      {
				   for(v=1;v<i;v++)
				     z[j+u*k][v]=z[j][v];
				   z[j+u*k][i]=z[j][i-u];
				   z[j+u*k][i-u]=i;
				  }
			  k*=i;
			 }
		   for(i=1;i<=n;i++)
		     for(j=1;j<=n;j++)
		       f[i][j]=0;
		   for(i=1;i<m;i++)
		     {
			  u=b[i];
			  for(j=1;j<=x[i+1][0];j++)
			    for(v=1;v<=x[i][0];v++)
			      {
				   if(u&1)
				     f[x[i+1][j]][x[i][v]]=1;
				   u>>=1;
				  }
			 }
		   p=0;
		   for(i=1;i<=k;i++)
		     {
			  j=0;
			  for(u=1;u<=n;u++)
			    for(v=1;v<=n;v++)
			      if(f[u][v] && z[i][u]<z[i][v])
			        j=1;
			  if(!j)
			    p++;
			 }
		   if(l<=p && p<=r)
		     ans++;
		   return;
		  }
		//搜索层与层之间采用哪种连边 
		for(j=1;j<=a[i][0];j++)
		  {
		   b[i]=a[i][j];
		   dfs2(i+1,m);
		  }
	}
	void dfs(int m,int i)
	{
		//搜索层与层之间的哪些连边是可行的 
		if(!p)
		  {
		   if(m>1 && w[m]>w[m-1])
		     return;
		   int j,k;
		   for(j=1;j<m;j++)
		     {
			  a[j][0]=0;
		      for(k=0;k<(1<<x[j][0]*x[j+1][0]);k++)
		        if(pd(j,k))
		          a[j][++a[j][0]]=k;
			 }
		   dfs2(1,m);
		  }
		//搜索每种颜色放在哪层 
		else if(i>n)
		  {
		   if(!w[m] || m>1 && w[m]>w[m-1])
		     return;
		   dfs(m+1,1);
		  }
		else if(y[i])
		  dfs(m,i+1);
		else
		  {
		   dfs(m,i+1);
		   y[i]=1;
		   x[m][++x[m][0]]=i;
		   w[m]+=t[i];
		   p--;
		   dfs(m,i+1);
		   p++;
		   w[m]-=t[i];
		   x[m][0]--;
		   y[i]=0;
		  }
	}
public:
	int getNumOrders(vector<int> q,int ll,int rr)
	{
		int i,j;
		l=ll;
		r=rr;
		n=p=q.size();
		for(i=1;i<=n;i++)
		  t[i]=q[i-1];
		dfs(1,1);
		return ans;
	}
};
