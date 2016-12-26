// by ξ
// program sky  :)

#include <bits/stdc++.h>

#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define dto(i,r,l) for(int _l=l,i=r;i>=_l;--i)
#define pb push_back
#define x first
#define y second

using namespace std;

typedef pair<int ,int> PII;
typedef vector<int> VI;
typedef vector<PII> VII;
typedef int node_Arr[2000];
typedef int edge_Arr[140000];

const int inf=1e9;

int node,S,T,M,n,idx,want[44],ID[44][44];
node_Arr g,bo,dis,hh,he;
edge_Arr ne,pp,ee;
VII bian;

// 最小割部分

inline void Add(int u,int v,int e){
	pp[++M]=v;ne[M]=he[u];he[u]=M;ee[M]=e;
	pp[++M]=u;ne[M]=he[v];he[v]=M;ee[M]=0;
}

inline bool bfs(){
	int l=0,r=1;
	bo[g[l]=S]=++idx;dis[S]=0;
	for(;l<r;){
		int u=g[l++];
		for(int e=he[u];e;e=ne[e])if(ee[e]){
			int v=pp[e];
			if(bo[v]^idx){
				bo[v]=idx;
				dis[g[r++]=v]=dis[u]+1;
			}
		}
	}
	if(bo[T]==idx){
		rep(i,0,r)hh[g[i]]=he[g[i]];
		return 1;
	}
	return 0;
}

int dinic(int u,int ff){
	if(u==T)return ff;
	int res=0;
	for(int &e=hh[u];e;e=ne[e])if(ee[e]){
		int v=pp[e];
		if(dis[v]==dis[u]+1){
			int tmp=dinic(v,min(ff,ee[e]));
			ff-=tmp;res+=tmp;
			ee[e]-=tmp;ee[e^1]+=tmp;
			if(!ff)return res;
		}
	}
	return res?res:(dis[u]=-1,0);
}

inline int Flow(){
	int res=0;
	for(;bfs();)res+=dinic(S,inf);
	return res;
}

//============

inline int Main(){
	M=1;
	// 拆点dis[u]<=i
	For(i,1,n)rep(j,0,n)ID[i][j]=++node;
	T=++node;
	// 最小权闭合子图构图
	Add(ID[1][0],T,inf);
	// 必不成立
	For(i,2,n)	Add(S,ID[i][0],inf);
	// 必须成立
	For(i,2,n)	Add(ID[i][n-1],T,inf);
	// 分点相互关系
	For(i,1,n)rep(j,1,n)	Add(ID[i][j],ID[i][j-1],inf);
	for(PII it:bian){
		int u=it.x,v=it.y;
		// 图中边的效应
		rep(k,1,n){
			Add(ID[u][k],ID[v][k-1],inf);
		}
	}
	// 产生代价的地方
	For(u,1,n)rep(k,1,n)Add(ID[u][k-1],ID[u][k],(k-want[u])*(k-want[u]));
	return Flow();
}

struct FoxAndCity{
	int minimalCost(vector<string> linked, VI want){
		n=want.size();
		For(i,1,n)For(j,1,n)if(linked[i-1][j-1]=='Y'){
			bian.pb(PII(i,j));
		}
		For(i,1,n)::want[i]=want[i-1];
		return Main();
	}
};