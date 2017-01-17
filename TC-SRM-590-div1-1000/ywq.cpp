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
	int to,next,cap,flow;
}e[300000];

int head[1610],d[1610],q[1610],cur[1610];
int S,N,T,ecnt;

void push(int k,int x,int y,int c)
{
	e[k].to=y;e[k].cap=c;e[k].flow=0;e[k].next=head[x];head[x]=k;
}

void addedge(int x,int y,int c)
{
	push(ecnt++,x,y,c);
	push(ecnt++,y,x,0);
}

bool bfs()
{
	for (int i=0;i<N;i++) d[i]=N;d[S]=0;
	int f=1,r=1;q[1]=S;
	for (int i=0;i<N;i++) cur[i]=head[i];
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
			int tmp=dfs(e[p].to,min(res,e[p].cap-e[p].flow));
			e[p].flow+=tmp;e[p^1].flow-=tmp;
			s+=tmp;res-=tmp;
			if (!res) return s;
		}
		cur[k]=e[p].next;
	}
	return s;
}

struct FoxAndCity 
{
    int minimalCost(vector <string> linked, vector <int> want)
    {
    	int n=linked.size();
    	S=n*n;T=S+1;N=S+2;
    	for (int i=0;i<N;i++) head[i]=-1;
    	ecnt=0;
    	addedge(S,0,want[0]*want[0]);
    	for (int i=1;i<n;i++) addedge(i-1,i,inf);
    	addedge(n-1,T,inf);
    	for (int i=1;i<n;i++)
    	{
    		addedge(S,i*n,inf);
    		for (int j=1;j<n;j++) addedge(i*n+j-1,i*n+j,(want[i]-j)*(want[i]-j));
    		addedge((i+1)*n-1,T,inf);
    	}
    	for (int i=0;i<n;i++)
    		for (int j=0;j<n;j++)
    			if (linked[i][j]=='Y')
    				for (int k=1;k<n;k++) addedge(i*n+k,j*n+k-1,inf);
    	int ans=0;
    	while (bfs()) ans+=dfs(S,inf);
    	return ans;
    }
};
