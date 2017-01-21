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
class LittleElephantAndPermutationDiv1
{
	int f[55][55][2610],p,q=1000000007;
	inline void add(int &a,long long b)
	{
		a=(a+b)%q;
	}
public:
	int getNumber(int n,int m)
	{
		int i,j,k;
		//dp记录当前填完了1~i，前i个位置填了j个，当前max值<=i的和为k的方案数 
		f[0][0][0]=1;
		for(i=1;i<=n;i++)
		  for(j=0;j<i;j++)
		    for(k=0;k<=2500;k++)
		      if(f[i-1][j][k])
		        {
				 //枚举i填在哪以及第i个位置填什么 
				 add(f[i][j+1][k+i],f[i-1][j][k]);
				 add(f[i][j+2][k+2*i],(L)f[i-1][j][k]*(i-1-j)*(i-1-j));
				 add(f[i][j+1][k+i],(L)f[i-1][j][k]*(i-1-j));
				 add(f[i][j+1][k+i],(L)f[i-1][j][k]*(i-1-j));
				 add(f[i][j][k],f[i-1][j][k]);
				}
		for(i=m;i<=2500;i++)
		  p=(p+f[n][n][i])%q;
		for(i=1;i<=n;i++)
		  p=(L)p*i%q;
		return p;
    }
};
