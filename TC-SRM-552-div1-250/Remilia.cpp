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

struct FoxPaintingBalls{
	LL theMax(LL A,LL B,LL C, int N){
		// 每个至少要放的个数
		LL t=(N+1ll)*N/6;
		// 一个约束
		LL tmp=min(min(A,B),C);
		if(t==0)tmp=~0llu>>1;else tmp/=t;
		// 另一个约束
		if(N%3==1)return min(tmp,(A+B+C)/(3*t+1));
		return tmp;
	}
};