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

int head[20],q[20],cur[20],d[20];
int ecnt,S,T,N,n;
pii b[20];
int a[20],deg[20],dp[70],c[20];
bool ok[20];

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



struct CosmicBlocks 
{
    int getNumOrders(vector <int> blockTypes, int minWays, int maxWays)
    {
    	n=blockTypes.size();
    	int t=1;for (int i=0;i<n;i++) t*=n;
    	int ans=0;
    	for (int i=0;i<t;i++)
    	{
    		int x=i;
    		for (int j=0;j<n;j++)
    		{
    			a[j]=x%n;x/=n;
    		}
    		memset(ok,0,sizeof(ok));
    		for (int j=0;j<n;j++) ok[a[j]]=1;
    		int up=0;
    		for (int j=0;j<n;j++) if (ok[j]) up=j;
    		bool w=1;
    		for (int j=0;j<n;j++) if (j<up&&!ok[j]) w=0;//the heights are not consecutive
    		if (!w) continue;
    		int m=0;
    		for (int j=0;j<n;j++)
    			for (int k=0;k<n;k++)
    				if (a[j]+1==a[k]) b[m++]=mp(j,k);//block k can be put on block j
    		for (int j=0;j<(1<<m);j++)
    		{
    			//build graph
    			S=2*n+3;N=T=S+1;
    			for (int k=1;k<=N;k++) head[k]=-1;
    			ecnt=0;
    			memset(deg,0,sizeof(deg));
    			for (int k=0;k<n;k++)
    			{
    				deg[2*k+1]-=blockTypes[k];
    				deg[2*k+2]+=blockTypes[k];
    			}
    			for (int k=0;k<n;k++) if (!a[k]) addedge(S-2,2*k+1,inf);
    			for (int k=0;k<n;k++) addedge(2*k+2,T-2,inf);
    			for (int k=0;k<m;k++)
    				if (j&(1<<k))
    				{
    					deg[2*b[k].x+2]--;
						deg[2*b[k].y+1]++;
						addedge(2*b[k].x+2,2*b[k].y+1,inf);
					}
				addedge(T-2,S-2,inf);
				for (int k=1;k<=2*n;k++)
				{
					if (deg[k]>0) addedge(S,k,deg[k]);
					if (deg[k]<0) addedge(k,T,-deg[k]);
				}
				int s=0;
				while (bfs()) s+=dfs(S,inf);
				bool w=1;
				for (int k=0;k<ecnt;k++) if (e[k^1].to==S&&e[k].cap>e[k].flow) w=0;
				if (!w) continue;
				memset(c,0,sizeof(c));
				for (int p=1;p<n;p++)
					for (int k=0;k<m;k++)
						if (a[b[k].y]==p&&(j&(1<<k))) c[b[k].y]|=(c[b[k].x]|(1<<b[k].x));
				memset(dp,0,sizeof(dp));dp[0]=1;
				for (int k=0;k<(1<<n);k++)
					for (int p=0;p<n;p++)
						if ((!(k&(1<<p)))&&((c[p]&k)==c[p])) dp[k|(1<<p)]+=dp[k];
				if (minWays<=dp[(1<<n)-1]&&dp[(1<<n)-1]<=maxWays) ans++;
			}
		}
		return ans;
    }
};
