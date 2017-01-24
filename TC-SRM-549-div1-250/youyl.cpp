#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
struct node
{
	int to,next,opt,fl;
}g[12000];
int S,T,ed,st[1200];
inline void add(int x,int y,int z)
{
	ed++;
	g[ed].to=y;
	g[ed].next=st[x];
	g[ed].fl=z;
	g[ed].opt=ed+1;
	st[x]=ed;
	ed++;
	g[ed].to=x;
	g[ed].next=st[y];
	g[ed].fl=0;
	g[ed].opt=ed-1;
	st[y]=ed;
}
int lev[12000],fr[12000];
int maxflow,x1,x2,x3,sta[12000],stp;
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
			if(g[i].fl!=0&&lev[g[i].to]==-1)
			{
				q.push(g[i].to);
				lev[g[i].to]=lev[x1]+1;
				if(g[i].to==T)return true;
			}
		}
	}
	return false;
}
int stae[12000];
inline void extend()
{
	for (int i=S;i<=T;i++)
	{
		fr[i]=st[i];
	}
	stp=1;
	sta[stp]=S;
	while (stp!=0)
	{
		x1=sta[stp];
		if(x1==T)
		{
			maxflow++;
			for (int i=stp;i>=2;i--)
			{
				g[stae[i]].fl--;
				g[g[stae[i]].opt].fl++;
			}
			stp=1;
		}
		else
		{
			for (;fr[x1]!=0;fr[x1]=g[fr[x1]].next)
			{
				if(g[fr[x1]].fl!=0&&lev[g[fr[x1]].to]==lev[x1]+1)
				{
					break;
				}
			}
			if(fr[x1]==0)
			{
				lev[x1]=-1;
				stp--;
			}
			else
			{
				stp++;
				sta[stp]=g[fr[x1]].to;
				stae[stp]=fr[x1];
			}
		}
	}
}
inline int dinic()// network flow
{
	maxflow=0;
	while (makelev())
	{
		extend();
	}
	return maxflow;
}
const double eps=1e-9;
inline bool check(int th,int tr,int bh,int br)// if it is possible to make a hat
{
	if(br<=tr)return false;
	double newbh=(bh*tr*1.0)/br;
	if(eps+newbh>th)return false;
	return true;
}
struct PointyWizardHats
{
	inline int getNumHats(vector<int>th,vector<int>tr,vector<int>bh,vector<int>br)
	{
		int n=th.size();
		int m=bh.size();
		S=0;
		ed=0;
		T=n+m+1;
		for (int i=S;i<=T;i++)
		{
			st[i]=0;
		}
		for (int i=1;i<=n;i++)
		{
			add(S,i,1);
		}
		for (int i=1;i<=m;i++)
		{
			add(i+n,T,1);
		}
		for (int i=1;i<=n;i++)// build the graph
		{
			for (int j=1;j<=m;j++)
			{
				if(check(th[i-1],tr[i-1],bh[j-1],br[j-1]))
				{
					add(i,j+n,1);
				}
			}
		}
		return dinic();
	}
};