#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
const int N=55,maxn=10000,maxm=1000000,inf=(1<<28)-1;
const int dx[4]={0,0,-1,1},dy[4]={-1,1,0,0};

class SurroundingGame
{
	public:
	int n,m;
	int c[N][N],b[N][N];
	int head[maxn],adj[maxm],f[maxm],next[maxm],tot;
	int I[N][N],P[N][N],A[N][N];
	int S,T,dn,level[maxn],q[maxn],qh,qt;
	
	void addedge(int u,int v,int w)
	{tot++;adj[tot]=v;f[tot]=w;next[tot]=head[u];head[u]=tot;
	tot++;adj[tot]=u;f[tot]=0;next[tot]=head[v];head[v]=tot;}
	
	bool bfs()
	{
		memset(level,-1,dn+1<<2);level[S]=0;
		qh=0;q[qt=1]=S;
		for(int u,i;qh<qt;)
		{
			u=q[++qh];
			for(i=head[u];i;i=next[i])
				if(level[adj[i]]==-1&&f[i]>0)
				{
					level[adj[i]]=level[u]+1;
					q[++qt]=adj[i];
					if(adj[i]==T)return 1;
				}
		}
		return 0;
	}
	 
	int aug(int u,int flow)
	{
		if(u==T)return flow;
		int left=flow,t,i;
		for(i=head[u];i&&left;i=next[i])
			if(f[i]>0&&level[adj[i]]==level[u]+1)
			{
				t=aug(adj[i],left<f[i]?left:f[i]);
				f[i]-=t,f[i^1]+=t,left-=t;
			}
		if(left==flow)level[u]=-1;
		return flow-left;
	}
	
	int getval(char c)
	{
		if(c<='9')return c-'0';
		if(c<='Z')return c-'A'+36;
		return c-'a'+10;
	}
	
	int maxScore(vector<string> cost,vector<string> benefit)
	{
		//We can transform this problem to a min-cut problem.
		//First we color the cells with black when i+j mod 2 = 0 and white otherwise.
		//For each black cell, we create a vertex p. It means we place a piece here if p belongs to S.
		//And for each white cell, it means we place a piece here if p is belong to T.
		//So for each black cell, we add an edge (p,T,cost[i][j])
		//Then we create a vertex s to represent if it is surrounded.
		//Think about a black cell, and we should add edges (p_w,s,+inf), in which p_w means the adjacent white cells.
		//So that s will belong to S if it is not surrounded. In this case we cost benefit[i][j].
		//So we should also add edges (s,T,benefit).
		//Last case if we place a piece here and this cell is surrounded at the same time, we get benefit[i][j] twice.
		//Add edge (p,s,benefit) to remove the extra benefit.
		//Edges about white cells are similar.
		int res=0,i,j,x,y;
		//Build the graph.
		tot=1;dn=0;
		n=cost.size(),m=cost[0].size();
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
			{
				c[i][j]=getval(cost[i-1][j-1]);
				b[i][j]=getval(benefit[i-1][j-1]);
				res+=b[i][j]<<1;
				I[i][j]=++dn;
				P[i][j]=++dn;
				A[i][j]=++dn;
			}
		S=++dn,T=++dn;
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				if(i+j&1)
				{
					addedge(I[i][j],T,c[i][j]);
					addedge(S,P[i][j],b[i][j]);
					addedge(P[i][j],I[i][j],inf);
					addedge(P[i][j],A[i][j],b[i][j]);
				}
				else
				{
					addedge(S,I[i][j],c[i][j]);
					addedge(P[i][j],T,b[i][j]);
					addedge(I[i][j],P[i][j],inf);
					addedge(A[i][j],P[i][j],b[i][j]);
				}
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				if(i+j&1)
				{
					for(int k=0;k<4;k++)
					{
						x=i+dx[k],y=j+dy[k];
						if(I[x][y])addedge(I[x][y],A[i][j],inf);
					}
					addedge(A[i][j],T,b[i][j]);
				}
				else
				{
					for(int k=0;k<4;k++)
					{
						x=i+dx[k],y=j+dy[k];
						if(I[x][y])addedge(A[i][j],I[x][y],inf);
					}
					addedge(S,A[i][j],b[i][j]);
				}
		//Use dinic algorithm to solve the min-cut problem.
		while(bfs())
			res-=aug(S,inf);
		return res;
	}
};

