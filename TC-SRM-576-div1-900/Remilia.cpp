// by ξ
// program sky  :)

#include <bits/stdc++.h>

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

void dpri(VI A){
	for(auto it:A)cerr<<it<<' ';
	cerr<<endl;
}

const int mo=1e9+9;

void inc(int&x,int y){if((x+=y)>=mo)x-=mo;}

int Pow(int x,int y){
	int z=1;
	for(;y;y>>=1,x=1ll*x*x%mo)if(y&1)z=1ll*z*x%mo;
	return z;
}

int n,m,W,Ans;
char A[22][22];
map<int,char> fafafa;
VI li;

int Main(){
	// decompose
	rep(i,0,n)rep(j,1-m,m){
		LL x=1ll*i*W+j;
		for(LL k=1;k*k<=x;++k)if(x%k==0){
			if(k<=W)li.pb(k);
			if(x/k<=W)li.pb(x/k);
		}
	}
	li.pb(0);
	sort(ALL(li));
	li.resize(unique(ALL(li))-li.begin());
	// brute force
	rep(it,1,SZ(li)){
		int L=li[it],R;
		fafafa.clear();
		rep(i,0,n)rep(j,0,m){
			int pos=(1ll*i*W+j)%L;
			if(fafafa.find(pos)!=fafafa.end()){
				if(fafafa[pos]!=A[i][j])goto loop;
			}else{
				fafafa[pos]=A[i][j];
			}
		}
		R=L-SZ(fafafa);
		if(R>=0)inc(Ans,Pow(26,R));
		loop:;
	}
	// 等比数列
	li.pb(W+1);
	LL inv=Pow(25,mo-2);
	rep(i,0,SZ(li)-1){
		int a=li[i]+1,b=li[i+1]-1;
		a-=n*m;b-=n*m;
		a=max(a,0);
		if(a<=b){
			inc(Ans,(Pow(26,b+1)-Pow(26,a)+mo)*inv%mo);
		}
	}
	return Ans;
}

struct CharacterBoard{
	int countGenerators(vector<string> fragment, int W, int i0, int j0){
		n=SZ(fragment);m=SZ(fragment[0]);
		rep(i,0,n)rep(j,0,m)A[i][j]=fragment[i][j];
		::W=W;
		return Main();
	}
};