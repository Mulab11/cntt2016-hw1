#include<bits/stdc++.h>
#define vs vector<string>
#define C L=SL[j][v]-SL[i-1][v]-SL[j][u-1]+SL[i-1][u-1],P=SP[j][v]-SP[i-1][v]-SP[j][u-1]+SP[i-1][u-1]
using namespace std;
int n,m,k,i,j,u,v,F,S,SL[55][55],SP[55][55],F1[2017],F2[2017],P,L;
int G(vs A)//枚举
{
	int S=-1;
	for(i=1;i<=n;i++)for(j=1;j<=m;j++)SL[i][j]=SL[i-1][j]+SL[i][j-1]-SL[i-1][j-1]+(A[i-1][j-1]=='L'),SP[i][j]=SP[i-1][j]+SP[i][j-1]-SP[i-1][j-1]+(A[i-1][j-1]=='P');
	for(k=2;k<=n;k++)
	{
		for(i=0;i<2017;i++)F1[i]=F2[i]=-999;
		for(u=1;u<=m;u++)for(v=u;v<=m;v++)
		{
			for(i=1;i<k;i++)for(j=i;j<k;j++)C,F1[P-L+999]=max(F1[P-L+999],P+L);
			for(i=k;i<=n;i++)for(j=i;j<=n;j++)C,F2[P-L+999]=max(F2[P-L+999],P+L);
		}
		for(i=0;i<2017;i++)for(j=0;j<2017;j++)if(abs(i+j-1998)<=F)S=max(S,F1[i]+F2[j]); 
	}
	return S;
}
struct FoxAndFlowerShopDivOne
{
	int theMaxFlowers(vs A,int _)
	{
		vs B(m=A[0].size(),string(n=A.size(),' '));
		for(F=_;i<n;i++)for(j=0;j<m;j++)B[j][i]=A[i][j];
		return S=G(A),swap(n,m),max(S,G(B));
	}
};
