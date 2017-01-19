#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#define L long long
using namespace std;
class KingdomAndCities
{
	int f[60][60],c[1300][60];
public:
	int howMany(int n,int t,int m)
	{
		int i,j,k,l,ans,q=1000000007;
		if(n==1)
		  return t==0 && m==0;
		if(n==2)
		  return t==0 && m==1;
		//预处理组合数 
		for(i=0;i<=(n*(n-1)>>1);i++)
		  {
		   c[i][0]=1;
		   for(j=1;j<=i && j<=m;j++)
		     c[i][j]=(c[i-1][j]+c[i-1][j-1])%q;
		  }
		//dp求出不考虑二度点的方案数 
		for(i=1;i<=n;i++)
		  for(j=0;j<=m;j++)
		    {
			 f[i][j]=c[i*(i-1)>>1][j];
			 for(k=1;k<i;k++)
			   for(l=0;l<=j;l++)
			     f[i][j]=(f[i][j]-(L)c[i-1][k-1]*f[k][l]%q*c[(i-k)*(i-k-1)>>1][j-l])%q;
			}
		ans=0;
		if(t==0)
		  ans=f[n][m];
		//插入二度点 
		if(t==1)
		  {
		   if(m>=1)
		     ans=(ans+(L)f[n-1][m-1]*(m-1))%q;
		   if(m>=2)
		     ans=(ans+(L)f[n-1][m-2]*(m-2))%q;
		  }
		if(t==2)
		  {
		   if(m>=2)
		     ans=(ans+(L)f[n-2][m-2]*(m-2)%q*(m-3+2))%q;
		   if(m>=3)
		     ans=(ans+(L)f[n-2][m-3]*(m-3)%q*(m-4+m-3+2))%q;
		   if(m>=4)
		     ans=(ans+(L)f[n-2][m-4]*(m-4)%q*(m-4))%q;
		   if(m>=3)
		     ans=(ans+(L)f[n-2][m-3]*(n-2))%q;
		  }
		ans=(ans+q)%q;
		return ans;
	}
};
