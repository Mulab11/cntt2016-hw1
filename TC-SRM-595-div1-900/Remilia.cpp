// by ξ
// program sky  :)

#include <cmath>
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
db P[55];

struct ww{
	int x,y;
	ww operator - (ww A){return {x-A.x,y-A.y};}
	int operator ^ (ww A){return x*A.y-y*A.x;}
	db len(){return sqrt(x*x+y*y);}
}p[55];

bool Ponl(ww A,ww B,ww C){
	return fabs((A-B).len()+(A-C).len()-(B-C).len())<1e-9;
}

db Main(){
	db ans=0;
	// 枚举凸包上相邻的两个点
	For(i,1,n)For(j,1,n)if(i^j){
		// 这两个点要存在
		db pp=P[i]*P[j]*(p[i]^p[j]);
		For(k,1,n)if(k^i && k^j){
			// 这两个点之间不能有点
			if(Ponl(p[k],p[i],p[j]))pp*=1-P[k];
			// 这两个点右侧不能有点
			else if(((p[k]-p[i])^(p[j]-p[i]))>0)pp*=1-P[k];
		}
		ans+=pp;
	}
	return ans;
}

struct Constellation{
	db expectation(VI x,VI y,VI prob){
		n=SZ(x);
		For(i,1,n)p[i]={x[i-1],y[i-1]},P[i]=prob[i-1]*.001;
		return Main()/2;
	}
};