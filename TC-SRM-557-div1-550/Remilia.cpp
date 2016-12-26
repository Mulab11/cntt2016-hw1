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

int n,N,A[55][55],B[55][55],mate[55],ID[55];
bool vis[55];

// 匈牙利

bool gao(int u){
	if(vis[u])return 0;
	vis[u]=1;
	For(v,1,N)if(B[u][v]){
		if(!mate[v] || gao(mate[v])){
			mate[v]=u;
			return 1;
		}
	}
	return 0;
}

int ans(){
	int res=0;
	For(i,1,N){
		For(j,1,N)vis[j]=0;
		res+=gao(i);
	}
	return res;
}

int Main(){
	// 传递闭包
	rep(k,0,n)rep(i,0,n)rep(j,0,n)A[i][j]=A[i][j] || A[i][k] && A[k][j];
	// 扔掉自己能够到达自己的点
	rep(i,0,n)if(!A[i][i])ID[++N]=i;
	// 拓扑图最长链
	For(i,1,N)For(j,1,N)
	if(A[ID[i]][ID[j]]){
		B[i][j]=1;
	}
	return N-ans();
}

struct Incubator{
	int maxMagicalGirls(vector<string> love){
		n=SZ(love);
		rep(i,0,n)rep(j,0,n)A[i][j]=love[i][j]=='Y';
		return Main();
	}
};