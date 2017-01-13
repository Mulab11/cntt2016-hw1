#include<bits/stdc++.h>
#define G(x,F,y) for(y=0;;y++)if(d[x][y]==1&&d[y][F]<d[x][F])break;
using namespace std;
int d[55][55],P=1e9+9,c[55][55],J[55],s[55][55],f[55][55],g[55][55][55][55],n,i,j,k,l,m,S,t;
void D(int x,int F)
{
	if(f[F][x])return;
	int y=0,r=0;for(f[F][x]=g[F][x][0][0]=1;y<n;y++)if(d[x][y]==1&&y!=F)D(y,x),r+=s[x][y];
	for(s[F][x]=r+1,y=0;y<n;y++)if(d[x][y]==1&&y!=F)for(f[F][x]=1ll*f[F][x]*f[x][y]%P*c[r][s[x][y]]%P,r-=s[x][y],j=s[F][x]-r;~j;j--)for(k=s[F][x]-r;~k;g[F][x][j][k--]=t)for(l=t=0;l<=min(j,s[x][y]);l++)for(m=0;m<=min(k,s[x][y]);m++)t=(1ll*g[x][y][l][m]*g[F][x][j-l][k-m]%P*c[j][l]%P*c[k][m]+t)%P;g[F][x][s[F][x]][0]=g[F][x][0][s[F][x]]=f[F][x];
}
class InducedSubgraphs
{
	public:
		int getCount(vector<int> u,vector<int> v,int K)
		{
			for(memset(d,9,sizeof(d)),n=u.size()+1;i<=n;i++)for(J[d[i][i]=0]=c[i][0]=j=1;j<=i;j++)J[j]=1ll*J[j-1]*j%P,c[i][j]=(c[i-1][j]+c[i-1][j-1])%P;
			for(i=0;i<n-1;i++)d[u[i]][v[i]]=d[v[i]][u[i]]=1;
			for(k=0;k<n;k++)for(i=0;i<n;i++)for(j=0;j<n;j++)d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
			for(i=0;i<n;i++)D(i,n);if(K<2)return J[n];
			if(K*2>n){for(i=0;i<n;i++)S=(S+g[n][i][n-K][n-K])%P;S=1ll*S*J[K+K-n-1]%P;}else for(i=0;i<n;i++)for(j=0;j<n;j++)if(d[i][j]==n-K-K+1)
			{
				G(i,j,k);G(j,i,l);
				if(s[k][i]==K&&s[l][j]==K)S=(1ll*f[k][i]*f[l][j]+S)%P;
			}
			return S;
}
};
