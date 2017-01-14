#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;
class SkiResorts
{
	public:
	
	vector<int> H;
	int I[55][55];
	int dn;
	int head[3333],adj[4000005],c[4000005],next[4000005],tot;
	LL d[3333];
	int vis[3333];
	
	void addedge(int u,int v,int w)
	{tot++;adj[tot]=v;c[tot]=w;next[tot]=head[u];head[u]=tot;}
	
	int ABS(int xx){return xx<0?-xx:xx;}
	
	LL minCost(vector<string> road, vector<int> altitude)
	{
		//We can prove that all places' final altitude must be given at first.
		int n=road.size();
		H=altitude;
		sort(H.begin(),H.end());
		H.erase(unique(H.begin(),H.end()),H.end());
		for(int i=0;i<n;i++)
			for(int j=0;j<H.size();j++)
				I[i][j]=++dn;
		//I[i][j] : The minimum cost to change i-th place's altitude into H[j] and reach it.
		//The transform is like the shortest path.
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(road[i][j]=='Y')
				{
					for(int x=0;x<H.size();x++)
						for(int y=0;y<=x;y++)
							addedge(I[i][x],I[j][y],ABS(H[y]-altitude[j]));
				}
		//Use dijkstra algorithm to solve SSSP
		memset(d,31,sizeof(d));
		for(int i=0;i<H.size();i++)
			d[I[0][i]]=ABS(H[i]-altitude[0]);
		for(int k=0;k<dn;k++)
		{
			int x,y,i;
			x=-1;
			for(i=1;i<=dn;i++)
				if(!vis[i]&&(x==-1||d[i]<d[x]))
					x=i;
			vis[x]=1;
			for(i=head[x];i;i=next[i])
				if(d[y=adj[i]]>d[x]+c[i])
					d[y]=d[x]+c[i];
		}
		LL ans=1LL<<60;
		for(int i=0;i<H.size();i++)
			ans=min(ans,d[I[n-1][i]]);
		return ans<1LL<<55?ans:-1;
	}
};

