#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
const int dx[4]={1,0,-1,0};
const int dy[4]={0,1,0,-1};
const int maxp=2555,maxe=100005,inf=maxe;
class BoardPainting
{
	public:
	int n,m;
	char s[55][55];

int head[maxp],adj[maxe],f[maxe],next[maxe],tot;
int S,T,dn,level[maxp],q[maxp],qh,qt,mf;
int I[55][55];

//Max flow: 

inline void addedge(const int &u,const int &v,const int &w)
{tot++;adj[tot]=v;f[tot]=w;next[tot]=head[u];head[u]=tot;
tot++;adj[tot]=u;f[tot]=0;next[tot]=head[v];head[v]=tot;}

bool bfs()
{
	qh=0,q[qt=1]=S;
	memset(level,-1,dn+1<<2),level[S]=0;
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

	int minimalSteps(vector<string> target)
	{
		//We can prove that the answer equal a half of the min-cut between the horizontal borders and vertical borders.
		//That means each cells are connected to all neighbouring cells and borders.
		//Each horizontal border is connected to S and each vertical border is connected to T.
		tot=1;
		n=target.size();
		m=target[0].size();
		memset(s,'.',sizeof(s));
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				s[i+1][j+1]=target[i][j];
		for(int i=1;i<=n;i++)//Create nodes to represent cells.
			for(int j=1;j<=m;j++)
				if(s[i][j]=='#')I[i][j]=++dn;
		S=++dn;T=++dn;
		//build the graph
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(s[i][j]=='#')
				{
					for(int x,y,k=0;k<4;k++)
					{
						x=i+dx[k];
						y=j+dy[k];
						if(s[x][y]=='#')//neighbouring cells
							addedge(I[i][j],I[x][y],1);
						else//be adjacent to border
						{
							if(k&1)addedge(S,I[i][j],1);
							else addedge(I[i][j],T,1);
						}
					}
				}
		return dinic()>>1;//use Max-flow to solve Min-cut
	}
};

