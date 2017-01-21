// BEGIN CUT HERE

// END CUT HERE
#line 5 "InducedSubgraphs.cpp"
#include <bits/stdc++.h>
#define ll long long
#define P 1000000009

using namespace std;
int fast_pow(int x,int y){
	int ret=1;
	while (y){
		if (y&1) ret=1LL*ret*x%P;
		x=1LL*x*x%P;
		y>>=1;
	}
	return ret;
}

const int maxn=44;
int fact[maxn],inv[maxn];
void Init(){
	for (int i=fact[0]=1;i<maxn;++i) fact[i]=1LL*fact[i-1]*i%P;
	for (int i=0;i<maxn;++i) inv[i]=fast_pow(fact[i],P-2);
}
int c(int n,int m){
	if (m>n||m<0) return 0;
	return 1LL*fact[n]*inv[m]%P*inv[n-m]%P;
}

struct edge{
	int adj,next;
	edge(){}
	edge(int _adj,int _next):adj(_adj),next(_next){}
} e[maxn*2];
int n,g[maxn],m,dgr[maxn];
void AddEdge(int u,int v){
	e[++m]=edge(v,g[u]);g[u]=m;
	e[++m]=edge(u,g[v]);g[v]=m;
	++dgr[u];++dgr[v];
}

#define inc(x,y) if(((x)+=(y))>=P)(x)-=P
#define dec(x,y) if(((x)-=(y))<0)(x)+=P

int K;
int ans;

namespace subtask1{
	bool vis[maxn];
	int check(int u,int fa){
		int ret=1;
		for (int i=g[u];i;i=e[i].next){
			int v=e[i].adj;
			if (v==fa) continue;
			ret+=check(v,u);
		}
		return ret;
	}
	int sz[maxn];
	int solve(int u){
		vis[u]=1;
		int ret=1;
		sz[u]=0;
		for (int i=g[u];i;i=e[i].next){
			int v=e[i].adj;
			if (vis[v]) continue;
			ret=1LL*ret*solve(v);
			sz[u]+=sz[v];
			ret=1LL*ret*c(sz[u],sz[v])%P;
		}
		++sz[u];
		return ret;
	}
	void dfs(int u,int cnt,int rt){
		vis[u]=1;
		if (cnt==n-2*K+1){
			for (int i=g[u];i;i=e[i].next){
				int v=e[i].adj;
				if (vis[v]) continue;
				if (check(v,u)!=K) continue;
				int res=solve(v);
				res=1LL*res*solve(rt)%P;
				inc(ans,res);
			}
			vis[u]=0;
			return;
		}
		for (int i=g[u];i;i=e[i].next){
			int v=e[i].adj;
			if (vis[v]) continue;
			if (dgr[v]!=2) continue;
			dfs(v,cnt+1,rt);
		}
		vis[u]=0;
	}
	void work(){
		for (int i=0;i<n;++i){
			memset(vis,0,sizeof(vis));
			dfs(i,1,i);
		}
	}
};

namespace subtask2{
	bool vis[maxn];
	int f[maxn],size[maxn];
	int getroot(int u,int sum){
		vis[u]=1;
		int nowroot=-1;
		size[u]=1;f[u]=0;
		for (int i=g[u];i;i=e[i].next){
			int v=e[i].adj;
			if (vis[v]) continue;
			int tmp=getroot(v,sum);
			size[u]+=size[v];
			f[u]=max(f[u],size[v]);
			if (nowroot<0||f[tmp]<f[nowroot]) nowroot=tmp;
		}
		f[u]=max(f[u],sum-size[u]);
		if (nowroot<0||f[u]<f[nowroot]) nowroot=u;
		vis[u]=0;
		return nowroot;
	}
	
	int dp[maxn][maxn/2][maxn/2];
	int h[maxn/2][maxn/2];
	int sz[maxn];
	void dfs(int u,int fa){
		sz[u]=0;
		dp[u][0][0]=1;
		for (int i=g[u];i;i=e[i].next){
			int v=e[i].adj;
			if (v==fa) continue;
			dfs(v,u);
//			printf("v:%d\n",v);
			memset(h,0,sizeof(h));
			for (int j0=0;j0<=sz[u];++j0)for (int k0=0;k0<=sz[u];++k0)if (dp[u][j0][k0])
				for (int j=0;j<=sz[v]&&j0+j<=n-K;++j)for (int k=0;k<=sz[v]&&k0+k<=n-K;++k)
					h[j0+j][k0+k]=(1LL*dp[u][j0][k0]*dp[v][j][k]%P*c(j0+j,j)%P*c(k0+k,k)+h[j0+j][k0+k])%P;//,printf("%d %d %d %d %d %d %lld\n",j0,j,k0,k,dp[u][j0][k0],dp[v][j][k],1LL*dp[u][j0][k0]*dp[v][j][k]%P*c(j0+j,j)%P*c(k0+k,k));
			memcpy(dp[u],h,sizeof(h));
			sz[u]+=sz[v];
		}
		++sz[u];
		if (sz[u]<=n-K) dp[u][sz[u]][0]=dp[u][sz[u]-1][0],dp[u][0][sz[u]]=dp[u][0][sz[u]-1];
//		puts("=======");
//		printf("%d %d %d %d\n",u,dp[u][sz[u]][0],dp[u][0][sz[u]],sz[u]);
	}
	void work(){
		int rt=getroot(0,n);
		memset(dp,0,sizeof(dp));
		dfs(rt,-1);
		ans=1LL*fact[2*K-n]*dp[rt][n-K][n-K]%P;
	}
};


class InducedSubgraphs{
	public:
	int getCount(vector <int> edge1, vector <int> edge2, int k){
		Init();
		K=k;n=edge1.size()+1;
		if (k==n||k==1) return fact[n];
		memset(g,0,sizeof(g));m=1;
		for (int i=0;i<n-1;++i) AddEdge(edge1[i],edge2[i]);
		ans=0;
		if (2*k<=n) subtask1::work();
		else subtask2::work();
		return ans;
	}
};
