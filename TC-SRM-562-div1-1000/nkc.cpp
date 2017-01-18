#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<iomanip>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<queue>
#include<stack>
using namespace std;
#define MAXN 42
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000009
#define eps 1e-8
#define ll long long
ll C[MAXN][MAXN]; 
ll fac[MAXN];
int siz[MAXN][MAXN];
ll g[MAXN][MAXN];
ll f[MAXN][MAXN][MAXN][MAXN];
ll t[MAXN][MAXN];
int dis[MAXN][MAXN];
bool mp[MAXN][MAXN];
bool vis[MAXN][MAXN];
int n,K;
void dfs(int x,int p)
{
	int y;
	if(siz[x][p])
	{
		return ;
	}
	g[x][p]=1;
	for(y=1;y<=n;y++)
	{
		if(mp[x][y]&&y!=p)
		{
			dfs(y,x);
			siz[x][p]+=siz[y][x];
			g[x][p]=g[x][p]*g[y][x]%MOD*C[siz[x][p]][siz[y][x]]%MOD;//计算子树大小和标号方案数  
		}
	}
	siz[x][p]++;
}
int main1()
{ //2k<=n 
	int i,j,k,l;
	memset(dis,0x3f,sizeof(dis));
	for(i=1;i<=n;i++)
	{
		dis[i][i]=0;
		for(j=1;j<=n;j++)
		{
			if(mp[i][j])
			{
				dis[i][j]=1;
			}
		}
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			for(k=1;k<=n;k++)
			{
				dis[j][k]=min(dis[j][k],dis[j][i]+dis[i][k]);
			}
		}
	}
	int re=0;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(dis[i][j]==n-2*K+1)
			{
				
				for(k=1;k<=n;k++)
				{
					if(mp[i][k]&&dis[k][j]<dis[i][j])
					{
						break;
					}
				}
				for(l=1;l<=n;l++)
				{
					if(mp[j][l]&&dis[l][i]<dis[j][i])
					{
						break;
					}
				}
				if(siz[i][k]==K&&siz[j][l]==K)
				{
					(re+=g[i][k]*g[j][l]%MOD)%=MOD;
				}
			}
		}
	}
	return re;
}
void dfs2(int x,int p)
{
	int i,j,k,l;
	int y;
	int tmp=0;
	f[x][p][0][0]=1;
	if(!vis[x][p])
	{
		vis[x][p]=1;
		for(y=1;y<=n;y++)
		{
			if(mp[x][y]&&y!=p)
			{
				dfs2(y,x);
				memset(t,0,sizeof(t));
				for(i=0;i<=tmp;i++)
				{
					for(j=0;j<=tmp;j++)
					{
						for(k=0;k<=siz[y][x];k++)
						{
							for(l=0;l<=siz[y][x];l++)
							{
								/*
								if(x==2&&p==0)
								{
									cerr<<i<<' '<<j<<' '<<k<<' '<<l<<'!'<<endl;
									cerr<<f[x][p][i][j]<<' '<<f[y][x][k][l]<<' '<<C[i+k][k]<<' '<<C[j+l][l]<<endl;
								}
								//*/
								(t[i+k][j+l]+=f[x][p][i][j]*f[y][x][k][l]%MOD*C[i+k][k]%MOD*C[j+l][l]%MOD)%=MOD;
							}
						}
					}
				}
				memcpy(f[x][p],t,sizeof(t));
				tmp+=siz[y][x];
			}
		}
		f[x][p][siz[x][p]][0]=f[x][p][0][siz[x][p]]=g[x][p];
	}
}
int main2()
{//2k>n
	int i;
	for(i=1;i<=n;i++)
	{
		dfs2(i,0);
	}
	int mid=2*K-n;
	ll re=0;
	for(i=1;i<=n;i++)
	{
		(re+=f[i][0][n-K][n-K])%=MOD;;
	}
	return re*fac[mid-1]%MOD;
}
struct InducedSubgraphs
{
	int getCount(vector<int>v1,vector<int>v2,int _k)
	{
		int i,j;
		K=_k;
		n=v1.size()+1;
		for(i=0;i<v1.size();i++)
		{
			mp[v1[i]+1][v2[i]+1]=mp[v2[i]+1][v1[i]+1]=1;
		}
		for(i=0;i<MAXN;i++)
		{
			C[i][0]=1;
			for(j=1;j<=i;j++)
			{
				C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
			}
		}
		fac[0]=1;
		for(i=1;i<MAXN;i++)
		{
			fac[i]=fac[i-1]*i%MOD;
		}
		if(K==1)
		{
			return fac[n];
		}
		for(i=1;i<=n;i++)
		{
			dfs(i,0);//预处理 
		}
		if(K*2<=n)
		{
			return main1();
		}
		else
		{
			return main2();
		}
	}
};

/*

*/