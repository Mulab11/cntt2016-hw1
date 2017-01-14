#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

namespace MinCostFlow
{
const int maxn=105,maxm=100005,L=1023,inf=1<<15;
int adj[maxm],f[maxm],c[maxm],next[maxm],tot=1;
int head[maxn];
int S,T,dn,d[maxn],cost;
 
int q[L+1],qh,qt,st[maxn],top;
bool inq[maxn],vis[maxn];
 
void addedge(int u,int v,int w,int p)
{tot++;adj[tot]=v;f[tot]=w;c[tot]=p;next[tot]=head[u];head[u]=tot;
tot++;adj[tot]=u;f[tot]=0;c[tot]=-p;next[tot]=head[v];head[v]=tot;}

bool spfa()
{
	memset(d,-20,dn+1<<2);
	memset(inq,0,dn+1);
	d[S]=0;qh=0;q[qt=1]=S;
	for(int u,i;qh!=qt;)
	{
		qh=qh+1&L;
		u=q[qh];
		inq[u]=0;
		for(i=head[u];i;i=next[i])
			if(f[i]&&d[adj[i]]<d[u]+c[i])
			{
				d[adj[i]]=d[u]+c[i];
				if(!inq[adj[i]])
				{
					qt=qt+1&L;
					q[qt]=adj[i];
					inq[adj[i]]=1;
				}
			}
	}
	return d[T]>0;
}
 
int dfs(int u,int flow)
{
	vis[u]=1;
	if(u==T)return cost+=flow*d[T],flow;
	int left=flow,i,t;
	for(i=head[u];i&&left;i=next[i])
		if(!vis[adj[i]]&&f[i]&&d[u]+c[i]==d[adj[i]])
		{
			t=dfs(adj[i],min(f[i],left));
			f[i]-=t,f[i^1]+=t;
			left-=t;
		}
	return flow-left;
}

int MCF()
{
	cost=0;
	while(spfa())
	{
		vis[T]=1;
		while(vis[T])
		{
			memset(vis,0,sizeof(vis));
			dfs(S,inf);
		}
	}
	return cost;
}
} 

class DeerInZooDivOne
{
	public:
	int n;
	int F[55][55][55][55];
	int wh[55];
	vector<int> adj[55];
	int I1[55],I2[55];
	int dp(int fx,int x,int fy,int y)
	{
		int &res=F[fx][x][fy][y];
		if(!res)return res;
		//DP in subtree.
		for(int i=0;i<adj[x].size();i++)if(adj[x][i]!=fx)
			for(int j=0;j<adj[y].size();j++)if(adj[y][j]!=fy)
				dp(x,adj[x][i],y,adj[y][j]);
		using namespace MinCostFlow;
		//We can use min-cost flow to match the x's and y's children.
		//It is clear that matching the children is like bipartite weighted graph maximum matching.
		//And the edges (p,q)'s weight is the grestest isomorphic part between p's and q's subtrees.
		tot=1;dn=0; 
		head[S=++dn]=0;
		head[T=++dn]=0;
		for(int i=0;i<adj[x].size();i++)
			if(adj[x][i]!=fx)
			{
				head[I1[i]=++dn]=0;
				addedge(S,I1[i],1,0);
			}
		for(int i=0;i<adj[y].size();i++)
			if(adj[y][i]!=fy)
			{
				head[I2[i]=++dn]=0;
				addedge(I2[i],T,1,0);
			}
		for(int i=0;i<adj[x].size();i++)if(adj[x][i]!=fx)
			for(int j=0;j<adj[y].size();j++)if(adj[y][j]!=fy)
				addedge(I1[i],I2[j],1,F[x][adj[x][i]][y][adj[y][j]]);
		res=MCF()+1;//x and y are matched.
		return res;
	}
	
	void ddfs(int x)
	{
		wh[x]=1;
		for(int i=0;i<adj[x].size();i++)
			if(!wh[adj[x][i]])
				ddfs(adj[x][i]);
	}
	
	int getmax(vector<int> a,vector<int> b)
	{
		int ans=0;
		n=a.size()+1;
		for(int i=0;i<n-1;i++)
			a[i]++,b[i]++;
		//F[fx][x][fy][y]:The size of largest isomorphic connective graph between x's and y's subtree,
		//while x matches y. fx is x's father and fy is y's father.
		memset(F,-1,sizeof(F));
		for(int k=0;k<n-1;k++)
		{
			for(int i=1;i<=n;i++)
				adj[i].clear();
			for(int i=0;i<n-1;i++)
			{
				//initialize all possible used elements
				for(int j=0;j<n-1;j++)
				{
					F[a[i]][b[i]][a[j]][b[j]]=-1;
					F[a[i]][b[i]][b[j]][a[j]]=-1;
					F[b[i]][a[i]][a[j]][b[j]]=-1;
					F[b[i]][a[i]][b[j]][a[j]]=-1;
				}
				for(int j=0;j<n;j++)
				{
					F[0][j][a[i]][b[i]]=-1;
					F[0][j][b[i]][a[i]]=-1;
					F[a[i]][b[i]][0][j]=-1;
					F[b[i]][a[i]][0][j]=-1;
				}
				if(i!=k)//Delete one edge
					adj[a[i]].push_back(b[i]),
					adj[b[i]].push_back(a[i]);
			}
			memset(wh,0,sizeof(wh));
			ddfs(1);
			for(int i=1;i<=n;i++)
				if(wh[i]==1)
					for(int j=1;j<=n;j++)
						if(wh[j]==0)
							ans=max(ans,dp(0,i,0,j));
		}
		return ans;
	}
};

