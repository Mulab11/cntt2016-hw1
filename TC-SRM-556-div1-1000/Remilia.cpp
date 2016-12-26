// by ξ
// program sky  :)

#include <vector>
#include <stdio.h>
#include <iostream>
#include <algorithm>

#define Rin register int
#define oo (c=getchar())
#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define dto(i,r,l) for(int _l=l,i=r;i>=_l;--i)
#define ALL(V) V.begin(),V.end()
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

const int inf=1e9;

int S,T,n,tot,idx;

typedef int nArr[55];
typedef int mArr[20000];

nArr he,bo,dis,g;
mArr ne,pp,ee;

inline void init(){
	For(i,S,T)bo[i]=he[i]=0;tot=1;idx=0;
}

inline void Add(int u,int v,int c){
	pp[++tot]=v;ne[tot]=he[u];he[u]=tot;ee[tot]=c;
	pp[++tot]=u;ne[tot]=he[v];he[v]=tot;ee[tot]=0;
}

inline bool bfs(){
	int l=0,r=1;
	dis[S]=0;
	for(bo[g[l]=S]=++idx;l<r;){
		int u=g[l++];
		for(int e=he[u];e;e=ne[e])if(ee[e]>0){
			int v=pp[e];
			if(bo[v]<idx){
				bo[g[r++]=v]=idx;
				dis[v]=dis[u]+1;
				if(v==T)return 1;
			}
		}
	}
	return 0;
}

int dinic(int u,int ff){
	if(u==T)return ff;
	int res=0;
	for(int e=he[u];e;e=ne[e])if(ee[e]){
		int v=pp[e];
		if(bo[v]==idx && dis[v]==dis[u]+1){
			int tmp=dinic(v,min(ff,ee[e]));
			ff-=tmp;res+=tmp;
			ee[e]-=tmp;ee[e^1]+=tmp;
			if(!ff)return res;
		}
	}
	return res?res:(dis[u]=-1,0);
}

inline int flow(){
	int res=0;
	for(;bfs();)res+=dinic(S,inf);
	return res;
}

struct OldBridges{
	string isPossible(vector<string> A, int a1, int a2, int an, int b1, int b2, int bn){
		n=A.size();T=n+1;++a1;++a2;++b1;++b2;
		init();//初始化
		For(i,1,n)For(j,1,n)if(j^i){
			char c=A[i-1][j-1];
			if(c=='O')Add(i,j,1);
			else if(c=='N')Add(i,j,inf);
		}//连边
		Add(S,a1,an);
		Add(a2,T,an);
		Add(S,b1,bn);
		Add(b2,T,bn);
		if(flow()<an+bn)return "No";//最大流
		init();
		For(i,1,n)For(j,1,n)if(i^j){
			char c=A[i-1][j-1];
			if(c=='O')Add(i,j,1);
			else if(c=='N')Add(i,j,inf);
		}
		Add(S,a1,an);
		Add(a2,T,an);
		Add(S,b2,bn);
		Add(b1,T,bn);
		if(flow()<an+bn)return "No";//重复一遍最大流
		return "Yes";
	}
};