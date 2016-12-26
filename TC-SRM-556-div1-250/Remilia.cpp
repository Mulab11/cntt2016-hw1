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

int n,base[10],g[55],bo[55],val[55];
VI li[55];

inline void Link(int u,int v){
	li[u].pb(v);
	li[v].pb(u);
}

inline void app(int x){
	// 加一个数维护基
	dto(i,9,0)if(x>>i&1){
		if(!base[i]){
			base[i]=x;
			break;
		}else x=x^base[i];
	}
}

inline int Main(){
	// 搜出连通块 
	int l=0,r=1;
	for(bo[g[l]=1]=1;l<r;){
		int u=g[l++];
		for(int v:li[u])if(!bo[v]){
			app(val[v]);
			bo[v]=1;
			g[r++]=v;
		}
	}
	app(val[1]);
	int ans=0;
	dto(i,9,0)ans=max(ans,ans^base[i]);
	return ans;
}

struct XorTravelingSalesman{
	int maxProfit(vector<int> a1,vector<string> a2){
		n=SZ(a1);
		For(i,1,n)val[i]=a1[i-1];
		For(i,1,n)For(j,i+1,n)if(a2[i-1][j-1]=='Y')Link(i,j);
		return Main();
	}
};