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
class WallGameDiv1
{
	int n,m,f[60][60][60],g[60][60][60],s[60][60],p;
public:
	int play(vector<string> a)
	{
		int i,j,k;
		n=a.size();
		m=a[0].size();
		//预处理每行的前缀和 
		for(i=1;i<=n;i++)
		  {
		   s[i][1]=1000000;
		   s[i][m+2]=2000000;
		   for(j=1;j<=m;j++)
		     s[i][j+1]=s[i][j]+a[i-1][j-1]-'0';
		  }
		//dp求出当前在第i行第j或k格，墙在第j+1~k或j~k-1列的答案 
		for(i=n-1;i>0;i--)
		  for(j=1;j<=m;j++)
		    for(k=m;k>=j;k--)
		      if(j==1 && k==m)
		        {
				 f[i][j][k]=f[i+1][1][1]+s[i+1][2]-s[i+1][1];
				 g[i][j][k]=g[i+1][m][m]+s[i+1][m+1]-s[i+1][m];
				}
			  else
			    {
				 f[i][j][k]=max(f[i+1][j][j]+s[i+1][j+1]-s[i+1][j],min(f[i][j-1][k]+s[i][j]-s[i][j-1],g[i][j][k+1]+s[i][k+2]-s[i][j+1]));
				 g[i][j][k]=max(f[i+1][k][k]+s[i+1][k+1]-s[i+1][k],min(f[i][j-1][k]+s[i][k]-s[i][j-1],g[i][j][k+1]+s[i][k+2]-s[i][k+1]));
				}
		p=1000000;
		for(i=1;i<=m;i++)
		  p=min(p,f[1][i][i]+s[1][i+1]-s[1][i]);
		return p;
    }
};
