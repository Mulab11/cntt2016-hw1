// by ξ
// program sky  :)

#include <vector>
#include <bitset>
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

int n,m,pre[666];
bitset<2555> dp[55];
VI c;

struct KingdomAndDice{
	db newFairness(VI A,VI B,int X){
		n=SZ(A);
		c=VI{-1,X+1};
		// 初始贡献
		int tmp=0;
		for(int x:A)if(x){
			for(int y:B)tmp+=y<x;
			c.pb(x);
		}else ++m;
		for(int x:B)c.pb(x);
		sort(ALL(c));
		for(int x:B){
			rep(i,0,SZ(c))if(c[i]==x)++pre[i];
		}
		rep(i,1,SZ(c))pre[i]+=pre[i-1];
		// 背包
		For(i,0,m)dp[i][tmp]=1;
		rep(i,1,SZ(c)-1){
			rep(j,c[i]+1,min(c[i+1],c[i]+1+m)){
				dto(k,m,1)dp[k]|=dp[k-1]<<pre[i];
			}
		}
		// 找离中间最近的答案
		int K=n*n;
		if(~K&1 && dp[m][K>>1])return 0.5;
		int i=(K-1)/2,j=K/2+1;
		for(;~i;--i,++j){
			if(dp[m][i])return 1.*i/K;
			if(dp[m][j])return 1.*j/K;
		}
	}
};