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
class XorBoard
{
    int n,a[2010],b[2010],c[3010][3010],p,q;
    inline void js(int n,int x,int a[])
    {
        int i;
        for(i=(x&1);i<=n && i<=x;i+=2)
          a[i]=(L)c[n][i]*c[n+(x-i>>1)-1][n-1]%q;
    }
public:
	int count(int n,int m,int x,int y,int s)
	{
		int i,j;
		q=555555555;
		for(i=0;i<=3000;i++)
		  {
           c[i][0]=1;
           for(j=1;j<=i;j++)
             c[i][j]=(c[i-1][j]+c[i-1][j-1])%q;
          }
		js(n,x,a);  //求出有k行翻转的方案数 
		js(m,y,b);  //求出有k列翻转的方案数 
		for(i=0;i<=n;i++)
		  for(j=0;j<=m;j++)
		    if(i*m+j*n-2*i*j==s)
		      p=(p+(L)a[i]*b[j])%q;
		return p;
    }
};
