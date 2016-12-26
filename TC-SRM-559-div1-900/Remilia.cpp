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

const db pi=acos(-1),eps=1e-9;

int n;

struct ww{
	db x,y;
	db operator * (ww A){return x*A.x+y*A.y;}
	db operator ^ (ww A){return x*A.y-y*A.x;}
	ww operator - (ww A){return {x-A.x,y-A.y};}
	db len(){return sqrt(x*x+y*y);}
	db jj(){return atan2(y,x);}
}p[55];
db r[55];

vector<cpx> g;

inline void append(db a,db b){
	assert(b-a<2*pi);
	for(;b>=pi;b-=2*pi);
	for(;b<-pi;b+=2*pi);
	for(;a>=pi;a-=2*pi);
	for(;a<-pi;a+=2*pi);
	if(a<=b)g.pb({a,b});
	else{
		g.pb({a,pi});
		g.pb({-pi,b});
	}
}

inline bool ck(db L){
	g.resize(0);
	rep(i,1,n)if(L+r[i]+r[0]>=p[i].len()){// if touches
		db a=p[i].jj()-acos(r[0]/p[i].len()),b=p[i].jj()+acos(r[0]/p[i].len());// target line
		ww P={r[0]*cos(a),r[0]*sin(a)};
		if((P-p[i]).len()>=L+r[i]){// in
			db ang=acos((r[0]*r[0]+p[i].x*p[i].x+p[i].y*p[i].y-(L+r[i])*(L+r[i]))/(2*r[0]*p[i].len()));// intersect
			append(p[i].jj()-ang,p[i].jj()+ang);
		}else{
			db ang=(L+r[i]-(P-p[i]).len())/r[0];// go cir
			a-=ang;b+=ang;
			if(b-a>=2*pi)return 0;
			append(a,b);
		}
	}
	g.pb({pi,pi});
	sort(ALL(g));
	db ma=-pi;
	for(auto it:g){// cover it all
		if(!(ma>=it.x || fabs(ma-it.x)<eps))return 1;
		ma=max(ma,it.y);
	}
	return 0;
}

struct CircusTents{
	db findMaximumDistance(VI x,VI y,VI r){
		n=x.size();
		rep(i,0,n)p[i]={1.*x[i]-x[0],1.*y[i]-y[0]},::r[i]=1.*r[i];// let p[0] be origin
		db ll=0,rr=1e9;
		For(xx,1,100){// binary search
			db mm=(ll+rr)/2;
			if(ck(mm))ll=mm;else rr=mm;
		}
		return ll;
	}
};