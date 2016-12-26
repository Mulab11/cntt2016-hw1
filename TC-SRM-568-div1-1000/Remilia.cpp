// by ξ
// program sky  :)

#include <vector>
#include <stdio.h>
#include <cassert>
#include <iostream>
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

const string done="POSSIBLE",undone="IMPOSSIBLE";

int n,m,g[88],be[88];
PII a[88];
bool bo[88];

void append(int i,int p){
	++i;++p;be[i]=p;
	if(a[p].x)a[p].y=i;else a[p].x=i;// store every pair
}

namespace bip{
	int vis[88],col[88];
	VII li[88];
	void init(){
		For(i,0,n)col[i]=vis[i]=0,li[i].resize(0);// initialize
	}
	void append(int u,int v,int c){
		li[u].pb({v,c});
		li[v].pb({u,c});// add edges
	}
	bool gao(int u){
		// determine if the graph is legal
		vis[u]=1;
		for(auto it:li[u]){
			int v=it.x;
			if(vis[v] && col[v]^col[u]^it.y)return 0;
			if(!vis[v]){
				col[v]=col[u]^it.y;
				if(!gao(v))return 0;
			}
		}
		return 1;
	}
	bool ok(){
		For(i,0,n)if(!vis[i]){
			if(!gao(i))return 0;
		}
		return 1;
	}
}

bool jiao(int i,int j){
	if(a[i].x>a[j].x)swap(i,j);
	return a[j].x<a[i].y && a[j].y>a[i].y;
	// determine if the two seg are intersected
}

string dfs(int s){
	if(s==*g+1){
		bip::init();
		For(i,1,m)For(j,i+1,m){
			if(jiao(i,j))bip::append(i,j,1);// bip graph
		}
		if(bip::ok())return done;
	}
	if(be[g[s]])return dfs(s+1);
	For(i,s+1,*g){
		if(!be[g[i]]){
			be[g[s]]=be[g[i]]=++m;
			a[m]={g[s],g[i]};
			if(dfs(s+1)==done)return done;
			be[g[s]]=be[g[i]]=0;
			a[m]=PII();
			--m;
		}
	}
	return undone;
}

string Main(){
	// 0 over 1 below
	if(m<=20){
		rep(i,0,1<<m){
			//枚举已匹配点朝向
			if([i](){
				For(j,1,m)For(k,j+1,m)if(jiao(j,k) && (i>>k-1&1)==(i>>j-1&1))return 1;
				return 0;
			}())continue;
			bip::init();
			bip::append(0,n,0);
			For(j,1,m)if(i>>j-1&1){
				bip::append(a[j].x-1,a[j].y,0);
				bip::append(a[j].x-1,a[j].x,1);
				bip::append(a[j].y-1,a[j].y,1);
			}else{
				bip::append(a[j].x-1,a[j].y,a[j].y-a[j].x+1&1);
				bip::append(a[j].x-1,a[j].x,0);
				bip::append(a[j].y-1,a[j].y,0);
			}
			if(bip::ok())return done;//2色数约束
		}
		return undone;
	}else{
		//爆搜未匹配点
		For(i,1,n)if(bo[i])g[++*g]=i;
		return dfs(1);
	}
}

struct DisjointSemicircles{
	string getPossibility(VI lab){
		n=SZ(lab);
		VI tt(88,-1);int col=0;
		for(int&i:lab)if(~i){
			if(~tt[i])i=tt[i];else i=tt[i]=col++;
		}
		rep(i,0,n)if(~lab[i])append(i,lab[i]),m=max(m,lab[i]+1);else bo[i+1]=1;
		return Main();
	}
};