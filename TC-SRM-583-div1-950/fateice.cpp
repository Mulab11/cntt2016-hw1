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
class RandomPaintingOnABoard
{
	int n,m,x[30][30],a[30],b[30],c[30],f[30][2000][2],s;
	double p;
	inline void dp(int u,int v)  //dp处理哪些列没有覆盖 
	{
		int i,j,k;
		for(i=1;i<=m;i++)
		  c[i]=0;
		for(i=1;i<=n;i++)
		  for(j=1;j<=m;j++)
		    if(!b[i])
		      c[j]+=x[i][j];
		f[0][0][v]=1;
		f[0][0][v^1]=0;
		for(i=1;i<=m;i++)
		  for(j=0;j<=s;j++)
		    for(k=0;k<=1;k++)
		      f[i][j][k]=f[i-1][j][k]+(j>=c[i]?f[i-1][j-c[i]][k^1]:0);
		for(i=0;i<=s;i++)
		  if(i+u)
		    p+=(double)(f[m][i][1]-f[m][i][0])*s/(i+u);
	}
	inline void dfs(int i,int j,int k)  //容斥，枚举哪些行没有覆盖 
	{
		if(i>n)
		  {
		   dp(j,k);
		   return;
		  }
		dfs(i+1,j,k);
		b[i]=1;
		dfs(i+1,j+a[i],k^1);
		b[i]=0;
	}
public:
	double expectedSteps(vector<string> y)
	{
		int i,j;
		n=y.size();
		m=y[0].size();
		if(n<m)
  		  for(i=0;i<n;i++)
		    for(j=0;j<m;j++)
		      x[i+1][j+1]=y[i][j]-'0';
		else
		  {
		   swap(n,m);
  		   for(i=0;i<n;i++)
		     for(j=0;j<m;j++)
		       x[i+1][j+1]=y[j][i]-'0';
		  }
		//预处理总和以及每行的和 
		for(i=1;i<=n;i++)
		  for(j=1;j<=m;j++)
		    {
			 a[i]+=x[i][j];
			 s+=x[i][j];
			}
		dfs(1,0,0);
		return p;
    }
};
