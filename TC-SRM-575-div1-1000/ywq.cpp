#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair
#define x first
#define y second

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

const int di[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
const int inf=1000000000;

struct edge
{
	int to,cap,flow,next;
}e[50010];

int N,S,T,ecnt;
int head[5010],cur[5010],d[5010],q[5010];
int id[50][50],type[50][50];

void push(int k,int x,int y,int c)
{
	e[k].to=y;e[k].cap=c;e[k].flow=0;e[k].next=head[x];head[x]=k;
}

void addedge(int x,int y,int c)
{
	push(ecnt++,x,y,c);push(ecnt++,y,x,0);
}

bool bfs()
{
	for (int i=1;i<=N;i++) d[i]=N;d[S]=0;
	for (int i=1;i<=N;i++) cur[i]=head[i];
	int f=1,r=1;q[1]=S;
	while (f<=r)
	{
		int p=head[q[f]];
		while (p!=-1)
		{
			if (e[p].cap>e[p].flow&&d[e[p].to]==N)
			{
				q[++r]=e[p].to;d[q[r]]=d[q[f]]+1;
			}
			p=e[p].next;
		}
		f++;
	}
	return d[T]<N;
}

int dfs(int k,int res)
{
	if (k==T) return res;
	int s=0;
	while (cur[k]!=-1)
	{
		int p=cur[k];
		if (e[p].cap>e[p].flow&&d[k]+1==d[e[p].to])
		{
			int t=dfs(e[p].to,min(e[p].cap-e[p].flow,res));
			e[p].flow+=t;e[p^1].flow-=t;
			s+=t;res-=t;
			if (!res) return s;
		}
		cur[k]=e[p].next;
	}
	return s;
}

struct TheTilesDivOne 
{
    int find(vector <string> board)
    {
    	int n=board.size(),m=board[0].size();
    	S=2*n*m+1;T=N=S+1;ecnt=0;
    	for (int i=1;i<=N;i++) head[i]=-1;
    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    			if (board[i][j]=='.')
    			{
    				id[i][j]=i*m+j;
    				if ((i+j)&1)
    				{
    					if (i&1) type[i][j]=3; else type[i][j]=1;
    				}
    				else
    					type[i][j]=2;
    			}
    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    			if (board[i][j]=='.')
    			{
    				if (type[i][j]==1) addedge(S,2*id[i][j]+1,1);
    				if (type[i][j]==3) addedge(2*id[i][j]+2,T,1);
    				addedge(2*id[i][j]+1,2*id[i][j]+2,1);
    				for (int k=0;k<4;k++)
    				{
    					int x=i+di[k][0],y=j+di[k][1];
    					if (x>=0&&x<n&&y>=0&&y<m&&board[x][y]=='.'&&type[x][y]==type[i][j]+1) addedge(2*id[i][j]+2,2*id[x][y]+1,1);
    				}
    			}
    	int ans=0;
    	while (bfs()) ans+=dfs(S,inf);
    	return ans;
    }
};
