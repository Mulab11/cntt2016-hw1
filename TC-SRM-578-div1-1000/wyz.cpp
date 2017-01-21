// BEGIN CUT HERE

// END CUT HERE
#line 5 "DeerInZooDivOne.cpp"
#include <bits/stdc++.h>
#define ll long long
#define N 53
#define INF (1e8)

using namespace std;
struct KM{
	int n;
	int g[N][N],slk[N],A[N],B[N];
	int prev[N],fx[N],fy[N];
	bool visx[N],visy[N];
	int q[N],qh,qt;
	void clear(int _n){
		n=_n;memset(g,0,sizeof(g));
	}
	void AddEdge(int u,int v,int w){
		g[u][v]=w;
	}
	void aug(int v){
		if (!v) return;
		fy[v]=prev[v];
		aug(fx[fy[v]]);
		fx[fy[v]]=v;
	}
	void bfs(int _s){
		memset(visx,0,sizeof(visx));
		memset(visy,0,sizeof(visy));
		memset(slk,127,sizeof(slk));
		qh=qt=0;q[++qt]=_s;
		for (;;){
			while (qh<qt){
				int u=q[++qh];
				visx[u]=1;
				for (int v=1;v<=n;++v)if (!visy[v]){
					if (A[u]+B[v]==g[u][v]){
						visy[v]=1;
						prev[v]=u;
						if (!fy[v]){aug(v);return;}
						q[++qt]=fy[v];
					}
					else if (slk[v]>A[u]+B[v]-g[u][v]){
						slk[v]=A[u]+B[v]-g[u][v];
						prev[v]=u;
					}
				}
			}
			int d=INF;
			for (int i=1;i<=n;++i)if (!visy[i])d=min(d,slk[i]);
			for (int i=1;i<=n;++i){
				if (visx[i]) A[i]-=d;
				if (visy[i]) B[i]+=d;
				else slk[i]-=d;
			}
			for (int v=1;v<=n;++v)
				if (!visy[v]&&!slk[v]){
					visy[v]=1;
					if (!fy[v]){aug(v);return;}
					q[++qt]=fy[v];
				}
		}
	}
	int solve(){
		memset(A,128,sizeof(A));
		memset(B,0,sizeof(B));
		memset(fx,0,sizeof(fx));
		memset(fy,0,sizeof(fy));
		for (int i=1;i<=n;++i)
			for (int j=1;j<=n;++j) A[i]=max(A[i],g[i][j]);
		for (int i=1;i<=n;++i) bfs(i);
		int ret=0;
		for (int i=1;i<=n;++i) ret+=A[i]+B[i];
		return ret;
	}
} km;

struct edge{
	int adj,next;
	edge(){}
	edge(int _adj,int _next):adj(_adj),next(_next){}
} e[N*2];
int n,g[N],m;
void AddEdge(int u,int v){
	e[++m]=edge(v,g[u]);g[u]=m;
	e[++m]=edge(u,g[v]);g[v]=m;
}

bool vis[N];
int fa[N];
void dfs0(int u){
	vis[u]=1;
	for (int i=g[u];i;i=e[i].next){
		int v=e[i].adj;
		if (vis[v]) continue;
		fa[v]=u;
		dfs0(v);
	}
}

int dp[N][N][N];
int solve(int u,int u1,int fa1){
	if (dp[u][u1][fa1]>=0) return dp[u][u1][fa1];
	int _n=0,_n1=0,son[N],son1[N];
	for (int i=g[u];i;i=e[i].next){
		int v=e[i].adj;
		if (v==fa[u]) continue;
		son[++_n]=v;
	}
	
	for (int j=g[u1];j;j=e[j].next){
		int v=e[j].adj;
		if (v==fa1) continue;
		son1[++_n1]=v;
	}

	for (int i=1;i<=_n;++i)for (int j=1;j<=_n1;++j)solve(son[i],son1[j],u1);
	km.clear(max(_n,_n1));
	for (int i=1;i<=_n;++i)for (int j=1;j<=_n1;++j)km.AddEdge(i,j,solve(son[i],son1[j],u1));
	return dp[u][u1][fa1]=km.solve()+1;
}

class DeerInZooDivOne{
	public:
	int getmax(vector <int> a, vector <int> b){
		n=a.size()+1;
		memset(vis,0,sizeof(vis));
		for (int j=0;j<n-1;++j)AddEdge(a[j],b[j]);
		dfs0(0);
		for (int j=0;j<n-1;++j)if (fa[a[j]]!=b[j]) swap(a[j],b[j]);
		int ret=0;
		for (int i=0;i<n-1;++i){
			memset(g,0,sizeof(g));m=1;
			for (int j=0;j<n-1;++j)if (j!=i)AddEdge(a[j],b[j]);
			int rt=a[i];
			fa[rt]=n;
			memset(vis,0,sizeof(vis));
			dfs0(rt);
			memset(dp,-1,sizeof(dp));
			for (int j=0;j<n;++j)if (!vis[j])
				ret=max(ret,solve(rt,j,n));
		}
		return ret;
	}
};
