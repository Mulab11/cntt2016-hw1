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
#define inf 1000000000
using namespace std;
class StringPath
{
	int f[10][10][300][300],p,q=1000000009;
	inline void add(int &a,long long b)
	{
		a=(a+b)%q;
	}
	inline int get(int i,int j)
	{
		if(i&(1<<j-1))
		  i|=1<<j;
		return i;
	}
	inline int del(int i,int j)
	{
		if(i&(1<<j))
		  i-=1<<j;
		return i;
	}
public:
	int countBoards(int n,int m,string a,string b)
	{
		int i,j,k,l;
		if(a[0]==b[0])
		  {
		   f[0][m][1][1]=1;
		   f[0][m][0][0]=25;
		  }
		else
		  {
		   f[0][m][1][0]=f[1][1][0][1]=1;
		   f[0][m][0][0]=24;
		  }
		//插头dp，记录当前填到第i行第j列，每一格分别能否走出两个字符串 
		for(i=1;i<=n;i++)
		  {
		   for(k=0;k<(1<<m);k++)
		     for(l=0;l<(1<<m);l++)
		       f[i][0][k][l]=f[i-1][m][k][l];
		   for(j=0;j<m;j++)
		     for(k=0;k<(1<<m);k++)
		       for(l=0;l<(1<<m);l++)
		         if(a[i+j-1]==b[i+j-1])
		           {
					add(f[i][j+1][get(k,j)][get(l,j)],f[i][j][k][l]);
					add(f[i][j+1][del(k,j)][del(l,j)],(L)f[i][j][k][l]*25);
				   }
				 else
		           {
					add(f[i][j+1][get(k,j)][del(l,j)],f[i][j][k][l]);
					add(f[i][j+1][del(k,j)][get(l,j)],f[i][j][k][l]);
					add(f[i][j+1][del(k,j)][del(l,j)],(L)f[i][j][k][l]*24);
				   }
		  }
		for(k=(1<<m-1);k<(1<<m);k++)
		  for(l=(1<<m-1);l<(1<<m);l++)
		    p=(p+f[n][m][k][l])%q;
		return p;
    }
};
