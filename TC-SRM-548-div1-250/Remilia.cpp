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

int n;
LL a[55],b[55];

inline bool ok(int X){
	// 贪心变小
	For(i,1,n)b[i]=a[i];
	For(i,1,n){
		if(a[i]+X<=b[i-1])return 0;
		b[i]=max(b[i-1]+1,a[i]-X);
	}
	return 1;
}

struct KingdomAndTrees{
	int minLevel(VI h){
		n=SZ(h);
		For(i,1,n)a[i]=h[i-1];
		//二分答案
		int l=-1,r=2e9;
		for(;l+1<r;){
			int m=(l+0ll+r)/2;
			if(ok(m))r=m;else l=m;
		}
		return r;
	}
};