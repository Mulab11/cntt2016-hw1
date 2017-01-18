#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 310
using namespace std;
struct TheExperiment
{
	int a[N],pre[N],f[N][N][3];
	/*
	f[i][j]表示前i个水龙头用j个盆
	0表示最后连着且至少有一个L
	1表示最后连着没有L
	2表示不连着且前面都满足条件 
	*/
	static const int mod=1e9+9;
	int countPlacements(vector <string> intensity, int M, int L, int A, int B)
	{
		string S="";
		int i,j,k;
		for(i=0;i<intensity.size();i++)
		S+=intensity[i];
		int n=S.size();
		for(i=0;i<n;i++)
		a[i+1]=S[i]-48;
		for(i=1;i<=n;i++)
		pre[i]=pre[i-1]+a[i];
		for(i=0;i<=n;i++)
		f[i][0][2]=1;
		for(i=1;i<=n;i++)
		for(j=1;j<=M&&j<=i;j++)
		{
			int tot=0;
			//先特判有长度正好为L的 
			if(i>=L&&pre[i]-pre[i-L]>=A&&pre[i]-pre[i-L]<=B) f[i][j][0]=((f[i-L][j-1][1]+f[i-L][j-1][0])%mod+f[i-L][j-1][2])%mod;
			f[i][j][2]=(f[i-1][j][0]+f[i-1][j][2])%mod;
			for(k=i;k>=1;k--)
			{
				tot+=a[k];
				if(tot>B||i-k+1==L) break;//停止 
				if(tot>=A&&tot<=B)
				{
					(f[i][j][1]+=(f[k-1][j-1][1]+f[k-1][j-1][2])%mod)%=mod;
					(f[i][j][0]+=f[k-1][j-1][0])%=mod;
				}
			}
		}
		return (f[n][M][0]+f[n][M][2])%mod;
	}
};