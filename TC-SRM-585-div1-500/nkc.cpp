#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 41
using namespace std;
int mod=1e9+7;
struct LISNumber
{
	int sum[N],a[N];
	int pre[1500],ni[1500];
	int f[N][N*N];
	int ksm(int d,int c)
	{
		int ret=1;
		while(c)
		{
			if(c&1) ret=(long long)ret*d%mod;
			d=(long long)d*d%mod;c/=2;
		}
		return ret;
	}
	int c(int x,int y)
	{
		if(x<y) return 0;
		return (long long)pre[x]*ni[y]%mod*ni[x-y]%mod;
	}
	int count(vector <int> cardsnum, int K)
	{
		int n=cardsnum.size();
		int i,j,k,x,y;
		pre[0]=1;
		for(i=1;i<1500;i++)
		pre[i]=(long long)pre[i-1]*i%mod;
		ni[1499]=ksm(pre[1499],mod-2);
		for(i=1498;i>=0;i--)
		ni[i]=(long long)ni[i+1]*(i+1)%mod;
		for(i=1;i<=n;i++)
		a[i]=cardsnum[i-1];
		for(i=1;i<=n;i++)
		sum[i]=sum[i-1]+a[i];
		f[2][sum[1]]=1;
		for(i=2;i<=n;i++)
		for(j=1;j<=sum[i-1];j++)
		{
			for(k=0;k<=min(j,a[i]);k++)
			(f[i+1][j+a[i]-k]+=(long long)f[i][j]*c(j,k)%mod*c(a[i]+sum[i-1]-j,sum[i-1]-(j-k))%mod)%=mod;
		}
		int ans=0;
		return f[n+1][K];
	}
};
/*int main()
{
	LISNumber P;
	vector<int>V;
	V.push_back(3);V.push_back(2);V.push_back(11);V.push_back(5);V.push_back(7);
	cout<<P.count(V,20);
}*/