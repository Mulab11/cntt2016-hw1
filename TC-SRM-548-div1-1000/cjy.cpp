#include<bits/stdc++.h>
using namespace std;
int g[55][55][3],f[55][55][3],c[2555][2555],P=1e9+7,i,j,k,u,v,e,t;
int C(int x,int y){return y<0?0:c[x][y];} 
struct KingdomAndCities//DP 容斥
{
	public:
	    int howMany(int n,int m,int K)
	    {
	    	for(;i<n*n;i++)for(c[i][0]=j=1;j<=i;j++)c[i][j]=(c[i-1][j-1]+c[i-1][j])%P;
	    	for(i=1;i<=n;i++)for(k=0;k<=K;k++)for(j=0;j<=min(m,i);f[i][k][j]=t,j++)
	    	{
	    		if(e=i*(i-1)/2,!j)t=C(e,k);
	    		if(e-=i-1,j==1)t=1ll*C(e,k-2)*C(i-1,2)%P;
	    		if(e-=i-2,j==2)t=(1ll*C(e,k-3)*(i-2)*(i-2)+1ll*C(e,k-4)*C(i-2,2)*C(i-2,2))%P;
	    		for(g[i][k][j]=t,u=1;u<i;u++)for(v=0;v<=k;v++)if(t=(t+P-1ll*f[u][v][j]*g[i-u][k-v][0]%P*C(i-max(j,1),u-max(j,1))%P)%P,j>1)t=(t+P-1ll*f[u][v][1]*g[i-u][k-v][1]%P*C(i-2,u-1)%P)%P;
	    	}
	    	return f[n][K][m];
	    }				
};
