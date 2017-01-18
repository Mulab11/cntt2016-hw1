#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 51
using namespace std;
struct AstronomicalRecords
{
	int a[N],b[N],f[N][N];
	long long c[N],d[N];
	int minimalPlanets(vector <int> A, vector <int> B)
	{
		int n=A.size(),m=B.size();
		int i,j,k,l;
		for(i=0;i<n;i++)
		a[i+1]=A[i];
		for(i=0;i<m;i++)
		b[i+1]=B[i];
		int ans=0;
		for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)//枚举相同的行星 
		{
			for(k=1;k<=n;k++)
			c[k]=(long long)a[k]*b[j];
			for(l=1;l<=m;l++)
			d[l]=(long long)b[l]*a[i];
			for(k=1;k<=n;k++)
			for(l=1;l<=m;l++)//求最长公共子序列 
			{
				f[k][l]=max(f[k-1][l],f[k][l-1]);
				if(c[k]==d[l]) f[k][l]=max(f[k][l],f[k-1][l-1]+1);
			}
			ans=max(ans,f[n][m]);
		}
		return n+m-ans;//总行星数减去重复的个数 
	}
};