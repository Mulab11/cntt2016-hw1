#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 110
using namespace std;
struct GooseTattarrattatDiv1
{
	int to[N],nxt[N],pre[N],cnt;
	void ae(int ff,int tt)
	{
		cnt++;
		to[cnt]=tt;
		nxt[cnt]=pre[ff];
		pre[ff]=cnt;
	}
	int a[27];
	bool vis[N];
	int tot,maxn;
	void dfs(int x)//DFS求出每个连通块的最大值和总和 
	{
		vis[x]=true;
		tot+=a[x];
		maxn=max(maxn,a[x]);
		int i,j;
		for(i=pre[x];i;i=nxt[i])
		{
			j=to[i];
			if(vis[j]) continue;
			dfs(j);
		}
	}
	int getmin(string S)
	{
		int n=S.size();
		int i,j;
		for(i=0;i<n/2;i++)//把需要变成一样的字母连起来 
		{
			ae(S[i]-96,S[n-i-1]-96);
			ae(S[n-i-1]-96,S[i]-96);
		}
		for(i=0;i<n;i++)
		a[S[i]-96]++;
		int ans=0;
		for(i=1;i<=26;i++)
		if(!vis[i])
		{
			tot=0;maxn=0;
			dfs(i);
			ans+=tot-maxn;
		}
		return ans;
	}
};