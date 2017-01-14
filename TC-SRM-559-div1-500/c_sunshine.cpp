#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;

class HatRack
{
	public:
	
	int n,free;
	int head[55],adj[105],next[105],tot;
	int fa[55],siz[55],per[55],ful[55];
	
	void addedge(int u,int v)
	{tot++;adj[tot]=v;next[tot]=head[u];head[u]=tot;
	tot++;adj[tot]=u;next[tot]=head[v];head[v]=tot;}
	
	void dp(int x)
	{
		int lc=0,rc=0;
		per[x]=1;
		for(int i=head[x];i;i=next[i])
			if(adj[i]!=fa[x])
			{
				fa[adj[i]]=x;
				dp(adj[i]);
				per[x]&=per[adj[i]];//subtree must be valid.
				//Find left and right children.
				if(!lc)lc=adj[i];
				else if(!rc)rc=adj[i];
				else {per[x]=ful[x]=0;return;}//more than two children.
			}
		if(!per[x]){per[x]=ful[x]=0;return;}//invalid
		siz[x]=1;
		if(lc+rc==0){per[x]=ful[x]=1;return;}//leaf
		siz[x]+=siz[lc]+siz[rc];
		if(siz[lc]<siz[rc])swap(lc,rc);
		if(siz[lc]==siz[rc])free++;//We can swap x's two children.
		if(ful[lc]&&ful[rc]&&ful[lc]==ful[rc])//Two children are both full and of the same size.
		{
			ful[x]=ful[lc]+1;
			per[x]=1;
			return;
		}
		if(!ful[lc]&&!ful[rc]){ful[x]=per[x]=0;return;}//One of two children must be full.
		ful[x]=0;
		if(ful[lc])//left child is full
		{
			if(per[rc]&&siz[rc]>=siz[lc]/2&&siz[rc]<=siz[lc])per[x]=1;
			else per[x]=0;
		}
		else//right child is full
		{
			if(per[lc]&&siz[lc]>=siz[rc]&&siz[lc]<=siz[rc]*2+1)per[x]=1;
			else per[x]=0;
		}
	}
	
	LL countWays(vector<int> knob1,vector<int> knob2)
	{
		tot=1;n=knob1.size()+1;
		for(int i=0;i<n-1;i++)
			addedge(knob1[i],knob2[i]);
		LL ans=0;
		per[0]=1;
		//Pick the root.
		for(int i=1;i<=n;i++)
		{
			fa[i]=0;free=0;
			dp(i);
			if(per[i])//It is valid to use i as the root.
				ans+=1LL<<free;//"free" is the number of nodes who can swap its left and right children.
		}
		return ans;
	}
};

