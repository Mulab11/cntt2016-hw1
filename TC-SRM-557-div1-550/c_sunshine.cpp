#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
const int inf=(1<<25)-1;
class Incubator
{
	public:
	
	int n;
	int g[55][55];
	int head[111],adj[20000],f[20000],next[20000],tot;
	int S,T,dn,level[111],q[111],qh,qt;
	
	void addedge(int u,int v,int w)
	{tot++;adj[tot]=v;f[tot]=w;next[tot]=head[u];head[u]=tot;
	tot++;adj[tot]=u;f[tot]=0;next[tot]=head[v];head[v]=tot;}
	
	bool bfs()
	{
		memset(level,-1,dn+1<<2);
		qh=0,q[qt=1]=S;
		level[S]=0;
		for(int u,v,i;qh<qt;)
		{
			u=q[++qh];
			for(i=head[u];i;i=next[i])
				if(level[v=adj[i]]==-1&&f[i]>0)
				{
					level[v]=level[u]+1;
					if(v==T)return 1;
					q[++qt]=v;
				}
		}
		return 0;
	}
	
	int aug(int u,int flow)
	{
		if(u==T)return flow;
		int left=flow;
		for(int t,i=head[u];i&&left;i=next[i])
			if(level[adj[i]]==level[u]+1&&f[i]>0)
			{
				t=aug(adj[i],min(left,f[i]));
				left-=t;
				f[i]-=t,f[i^1]+=t;
			}
		if(left==flow)level[u]=-1;
		return flow-left;
	}
	
	int maxMagicalGirls(vector<string> love)
	{
		//We use Floyd to do transitive closure firstly.
		tot=1;n=love.size();
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				g[i][j]=love[i][j]=='Y';
		for(int k=0;k<n;k++)
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					g[i][j]|=g[i][k]&g[k][j];
		//Then the task become that we should find the maximum number of vertices none of which are connected.
		//We can create two nodes x,x' for each vertex. And for all edges(u,v), we add edges (u,v').
		//We can prove the answer is n - maximum match and use max-flow to solve bipartite maximum match.
		S=dn=n+n,T=++dn;
		for(int i=0;i<n;i++)
			addedge(S,i,1),addedge(n+i,T,1);
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(g[i][j])addedge(i,n+j,1);
		int res=n;
		while(bfs())
			res-=aug(S,inf);
		return res;
	}
};

