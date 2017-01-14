#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
int N,M,H,D;
int S,T,dn;

namespace MinCut//Maxflow
{
	const int maxp=55,maxe=6666;
	int adj[maxe],f[maxe],next[maxe],head[maxp],tot=1;
	int level[maxp],q[maxp],qh,qt,maxflow;
	
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
			aug(S,1000000);
		return maxflow;
	}
}

class GearsDiv1
{
	public:
	int n;
	string color;
	vector<string> graph;
	
	int work(char A,char B)
	{
		dn=0;
		MinCut::tot=1;
		memset(MinCut::head,0,sizeof(MinCut::head));
		//Build the graph
		int I[55];
		memset(I,0,sizeof(I));
		S=++dn,T=++dn;
		for(int i=0;i<n;i++)
			if(color[i]==A)
			{
				I[i]=++dn;
				MinCut::addedge(S,dn,1);
			}
			else if(color[i]==B)
			{
				I[i]=++dn;
				MinCut::addedge(dn,T,1);
			}
		//Use Max-flow algorithm to solve the maximum matchings
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(color[i]==A&&color[j]==B&&graph[i][j]=='Y')
					MinCut::addedge(I[i],I[j],1);
		return MinCut::dinic();
	}
	
	int getmin(string color,vector <string> graph)
	{
		//We will never turn all colors of gears in same direction.
		//If we do so, we can always change one color gears into the opposite direction, and it won't be worse
		//The conflicts only occurs between gears turned in the same direction.
		//We can link conflicting gear pairs and it must be a bipartite graph,
		//and the remain is a vertex cover in bipartite graph and it equals to maximum matchings.
		this->color=color;
		this->graph=graph;
		n=color.size();
		int ans=1000005;
		ans=min(ans,work('R','G'));
		ans=min(ans,work('R','B'));
		ans=min(ans,work('G','B'));
		return ans;
	}
};

