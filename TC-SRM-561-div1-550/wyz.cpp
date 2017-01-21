// BEGIN CUT HERE

// END CUT HERE
#line 5 "CirclesGame.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

#define N 55

struct edge{
	int adj,next;
	edge(){}
	edge(int _adj,int _next):adj(_adj),next(_next){}
} e[N*2];
int n,g[N],m;
void AddEdge(int u,int v){
//	printf("%d %d\n",u,v);
	e[++m]=edge(v,g[u]);g[u]=m;
	e[++m]=edge(u,g[v]);g[v]=m;
}




class CirclesGame{
	int dfn[N],stamp;
	int fa[N],size[N];
	bool mark[N*2];
	int sg[N];
	void solve(int u,int now){
		now^=sg[u];
		for (int i=g[u];i;i=e[i].next){
			int v=e[i].adj;
			if (v==fa[u]) continue;
			now^=sg[v];
		}
		mark[now]=1;
		for (int i=g[u];i;i=e[i].next){
			int v=e[i].adj;
			if (v==fa[u]) continue;
			solve(v,now);
		}
	}
	void dfs(int u){
		dfn[u]=++stamp;
		size[u]=1;
		for (int i=g[u];i;i=e[i].next){
			int v=e[i].adj;
			if (v==fa[u]) continue;
			fa[v]=u;
			dfs(v);
			size[u]+=size[v];
		}
		int tmp=sg[u];
		memset(mark,0,sizeof(int)*(size[u]+2));
		solve(u,tmp);
		for (int i=0;;++i)if (!mark[i]){sg[u]=i;break;}
	}
	bool work(){
		memset(dfn,0,sizeof(dfn));stamp=0;
		int res=0;
		for (int i=0;i<n;++i)if (fa[i]<0){
//			printf("%d\n",i);
			fa[i]=-1;
			dfs(i);
			res^=sg[i];
		}
		return res;
	}
	
	double dist(int x0,int y0,int x1,int y1){
		return sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
	}
	public:
	string whoCanWin(vector <int> x, vector <int> y, vector <int> r){
		n=x.size();
		memset(g,0,sizeof(g));m=1;
		memset(fa,0,sizeof(fa));
		for (int i=0;i<n;++i){
			int _fa=-1;
			for (int j=0;j<n;++j)if (r[i]<r[j])
				if (dist(x[i],y[i],x[j],y[j])<r[j])
					if (_fa<0||r[j]<r[_fa]) _fa=j;
			if (_fa>=0) AddEdge(_fa,i);
			else fa[i]=-1;
		}
		return work()?"Alice":"Bob";
	}
};
