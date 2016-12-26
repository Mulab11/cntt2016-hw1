// by ξ
// program sky  :)

#include <vector>
#include <stdio.h>
#include <cassert>
#include <algorithm>

#define Rin register int
#define oo (c=getchar())
#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define dto(i,r,l) for(int _l=l,i=r;i>=_l;--i)
#define ALL(V) V.begin(),V.end()
#define SZ(A) (int(A.size()))
#define pb push_back
#define mk make_pair
#define x first
#define y second

using namespace std;

typedef double db;
typedef long long LL;
typedef pair<int ,int> PII;
typedef pair<db ,db> cpx;
typedef vector<int> VI;
typedef vector<PII> VII;

const int mo=1e9+9;

int Ans,n,K,pei[55][55],sz[55][55],binom[55][55],ga[55],invga[55],dp[55][55][55],size[55];
bool done[55][55];
VI li[55];

inline void Add(int u,int v){
	li[u].pb(v);li[v].pb(u);
}

inline void inc(int &x,int y){if((x+=y)>=mo)x-=mo;}

inline int Pow(int x,int y){
	int z=1;
	for(;y;y>>=1,x=1ll*x*x%mo)if(y&1)z=1ll*z*x%mo;
	return z;
}

void dfs(int u,int ff){
	if(done[u][ff])return;
	done[u][ff]=1;
	pei[u][ff]=1;
	for(int v:li[u])if(v^ff){
		dfs(v,u);
		sz[u][ff]+=sz[v][u];
		pei[u][ff]=1ll*pei[v][u]*invga[sz[v][u]]%mo*pei[u][ff]%mo;
	}
	pei[u][ff]=1ll*pei[u][ff]*ga[sz[u][ff]]%mo;//ways of a subtree
	++sz[u][ff];
}

int gao(int u,int ff,int len){
	if(sz[u][ff]==K && len==n-2*K)return pei[u][ff];// a (n-2k+1)-long chain exists
	for(int v:li[u])if(v^ff){
		if(sz[v][u]>=K)return gao(v,u,len+1);
	}
	return 0;
}

int DFS(int u,int ff){
	if(sz[u][ff]==K)return pei[u][ff]*1ll*gao(ff,u,0)%mo;
	for(int v:li[u])if(v^ff){
		if(sz[v][u]>=K){
			int _=DFS(v,u);
			if(_)return _;
		}
	}
	return 0;
}

inline void pret(){
	*ga=1;
	For(i,1,n)ga[i]=1ll*ga[i-1]*i%mo;
	For(i,0,n)invga[i]=Pow(ga[i],mo-2);
	For(i,0,n){
		*binom[i]=1;
		For(j,1,i)binom[i][j]=(binom[i-1][j]+binom[i-1][j-1])%mo;
	}
}

void dfss(int u,int ff){
	dp[u][0][0]=1;// [node][red][blue]
	for(int v:li[u])if(v^ff)dfss(v,u);

	for(int v:li[u])if(v^ff){
		dto(r,size[u],0)
		dto(b,size[u]-r,0)if(dp[u][r][b])
		For(rr,0,size[v])
		For(bb,0,size[v]-rr)if(dp[v][rr][bb] && (rr || bb)){
			inc(dp[u][r+rr][b+bb],1ll*dp[u][r][b]*dp[v][rr][bb]%mo*binom[r+rr][r]%mo*binom[b+bb][b]%mo);
			//a package
		}
		size[u]+=size[v];
	}
	++size[u];
	
	dp[u][size[u]][0]=dp[u][0][size[u]]=pei[u][ff];//same color
	
	if(!ff)return inc(Ans,dp[u][n-K][n-K]);//root
	
	if(size[u]>=K)inc(Ans,1ll*dp[u][n-K][size[u]-K]*pei[ff][u]%mo*binom[n-K][size[u]-K]%mo);
	if(size[u]>=K)inc(Ans,1ll*dp[u][size[u]-K][n-K]*pei[ff][u]%mo*binom[n-K][size[u]-K]%mo);
	// u is the root of white nodes
}

inline int Main(){
	pret();
	if(K==n || K==1)return ga[n];//special case
	For(i,1,n){
		dfs(i,0);
		for(int x:li[i])dfs(i,x);//calc the ways when [iff key[u]>key[son]]
	}
	if(2*K<=n){//there's a chain
		return DFS(1,0)*2%mo;
	}
	dfss(1,0);//2K>n
	return Ans*1ll*ga[2*K-n]%mo;//shuffle
}

struct InducedSubgraphs{
	int getCount(VI edge1,VI edge2,int k){
		n=SZ(edge1)+1;
		rep(i,0,n-1)Add(edge1[i]+1,edge2[i]+1);
		K=k;
		return Main();
	}
};