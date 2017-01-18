#include<iostream>
#include<cstdio>
#include<vector>
#define N 10000
using namespace std;
int n,s,to[N],ne[N],pre[N],f[N],g[N],ans=1e9;
void add(int u,int v)
{to[++s]=v;ne[s]=pre[u];pre[u]=s;}
void dp(int k,int x)
{
	int o=0;
	for(int i=pre[k];i;i=ne[i]) if(to[i]!=x) o++,dp(to[i],k);
	if(!o)
	{
		f[k]=0;
		g[k]=1;
		return;
	}
	if(o==1)
	{
		for(int i=pre[k];i;i=ne[i]) if(to[i]!=x) f[k]=f[to[i]],g[k]=g[to[i]];
		return;
	}
	int sum=0;
	for(int i=pre[k];i;i=ne[i]) if(to[i]!=x) sum+=g[to[i]];
	g[k]=1e9;
	for(int i=pre[k];i;i=ne[i]) if(to[i]!=x) g[k]=min(g[k],sum-g[to[i]]+f[to[i]]);
	f[k]=g[k];
}
struct TPS
{
int minimalBeacons(vector<string> c)
{
	n=c[0].size();
	if(n==1) return 0;
	for(int i=0;i<n;i++) for(int j=0;j<n;j++) if(c[i][j]=='Y') add(i+1,j+1);
	for(int i=1;i<=n;i++)
	{
		dp(i,0);
		ans=min(ans,f[i]+1);
	}
	return ans;
}
};