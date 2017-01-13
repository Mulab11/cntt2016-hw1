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

int N,S,T,n,m,ecnt;
int head[1260],q[1260],pre[1260],d[1260];
bool inq[1260];

struct edge
{
	int to,cap,flow,weight,next;
}e[10000];

int id(int x,int y) {return x*m+y;}

void push(int k,int x,int y,int c,int w)
{
	e[k].to=y;e[k].cap=c;e[k].flow=0;e[k].weight=w;e[k].next=head[x];head[x]=k;
}

void addedge(int x,int y,int c,int w)
{
	push(ecnt++,x,y,c,w);push(ecnt++,y,x,0,-w);
}

bool spfa()
{
	for (int i=1;i<=N;i++) d[i]=N+1;d[S]=0;
	int f=1,r=1;q[1]=S;
	memset(inq,0,sizeof(inq));inq[S]=1;
	while (f<=r)
	{
		int x=q[f%N];int p=head[x];
		while (p!=-1)
		{
			if (e[p].cap>e[p].flow&&d[e[p].to]>d[x]+e[p].weight)
			{
				d[e[p].to]=d[x]+e[p].weight;pre[e[p].to]=p;
				if (!inq[e[p].to])
				{
					r++;q[r%N]=e[p].to;inq[e[p].to]=1;
				}
			}
			p=e[p].next;
		}
		inq[x]=0;f++;
	}
	return d[T]<=N;
}

void augment()
{
	int x=T;
	while (x!=S)
	{
		int y=pre[x];
		e[y].flow++;e[y^1].flow--;
		x=e[y^1].to;
	}
}

struct CurvyonRails 
{
    int getmin(vector <string> field)
    {
    	n=field.size();m=field[0].size();
    	S=2*n*m+1;T=N=S+1;ecnt=0;
    	for (int i=1;i<=N;i++) head[i]=-1;
    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    			if (field[i][j]!='w')
    			{
    				int x=id(i,j);
    				if (field[i][j]=='C')
    				{
    					addedge(2*x+1,2*x+2,1,1);
    					addedge(2*x+2,2*x+1,1,1);
    				}
    				else
    				{
    					addedge(2*x+1,2*x+2,1,0);
    					addedge(2*x+2,2*x+1,1,0);
    				}
    				if ((i+j)&1)
    				{
    					addedge(2*x+1,T,1,0);
    					addedge(2*x+2,T,1,0);
    				}
    				else
    				{
    					addedge(S,2*x+1,1,0);
    					addedge(S,2*x+2,1,0);
    					for (int k=0;k<4;k++)
    					{
    						int tx=i+di[k][0],ty=j+di[k][1];
    						if (tx>=0&&tx<n&&ty>=0&&ty<m&&field[tx][ty]!='w')
    						{
    							int p=id(tx,ty);
    							addedge(2*x+1+(k&1),2*p+1+(k&1),1,0);
    						}
    					}
    				}
    			}
    	while (spfa()) augment();
    	int ans=0;
    	for (int i=0;i<ecnt;i+=2)
    	{
    		if (e[i^1].to==S&&e[i].cap>e[i].flow) return -1;
    		ans=ans+e[i].flow*e[i].weight;
    	}
    	return ans;
    }
};
