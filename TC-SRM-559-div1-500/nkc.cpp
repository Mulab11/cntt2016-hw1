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
#define MAXN 1010
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
struct vec
{
	int to;
	int fro;
};
vec mp[MAXN*2];
int tai[MAXN],cnt;
int d[MAXN];
int h[MAXN];
int n;
int rt;
int deg[MAXN],dep[MAXN];
ll f[MAXN][3][3];
ll ans;
int abl[3][4]=
{
{1,0},
{1,0},
{3,2,1,0}};
int abll[3][4]=
{
{1,0},
{2,1,0},
{3,2,1,0}};
inline void be(int x,int y)
{
	mp[++cnt].to=y;
	mp[cnt].fro=tai[x];
	tai[x]=cnt;
}
inline void bde(int x,int y)
{
	deg[x]++;
	deg[y]++;
	be(x,y);
	be(y,x);
}
void pre(int x,int F)
{
	int i,y;
	h[x]=1;
	for(i=tai[x];i;i=mp[i].fro)
	{
		y=mp[i].to;
		if(y!=F)
		{
			pre(y,x);
			h[x]=max(h[x],h[y]+1);
		}
	}
}
void ud(int x,int s1,int s2)
{
	int i,j,J,k,K,l,L;
	for(i=2;~i;i--)
	{
		for(J=1;J<=abll[i][0];J++)
		{
			j=abll[i][J];
			for(K=1;K<=abl[j][0];K++)
			{
				k=abl[j][K];
				for(L=1;L<=abll[k][0];L++)
				{
					l=abll[k][L];
					f[x][i][l]+=f[s1][i][j]*f[s2][k][l];
				}
			}
		}
	}
}
void dp(int x,int F)
{
	int i,j,y;
	dep[x]=dep[F]+1;
	memset(f[x],0,sizeof(f[x]));
	if(dep[x]==h[rt]-1)
	{
		if(deg[x]==3)
		{
			f[x][deg[x]-1][deg[x]-1]=2;
		}
		else
		{
			f[x][deg[x]-1][deg[x]-1]=1;
		}
		//<<x<<"!"<<f[x][deg[x]-1][deg[x]-1]<<endl;
		return ;
	}
	if(x!=rt)
	{
		if(deg[x]!=3)
		{
			return ;
		}
	}
	else
	{
		if(deg[x]!=2)
		{
			return ;
		}
	}
	int s1=-1,s2;
	for(i=tai[x];i;i=mp[i].fro)
	{
		y=mp[i].to;
		if(y!=F)
		{
			dp(y,x);
			if(s1==-1)
			{
				s1=y;
			}
			else
			{
				s2=y;
			}
		}
	}
	ud(x,s1,s2);
	ud(x,s2,s1);
	/*
	cerr<<x<<"!"<<endl;
	for(i=0;i<=2;i++)
	{
		for(j=0;j<=2;j++)
		{
			cerr<<f[x][i][j]<<' ';
		}
		cerr<<endl;
	}
	//*/
}
struct HatRack
{
	ll countWays(vector<int>v1,vector<int>v2)
	{
		int i,j,J;
		n=v1.size()+1;
		for(i=0;i<v1.size();i++)
		{
			bde(v1[i],v2[i]);
		}
		for(rt=1;rt<=n;rt++)
		{
			pre(rt,0);
			if(h[rt]==2)
			{
				if(deg[rt]==1)
				{
					ans++;
				}
				if(deg[rt]==2)
				{
					ans+=2;
				}
				continue ;
			}
			dp(rt,0);
			for(i=2;~i;i--)
			{
				for(J=1;J<=abll[i][0];J++)
				{
					j=abll[i][J];
					ans+=f[rt][i][j];
				}
			}
		}
		return ans;
	}
};