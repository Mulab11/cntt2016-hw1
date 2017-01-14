#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

namespace Flow
{
	const int maxp=22,maxe=2333;
	int head[maxp],adj[maxe],f[maxe],next[maxe],tot=1;
	int S,T,PS,PT,dn,level[maxp],q[maxp],qh,qt,mf;
	
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
			mf+=aug(S,1<<20);
		return mf;
	}
} 

class CosmicBlocks
{
	public:
	
	int n,level[9],cnt[750],adj[9];
	bool used[9];
	int F[1<<6];
	vector<int> B[9],block;
	int sx[22],tx[22];
	
	bool judge()
	{
		//We can check it with a simple Network Flow with upper and lower bound.
		//For each pair of colors between which there are a pair of adjacent blocks,
		//we can add an edge from the higher color to the other, with lower bound 1 and infinite capacity.
		//Then check if there is a Full-Flow.
		using namespace Flow;
		dn=n+n+5;S=n+n+2;T=S+1;PS=T+1;PT=PS+1;
		memset(head,0,dn+1<<2);tot=1;
		mf=0;
		memset(sx,0,dn+1<<2);
		memset(tx,0,dn+1<<2);
		//Build the network.
		addedge(T,S,1<<20);
		for(int i=0;i<n;i++)
		{
			sx[S]+=block[i];
			tx[i+1]+=block[i];
			addedge(n+i+1,T,block[i]);
			if(adj[i]==0)addedge(i+1,n+n+1,1<<20);
		}
		addedge(n+n+1,T,1<<20);
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(adj[i]>>j&1)
				{
					sx[i+1]++;
					tx[n+j+1]++;
					addedge(i+1,n+j+1,1<<20);
				}
		int ff=0;
		for(int i=1;i<=T;i++)
		{
			if(sx[i]>tx[i])addedge(i,PT,sx[i]-tx[i]);
			if(sx[i]<tx[i])addedge(PS,i,tx[i]-sx[i]);
			ff+=max(sx[i]-tx[i],0);
		}
		swap(S,PS);
		swap(T,PT);
		int tmf=dinic();//use dinic to find the maximum flow.
		if(tmf==ff)
			return 1;
		return 0;
	}
	
	int dp(int s)
	{
		int &res=F[s];
		if(res!=-1)
			return res;
		if(s+1==1<<n)
			return res=1;
		res=0;
		for(int i=0;i<n;i++)//pick the next color of blocks to remove.
			if((s>>i&1)==0&&(s&adj[i])==adj[i])
					res+=dp(s|1<<i);
		return res;
	}
	
	int calc()
	{
		memset(F,-1,sizeof(F));
		//We use a simple state compression DP to solve it.
		return dp(0);
	}
	
	void dfs(int h,int k,int pre)
	{
		//We simply pick the height for each color.
		//And for each colors pair with adjacent height, we determine if there are adjacent blocks between them.
		if(h>0&&B[h-1].empty())return;
		if(k==n)
		{
			if(!B[h].empty()&&judge())
				cnt[calc()]++;
			return;
		}
		for(int i=pre+1;i<n;i++)
			if(!used[i])
			{
				B[h].push_back(i);
				used[i]=1;
				if(h>0)
				{
					int c=B[h-1].size();
					for(int s=1;s<1<<c;s++)//pick all possible relationships.
					{
						for(int j=0;j<c;j++)
							if(s>>j&1)adj[i]^=1<<B[h-1][j];
						dfs(h,k+1,i);
						dfs(h+1,k+1,-1);
						for(int j=0;j<c;j++)
							if(s>>j&1)adj[i]^=1<<B[h-1][j];
					}
				}
				else
				{
					dfs(h,k+1,i);
					dfs(h+1,k+1,-1);
				}
				used[i]=0;
				B[h].pop_back();
			}
	} 
	
	int getNumOrders(vector<int> blockTypes,int minWays,int maxWays)
	{
		n=blockTypes.size();
		block=blockTypes;
		dfs(0,0,-1);
		int res=0;
		for(int i=minWays;i<=maxWays;i++)
			res+=cnt[i];
		return res;
	}
	
};

