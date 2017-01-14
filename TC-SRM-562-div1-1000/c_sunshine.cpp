#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;
const int N=55,M=1000000009,inf=(1<<28)-1;
typedef int list[N][N];

inline bool ten(int &x,const int &y){return y<x?(x=y,1):0;}
inline bool rel(int &x,const int &y){return x<y?(x=y,1):0;}
inline void up(int &x,const int &y){x+=y;if(x>=M)x-=M;}

class InducedSubgraphs
{
	public:
	int n,K;
	vector<int> adj[N];
	int g[N][N],dis[N][N];
	int siz[N][N],cnt[N][N];
	list f[N][N],tmp;
	bool vis[N][N];
	
	int co[N][N],fact[N];
	
	void dfs(int fa,int x)
	{
		if(siz[fa][x])return;
		int &s=siz[fa][x],&c=cnt[fa][x];
		s=0;c=1;
		for(int i=0,y;i<adj[x].size();i++)
			if((y=adj[x][i])!=fa)
			{
				dfs(x,y);
				c=(LL)c*cnt[x][y]%M*co[s+siz[x][y]][s]%M;
				s+=siz[x][y];
			}
		s++;
	}
	
	int solve1()
	{
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(i!=j)dis[i][j]=g[i][j]?1:inf;
		//Use Floyd to determine the shortest distances between pairs.
		for(int k=0;k<n;k++)
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
						ten(dis[i][j],dis[i][k]+dis[k][j]);
		int u,v,fu,fv,d=n-K-K+1,ans=0;
		//Pick all possible chains for interval [k,n-k+1].
		for(u=0;u<n;u++)
			for(v=0;v<n;v++)
				if(dis[u][v]==d)
				{
					for(int i=0;i<adj[u].size();i++)
						if(dis[adj[u][i]][v]<d){fu=adj[u][i];break;}
					for(int i=0;i<adj[v].size();i++)
						if(dis[adj[v][i]][u]<d){fv=adj[v][i];break;}
					//Count the ways with cnt[fx][x].
					if(siz[fu][u]==K&&siz[fv][v]==K)
						up(ans,(LL)cnt[fu][u]*cnt[fv][v]%M);
				}
		return ans;
	}
	
	int merge(list &a,int A,list &b,int B,list &c)
	{
		//It is like to merge two 2-dimensional knapsacks.
		int C=A+B;
		for(int i=0;i<=C;i++)
			for(int j=0;j<=C;j++)
				tmp[i][j]=0;
		for(int i=0;i<=A;i++)
			for(int j=0;j<=A;j++)
				for(int k=0;k<=B;k++)
					for(int l=0;l<=B;l++)
						up(tmp[i+k][j+l],(LL)a[i][j]*b[k][l]%M*co[i+k][i]%M*co[j+l][j]%M);
		for(int i=0;i<=C;i++)
			for(int j=0;j<=C;j++)
				c[i][j]=tmp[i][j];
		return C;
	}
	
	void dp(int fa,int x)
	{
		//f[fx][x][r][b]: the number to color the x's subtree with exactly r red nodes and b blue nodes.
		if(vis[fa][x])return;
		vis[fa][x]=1;
		f[fa][x][0][0]=1;
		int s=0;
		for(int i=0,y;i<adj[x].size();i++)
			if((y=adj[x][i])!=fa)
			{
				dp(x,y);
				//Merge two exponential generating functions.
				s=merge(f[fa][x],s,f[x][y],siz[x][y],f[fa][x]);
			}
		//When we have only one color and the number of this color of nodes is equal to the size of x's subtree,
		//the number of ways to color the subtree is cnt[fx][x].
		f[fa][x][0][siz[fa][x]]=cnt[fa][x];
		f[fa][x][siz[fa][x]][0]=cnt[fa][x];
	}
	
	int solve2()
	{
		for(int i=0;i<n;i++)
			dp(n,i);
		int ans=0,middle=K+K-n;
		for(int i=0;i<n;i++)
			up(ans,f[n][i][n-K][n-K]);
		//Because we haven't considered the white nodes' labels and we count a way of coloring exactly (n-2K) times,
		//we should multiply the answer by (n-2K)!/(n-2K)=(middle-1)!
		ans=(LL)ans*fact[middle-1]%M;
		return ans;
	}
	
	int getCount(vector<int> edge1,vector<int> edge2,int k)
	{
		n=edge1.size()+1;K=k;
		for(int u,v,i=0;i<n-1;i++)
		{
			u=edge1[i],v=edge2[i];
			g[u][v]=g[v][u]=1;
			adj[u].push_back(v);
			adj[v].push_back(u); 
		}
		//get factorials
		fact[0]=1;
		for(int i=1;i<=n;i++)
			fact[i]=(LL)fact[i-1]*i%M;
		if(K==1)return fact[n];
		//calculate conbinational nubers
		for(int i=0,j;i<=n;i++)
			for(co[i][0]=co[i][i]=j=1;j<i;j++)
				co[i][j]=(co[i-1][j-1]+co[i-1][j])%M;
		//Determine cnt[fx][x] which is the number of ways to label the nodes in x's subtree,
		//satisfying that each node's label is less than the nodes in it's subtree. 
		for(int i=0;i<n;i++)
			dfs(n,i);
		if(K*2<=n)return solve1();
		else return solve2();
	}
};

