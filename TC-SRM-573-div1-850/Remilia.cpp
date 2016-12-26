// by ¦Î

#include <bits/stdc++.h>

#define Rin register int
#define oo (c=getchar())
#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define sqr(x) (x)*(x)
#define ALL(V) V.begin(),V.end()
#define pb push_back
#define x first
#define y second

using namespace std;

typedef double db;
typedef long long LL;
typedef pair<int ,int> PII;
typedef pair<db ,db> PDD;
typedef vector<int> VI;
typedef vector<PII> VII;

const int p=1e9+7;

int n,T,fac[200005],Invfac[200005];
VI x,y;

struct WolfPack{
	void inc(int &x,int y){
		if((x+=y)>=p)x-=p;
	}
	void pro(int &x,int y){
		x=1ll*x*y%p;
	}
	int Pow(int x,int y){
		int z=1;
		for(;y;y>>=1,pro(x,x))if(y&1)pro(z,x);
		return z;
	}
	int C(int N,int M){
		// binomial
		if(M<0 || M>N)return 0;
		return 1ll*fac[N]*Invfac[M]%p*Invfac[N-M]%p;
	}
	int __(int x){
		if(x+T&1)return 0;
		return C(T,T+x>>1);
	}
	int suan(VI x){
		int an=0;
		For(i,x[0]-T,x[0]+T){
			int tmp=1;
			rep(j,0,n)pro(tmp,__(abs(x[j]-i)));// mul
			inc(an,tmp);
		}return an;
	}
	int calc(VI _x,VI _y,int _m){
		x=_x;y=_y;T=_m;n=x.size();
		*fac=1;
		For(i,1,200000)fac[i]=1ll*fac[i-1]*i%p;
		Invfac[200000]=Pow(fac[200000],p-2);
		for(int i=200000;i;--i)Invfac[i-1]=1ll*Invfac[i]*i%p;
		rep(i,0,n){
			int xx=x[i]-y[i],yy=x[i]+y[i];// rotate
			x[i]=xx;y[i]=yy;
		}
		return 1ll*suan(x)*suan(y)%p;// calculate the ans of x aixs and y axis ,then multiply them
	}
};

