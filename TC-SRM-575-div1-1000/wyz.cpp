// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheTilesDivOne.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;


namespace isap{
	#define N 6666
	#define M 233333
	#define INF (1e8)
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
	void clear(){memset(g,0,sizeof(g));m=1;}
	int gap[N],h[N],cur[N],maxflow,flow;
	bool found;
	void aug(int u){
		if (u==n){
			found=1;
			maxflow+=flow;
			return;
		}
		int i,tmp=flow;
		for (i=cur[u];i;i=e[i].next)if (e[i].cap){
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


const int maxn=2333;
class TheTilesDivOne{
	int in[66][66],out[66][66];
	public:
	int find(vector <string> board){
		using namespace isap;
//---------------build-----------------begin
		memset(in,0,sizeof(in));
		memset(out,0,sizeof(out));
		n=2;
		int r=board.size(),c=board[0].size();
		for (int i=0;i<r;++i)for (int j=0;j<c;++j)if (board[i][j]=='.'){
			in[i+1][j+1]=n++;
			out[i+1][j+1]=n++;
		}
		const int dx[4]={1,0,-1,0};
		const int dy[4]={0,1,0,-1};
		memset(g,0,sizeof(g));m=1;
		for (int i=1;i<=r;++i)for (int j=1;j<=c;++j)if (in[i][j]){
			AddEdge(in[i][j],out[i][j],1);
			for (int k=0;k<4;++k)
				if (in[i+dx[k]][j+dy[k]])
					AddEdge(out[i][j],in[i+dx[k]][j+dy[k]],1);
			if ((i+j)&1){
				if (i&1) AddEdge(1,in[i][j],1);
				if (j&1) AddEdge(out[i][j],n,1);
			}
		}
//---------------build-----------------end
		return doit();
	}
};
