#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class DisjointSemicircles
{
	public:
	int N;
  int a[105],cnt[105];
  int l[105],r[105],col[105];
  bool g[105][105],down[105];
  
  //Case 1 pick all different ways to fill out the empty cells.
  
  bool ff(int x,int c)//Check if it is a bipartite graph.
  {
  	if(col[x])return col[x]==c;
  	col[x]=c;
  	for(int i=0;i<N;i++)
  		if(g[x][i])
  			if(!ff(i,c^2))return 0;
  	return 1;
	}
  
  bool check1()
  {
  	//build the graph.
  	memset(l,-1,N<<2),memset(r,-1,N<<2);
  	for(int i=0;i<N+N;i++)
  		if(~l[a[i]])r[a[i]]=i;
  		else l[a[i]]=i;
  	for(int i=0;i<N;i++)
  		for(int j=0;j<N;j++)
				g[i][j]=(l[i]<l[j]&&l[j]<r[i]&&r[i]<r[j]||l[j]<l[i]&&l[i]<r[j]&&r[j]<r[i]);
		//Check if it is possible.
		memset(col,0,N<<2);
		for(int i=0;i<N;i++)
			if(!col[i])
				if(!ff(i,1))return 0;
		return 1;
	}
  
  bool dfs1(int p)//Depth First Search for all available ways to fill out them.
  {
  	if(p==N+N)return check1();
  	if(a[p]!=-1)return dfs1(p+1);
  	for(int i=0;i<N;i++)
  		if(cnt[i]==2)
  		{
  			a[p]=i;cnt[i]--;
  			if(dfs1(p+1))return 1;
  			a[p]=-1,cnt[i]++;
  			//It is equivalent if we swap the index,
  			//so it is enough to fill the least index in.
  			break;
			}
		for(int i=0;i<N;i++)
			if(cnt[i]==1)
			{
				a[p]=i;cnt[i]--;
				if(dfs1(p+1))return 1;
				a[p]=-1;cnt[i]++;
			}
		return 0;
	}
  
	bool work1(int N,vector<int> x)
	{
		for(int i=0;i<N;i++)cnt[i]=2;
		for(int i=0;i<N+N;i++)
			if(~(a[i]=x[i]))cnt[x[i]]--;
		return dfs1(0);
	}
	
	//Case 2 pick all different directions assemblies of known indices pairs.
	int sum[105],opp[105];
  int head[105],adj[105*105],d[105*105],next[105*105],tot;
  
	void addedge(int u,int v,int w)
  {tot++;adj[tot]=v;d[tot]=w;next[tot]=head[u];head[u]=tot;
	tot++;adj[tot]=u;d[tot]=w;next[tot]=head[v];head[v]=tot;}
	
  bool ff2(int x,int c)//Check if it is a bipartite graph.
  {
  	if(col[x])return col[x]==c;
  	col[x]=c;
  	for(int i=head[x];i;i=next[i])
  		if(!ff2(adj[i],c^d[i]))return 0;
  	return 1;
	}
	
	bool check2()
	{
		memset(head,0,N+1<<2);tot=1;
		//build the graph on the vertices representing prefix sums.
		for(int i=0;i<N;i++)
			if(a[i]!=-1)addedge(i,i+1,0);
		addedge(0,N,0);
		for(int i=0;i<N;i++)
			if(a[i]!=-1&&opp[i]>i)
			{
				int j=opp[i];
				if(!down[i])
					addedge(i,j,0);
				else
					addedge(i,j,sum[j]-sum[i]&1);
			}
		//the prefix sums' parities must be available.
		memset(col,0,N+1<<2);
			for(int i=0;i<=N;i++)
				if(!col[i])
					if(!ff2(i,2))return 0;
		return 1;
	}
  
	bool dfs2(int p)//Pick all available ways of directions assemblies.
	{
		if(p==N)return check2();
		if(a[p]==-1)return dfs2(p+1);
		int op=opp[p];
		if(op<p)return dfs2(p+1);
		bool flag;
		down[p]=down[op]=0;flag=1;//this pair goes above
		for(int i=0;i<p&&flag;i++)
			if(g[p][i]&&down[p]==down[i])flag=0;//There is an intersection
		if(flag&&dfs2(p+1))return 1;
		down[p]=down[op]=1;flag=1;//this pair goes under
		for(int i=0;i<p&&flag;i++)
			if(g[p][i]&&down[p]==down[i])flag=0;//There is an intersection
		if(flag&&dfs2(p+1))return 1;
		return 0;
	}
	
	bool work2(int n,vector<int> x)
	{
		N=n;
		for(int i=0;i<N;i++)
		{
			a[i]=x[i];
			sum[i+1]=sum[i]+(x[i]==-1);
			if(x[i]!=-1)
				for(int j=0;j<N;j++)
					if(i!=j&&x[i]==x[j])opp[i]=j;
		}
		for(int i=0;i<N;i++)
			for(int j=0;j<i;j++)
				g[i][j]=(i<opp[j]&&opp[j]<opp[i]);
		return dfs2(0);
	}
	
	string getPossibility(vector<int> labels)
	{
		N=labels.size()/2;//N<=25
		int ans,cnt=0;
		for(int i=0;i<N+N;i++)
			cnt+=(labels[i]==-1);
		if(cnt<=12)ans=work1(N,labels);//O((2*x)!/(2^x*x!)) ways.
		else ans=work2(N+N,labels);//O(2^(N-x)) ways.
		return ans?"POSSIBLE":"IMPOSSIBLE";
	}
};

