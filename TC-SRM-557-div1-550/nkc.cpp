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
#define MAXM 10010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
struct vec
{
	int to;
	int fro;
};
struct G
{
	vec mp[MAXM];
	int tai[MAXN],cnt;
	inline void be(int x,int y);
	void dfs(int x);
	void pre(int x);
	void build();
};
G g1;
int n;
bool vis[MAXN];
int siz[MAXN];
int bel[MAXN];
int dfn[MAXN],low[MAXN],tim;
bool ist[MAXN];
int st[MAXN],tp;
int tot;
bool nbl[MAXN];
int now;
bool MP[MAXN][MAXN];
int bf[MAXN];
inline void G::be(int x,int y)
{
	mp[++cnt].to=y;
	mp[cnt].fro=tai[x];
	tai[x]=cnt;
}
void G::dfs(int x)
{
	int i,y;
	dfn[x]=low[x]=++tim;
	ist[st[++tp]=x]=1;
	for(i=tai[x];i;i=mp[i].fro)
	{
		y=mp[i].to;
		if(!dfn[y])
		{
			dfs(y);
			low[x]=min(low[x],low[y]);
		}
		else if(ist[y])
		{
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(dfn[x]==low[x])
	{
		int t=0;
		tot++;
		while(t!=x)
		{
			ist[t=st[tp--]]=0;
			siz[bel[t]=tot]++;
		}
	}
}
void G::build()
{
	int i,x,y;
	for(x=1;x<=n;x++)
	{
		for(i=tai[x];i;i=mp[i].fro)
		{
			y=mp[i].to;
			if(bel[x]!=bel[y])
			{
				MP[bel[x]][bel[y]]=1;
			}
		}
	}
}
void pre(int x)
{
	int i;
	vis[x]=1;
	for(i=1;i<=tot;i++)
	{
		if(MP[x][i]&&!vis[i])
		{
			if(!nbl[i])
			{
				MP[now][i]=1;
			}
			pre(i);
		}
	}
}
int find(int x)
{
	int i;
	for(i=1;i<=n;i++)
	{
		if(MP[x][i])
		{
			if(vis[i]||bf[i]==x)
			{
				continue ;
			}
			vis[i]=1;
			if(!bf[i]||find(bf[i]))
			{
				bf[i]=x;
				return 1;
			}
		}
	}
	return 0;
}
struct Incubator
{
	int maxMagicalGirls(vector<string>_mp)
	{
		int i,j,k;
		n=_mp.size();
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				if(_mp[i][j]=='Y')
				{
					MP[i+1][j+1]=1;
				}
			}
		}
		for(k=1;k<=n;k++)
		{
			for(i=1;i<=n;i++)
			{
				for(j=1;j<=n;j++)
				{
					MP[i][j]|=(MP[i][k]&MP[k][j]);//传递闭包 
				}
			}
		}
		int ans=n;
		for(i=1;i<=n;i++)
		{
			memset(vis,0,sizeof(vis));
			ans-=find(i);//求最长反链 
		}
		return ans;
	}
};