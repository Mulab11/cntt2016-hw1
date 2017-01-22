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
class Tunnels
{
	int n,m,t,l[60],r[60],x[60],a[60][60],u[3000],d[3000],p;
	vector<string> s;
	inline void dfs(int i,int j)
	{
		u[a[i][j]]=min(u[a[i][j]],i);
		d[a[i][j]]=max(d[a[i][j]],i);
		if(i>0 && s[i-1][j]=='X' && !a[i-1][j])
		  {
		   a[i-1][j]=a[i][j];
		   dfs(i-1,j);
		  }
		if(i<n-1 && s[i+1][j]=='X' && !a[i+1][j])
		  {
		   a[i+1][j]=a[i][j];
		   dfs(i+1,j);
		  }
		if(j>0 && s[i][j-1]=='X' && !a[i][j-1])
		  {
		   a[i][j-1]=a[i][j];
		   dfs(i,j-1);
		  }
		if(j<m-1 && s[i][j+1]=='X' && !a[i][j+1])
		  {
		   a[i][j+1]=a[i][j];
		   dfs(i,j+1);
		  }
	}
	inline bool pd(int i,int j)
	{
		if(!a[i][j])
		  return 0;
		int p=0;
		if(i>0 && a[i-1][j])
		  p++;
		if(i<n-1 && a[i+1][j])
		  p++;
		if(j>0 && a[i][j-1])
		  p++;
		if(j<m-1 && a[i][j+1])
		  p++;
		return p<=1;
	}
	inline void dfs(int i,int j,int k,int u)
	{
		if(i==n)
		  {
		   p=max(p,u);
		   return;
		  }
		if(x[i])
		  {
		   dfs(i+1,j+1,max(k-1,0),u+(k>0));
		   dfs(i+1,max(j-1,0),k+1,u+(j>0));
		  }
		else
		  dfs(i+1,max(j+l[i],0),max(k+r[i],0),u+(l[i]==-1 && j)+(r[i]==-1 && k));
	}
public:
	int minimumTunnels(vector<string> ss)
	{
		int i,j;
		s=ss;
		n=s.size();
		m=s[0].size();
		for(i=0;i<n;i++)
		  for(j=0;j<m;j++)
		    if(s[i][j]=='X' && !a[i][j])
		      {
			   a[i][j]=++t;
			   u[t]=d[t]=i;
			   dfs(i,j);
			  }
		if(m==1)
		  return min(t,1);
		if(n==1)
		  return t;
		for(i=0;i<n;i++)
		  if(a[i][0] && a[i][0]==a[i][m-1] && u[a[i][0]]==i && d[a[i][0]]==i)
		    x[i]=1;
		  else
		    {
			 if(a[i][0] && pd(i,0))
			   if(u[a[i][0]]==i && d[a[i][0]]==i)
			     if(i==0)
			       l[i]=1;
			     else
			       l[i]=-1;
			   else if(u[a[i][0]]==i)
			     if(!(i==0 && d[a[i][0]]==1 && pd(1,0)))
			       l[i]=-1;
			     else
			       l[i+1]=1;
			   else if(d[a[i][0]]==i)
			     if(!(u[a[i][0]]==i-1 && pd(i-1,0)))
			       l[i]=1;
			 if(a[i][m-1] && pd(i,m-1))
			   if(u[a[i][m-1]]==i && d[a[i][m-1]]==i)
			     if(i==0)
			       r[i]=1;
			     else
			       r[i]=-1;
			   else if(u[a[i][m-1]]==i)
			     if(!(i==0 && d[a[i][m-1]]==1 && pd(1,m-1)))
			       r[i]=-1;
			     else
			       r[i+1]=1;
			   else if(d[a[i][m-1]]==i)
			     if(!(u[a[i][m-1]]==i-1 && pd(i-1,m-1)))
			       r[i]=1;
			}
		for(i=0;i<n;i++)
		  cout<<x[i]<<" "<<l[i]<<" "<<r[i]<<"\n";
		dfs(0,0,0,0);
		return t-p;
    }
};
