// BEGIN CUT HERE

// END CUT HERE
#line 5 "TurnOnLamps.cpp"
#include <bits/stdc++.h>
#define ll long long
#define N 55
#define M 105

using namespace std;

struct edge{
	int adj,next,type;
	edge(){}
	edge(int _adj,int _next,int _type):adj(_adj),next(_next),type(_type){}
} e[M];
int n,g[N],m;
void AddEdge(int u,int v,int t){
//	printf("%d %d %d\n",u,v,t);
	e[++m]=edge(v,g[u],t);g[u]=m;
	e[++m]=edge(u,g[v],t);g[v]=m;
}
int ans;

int fa[N],w[N],d[N];
void dfs(int u){
	d[u]=0;
	for (int i=g[u];i;i=e[i].next){
		int v=e[i].adj;
		if (v==fa[u]) continue;
		fa[v]=u;w[v]=e[i].type;
		dfs(v);
	}
	if (w[u]>=0){
		ans+=d[u]>>1;
		if (w[u]) ans+=d[u]&1;
		else ++d[fa[u]];
	}
	else d[fa[u]]+=d[u];
//	printf("%d %d",u,d[u]);
}

class TurnOnLamps{
	public:
	int minimize(vector <int> roads, string initState, string isImportant){
		n=roads.size()+1;
		memset(g,0,sizeof(g));m=1;
		for (int i=0;i<n-1;++i)
			AddEdge(i+2,roads[i]+1,isImportant[i]=='1'?initState[i]-48:-1);
		w[1]=1;fa[1]=0;
		ans=0;
		dfs(1);
		return ans;
	}
};
