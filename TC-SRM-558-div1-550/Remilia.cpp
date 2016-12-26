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

int n,m,rx[333];
struct ww{
	int x,y;
	ww operator - (ww A){
		return {x-A.x,y-A.y};
	}
	LL operator ^ (ww A){
		return 1ll*x*A.y-1ll*y*A.x;
	}
}p[333];

LL cr(int u,int v){
	LL ans=0,tmp=0;
	For(i,1,n){
		ww A={rx[i],0};
		if(((p[u]-A)^(p[v]-A))>0 && rx[i]>p[u].x)ans+=tmp;
		if(rx[i]>p[v].x)++tmp;
	}
	return ans;
}

LL cl(int u,int v){
	LL ans=0,tmp=0;
	dto(i,n,1){
		ww A={rx[i],0};
		if(((p[u]-A)^(p[v]-A))<0 && rx[i]<p[u].x)ans+=tmp;
		if(rx[i]<p[v].x)++tmp;
	}
	return ans;
}

LL Main(){
	LL ans=0;
	sort(rx+1,rx+n+1);
	For(i,1,m)For(j,1,m)if(p[j].y<p[i].y){
		ans+=cl(i,j)*cr(i,j);
	}
	return ans;
}

VI Convert(vector<string> a){
	VI A{0};
	string ss="";
	for(auto xx:a)ss+=xx;
	for(auto c:ss){
		int &x=*A.rbegin();
		if(isdigit(c))x=x*10+c-48;else A.pb(0);
	}
	return A;
}

struct Ear{
	LL getCount(vector<string> a,vector<string> b,vector<string> c){
		VI rx=Convert(a),x=Convert(b),y=Convert(c);
		n=SZ(rx);m=SZ(x);
		For(i,1,n)::rx[i]=rx[i-1];
		For(i,1,m)p[i]={x[i-1],y[i-1]};
		return Main();
	}
};