// BEGIN CUT HERE

// END CUT HERE
#line 5 "GearsDiv1.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
#define INF (1e9)

namespace isap{
	#define N 66
	#define M 6666
	struct edge{
		int adj,next,cap;
		edge(){}
		edge(int _adj,int _next,int _cap):adj(_adj),next(_next),cap(_cap){}
	} e[M];
	int n,g[N],m;
	void AddEdge(int u,int v,int c){
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


class GearsDiv1{
	public:
	int getmin(string color, vector <string> graph){
		const char col[3]={'R','G','B'};
		int ret=INF;
		using namespace isap;
		n=graph.size()+2;
		for (int K=0;K<3;++K){
			memset(g,0,sizeof(g));m=1;
			for (int i=0;i<n-2;++i)
				if (color[i]==col[(K+1)%3]) AddEdge(1,i+2,1);
				else if (color[i]==col[K]) AddEdge(i+2,n,1);
			for (int i=0;i<n-2;++i)if (color[i]==col[(K+1)%3])
				for (int j=0;j<n-2;++j)if (color[j]==col[K])
					if (graph[i][j]=='Y') AddEdge(i+2,j+2,INF);
			ret=min(ret,doit());
		}
		return ret;
	}
};

//this is for test
/*
int main(){
	GearsDiv1 test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
