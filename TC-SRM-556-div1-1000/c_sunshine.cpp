#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
#define del(_p) head[_p]=next[head[_p]]
const int maxn=6000,maxm=200000,inf=1<<20;

class OldBridges
{
	public:
	int n,a1,a2,an,b1,b2,bn;
	char g[55][55];
	int adj[maxm],f[maxm],next[maxm],head[maxn],tot;
	int level[maxn],dn,S,T,maxflow;
	int q[maxn],qh,qt;
	 
	void addedge(int u,int v,int w)
	{tot++;adj[tot]=v;f[tot]=w;next[tot]=head[u];head[u]=tot;
	tot++;adj[tot]=u;f[tot]=0;next[tot]=head[v];head[v]=tot;}
	 
	void init()
	{
		a1++,a2++,b1++,b2++;an<<=1;bn<<=1;
		dn=n;S=++dn;T=++dn;
		tot=0;
		memset(head,0,n+n*n+3<<3);tot=1;
		for(int i=1;i<=n;i++)
		{
				scanf("%s",g[i]+1);
				for(int j=i+1;j<=n;j++)
					{
 					 if(g[i][j]=='X')continue;
						dn++;
						addedge(i,dn,inf);
						addedge(j,dn,inf);
						dn++;
						addedge(dn,i,inf);
						addedge(dn,j,inf);
						addedge(dn-1,dn,g[i][j]=='O'?2:inf);
				}
		}
		addedge(S,a1,an);
		addedge(a2,T,an);
		addedge(S,b1,bn);
		addedge(b2,T,bn);
	}
	
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
		if(u==T)return maxflow+=flow,flow;
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
	 
	int dinic()
	{
		maxflow=0;
		while(bfs())
			aug(S,inf);
		return maxflow;
	}

	bool work()
	{
		if(dinic()!=an+bn)return 0;//check if we can find the first flow
		for(int i=2;i<=tot;i+=2)
			f[i]+=f[i^1],f[i^1]=0;
		//change the graph.
		del(S),del(b1),del(b2),del(T);
		addedge(S,b2,bn);
		addedge(b1,T,bn);
		if(dinic()!=an+bn)return 0;//check if we can find the second flow
		return 1;
	}
	string isPossible(vector<string> bridges,int a1,int a2,int an,int b1,int b2,int bn)
	{
		//We can prove it is possible if we can find the following two flows.
		//an+bn units of flow from a1,b1 to a2,b2
		//ab+bn units of flow from a1,b2 to a2,b1
		this->a1=a1;
		this->a2=a2;
		this->an=an;
		this->b1=b1;
		this->b2=b2;
		this->bn=bn;
		n=bridges.size();
		tot=1;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				g[i][j]=bridges[i-1][j-1];
		init();//build the graph.
		return work()?"Yes":"No";
	}
};


