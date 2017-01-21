// BEGIN CUT HERE

// END CUT HERE
#line 5 "Incubator.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;

#define N 105
#define M 5005

struct edge{
	int from,adj,next;
	edge(){}
	edge(int _adj,int _next):adj(_adj),next(_next){}
} e[M];
int n,g[N],m;
void AddEdge(int u,int v){
//	printf("%d %d\n",u,v);
	e[++m]=edge(v,g[u]);g[u]=m;
}


namespace hungary{
	int fx[N],fy[N];
	bool vis[N];
	bool dfs(int u){
		if (vis[u]) return 0;
		vis[u]=1;
		for (int i=g[u];i;i=e[i].next){
			int v=e[i].adj;
			if (fy[v]<0||dfs(fy[v])){
				fx[u]=v;
				fy[v]=u;
				return 1;
			}
		}
		return 0;
	}
	int doit(){
		int ret=0;
		memset(fx,-1,sizeof(fx));
		memset(fy,-1,sizeof(fy));
		for (int i=0;i<n;++i)if (fx[i]<0){
			memset(vis,0,sizeof(vis));
			ret+=dfs(i);
		}
		return ret;
	}
};

class Incubator {
	bool _g[N][N];
	public:
	int maxMagicalGirls(vector <string> love){
		n=love.size();
		memset(_g,0,sizeof(_g));
		for (int i=0;i<love.size();++i)for(int j=0;j<love[i].size();++j)
			if (love[i][j]=='Y') _g[i][j]=1;
		for (int k=0;k<n;++k)for (int i=0;i<n;++i)for (int j=0;j<n;++j)
			_g[i][j]=_g[i][j]||_g[i][k]&_g[k][j];
		memset(g,0,sizeof(g));m=1;
		for (int i=0;i<n;++i)for (int j=0;j<n;++j)
			if (_g[i][j]) AddEdge(i,j);
		return n-hungary::doit();
	}
};
