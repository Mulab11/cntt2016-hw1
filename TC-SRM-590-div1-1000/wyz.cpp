// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxAndCity.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
#define INF (1e9)

namespace isap{
	#define N 2333
	#define M 233333
	struct edge{
		int adj,next,cap;
		edge(){}
		edge(int _adj,int _next,int _cap):adj(_adj),next(_next),cap(_cap){}
	} e[M];
	int n,g[N],m;
	void AddEdge(int u,int v,int c){
//		printf("%d %d %d\n",u,v,c);
		e[++m]=edge(v,g[u],c);g[u]=m;
		e[++m]=edge(u,g[v],0);g[v]=m;
	}
	int h[N],gap[N],cur[N],flow,maxflow;
	bool found;
	void aug(int u){
		if (u==n){
			found=1;
			maxflow+=flow;
			return;
		}
		int i=cur[u],tmp=flow;
		for (;i;i=e[i].next)if (e[i].cap){
			int v=e[i].adj;
			if (h[u]==h[v]+1){
				cur[u]=i;
				flow=min(flow,e[i].cap);
				aug(v);
				if (h[1]==n) return;
				if (found) break;
				flow=tmp;
			}
		}
		if (found){
			e[i].cap-=flow;
			e[i^1].cap+=flow;
		}
		else{
			int minh=n;
			for (int i=cur[u]=g[u];i;i=e[i].next)if (e[i].cap)
				minh=min(minh,h[e[i].adj]+1);
			if (!--gap[h[u]]) h[1]=n;
			++gap[h[u]=minh];
		}
	}
	int doit(){
		memset(h,0,sizeof(h));
		memset(gap,0,sizeof(gap));
		gap[0]=n;
		for (int i=1;i<=n;++i) cur[i]=g[i];
		maxflow=0;
		while (h[1]<n){
			flow=INF;
			found=0;
			aug(1);
		}
		return maxflow;
	}
};


class FoxAndCity{
	int id[66][66];
	public:
	int minimalCost(vector <string> linked, vector <int> want){
		using namespace isap;
//---build graph---begin
		memset(g,0,sizeof(g));m=1;
		n=1;
		int n0=want.size();
		for (int i=0;i<n0;++i)
			for (int j=0;j<=n0;++j)
				id[i][j]=++n;
		++n;
		for (int i=0;i<n0;++i){
			AddEdge(1,id[i][0],INF);
			AddEdge(id[i][n0],n,INF);
			AddEdge(id[i][0],id[i][1],INF*(i>0));
			for (int j=1;j<n0;++j)
				AddEdge(id[i][j],id[i][j+1],i?(want[i]-j)*(want[i]-j):INF);
		}
		for (int i=0;i<n0;++i)for (int j=0;j<n0;++j)if (linked[i][j]=='Y')
			for (int k=0;k<n0;++k)
				AddEdge(id[i][k+1],id[j][k],INF);
//---build graph---end
		return doit();//flow!
	}
};

//this is for test
/*
int main(){
	FoxAndCity test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
