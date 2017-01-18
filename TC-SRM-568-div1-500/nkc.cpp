#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 20010
using namespace std;
int mod=1e9+7;
struct EqualSums
{
	int vis[N],T;
	int V[N];
	bool hav0,cant;
	int n;
	int to[N],nxt[N],w[N],pre[N],cnt;
	void ae(int ff,int tt,int ww)
	{
		cnt++;
		to[cnt]=tt;
		nxt[cnt]=pre[ff];
		pre[ff]=cnt;
		w[cnt]=ww;
	}
	void dfs(int x,int v)//向外扩展 
	{
		vis[x]=T;
		V[x]=v;
		if(v<0) cant=true;
		if(v==0&&x<n) hav0=true;
		int i,j;
		for(i=pre[x];i;i=nxt[i])
		{
			j=to[i];
			if(vis[j]==T)
			{
				if(V[x]+V[j]!=w[i]) cant=true;
				continue;
			}
			dfs(j,w[i]-V[x]);
		}
	}
	int count(vector <string> board)
	{
		n=board.size();
		int i,j;
		for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		if(board[i][j]!='-')
		{
			ae(i,n+j,board[i][j]-48);
			ae(n+j,i,board[i][j]-48);
		}
		long long ans1=1,ans2=1; //容斥原理算方案数，所有方案减去没有bi=0的方案 
		for(i=0;i<n+n;i++)
		if(!vis[i])
		{
			int tot=0,gg=0;
			for(j=0;j<10;j++)//枚举这个点的值 
			{
				hav0=false;cant=false;//分别判断 是否有0和是否合法 
				T++;
				dfs(i,j);
				if(cant) continue;
				tot++;
				if(!hav0) gg++;
			}
			(ans1*=tot)%=mod;
			(ans2*=gg)%=mod;
		}
		return (ans1-ans2+mod)%mod;
	}
};