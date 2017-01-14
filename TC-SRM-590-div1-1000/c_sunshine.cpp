#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
const int maxp=5555,maxe=666666,inf=(1<<28)-1;;
class FoxAndCity
{
	public:
	int n,g[45][45];
	int adj[maxe],f[maxe],next[maxe],head[maxp],tot=1;
	int level[maxp],q[maxp],qh,qt,maxflow;
	int S,T,dn,I[45][45]; 
	
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
	
	//Above is dinic algorithem for max-flow problem
	
	int sqr(const int &xx)
	{return xx*xx;}
	
	int minimalCost(vector<string> linked,vector<int> want)
	{
		//We can transform this problem to Min-Cut.
		//Let dist(x,y) equal the minimum distance from x to y, 
		//and d(x)/D(x) means the original/final distance from 0 to x.
		//It is clearly that D(x)<=d(x) and D(y)<=D(x)+dist(x,y).
		//for each point x we create d(x)+1 points P(x,0..d(x)),
		//and edges from P(x,i-1) to P(x,i) with weight (i-want[x])^2.
		//So it means we set D(x)=i when we cut edge <P(x,i-1),P(x,i)>
		//Then for each pair <x,y>, we add edges <P(y,i+dist(x,y)),P(x,i)> with weight infinity
		//to make it impossible to set D(x)=k and D(y)>k+dist(x,y) at same time,
		//because there exist a path S->P(y,k+dist(x,y))->P(x,k)->T
		//Then use max-flow algoritham to solve it
		memset(g,31,sizeof(g));
		n=want.size();
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(linked[i][j]=='Y')
					g[i][j]=1;
		//Use floyd to determine minimum distance between pairs
		for(int k=0;k<n;k++)
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
		for(int i=1;i<n;i++)
			for(int j=0;j<=g[0][i];j++)
				I[i][j]=++dn;
		S=++dn,T=++dn;
		for(int i=1;i<n;i++)
		{
			int L=g[0][i];
			//Don't forget to add edges <S,P(x,0)> and <P(x,d(x)),T>
			addedge(S,I[i][0],inf);
			addedge(I[i][L],T,inf);
			for(int j=1;j<=L;j++)
				addedge(I[i][j-1],I[i][j],sqr(j-want[i]));
		}
		for(int i=1;i<n;i++)
			for(int j=1;j<n;j++)
				if(i!=j)
				{
					for(int k=0;k<=g[0][i]&&k+g[i][j]<=g[0][j];k++)
						addedge(I[j][k+g[i][j]],I[i][k],inf);
				}
		return dinic();
	}
};

