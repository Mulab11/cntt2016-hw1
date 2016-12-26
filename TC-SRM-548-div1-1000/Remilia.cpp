// by ξ
// program sky  :)

#include <vector>
#include <stdio.h>
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

#include <cstring>
#define clr(a) memset(a,0,sizeof a)

const int mo=1e9+7;

inline void inc(int &x,int y){if((x+=y)>=mo)x-=mo;}
inline void dec(int &x,int y){if((x-=y)<0)x+=mo;}

int binom[2555][2555],DP[55][55],dp[55][55];

inline int f(int n,int m){
	return binom[binom[n][2]][m];
	// n个点，m条边的无向图个数
}

inline int ff(int n,int m){
	return binom[binom[n+2][2]][m];
	// n个点，一个2-pack，m条边的无向图个数
}

inline void pret(){
	For(i,0,2500){
		*binom[i]=1;
		For(j,1,i)binom[i][j]=(binom[i-1][j-1]+binom[i-1][j])%mo;
	}
	//组合数
	DP[0][0]=DP[0][1]=1;
	For(i,1,50)For(j,0,50){
		DP[i][j]=ff(i,j);
		rep(k,0,i)
		For(l,0,j)
		dec(DP[i][j],1ll*binom[i][k]*DP[k][l]%mo*f(i-k,j-l)%mo);
	}
}

inline int gao0(int n,int K){
	// n个点，m条边的无向连通图个数
	if(n<0 || K<0)return 0;
	clr(dp);
	dp[0][0]=1;
	For(i,1,n)For(j,0,K){
		dp[i][j]=f(i,j);
		rep(k,1,i)
		For(l,0,j)
		dec(dp[i][j],1ll*binom[i-1][k-1]*dp[k][l]%mo*f(i-k,j-l)%mo);
	}
	return dp[n][K];
}

inline int gao1(int n,int K){
	// n个点，一个2-pack，m条边的无向连通图个数
	if(n<0 || K<0)return 0;
	return DP[n][K];
}

inline int fff(int n,int m){
	return binom[binom[n+3][2]][m];
	// n个点，一个3-pack，m条边的无向图个数
}

inline int gao3(int n,int K){
	// n个点，一个3-pack，m条边的无向连通图个数
	if(n<0 || K<0)return 0;
	clr(dp);
	For(i,0,binom[3][2])dp[0][i]=binom[binom[3][2]][i];
	For(i,1,n)For(j,0,K){
		dp[i][j]=fff(i,j);
		rep(k,0,i)
		For(l,0,j)
		dec(dp[i][j],1ll*binom[i][k]*dp[k][l]%mo*f(i-k,j-l)%mo);
	}
	return dp[n][K];
}

inline int ffff(int n,int m){
	return binom[binom[n+4][2]][m];
	// n个点，一个4-pack，m条边的无向图个数
}

inline int gao2(int n,int K){
	// n个点，两个2-pack，m条边的无向连通图个数
	if(n<0 || K<0)return 0;
	clr(dp);
	For(i,0,binom[4][2])dp[0][i]=binom[binom[4][2]][i];
	For(i,1,n)For(j,0,K){
		dp[i][j]=ffff(i,j);
		rep(k,0,i)
		For(l,0,j)
		dec(dp[i][j],1ll*binom[i][k]*dp[k][l]%mo*f(i-k,j-l)%mo);
	}
	// 先算一个4-pack的方案数
	int res=dp[n][K];
	For(i,0,n)For(k,0,K)dec(res,1ll*binom[n][i]*DP[i][k]%mo*DP[n-i][K-k]%mo);
	// 减去两个2-pack不连通的情况
	return res;
}

struct KingdomAndCities{
	int howMany(int n,int m,int K){
		pret();
		if(m==0)return gao0(n,K);
		if(m==1)return 1ll*binom[n-1][2]*gao1(n-3,K-2)%mo;
		int ans=1ll*(n-2)*gao0(n-2,K-3)%mo;
		inc(ans,2ll*binom[n-2][2]%mo*gao1(n-4,K-3)%mo);
		inc(ans,1ll*binom[4][2]*binom[n-2][4]%mo*gao2(n-6,K-4)%mo);
		inc(ans,6ll*binom[n-2][3]%mo*gao3(n-5,K-4)%mo);
		inc(ans,1ll*binom[n-2][2]*gao1(n-4,K-4)%mo);
		// 讨论m个特殊点的出边情况
		return ans;
	}
};