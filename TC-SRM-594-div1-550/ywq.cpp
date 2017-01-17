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

int n,N,S,T,ecnt;
int head[2510],cur[2510],d[2510],q[2510];

const int inf=1000000000;
const int di[4][2]={{1,0},{0,1},{-1,0},{0,-1}};

struct edge
{
	int to,cap,flow,next;
}e[100010];

int f(int x,int y)
{
	return x*n+y+1;
}

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
	for (int i=1;i<=N;i++) d[i]=T;d[S]=0;
	for (int i=1;i<=N;i++) cur[i]=head[i];
	int f=1,r=1;q[1]=S;
	while (f<=r)
	{
		int p=head[q[f]];
		while (p!=-1)
		{
			if (e[p].cap>e[p].flow&&d[e[p].to]==T)
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
			int tmp=dfs(e[p].to,min(e[p].cap-e[p].flow,res));
			e[p].flow+=tmp;e[p^1].flow-=tmp;
			s+=tmp;res-=tmp;
			if (!res) return s;
		}
		cur[k]=e[p].next;
	}
	return s;
}

struct FoxAndGo3 
{
    int maxEmptyCells(vector <string> board)
    {
		n=board.size();
    	S=n*n+1;T=N=S+2;
    	for (int i=1;i<=N;i++) head[i]=-1;
    	ecnt=0;int ans=0;
    	for (int i=0;i<n;i++)
    		for (int j=0;j<n;j++)
    		{
    			if (board[i][j]=='o') {ans++;addedge(S,f(i,j),1);}
    			if (board[i][j]=='.') {ans++;addedge(f(i,j),T,1);}
    		}
    	for (int i=0;i<n;i++)
    		for (int j=0;j<n;j++)
    			if (board[i][j]=='o')
    				for (int k=0;k<4;k++)
    				{
    					int x=i+di[k][0],y=j+di[k][1];
    					if (x>=0&&x<n&&y>=0&&y<n&&board[x][y]=='.') addedge(f(i,j),f(x,y),inf);
    				}
    	while (bfs()) ans-=dfs(S,inf);
    	return ans;	
    }
};
