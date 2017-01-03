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

const int inf=1000000000;

int n,m,N,S,T;
int head[810],cur[810],q[810],d[810],ecnt,w[128];

const int di[4][2]={{1,0},{0,1},{-1,0},{0,-1}};

int id(int x,int y)
{
	return x*m+y;
}

//dinic

struct edge
{
	int cap,flow,to,next;
}e[10010];

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
			int t=dfs(e[p].to,min(res,e[p].cap-e[p].flow));
			e[p].flow+=t;e[p^1].flow-=t;
			s+=t;res-=t;
			if (!res) return s;
		}
		cur[k]=e[p].next;
	}
	return s;
}

struct SurroundingGame 
{
    int maxScore(vector <string> cost, vector <string> benefit)
    {
    	n=cost.size();m=cost[0].size();
    	N=T=2*n*m+2;S=N-1;int val=0;
    	for (char c='0';c<='9';c++) w[c]=val++;
    	for (char c='a';c<='z';c++) w[c]=val++;
    	for (char c='A';c<='Z';c++) w[c]=val++;
    	for (int i=1;i<=N;i++) head[i]=-1;
    	ecnt=0;
    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    		{
    			int x=id(i,j);
    			if ((i+j)&1) //right
    			{
    				addedge(2*x+1,2*x+2,w[benefit[i][j]]);
    				addedge(2*x+2,T,w[cost[i][j]]);
    			}
    			else //left
    			{
    				addedge(S,2*x+1,w[cost[i][j]]);
    				addedge(2*x+1,2*x+2,w[benefit[i][j]]);
    				for (int k=0;k<4;k++)
    				{
    					int ti=i+di[k][0],tj=j+di[k][1];
    					if (ti>=0&&ti<n&&tj>=0&&tj<m)
    					{
    						int tx=id(ti,tj);
    						addedge(2*x+1,2*tx+1,inf);
    						addedge(2*x+2,2*tx+2,inf);
    					}
    				}
    			}
    		}
    	int ans=0;
    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    			ans+=w[benefit[i][j]];
    	while (bfs()) ans-=dfs(S,inf);
    	return ans;
    }
};
