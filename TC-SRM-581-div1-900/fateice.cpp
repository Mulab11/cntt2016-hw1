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
class YetAnotherBoardGame
{
	int n,m,x[20][20],f[20],p;
	inline void orz(int i,int j,int k)
	{
		x[i-1][j]^=1;
		x[i][j-1]^=1;
		x[i+1][j]^=1;
		x[i][j+1]^=1;
		if(k==2)
		  x[i][j]^=1;
	}
	inline void dfs2(int i,int q)  //搜索第i行状态 
	{
		int j,k=0,l,a[20],g[20];
		if(i>n)
		  {
		   for(j=1;j<=m;j++)
		     if(x[i-1][j])
		       return;
		   p=min(p,q);
		   return;
		  }
		//找到所有要操作的格子 
		for(j=1;j<=m;j++)
		  {
		   a[j]=x[i-1][j];
		   g[j]=f[j];
		   if(a[j])
		     q++;
		   if(a[j] && f[j])
		     if(k==f[j] || !k)
		       k=f[j];
		     else
		       return;
		  }
		//枚举操作 
		for(j=max(k,1);j<=(k==0?2:k);j++)
		  {
		   for(l=1;l<=m;l++)
		     if(a[l])
		       {
				f[l]=j;
				orz(i,l,j);
			   }
		   dfs2(i+1,q);
		   for(l=1;l<=m;l++)
		     if(a[l])
		       {
				f[l]=g[l];
				orz(i,l,j);
			   }
		  }
	}
	inline void dfs(int i,int j,int q)  //搜索第一行状态 
	{
		if(i>m)
		  {
		   dfs2(2,q);
		   return;
		  }
		dfs(i+1,j,q);
		orz(1,i,j);
		f[i]=j;
		dfs(i+1,j,q+1);
		orz(1,i,j);
		f[i]=0;
	}
public:
	int minimumMoves(vector<string> a)
	{
		int i,j;
		n=a.size();
		m=a[0].size();
		for(i=1;i<=n;i++)
		  for(j=1;j<=m;j++)
		    if(a[i-1][j-1]=='W')
		      x[i][j]=1;
		p=10000;
		dfs(1,1,0);
		dfs(1,2,0);
		return p==10000?-1:p;
    }
};
