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

//dinic

struct edge
{
	int cap,flow,to,next;
}e[40010];

int head[2510],d[2510],q[2510],cur[2510],f[55][55];
int n,N,S,T,ecnt;
char a[55][55];

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

void init()
{
	for (int i=1;i<=N;i++) head[i]=-1;
	ecnt=0;
	for (int i=0;i<N;i++)
		for (int j=i+1;j<N;j++)
			if (a[i][j]=='N')
			{
				addedge(i+1,j+1,inf);
				addedge(j+1,i+1,inf);
			}
			else
				if (a[i][j]=='O')
				{
					addedge(i+1,j+1,2);
					addedge(j+1,i+1,2);
				}
}

struct OldBridges 
{
    string isPossible(vector <string> bridges, int a1, int a2, int an, int b1, int b2, int bn)
    {
    	n=bridges.size();
    	for (int i=0;i<n;i++)
    		for (int j=0;j<n;j++)
    			a[i][j]=bridges[i][j];
    	N=T=n+2;S=N-1;
   		init();
   		addedge(S,a1+1,2*an);addedge(a2+1,T,2*an);
   		addedge(S,b1+1,2*bn);addedge(b2+1,T,2*bn);
   		int ans=0;
   		while (bfs()) ans+=dfs(S,inf);
   		if (ans<2*(an+bn)) return "No";
   		init();
   		addedge(S,a1+1,2*an);addedge(a2+1,T,2*an);
   		addedge(S,b2+1,2*bn);addedge(b1+1,T,2*bn);
   		ans=0;
   		while (bfs()) ans+=dfs(S,inf);
   		if (ans<2*(an+bn)) return "No"; else return "Yes";
    }
};
