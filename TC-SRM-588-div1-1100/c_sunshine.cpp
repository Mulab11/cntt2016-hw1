#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

class GameInDarknessDiv1
{
	public:
	int n,A,B;
	int I[55][55];
	int head[2505],adj[6666],next[6666],tot;
	int dep[2505],fa[2505],md[2505];
	void addedge(int u,int v)
	{tot++;adj[tot]=v;next[tot]=head[u];head[u]=tot;
	tot++;adj[tot]=u;next[tot]=head[v];head[v]=tot;} 
	
	void dfs(const int &x)
	{
		dep[x]=dep[fa[x]]+1;
		md[x]=dep[x];
		for(int i=head[x];i;i=next[i])
			if(adj[i]!=fa[x])
			{
				fa[adj[i]]=x;
				dfs(adj[i]);
				md[x]=max(md[x],md[adj[i]]);
			}
	}
	
	string check(vector<string> field)
	{
		//It can be proved that Bob will win if and only if there is a node p satisfying:
		//dist(A,p)>=dist(B,p)+2 and if we take p as the root, it has 3 subtrees whose depths are not less than 3
		tot=1;
		int R=field.size(),C=field[0].size();
		//Build the tree
		for(int i=0;i<R;i++)
			for(int j=0;j<C;j++)
				if(field[i][j]!='#')
				{
					I[i][j]=++n;
					if(field[i][j]=='A')A=n;
					if(field[i][j]=='B')B=n;
				}
		for(int i=0;i<R;i++)
			for(int j=0;j<C;j++)
				if(field[i][j]!='#')
				{
					if(i+1<R&&field[i+1][j]!='#')
						addedge(I[i][j],I[i+1][j]);
					if(j+1<C&&field[i][j+1]!='#')
						addedge(I[i][j],I[i][j+1]);
				}
		for(int p=1;p<=n;p++)
		{
			fa[p]=0;dep[0]=-1;
			//Use Depth First Search to determine the distances and maximum depth in subtrees
			dfs(p);
			int cnt=0;
			for(int i=head[p];i;i=next[i])
				cnt+=(md[adj[i]]>=3); 
			if(dep[A]>=dep[B]+2&&cnt>=3)
				return "Bob wins";
		}
		return "Alice wins";
	}
};

