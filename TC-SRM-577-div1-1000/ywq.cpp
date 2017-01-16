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

struct edge
{
	int cap,flow,to,next;
}e[10010];

int head[2510],d[2510],q[2510],cur[2510];
int n,m,N,S,T,ecnt;

void push(int k,int x,int y,int c)
{
	e[k].to=y;e[k].cap=c;e[k].flow=0;e[k].next=head[x];head[x]=k;
}

void addedge(int x,int y,int c)
{
	push(ecnt++,x,y,c);push(ecnt++,y,x,0);
}

int f(int x,int y) {return x*m+y+1;}

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

struct BoardPainting 
{
    int minimalSteps(vector <string> target)
    {
    	n=target.size();m=target[0].size();
    	S=n*m+1;T=N=S+1;
    	ecnt=0;
    	for (int i=1;i<=N;i++) head[i]=-1;
    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    			if (target[i][j]=='#')
    			{
    				int x=f(i,j);
    				if (i>0&&target[i-1][j]=='#') addedge(x,f(i-1,j),1); else addedge(x,T,1);
    				if (j>0&&target[i][j-1]=='#') addedge(f(i,j-1),x,1); else addedge(S,x,1);
    			}
    	int ans=0;
    	while (bfs()) ans+=dfs(S,inf);
    	return ans;
    }
};
