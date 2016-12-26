// by ξ
// program sky  :)

#include <vector>
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
typedef pair<db ,db> cpx;
typedef vector<int> VI;
typedef vector<PII> VII;

const int mo=1e9+9;

int n,m,A[22],B[22],dp[9][9][1<<16];

void inc(int &x,int y){
	if((x+=y)>=mo)x-=mo;
}
int bit(int x,int i){
	// 取出第i位
	return x>> (2*(i-1)) & (3);
}
int clr(int x,int i){
	// 清除第i位
	return x-(bit(x,i)<<2*(i-1));
}
int jia(int x,int i,int y){
	// 修改第i位（已经清除的情况下）
	return x+(y<<2*(i-1));
}

int Main(){
	if(A[1]^B[1])return 0;
	dp[1][1][3]=1;
	For(i,1,n)For(j,1,m)if(i>1 || j>1){
		int *F=dp[i][j],*G=j==1?dp[i-1][m]:dp[i][j-1];
		rep(mask,0,1<<(2*m))if(G[mask]){
			if(A[i+j-1]==B[i+j-1]){
				// 1种字符能转移两个，25种不转移
				int xx=clr(mask,j),yy=0;
				if(j>1)yy|=bit(mask,j-1);
				yy|=bit(mask,j);
				inc(F[jia(xx,j,yy)],G[mask]);
				inc(F[xx],G[mask]*25ll%mo);
			}else{
				// 2种字符各转移一个，24种不转移
				int xx=clr(mask,j),yy=0;
				if(j>1)yy|=bit(mask,j-1);
				yy|=bit(mask,j);
				inc(F[jia(xx,j,yy&1)],G[mask]);
				inc(F[jia(xx,j,yy&2)],G[mask]);
				inc(F[xx],G[mask]*24ll%mo);
			}
		}
	}
	int ans=0;
	rep(mask,0,1<<(2*m))if(bit(mask,m)==3){
		inc(ans,dp[n][m][mask]);
	}
	return ans;
}

struct StringPath{
	int countBoards(int n, int m, string A, string B){
		::n=n;::m=m;
		For(i,1,n+m-1)::A[i]=A[i-1],::B[i]=B[i-1];
		return Main();
	}
};