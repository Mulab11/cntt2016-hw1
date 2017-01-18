#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
struct LittleElephantAndPermutationDiv1
{
	long long f[51][51][2510];
	static const int mod=1e9+7;
	int getNumber(int N, int K)
	{
		f[0][0][0]=1;
		long long i,j,k;
		for(i=1;i<=N;i++)
		for(j=0;j<=i;j++)
		for(k=0;k<=2500;k++)
		{
			if(j>=1&&k>=i) (f[i][j][k]+=f[i-1][j-1][k-i])%=mod;
			if(j>=2&&k>=2*i) (f[i][j][k]+=(i-j+1)*(i-j+1)*f[i-1][j-2][k-2*i])%=mod;
			if(j>=1&&k>=i) (f[i][j][k]+=(i-j)*f[i-1][j-1][k-i])%=mod;
			if(j>=1&&k>=i) (f[i][j][k]+=(i-j)*f[i-1][j-1][k-i])%=mod;
			(f[i][j][k]+=f[i-1][j][k])%=mod;
		}
		long long ans=0;
		for(i=K;i<=2500;i++)
		(ans+=f[N][N][i])%=mod;
		for(i=1;i<=N;i++)
		ans=ans*i%mod;
		return ans;
	}
};