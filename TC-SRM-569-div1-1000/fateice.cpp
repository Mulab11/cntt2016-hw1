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
int n,m,p,r,pr[4]={2,3,5,7};
long long u[20][20],v[20][20],w[20][20],t[20][20],q=1000000009;
class MegaFactorial
{
	inline void cheng(long long a[20][20],long long b[20][20])  //矩乘 
	{
		int i,j,k;
		for(i=0;i<=m;i++)
		  for(j=i;j<=m;j++)
			for(k=j;k<=m;k++)
			  t[i][k]=(t[i][k]+a[i][j]*b[j][k])%q;
		for(i=0;i<=m;i++)
		  for(j=0;j<=m;j++)
		    {
			 b[i][j]=t[i][j];
			 t[i][j]=0;
			}
	}
public:
	int countTrailingZeros(int nn,int mm,int b)
	{
		int i,j;
		n=nn;
		m=mm;
		for(i=3;i>=0;i--)
		  if(b%pr[i]==0)
			{
			 p=pr[i];
			 while(b%p==0)
			   {
			    b/=p;
			    r++;
			   }
			 break;
			}
		q*=r;
		u[0][0]=1;
		for(i=1;i<=m;i++)
		  for(j=i;j<=m;j++)
			u[i][j]=1;
		for(i=0;i<=m;i++)
		  w[i][i]=1;
		//倍增 
		for(;n>0;n/=p)
		  {
		   for(i=0;i<=m;i++)
		     v[i][i]=1;
		   i=p,j=n%p;
		   for(;i||j;i>>=1,j>>=1)
		     {
		      if(i&1)
		        cheng(u,v);
		      if(j&1)
		        cheng(u,w);
		      cheng(u,u);
		     }
		   for(i=0;i<=m;i++)
		     for(j=0;j<=m;j++)
		       {
		        u[i][j]=v[i][j];
		        v[i][j]=0;
		   	   }
		   for(i=1;i<=m;i++)
		     u[0][i]=(u[0][i]+1)%q;
		  }
		return (w[0][m]+q)%q/r;
	}
};
