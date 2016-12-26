// by ξ
// program sky  :)

#include <vector>
#include <stdio.h>
#include <cassert>
#include <cstring>
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

const int mo=1e9+7;

int n,X,A[55],dp[55][2][2];

inline void inc(int &x,int y){if((x+=y)>=mo)x-=mo;}

inline int Pow(int x,int y){
	int z=1;
	for(;y;y>>=1,x=1ll*x*x%mo)if(y&1)z=1ll*z*x%mo;
	return z;
}

inline int Main(){
	int ans=[=](){
		int x=0;
		For(i,1,n)x^=A[i];
		return x==X;
	}();
	dto(i,30,0){// enumerate the breakpoint
		memset(dp,0,sizeof dp);
		***dp=1;
		rep(j,0,n)rep(k,0,2)rep(l,0,2)if(dp[j][k][l]){
			int x=A[j+1]&((1<<i)-1);
			if(A[j+1]>>i&1){
				inc(dp[j+1][k][1],1ll*dp[j][k][l]*(1<<i)%mo);// when use 0
				inc(dp[j+1][k^1][l],1ll*dp[j][k][l]*(x+1)%mo);// use 1
			}else{
				inc(dp[j+1][k][l],1ll*dp[j][k][l]*(x+1)%mo);// use 0
			}
		}
		inc(ans,dp[n][X>>i&1][1]*1ll*Pow(1<<i,mo-2)%mo);// calc
		if(!dp[n][X>>i&1][0])break;// i-1 can't be the breakpoint
	}
	return ans;
}

struct DefectiveAddition{
	int count(VI cards,int X){
		n=SZ(cards);
		For(i,1,n)A[i]=cards[i-1];
		::X=X;
		return Main();
	}
};