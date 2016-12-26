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

int n;
LL rk,a[66],base[66];

inline LL Main(){
	For(i,1,n){
		dto(j,60,0)if(a[i]>>j&1){
			if(base[j])a[i]^=base[j];
			else{
				base[j]=a[i];
				++rk;
				break;
			}
		}
	}
	//Gauss
	For(j,0,60)For(k,j+1,60)
		base[k]=min(base[k],base[k]^base[j]);
	//Jordan
	LL T=0,ans=0;
	For(j,0,60)T^=base[j];
	//norm
	ans=T;
	dto(j,60,0)if(base[j]){
		rep(k,0,j)if(base[k])ans+=T^base[k];
		return ans+T*(n-rk);
	}
	//independent set
	return 0;
}

struct XorAndSum{
	LL maxSum(vector<LL> num){
		n=num.size();
		For(i,1,n)a[i]=num[i-1];
		return Main();
	}
};