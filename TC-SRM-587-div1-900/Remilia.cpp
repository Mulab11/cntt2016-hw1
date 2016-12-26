// by ξ
// program sky  :)

#include <vector>
#include <string>
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
typedef vector<string> VS;

int n,m;

namespace bip{
	// 判断是否是二分图
	int vis[55],col[55];
	VII li[55];
	// 初始化
	void init(){
		For(i,0,n)col[i]=vis[i]=0,li[i].resize(0);
	}
	// 加边
	void append(int u,int v,int c){
		li[u].pb({v,c});
		li[v].pb({u,c});
	}
	// 判断
	bool gao(int u){
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

VS A;

bool ok(){
	bip::init();
	rep(i,0,n)rep(j,0,i){
		rep(k,0,m){
			if(A[i][k]!='?' && A[j][k]!='?'){
				if(A[i][k]==A[j][k])bip::append(i,j,0);
				else bip::append(i,j,1);
			}
		}
	}
	return bip::ok();
}

VS Main(){
	if(!ok())return VS{};
	// 逐位确定
	rep(i,0,n)rep(j,0,m)if(A[i][j]=='?'){
		A[i][j]='N';
		if(!ok())A[i][j]='Z';
	}
	return A;
}

struct ThreeColorability{
	VS lexSmallest(VS cells){
		n=SZ(cells);m=SZ(cells[0]);
		A=cells;
		return Main();
	}
};