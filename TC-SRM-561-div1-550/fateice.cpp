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
class CirclesGame
{
	int n,a[60][60],b[60],f[60],g[60],w[60],t[60],p;
	inline void dfs(int i,int k)  //求出所有能到达的状态的sg值 
	{
		int j;
		k^=g[i];
		w[k]=1;
		for(j=1;j<=b[i];j++)
		  dfs(a[i][j],k);
	}
public:
	string whoCanWin(vector<int> x,vector<int> y,vector<int> r)
	{
		int i,j;
		n=x.size();
		for(i=0;i<n;i++)
		  for(j=i+1;j<n;j++)
		    if(r[i]<r[j])
		      {
			   swap(x[i],x[j]);
			   swap(y[i],y[j]);
			   swap(r[i],r[j]);
			  }
		//建树 
		for(i=0;i<n;i++)
		  for(j=i-1;j>=0;j--)
		    if((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])<r[j]*r[j])
		      {
			   a[j][++b[j]]=i;
			   t[i]=1;
			   break;
			  }
		//dp
		for(i=n-1;i>=0;i--)
		  {
		   for(j=0;j<=n;j++)
		     w[j]=0;
		   for(j=1;j<=b[i];j++)
		     g[i]^=f[a[i][j]];
		   dfs(i,0);
		   for(j=0;w[j];j++);
		   f[i]=j;
		   g[i]^=j;
		   if(!t[i])
		     p^=j;
		  }
		return p==0?"Bob":"Alice";
    }
};
