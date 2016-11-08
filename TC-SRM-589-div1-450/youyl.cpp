#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
struct node
{
	int to,next,opt,fl;
};
const int Des=1000000001;
const int Sta=-1;
struct dinic// network-flow using Dinic
{
	node g[20000];
	int ed,st[1200],fr[1200];
	int S,T,nx;
	int lev[1200];
	int sta[1200],stp;
	int stae[1200],maxflow,x1,x2,x3;
	inline void addedge(int x,int y,int z)
	{
		if(x<0)x=S;
		if(y<0)y=S;
		if(x>1000000000)x=T;
		if(y>1000000000)y=T;
		ed++;
		g[ed].to=y;
		g[ed].next=st[x];
		g[ed].opt=ed+1;
		g[ed].fl=z;
		st[x]=ed;
		ed++;
		g[ed].to=x;
		g[ed].next=st[y];
		g[ed].opt=ed-1;
		g[ed].fl=0;
		st[y]=ed;
	}
	inline void init(int n,int SS,int TT)
	{
		ed=0;
		maxflow=0;
		nx=n;
		for (int i=0;i<=n;i++)
		{
			st[i]=0;
		}
		S=SS;
		T=TT;
	}
	inline bool makelev()
	{
		memset(lev,-1,sizeof(lev));
		queue<int>q;
		q.push(S);
		lev[S]=1;
		while (!q.empty())
		{
			x1=q.front();
			q.pop();
			for (int i=st[x1];i!=0;i=g[i].next)
			{
				if(lev[g[i].to]==-1&&g[i].fl!=0)
				{
					q.push(g[i].to);
					lev[g[i].to]=lev[x1]+1;
					if(g[i].to==T)return true;
				}
			}
		}
		return false;
	}
	inline void extend()
	{
		stp=1;
		sta[stp]=S;
		for (int i=0;i<=nx;i++)
		{
			fr[i]=st[i];
		}
		while (stp!=0)
		{
			x1=sta[stp];
			if(x1!=T)
			{
				for (;fr[x1]!=0;fr[x1]=g[fr[x1]].next)
				{
					if(g[fr[x1]].fl!=0&&lev[g[fr[x1]].to]==lev[x1]+1)break;
				}
				if(fr[x1]==0)
				{
					stp--;
					lev[x1]=-1;
				}
				else
				{
					stp++;
					sta[stp]=g[fr[x1]].to;
					stae[stp]=fr[x1];
				}
			}
			else
			{
				int del=1000000000;
				for (int i=stp;i>=2;i--)
				{
					del=min(del,g[stae[i]].fl);
				}
				maxflow+=del;
				for (int i=stp;i>=2;i--)
				{
					g[stae[i]].fl-=del;
					g[g[stae[i]].opt].fl+=del;
					if(g[stae[i]].fl==0)stp=i-1;
				}
			}
		}
	}
	inline int solve()
	{
		while (makelev())
		{
			extend();
		}
		return maxflow;
	}
}mxf;
inline int get(char C)
{
	if(C=='R')return 1;
	if(C=='G')return 2;
	return 3;
}
struct GearsDiv1
{
	int n,ans;
	inline int getmin(string color,vector<string>graph)
	{
		n=color.length(); 
		ans=n+1;
		for (int ip=1;ip<=3;ip++)// pick the color(ip-1) as the useless color
		{
			mxf.init(n+1,0,n+1);
			for (int i=1;i<=n;i++)
			{
				for (int j=1;j<=n;j++)
				{
					if(graph[i-1][j-1]=='Y'&&(get(color[i-1])==ip&&get(color[j-1])==ip%3+1))
					{
						mxf.addedge(i,j,1);// build the graph
					}
				}
			}
			for (int i=1;i<=n;i++)
			{
				if(get(color[i-1])==ip)
				{
					mxf.addedge(Sta,i,1);
				}
				else if(get(color[i-1])==ip%3+1)
				{
					mxf.addedge(i,Des,1);
				}
			}
			ans=min(ans,mxf.solve());// it is actually ans=min(ans,n-(n-mxf.solve()))
		}
		return ans;
	}
};