#include<bits/stdc++.h>
#define inf 0x3fffffff
using namespace std;
const int N=55;
const int M=10010;
struct Edge{int q,w,l;}a[M<<1];
int n,m,p,he[M],ha[M],s[N][N];
int cl,op,t,ans,way[M],dis[M],qe[M];

void build(int x,int y,int z)
{
	a[++p].q=y; a[p].w=z; a[p].l=he[x]; he[x]=p;
}

void addedge(int x,int y)
{
	build(x,y,1);
	build(y,x,0);
} 

int bfs()
{
	memset(dis,0,sizeof(dis));
	dis[0]=1; qe[cl=op=1]=0;
	while (cl<=op)
	{
		int x=qe[cl];
		for (int i=he[x];i;i=a[i].l)
			if (a[i].w&&!dis[a[i].q])
			{
				dis[a[i].q]=dis[x]+1;
				qe[++op]=a[i].q;
			}
		cl++;
	}
	memcpy(ha,he,sizeof(he));
	return dis[m+1];
}

int dinic(int x,int l)
{
	if (x==m+1)
	{
		int mn=inf;
		for (int i=1;i<l;i++)
			if (a[way[i]].w<mn)
			{
				mn=a[way[i]].w;
				t=i;
			}
		ans+=mn;
		for (int i=1;i<l;i++)
		{
			a[way[i]].w-=mn;
			a[way[i]^1].w+=mn;
		}
		return 1;
	}
	for (int&i=ha[x];i;i=a[i].l)
		if (a[i].w&&dis[a[i].q]==dis[x]+1)
		{
			way[l]=i;
			if (dinic(a[i].q,l+1)&&t!=l) return 1;
		}
	return 0;
}

int maxflow()
{
	while (bfs()) dinic(0,1);
	return ans;
}

class FoxAndGo3
{
	public:
	
	int maxEmptyCells(vector<string> board)
	{
		n=board.size(); p=1;
		for (int i=0;i<n;i++)
			for (int j=0;j<n;j++)	
				if (board[i][j]=='.'||board[i][j]=='o') s[i][j]=++m;
		for (int i=0;i<n;i++)
			for (int j=0;j<n;j++)
				if (board[i][j]=='.')
				{
					addedge(0,s[i][j]);
					if (i-1>=0&&board[i-1][j]=='o') addedge(s[i][j],s[i-1][j]);
					if (i+1<n&&board[i+1][j]=='o') addedge(s[i][j],s[i+1][j]);
					if (j-1>=0&&board[i][j-1]=='o') addedge(s[i][j],s[i][j-1]);
					if (j+1<n&&board[i][j+1]=='o') addedge(s[i][j],s[i][j+1]);
				}
				else if (board[i][j]=='o') addedge(s[i][j],m+1);
		return 	m-maxflow();
	}	
};