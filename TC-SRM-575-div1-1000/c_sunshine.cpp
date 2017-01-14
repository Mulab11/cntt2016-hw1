#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
const int dx[4]={1,0,-1,0};
const int dy[4]={0,1,0,-1};
const int maxp=5555,maxe=233333,inf=1<<20;
class TheTilesDivOne
{
	public:

int head[maxp],adj[maxe],f[maxe],next[maxe],tot;
int S,T,dn,level[maxp],q[maxp],qh,qt,mf;

inline void addedge(const int &u,const int &v,const int &w)
{tot++;adj[tot]=v;f[tot]=w;next[tot]=head[u];head[u]=tot;
tot++;adj[tot]=u;f[tot]=0;next[tot]=head[v];head[v]=tot;}

bool bfs()
{
	qh=0,q[qt=1]=S;
	memset(level,-1,(dn+1)<<2),level[S]=0;
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
			t=aug(adj[i],min(f[i],left));
			left-=t;
			f[i]-=t,f[i^1]+=t;
		}
	if(left==flow)level[u]=-1;
	return flow-left;
}

int dinic()
{
	while(bfs())
		mf+=aug(S,inf);
	return mf;
}
	
	int n,m;
	int I[55][55];
	int tp[55][55];
	
	int find(vector<string> board)
	{
		//We divide the cells into three types:
		//12121
		//23232
		//12121
		//23232
		//12121
		//A tile is a path from a type-1 cell to a type-3 cell, and any cell should be passed at most once.
		//So the problem is transformed to a max-flow problem.
		tot=1;
		n=board.size();
		m=board[0].size();
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
			{
				//We create two points for each cell and add a 1-capacity edge between them to limit the number of passed time.
				I[i][j]=++dn;
				dn++;
				if(board[i][j]=='.')
					addedge(dn-1,dn,1);
				if((i+j)&1)tp[i][j]=(i&1)<<1|1;
				else tp[i][j]=2;
			}
		S=++dn;T=++dn;
		//addedge edge S->1->2->3->T 
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(tp[i][j]==1)
					addedge(S,I[i][j],1);
				else if(tp[i][j]==3)
					addedge(I[i][j]+1,T,1);
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				for(int x,y,k=0;k<4;k++)
				{
					x=i+dx[k];
					y=j+dy[k];
					if(x>=0&&x<n&&y>=0&&y<m&&tp[x][y]==tp[i][j]+1)
						addedge(I[i][j]+1,I[x][y],1);
				}
		return dinic();
	}
};

