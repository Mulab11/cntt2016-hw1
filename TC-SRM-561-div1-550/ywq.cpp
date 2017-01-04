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

struct node
{
	int x,y,r;
}a[55];

vi e[55];
int times,dfn[55][2],b[55],sg[55],fa[55],deg[55];
bool ok[55];

int sqr(int x) {return x*x;}

bool inside(int i,int j)
{
	if (a[i].r>a[j].r&&sqr(a[i].x-a[j].x)+sqr(a[i].y-a[j].y)<sqr(a[i].r-a[j].r)) return 1; else return 0;
}

void dfs(int k)
{
	dfn[k][0]=++times;b[times]=k;
	for (int i=0;i<e[k].size();i++)
	{
		fa[e[k][i]]=k;dfs(e[k][i]);
	}
	dfn[k][1]=times;
}

struct CirclesGame 
{
    string whoCanWin(vector <int> x, vector <int> y, vector <int> r)
    {
    	int n=x.size();
    	for (int i=0;i<n;i++) {a[i].x=x[i];a[i].y=y[i];a[i].r=r[i];}
    	for (int i=0;i<n;i++)
    		for (int j=0;j<n;j++)
    			if (inside(i,j))
    			{
    				bool ok=1;
    				for (int k=0;k<n;k++)
    					if (inside(i,k)&&inside(k,j)) {ok=0;break;}
    				if (ok) {e[i].pb(j);deg[j]++;}
    			}
    	times=0;
    	for (int i=0;i<n;i++) if (!deg[i]) dfs(i); //node i is a root of a tree
    	for (int i=n;i;i--)
    	{
            //calculate mex
    		memset(ok,0,sizeof(ok));
    		for (int j=dfn[b[i]][0];j<=dfn[b[i]][1];j++)
    		{
    			int x=b[j],t=0;
    			for (int k=0;k<e[x].size();k++) t^=sg[e[x][k]];
    			while (x!=b[i])
    			{
    				int y=x;x=fa[x];
    				for (int k=0;k<e[x].size();k++) if (e[x][k]!=y) t^=sg[e[x][k]];
    			}
    			ok[t]=1;
    		}
    		sg[b[i]]=0;while (ok[sg[b[i]]]) sg[b[i]]++;
    	}
    	int ans=0;
    	for (int i=0;i<n;i++) if (!deg[i]) ans^=sg[i];
    	if (ans) return "Alice"; else return "Bob";
    }
};
