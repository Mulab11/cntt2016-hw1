#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int N=30,L=32767,maxp=10000,maxm=100000,inf=1<<20;

inline bool ten(int &x,const int &y){return y<x?(x=y,1):0;}
inline bool rel(int &x,const int &y){return x<y?(x=y,1):0;}

class CurvyonRails
{
	public:
	int n,m;
	char g[N][N];
	int head[maxp],adj[maxm],f[maxm],c[maxm],next[maxm],tot;
	int S,T,dn,mf,cost,d[maxp],q[L+1],qh,qt;
	bool vis[maxp],inq[maxp];
	int I[N][N],UD[N][N],LR[N][N];
	
	void addedge(int u,int v,int w,int p)
	{tot++;adj[tot]=v;f[tot]=w;c[tot]=p;next[tot]=head[u];head[u]=tot;
	tot++;adj[tot]=u;f[tot]=0;c[tot]=-p;next[tot]=head[v];head[v]=tot;}
	
	bool spfa()
	{
		memset(d,31,dn+1<<2);
		d[S]=0;qh=0,q[qt=1]=S;
		for(int u,i;qh!=qt;)
		{
			u=q[qh=qh+1&L];inq[u]=0;
			for(i=head[u];i;i=next[i])
				if(f[i]>0&&ten(d[adj[i]],d[u]+c[i])&&!inq[adj[i]])
					q[qt=qt+1&L]=adj[i],inq[adj[i]]=1;
		}
		return d[T]<inf;
	}
	
	int aug(int u,int flow)
	{
		if(u==T)
		{
			cost+=flow*d[T];
			mf+=flow;
			return flow;
		}
		vis[u]=1;
		int left=flow;
		for(int t,i=head[u];i&&left;i=next[i])
			if(!vis[adj[i]]&&f[i]>0&&d[u]+c[i]==d[adj[i]])
			{
				t=aug(adj[i],min(left,f[i]));
				left-=t;
				f[i]-=t,f[i^1]+=t;
			}
		return flow-left;
	}
	
	void MCF()
	{
		mf=cost=0;
		while(spfa())
		{
			do memset(vis,0,dn+1);
			while(aug(S,inf));
		}
	}
	
	int getmin(vector<string> field)
	{
		//We can transform this problem to a Min-cost flow problem.
		//Let's forget the cost of the straight segment of tracks.
		//We color the board with black and white, and make sure that adjacent cells have different colors.
		//Then we find that each white cell should be matched with two black cells,
		//and each black cells should be matched with two white cells.
		//We can create S and T, and add edges from S to each white cell with capacity 2, then add edges from each black cell to T with capacity 2.
		//Add edges from each white cell to all its adjacent cells.
		//Then we can check if it is possible to arrange the tracks by using a max-flow algorithm.
		//Consider the cost of straight tracks now, and we can create two vertices for each cell which each has a edge with capacity 1 to S or T.
		//One is connected transversely and another is connected lengthways.
		//So when we add edges between cells, we choose the vertices with correct direction.
		//The max-flow equals the number of available cells, so we can do it freely.
		//We can bidirectionally connect two vertices of one cell with both capacity and cost 1(cost is 0 if there aren't Curvies).
		//So we can place straight tracks for cost 1 each cell, when we have to.
		tot=1;n=field.size(),m=field[0].size();
		memset(g,'w',sizeof(g));
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				I[i][j]=++dn;LR[i][j]=++dn,UD[i][j]=++dn;
				g[i][j]=field[i-1][j-1];
			}
		//Build the graph.
		S=++dn,T=++dn;
		int fs=0,ft=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(g[i][j]!='w')
				{
					if(i+j&1)
					{
						addedge(S,I[i][j],2,0);fs+=2;
						//Add the bidirectional edge with cost 1 if there are Curvies.
						addedge(I[i][j],LR[i][j],1,0);
						addedge(I[i][j],LR[i][j],1,(g[i][j]=='C'));
						addedge(I[i][j],UD[i][j],1,0);
						addedge(I[i][j],UD[i][j],1,(g[i][j]=='C'));
						//Add edges between adjacent cells.
						if(g[i][j+1]!='w')
							addedge(LR[i][j],LR[i][j+1],1,0);
						if(g[i][j-1]!='w')
							addedge(LR[i][j],LR[i][j-1],1,0);
						if(g[i+1][j]!='w')
							addedge(UD[i][j],UD[i+1][j],1,0);
						if(g[i-1][j]!='w')
							addedge(UD[i][j],UD[i-1][j],1,0);
					}
					else
					{
						addedge(I[i][j],T,2,0);ft+=2;
						addedge(LR[i][j],I[i][j],1,0);
						addedge(LR[i][j],I[i][j],1,(g[i][j]=='C'));
						addedge(UD[i][j],I[i][j],1,0);
						addedge(UD[i][j],I[i][j],1,(g[i][j]=='C'));
					}
			}
		if(fs!=ft)return -1;//The numbers of white cells and black cells are different.
		MCF();//Min-cost flow.
		if(mf!=fs)return -1;//Can't arrange the tracks.
		return cost;
	}
};

