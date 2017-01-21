// BEGIN CUT HERE

// END CUT HERE
#line 5 "HatRack.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn=55;

struct edge{
	int adj,next;
	edge(){}
	edge(int _adj,int _next):adj(_adj),next(_next){}
} e[maxn*2];
int n,g[maxn],m;
void AddEdge(int u,int v){
	e[++m]=edge(v,g[u]);g[u]=m;
	e[++m]=edge(u,g[v]);g[v]=m;
}

class HatRack{
	ll k;
	int size[maxn],fa[maxn];
	int son[maxn][2];
	void dfs0(int u){
		size[u]=1;
		int dgr=0;
		for (int i=g[u];i;i=e[i].next){
			int v=e[i].adj;
			if (v==fa[u]) continue;
			if (dgr==2){k=0;return;}
			son[u][dgr++]=v;
			fa[v]=u;
			dfs0(v);
			if (!k) return;
			size[u]+=size[v];
		}
		if (dgr==2){
			if (size[son[u][0]]<size[son[u][1]]) swap(son[u][0],son[u][1]);
			if (size[son[u][0]]==size[son[u][1]]) k<<=1;
		}
	}
	int id[maxn];
	void dfs1(int u){
		for (int j=0;j<2;++j)if (son[u][j]){
			int v=son[u][j];
			if ((id[v]=id[u]<<1^j)>n){k=0;return;}
			dfs1(v);
		}
	}
	public:
	long long countWays(vector <int> knob1, vector <int> knob2){
		n=knob1.size()+1;
		memset(g,0,sizeof(g));
		for (int i=0;i<n-1;++i)
			AddEdge(knob1[i],knob2[i]);
		ll ret=0;
		for (int rt=1;rt<=n;++rt){
			memset(son,0,sizeof(son));
			memset(fa,0,sizeof(fa));
			k=1;
			dfs0(rt);
			id[rt]=1;
			if (k) dfs1(rt);
			if (k) ret+=k;
		}
		return ret;
	}
};
