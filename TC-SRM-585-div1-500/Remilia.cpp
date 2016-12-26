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

int K,n,m,cnt[55],A[55],ga[1333],invga[1333],dp[1333];

inline void inc(int &x,int y){
	if((x+=y)>=mo)x-=mo;
}

inline int Pow(int x,int y){
	int z=1;
	for(;y;y>>=1,x=1ll*x*x%mo)if(y&1)z=1ll*z*x%mo;
	return z;
}

inline int binom(int n,int m){
	if(n<m)return 0;
	return 1ll*ga[n]*invga[m]%mo*invga[n-m]%mo;
}

int Main(){
	*ga=1;
	For(i,1,n)ga[i]=1ll*ga[i-1]*i%mo;
	For(i,0,n)invga[i]=Pow(ga[i],mo-2);
	dto(i,m,1)A[i]=A[i+1]+cnt[i];
	// 倒着DP，dp[i]表示划分成i段的方案数
	dp[0]=1;
	dto(i,m,1){
		dto(k,K,0)if(dp[k]){
			int xx=dp[k];
			dp[k]=0;
			/*
				有两种本质不同的位置：
				某段开头放k个：+k-1
				其他地方：+k
				枚举放了几段开头，组合数配进去转移
			*/
			For(p,0,min(cnt[i],k)){
				if(k+cnt[i]-p<=K)
					inc(dp[k+cnt[i]-p],1ll*xx*binom(k,p)%mo*binom(cnt[i]+A[i+1]-k,cnt[i]-p)%mo);
			}
		}
	}
	return dp[K];
	// 复杂度O(Kn)
}

struct LISNumber{
	int count(VI cds, int K){
		m=SZ(cds);
		For(i,1,m)cnt[i]=cds[i-1];
		for(int x:cds)n+=x;
		::K=K;
		return Main();
	}
};