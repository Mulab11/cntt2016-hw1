// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxAndGo3.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
#define N 2555
#define M 23333
#define INF (1e8)

namespace isap{
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

class FoxAndGo3{
	int id[66][66];
	public:
	int maxEmptyCells(vector <string> board){
		using namespace isap;
		n=1;
		memset(id,0,sizeof(id));
		for (int i=0;i<board.size();++i)
			for (int j=0;j<board[i].length();++j)
				if (board[i][j]!='x') id[i+1][j+1]=++n;
		++n;
		const int dx[4]={1,-1,0,0};
		const int dy[4]={0,0,1,-1};
		memset(g,0,sizeof(g));m=1;
		for (int i=0;i<board.size();++i)
			for (int j=0;j<board[i].length();++j)
				if (board[i][j]=='.') AddEdge(1,id[i+1][j+1],1);
				else if (board[i][j]=='o'){
					AddEdge(id[i+1][j+1],n,1);
					for (int k=0;k<4;++k)
						if (id[i+1+dx[k]][j+1+dy[k]])
							AddEdge(id[i+1+dx[k]][j+1+dy[k]],id[i+1][j+1],INF);
				}
		return n-2-doit();
	}
};

//this is for test
/*
int main(){
	FoxAndGo3 test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
