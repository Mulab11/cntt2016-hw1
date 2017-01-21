// BEGIN CUT HERE

// END CUT HERE
#line 5 "CentaurCompany.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
#define N 38
#define M 75

struct edge{
	int adj,next;
	edge(){}
	edge(int _adj,int _next):adj(_adj),next(_next){}
} e[M];
int n,g[N],m;
void AddEdge(int u,int v){
	e[++m]=edge(v,g[u]);g[u]=m;
	e[++m]=edge(u,g[v]);g[v]=m;
}

class CentaurCompany{
	int fa[N],sz[N];
	ll dp[N][2][N][N];
//	int dp[N][2][N][N];
	void solve(int u){
		sz[u]=1;
		memset(dp[u],0,sizeof(dp[u]));
		dp[u][0][0][0]=dp[u][1][1][0]=1;
		for (int i=g[u];i;i=e[i].next){
			int v=e[i].adj;
			if (v==fa[u]) continue;
			fa[v]=u;
			solve(v);
			for (int j=sz[u];j>=0;--j)for (int k=j;k>=0;--k)
				for (int jv=1;jv<=sz[v];++jv)for (int kv=0;kv<jv;++kv){
					dp[u][1][j+jv][k+kv+1]+=dp[v][1][jv][kv]*dp[u][1][j][k];
					dp[u][1][j+jv][k+kv]+=dp[v][0][jv][kv]*dp[u][1][j][k];
					dp[u][0][j+jv][k+kv]+=(dp[v][1][jv][kv]+dp[v][0][jv][kv])*dp[u][0][j][k];
				}
			sz[u]+=sz[v];
		}
	}
	public:
	double getvalue(vector <int> a, vector <int> b){
		n=a.size()+1;
		memset(g,0,sizeof(g));m=1;
		for (int i=0;i<n-1;++i) AddEdge(a[i]-1,b[i]-1);
		fa[0]=-1;
		solve(0);
		double ret=0;
		for (int i=1;i<=n;++i)
			for (int j=0;j<i;++j)
				ret+=1.0*max(i-2-2*j,0)*(dp[0][0][i][j]+dp[0][1][i][j]);
		for (int i=1;i<n;++i) ret/=2.0;
		return ret;
	}
};
