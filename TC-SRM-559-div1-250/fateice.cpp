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
class HyperKnight
{
	int lx[10],rx[10],ly[10],ry[10],c[10][10];
	long long f[10],p;
	inline void add(int a,int b,int c,int d,int e)
	{
		lx[a]=b;
		rx[a]=c;
		ly[a]=d;
		ry[a]=e;
	}
	inline void dfs(int i,int k,int xl,int xr,int yl,int yr)
	{
		if(i>8)
		  {
		   if(xl<=xr && yl<=yr)
		     f[k]+=(L)(xr-xl+1)*(yr-yl+1);
		   return;
		  }
		dfs(i+1,k,xl,xr,yl,yr);
		dfs(i+1,k+1,max(xl,lx[i]),min(xr,rx[i]),max(yl,ly[i]),min(yr,ry[i]));
	}
public:
	long long countCells(int a,int b,int n,int m,int k)
	{
		int i,j;
		//搜索至少k种的答案 
		add(1,1,n-a,1,m-b);
		add(2,1,n-b,1,m-a);
		add(3,1,n-a,b+1,m);
		add(4,1,n-b,a+1,m);
		add(5,a+1,n,1,m-b);
		add(6,b+1,n,1,m-a);
		add(7,a+1,n,b+1,m);
		add(8,b+1,n,a+1,m);
		dfs(1,0,1,n,1,m);
		//容斥 
		for(i=0;i<=8;i++)
		  {
		   c[i][0]=1;
		   for(j=1;j<=i;j++)
		     c[i][j]=c[i-1][j]+c[i-1][j-1];
		  }
		for(i=7;i>=0;i--)
		  for(j=i+1;j<=8;j++)
		    f[i]-=f[j]*c[j][i];
		return f[k];
    }
};
