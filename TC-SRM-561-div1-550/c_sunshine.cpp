#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<cmath>
#include<set>
using namespace std;

class CirclesGame
{
	public:
	
	int n;
	int fa[55],nr[55];
	int head[55],adj[55],next[55],tot;
	int f[55];
	
	vector<int> sub[55];
	set<int> can;
	
	void addedge(int u,int v)
	{tot++;adj[tot]=v;next[tot]=head[u];head[u]=tot;}
	
	inline int sqr(const int &xx){return xx*xx;}
	
	bool inside(int x,int y,int r,int X,int Y,int R)
	{
		return sqrt(sqr(x-X)+sqr(y-Y))+r<R;
	}
	
	int go(int x,int y)
	{
		//The xor sum of all nodes in x's subtree and connected to chain x-y.
		int p=0,res=0;
		for(;x!=fa[y];p=x,x=fa[x])
			for(int i=head[x];i;i=next[i])
				if(adj[i]!=p)
					res^=f[adj[i]];
		return res;
	}
	
	int dp(int x)
	{
		sub[x].push_back(x);
		//Find all nodes in x's subtree.
		for(int i=head[x];i;i=next[i])
		{
			dp(adj[i]);
			sub[x].insert(sub[x].end(),sub[adj[i]].begin(),sub[adj[i]].end());
		}
		//Pick next step, and calculate the SG function for all accessible status.
		can.clear();
		for(int i=0;i<sub[x].size();i++)
			can.insert(go(sub[x][i],x));
		//sg(x)=mex{sg(y)| x can reach y by one step}, while mex is the minimum natural number missing in the set.
		for(int i=0;;i++)
			if(!can.count(i))
				return f[x]=i;
	}
	
	string whoCanWin(vector<int> x,vector<int> y,vector<int> r)
	{
		n=x.size();
		//Build the tree.
		for(int i=0;i<n;i++)
		{
			int fi=-1;
			for(int j=0;j<n;j++)
				if(inside(x[i],y[i],r[i],x[j],y[j],r[j])&&(fi==-1||r[j]<r[fi]))
					fi=j;
			if(fi!=-1)
			{
				fa[i+1]=fi+1;
				nr[i+1]=1;
				addedge(fi+1,i+1);
			}
		}
		//The SG function of the game is the xor-sum of all subgames' SG function.
		//sg=sg_1 xor sg_2 xor ... xor sg_m
		int sg=0;
		for(int i=1;i<=n;i++)
			if(!nr[i])
				sg^=dp(i);
		return sg?"Alice":"Bob";
	}
	
};

