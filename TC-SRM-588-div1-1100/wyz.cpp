// BEGIN CUT HERE

// END CUT HERE
#line 5 "GameInDarknessDiv1.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;
#define N 6666

struct edge{
	int adj,next;
	edge(){}
	edge(int _adj,int _next):adj(_adj),next(_next){}
} e[N];
int n,g[N],m;
void AddEdge(int u,int v){
//	printf("%d %d\n",u,v);
	e[++m]=edge(v,g[u]);g[u]=m;
	e[++m]=edge(u,g[v]);g[v]=m;
}

int deep[N];
bool vis[N];
#define v e[i].adj
int dfs(int u){
	vis[u]=1;
	int ret=deep[u];
	for (int i=g[u];i;i=e[i].next){
		if (vis[v]) continue;
		deep[v]=deep[u]+1;
		ret=max(ret,dfs(v));
	}
	return ret;
}

class GameInDarknessDiv1 {
	int id[66][66];
	public:
	string check(vector <string> field){
		n=0;
		const int dx[2]={1,0};
		const int dy[2]={0,1};
		memset(id,0,sizeof(id));
		int a,b;
		memset(g,0,sizeof(g));
		for (int i=field.size()-1;i>=0;--i)
			for (int j=field[i].size()-1;j>=0;--j)if (field[i][j]!='#'){
				id[i][j]=++n;
				for (int k=0;k<2;++k)
					if (id[i+dx[k]][j+dy[k]])
						AddEdge(id[i][j],id[i+dx[k]][j+dy[k]]);
				if (field[i][j]=='A') a=id[i][j];
				if (field[i][j]=='B') b=id[i][j];
			}
		for (int u=1;u<=n;++u){
			memset(vis,0,sizeof(bool)*(n+2));
			deep[u]=0;vis[u]=1;
			int cnt=0;
			for (int i=g[u];i;i=e[i].next){
				deep[v]=1;
				if (dfs(v)>2) ++cnt;
			}
			if (deep[a]>=deep[b]+2&&cnt>2) return "Bob wins";
//			printf("%d %d %d\n",deep[a],deep[b],cnt);
//			for (int i=1;i<=n;++i) printf("%d ",deep[i]);puts("");
		}
		return "Alice wins";
	}
};
