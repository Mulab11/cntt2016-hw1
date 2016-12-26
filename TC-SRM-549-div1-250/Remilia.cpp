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

int n,m;

namespace bip{
	VI li[55];
	int mx[55],my[55],vis[55];
	inline void append(int u,int v){
		li[u].pb(v);
	}
	// 匈牙利算法
	bool gao(int u){
		if(vis[u])return 0;
		vis[u]=1;
		for(int v:li[u])if(!my[v] || gao(my[v])){
			mx[u]=v;my[v]=u;
			return 1;
		}
		return 0;
	}
	inline int Main(){
		int ans=0;
		For(i,1,n)if(!mx[i]){
			For(i,1,n)vis[i]=0;
			ans+=gao(i);
		}
		return ans;
	}
}

struct PointyWizardHats{
	int getNumHats(VI h,VI r,VI hh,VI rr){
		n=SZ(h);m=SZ(hh);
		// 如果一个圆锥可以放，就二分图里连一条边
		rep(i,0,n)rep(j,0,m)if(r[i]<rr[j] && h[i]*rr[j]>hh[j]*r[i])bip::append(i+1,j+1);
		return bip::Main();
	}
};