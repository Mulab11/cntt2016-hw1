// BEGIN CUT HERE

// END CUT HERE
#line 5 "PointyWizardHats.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

#define N 105
#define M 2505

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

class PointyWizardHats{
	int n1;
	public:
	int getNumHats(vector <int> topHeight, vector <int> topRadius, vector <int> bottomHeight, vector <int> bottomRadius){
		n=topHeight.size();n1=bottomHeight.size();
		#define rt topRadius[i]
		#define rb bottomRadius[j]
		#define ht topHeight[i]
		#define hb bottomHeight[j]
		memset(g,0,sizeof(g));m=1;
		for (int i=0;i<n;++i)for (int j=0;j<n1;++j)
			if (rt<rb&&ht*rb>rt*hb) AddEdge(i,j);
		return hungary::doit();
	}
};
