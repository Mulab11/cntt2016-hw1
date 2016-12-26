// by ξ
// program sky  :)

#include <vector>
#include <complex>
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
typedef complex<db> cpx;
typedef vector<int> VI;
typedef vector<PII> VII;

const int mo=1e9+7;

int n,bo[111],g[111];
PII F[111];
VII li[111];

// 有限制的连边

void Link(int u,int v,int w){
	li[u].pb({v,w});
	li[v].pb({u,w});
}

// 每个连通块的答案

int gao(int s,int bound){
	int l=0,r=1;
	// 表示成X=kx+b的形式
	F[s]={1,0};bo[s]=1;
	for(g[l]=s;l<r;){
		int u=g[l++];
		for(auto it:li[u]){
			int v=it.x,w=it.y;
			if(!bo[v]){
				F[v].x=-F[u].x;
				F[v].y=w-F[u].y;
				bo[g[r++]=v]=1;
			}else{
				if(F[v].x!=-F[u].x || F[v].y!=w-F[u].y)return 0;
			}
		}
	}
	// 整数解个数
	PII ans={0,888};
	rep(i,0,r){
		int u=g[i];
		if(u<=n){
			ans.x=max(ans.x,bound-F[u].y);
		}else{
			ans.y=min(ans.y,F[u].y+1);
		}
	}
	return max(ans.y-ans.x,0);
}

struct EqualSums{
	int count(vector<string> board){
		n=SZ(board);
		For(i,1,n)For(j,1,n)if(board[i-1][j-1]!='-'){
			Link(i,j+n,board[i-1][j-1]-'0');
		}
		// 容斥
		int A=1,B=1;
		For(i,1,2*n)if(!bo[i]){
			A=1ll*A*gao(i,0)%mo;
		}
		For(i,1,2*n)bo[i]=0;
		For(i,1,2*n)if(!bo[i]){
			B=1ll*B*gao(i,1)%mo;
		}
		return (A-B+mo)%mo;
	}
};