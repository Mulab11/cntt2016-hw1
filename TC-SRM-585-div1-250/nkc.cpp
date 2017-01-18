#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1000010
using namespace std;
int f[N],pre[N];
int mod=1e9+7;
struct TrafficCongestion
{
	long long theMinCars(int treeHeight)
	{
		int i,j;
		f[0]=1;f[1]=1;
		pre[0]=1;pre[1]=2;
		for(i=2;i<=treeHeight;i++)
		(f[i]=pre[i-2]*2+1)%=mod,(pre[i]=pre[i-1]+f[i])%=mod;
		return f[treeHeight];
	}
};