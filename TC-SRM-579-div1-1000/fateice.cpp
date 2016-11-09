#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
class RockPaperScissors
{
	double f[51][51][51][4],C[51][51],x[51][4];  //f[i][j][k][l]表示在已经出过i次石头，j次剪刀和k次布的情况下，下一次出l表示的手势的概率（未除以组合数） 
public:
	double bestScore(vector<int> a,vector<int> c,vector<int> b)  //a,b,c分别表示石头，剪刀，布 
	{
		int n=a.size();
		int i,j,k,l,u;
		double ans=0;
		for(i=1;i<=n;i++)
		  {
		   x[i][1]=a[i-1]/300.0;
		   x[i][2]=b[i-1]/300.0;
		   x[i][3]=c[i-1]/300.0;
		  }
		//计算组合数 
		for(i=0;i<=n;i++)
		  {
		   C[i][0]=1;
		   for(j=1;j<=i;j++)
		     C[i][j]=C[i-1][j]+C[i-1][j-1];
		  }
		//dp 
		f[0][0][0][0]=1;
		for(i=1;i<=n;i++)
		  for(j=i;j>=0;j--)
		    for(k=i-j;k>=0;k--)
		      for(l=i-j-k;l>=0;l--)
		        for(u=(j+k+l==i?0:3);u>=0;u--)
		          {
			       if(j)
				     f[j][k][l][u]+=f[j-1][k][l][u]*x[i][1];  //第i个为已经出的石头 
			       if(k)
				     f[j][k][l][u]+=f[j][k-1][l][u]*x[i][2];  //第i个为已经出的剪刀 
			       if(l)
				     f[j][k][l][u]+=f[j][k][l-1][u]*x[i][3];  //第i个为已经出的布 
			       if(u)
				     f[j][k][l][u]+=f[j][k][l][0]*x[i][u];  //第i个为下一次出的手势u 
				  }
		for(i=0;i<n;i++)
		  for(j=0;i+j<n;j++)
		    for(k=0;i+j+k<n;k++)
		      ans+=max(f[i][j][k][1]+3*f[i][j][k][2],max(f[i][j][k][2]+3*f[i][j][k][3],f[i][j][k][3]+3*f[i][j][k][1]))/(C[n][i+j+k]*(n-i-j-k));  //统计答案时除以组合数 
		return ans;
	}
};
