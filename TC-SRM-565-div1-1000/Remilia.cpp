// by ξ
// program sky  :)

#include <map>
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

inline void inc(int &x,int y){if((x+=y)>=mo)x-=mo;}

int n;
VI A,B,C;

inline VI pre(VI&A,VI&B,VI&C){
	// gen possible len(A,B)
	int x=1e9,y=0,z=1e9;
	For(i,1,n)x=min(x,A[i]+B[i]),y=max(y,abs(A[i]-B[i])),z=min(z,A[i]+B[i]-2*C[i]);
	if(x<y)return VI{};
	if(y==x)return VI{x};
	if(y==0)return z>0 && z<x?VI{z,x}:VI{x};
	return z>y && z<x?VI{y,z,x}:VI{y,x};
}

inline int F(VI&A){
	// calc the ans of one special point
	sort(ALL(A));
	if(A[0]!=0 || SZ(A)>1 && A[1]==0)return 0;
	int j=0,ans=1;
	rep(i,1,SZ(A)){
		for(;A[j]<A[i];++j);
		ans=1ll*ans*j%mo;
	}
	return ans;
}

inline int gao1(int u){
	// make it legal
	For(i,1,n)if(i^u){
		if(A[i]+B[i]<A[u]+B[u])return 0;
		if(B[i]+C[i]<B[u]+C[u])return 0;
		if(A[i]+C[i]<A[u]+C[u])return 0;
	}
	map<int,VI> ma{{0,{0}},{A[u]+B[u],{0}}},mc{{0,{0}}};
	int ans=1;
	For(i,1,n)if(A[i]-B[i]==A[u]-B[u]){
		// sub [u,C]
		int l=A[i]+C[i]-A[u]-C[u];
		// make it legal
		if(l&1)return 0;l/=2;
		if(C[i]-l<0 || C[i]-l>C[u])return 0;
		mc[C[i]-l].pb(l);
	}else{
		// sub [A,B]-{u}
		int l=A[i]+B[i]-A[u]-B[u];
		// make it legal
		if(l&1)return 0;l/=2;
		if(C[i]<=C[u])return 0;
		if(A[i]-B[i]<A[u]-B[u] && B[i]-B[u]+C[u]!=C[i])return 0;
		if(A[i]-B[i]>A[u]-B[u] && A[i]-A[u]+C[u]!=C[i])return 0;
		ma[A[i]-l].pb(l);
	}
	// calc ans respectively
	for(auto&it:ma)ans=1ll*ans*F(it.y)%mo;
	for(auto&it:mc)ans=1ll*ans*F(it.y)%mo;
	return ans;
}

inline int gao2(int ab,int bc,VI&A,VI&B,VI&C){
	int ans=1;
	map<int,VI> mm{{0,{0}},{ab,{0}},{ab+bc,{0}}};
	For(i,1,n)if(A[i]-B[i]>=ab){
		// sub [B,C]
		int l=B[i]+C[i]-bc;
		// make it legal
		if(l&1)return 0;l/=2;
		if(l<0 || B[i]<l || C[i]<l || A[i]-l<ab)return 0;
		if(A[i]!=B[i]+ab)return 0;
		mm[A[i]-l].pb(l);
	}else{
		// sub [A,B)
		int l=A[i]+B[i]-ab;
		// make it legal
		if(l&1)return 0;l/=2;
		if(l<0 || B[i]<l || C[i]-l<=bc || A[i]<l)return 0;
		if(B[i]+bc!=C[i])return 0;
		mm[A[i]-l].pb(l);
	}
	// calc ans respectively
	for(auto&it:mm)ans=1ll*ans*F(it.y)%mo;
	return ans;
}

inline int Main(){
	// case 1 : star
	int u=1,ans=0;
	For(i,2,n)if(A[i]+B[i]+C[i]<A[u]+B[u]+C[u])u=i;
	inc(ans,gao1(u));
	// case 2 : chain
	VI ab=pre(A,B,C),bc=pre(B,C,A),ac=pre(A,C,B);
	for(int x:ab)for(int y:ac)for(int z:bc){
		if(x==y+z)inc(ans,gao2(y,z,A,C,B));
		else if(y==x+z)inc(ans,gao2(x,z,A,B,C));
		else if(z==x+y)inc(ans,gao2(x,y,B,A,C));
	}
	return ans;
}

struct UnknownTree{
	int getCount(VI dA,VI dB,VI dC){
		n=SZ(dA);
		A.resize(n+1);B.resize(n+1);C.resize(n+1);
		For(i,1,n)A[i]=dA[i-1],B[i]=dB[i-1],C[i]=dC[i-1];
		return Main();
	}
};