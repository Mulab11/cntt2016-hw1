// by ξ
// program sky  :)

#include <cstdio>
#include <algorithm>

#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define dto(i,r,l) for(int _l=l,i=r;i>=_l;--i)
#define ALL(V) V.begin(),V.end()
#define pb push_back
#define x first
#define y second

using namespace std;

typedef int node_Arr[2505];
typedef int edge_Arr[30005];

const int inf=1e9;

int n,m,M,S,T,idx,node,ID[55][55],b[55][55];
node_Arr g,hh,he,dis,bo;
edge_Arr pp,ee,ne;

//最小割

inline void Add(int u,int v,int e){
	if(!e)return;
	pp[++M]=v;ne[M]=he[u];ee[M]=e;he[u]=M;
	pp[++M]=u;ne[M]=he[v];ee[M]=0;he[v]=M;
}

inline bool bfs(){
	int l=0,r=1;
	bo[g[l]=S]=++idx;
	for(;l<r;){
		int u=g[l++];
		for(int e=he[u];e;e=ne[e])if(ee[e]){
			int v=pp[e];
			if(bo[v]^idx){
				bo[g[r++]=v]=idx;
				dis[v]=dis[u]+1;
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
		if(bo[v]==idx && dis[v]==dis[u]+1){
			int tmp=dinic(v,min(ff,ee[e]));
			res+=tmp;ff-=tmp;
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

// 当且仅当纵向格子纵向方向上不是纵向格子，横向格子横向方向上不是横向格子时产生贡献。
// 这是个简单的最小割建模

inline int Main(){
	M=1;
	For(i,1,n)For(j,1,m)if(b[i][j])ID[i][j]=++node;
	T=++node;
	For(i,1,n)For(j,1,m)if(b[i][j]){
		Add(S,ID[i][j],(!b[i][j-1])+(!b[i][j+1]));
		Add(ID[i][j],T,(!b[i-1][j])+(!b[i+1][j]));
		if(i>1 && ID[i-1][j])Add(ID[i][j],ID[i-1][j],1);
		if(i<n && ID[i+1][j])Add(ID[i][j],ID[i+1][j],1);
		if(j>1 && ID[i][j-1])Add(ID[i][j-1],ID[i][j],1);
		if(j<m && ID[i][j+1])Add(ID[i][j+1],ID[i][j],1);
	}
	return Flow()>>1;
}

struct BoardPainting{
	int minimalSteps(vector<string> target){
		n=target.size();
		m=target[0].size();
		For(i,1,n)For(j,1,m)b[i][j]=target[i-1][j-1]=='#';
		return Main();
	}
};