// BEGIN CUT HERE

// END CUT HERE
#line 5 "SurroundingGame.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
namespace isap{
	#define N 6666
	#define M 233333
	#define INF (1e9)
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

const int maxn=23;

class SurroundingGame{
	int id[maxn][maxn],stamp;
	int r,c;
	public:
	int maxScore(vector <string> cost, vector <string> benefit){
		r=cost.size();
		c=cost[0].size();
		const int dx[4]={1,0,-1,0};
		const int dy[4]={0,1,0,-1};
		int val[233];
		for (int i='0';i<='9';++i) val[i]=i-'0';
		for (int i='a';i<='z';++i) val[i]=i+10-'a';
		for (int i='A';i<='Z';++i) val[i]=i+36-'A';
		using namespace isap;
		memset(g,0,sizeof(g));m=1;
		n=r*c*2+2;
		stamp=1;
		for (int i=0;i<r;++i)for (int j=0;j<c;++j) id[i][j]=++stamp;
		int sum=0;
		for (int i=0;i<r;++i)for (int j=0;j<c;++j){
			int _c=val[cost[i][j]],_b=val[benefit[i][j]];
			sum+=_b;
			if ((i+j)&1){
				AddEdge(1,id[i][j],_c);
				AddEdge(id[i][j],id[i][j]+r*c,_b);
				for (int k=0;k<4;++k){
					int x=i+dx[k],y=j+dy[k];
					if (0<=x&&x<r&&0<=y&&y<c)
						AddEdge(id[i][j]+r*c,id[x][y],INF);
				}
			}
			else{
				AddEdge(id[i][j],n,_c);
				AddEdge(id[i][j]+r*c,id[i][j],_b);
				for (int k=0;k<4;++k){
					int x=i+dx[k],y=j+dy[k];
					if (0<=x&&x<r&&0<=y&&y<c)
						AddEdge(id[x][y],id[i][j]+r*c,INF);
				}
			}
		}
		return sum-doit();
	}
};