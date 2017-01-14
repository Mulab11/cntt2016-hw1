#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
const int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};
const int maxp=3333,maxe=66666,inf=1<<20;

class FoxAndGo3
{
	public:
	
	int adj[maxe],f[maxe],next[maxe],head[maxp],tot=1;
	int level[maxp],q[maxp],qh,qt,maxflow;
	int S,T,dn;
	
	void addedge(int u,int v,int w)
	{tot++;adj[tot]=v;f[tot]=w;next[tot]=head[u];head[u]=tot;
	tot++;adj[tot]=u;f[tot]=0;next[tot]=head[v];head[v]=tot;}
	
	int aug(int u,int flow)
	{
		if(u==T)return maxflow+=flow,flow;
		int left=flow;
		for(int i=head[u],t;i&&left;i=next[i])
			if(level[adj[i]]==level[u]+1&&f[i]>0)
			{
				t=aug(adj[i],min(f[i],left));
				f[i]-=t,f[i^1]+=t,left-=t;
			}
		if(left==flow)level[u]=-1;
		return flow-left;
	}
	
	int bfs()
	{
		memset(level,-1,dn+1<<2);
		level[q[qt=1]=S]=0,qh=0;
		for(int u,i;qh<qt;)
		{
			u=q[++qh];
			for(i=head[u];i;i=next[i])
				if(level[adj[i]]==-1&&f[i]>0)
				{
					level[adj[i]]=level[u]+1;
					if(adj[i]==T)return 1;
					q[++qt]=adj[i];
				}
		}
		return 0;
	}
	
	int dinic()
	{
		maxflow=0;
		while(bfs())
			aug(S,inf);
		return maxflow;
	}
	
	int n,m,I[55][55];
	
	int maxEmptyCells(vector<string> board)
	{
		//We can transform this problem into a min-cut problem.
		//For each cell (i,j) on the board, we create a node I(i,j) to represent it.
		//For each white pieces, we think it remain on the board at last if it's belong T.
		//And it cost 1 if a white piece remain. So add edges <S,I(x,y),1> for (x,y) is white piece.
		//For each black piece or empty cell, we think black pieces occur there at last it if it's belong to S.
		//And it cost 1 to place a black piece on an empty cell. So add edges<I(x,y),T,1> for (x,y) is empty.
		//Then if a adjacent cell of a white piece belong to T that means it's still empty at last,
		//the white piece must remain and belong to T.
		//So we add edges <I(i,j),I(x,y),inf> for (i,j) is white piece and (x,y) is the adjacent empty cell.
		n=board.size();
		m=board[0].size();
		S=++dn,T=++dn;
		int cnt=0;
		//Build the network
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
			{
				cnt+=board[i][j]!='x';
				I[i][j]=++dn;
				if(board[i][j]=='o')addedge(S,I[i][j],1);
				else if(board[i][j]=='.')addedge(I[i][j],T,1);
			}
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(board[i][j]=='o')
				{
					for(int x,y,k=0;k<4;k++)
					{
						x=i+dx[k];
						y=j+dy[k];
						if(x>=0&&x<n&&y>=0&&y<m)
							addedge(I[i][j],I[x][y],inf);
					}
				}
		//Use dinic to solve the maxflow-mincut problem
		return cnt-dinic();
	}
};

