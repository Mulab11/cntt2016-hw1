#include<bits/stdc++.h>
#define A(x,y) to[++t]=y,la[t]=h[x],h[x]=t,to[++t]=x,la[t]=h[y],h[y]=t
#define N 2520
using namespace std;
int n,m,K,p[N],la[2*N],to[2*N],h[N],t,i,j,k,d[333][N],a[N],w,x,y,sz[N],ID[55][55];double c[N][N],ans;
int G(int fr,int fa,int x,int di){d[fr][x]=di;for(int i=h[x];i;i=la[i])if(to[i]!=fa)G(fr,x,to[i],di+1);}
double C(int x,int y){if(x<0||y<0)return 0;return c[x][y];}
void D(int x,int f)
{
	sz[x]=a[x];
	for(int i=h[x];i;i=la[i])if(to[i]!=f)D(to[i],x),sz[x]+=sz[to[i]];
	if(x!=1)ans+=(c[m][K]-C(m-sz[x],K)-C(sz[x],K))*2;
}
class Orienteering
{
	public:
		double expectedLength(vector<string> S,int _)
		{
			for(K=_;i<S.size();i++)for(j=0;j<S[0].size();j++)if(S[i][j]!='#')
			{
				if(ID[i][j]=++n,S[i][j]=='*')a[p[++m]=n]=1;
				if(i&&S[i-1][j]!='#')A(ID[i-1][j],n);
				if(j&&S[i][j-1]!='#')A(ID[i][j-1],n);
			}
			for(i=0;i<=n;i++)for(c[i][0]=j=1;j<=i;j++)c[i][j]=c[i-1][j-1]+c[i-1][j];
			for(i=1;i<=m;i++)G(i,p[i],p[i],0);
			for(i=1;i<=m;i++)for(j=i+1;j<=m;j++)
			{
				for(k=1;k<=m;k++)if(k!=i&&k!=j&&((d[i][p[k]]<d[i][p[j]]&&d[j][p[k]]<d[i][p[j]])||(d[i][p[k]]==d[i][p[j]]&&d[j][p[k]]<=d[i][p[j]]&&k>j)||(d[i][p[k]]<d[i][p[j]]&&d[j][p[k]]==d[i][p[j]]&&k>i)))w++;
				ans-=c[w][K-2]*d[i][p[j]];w=0;
			}
			return D(1,0),ans/c[m][K];
		}
};
