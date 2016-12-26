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

int m,d;
LL mo,p,n,pp[66];

LL inc(LL&x,LL c=1){x=(x+c)%mo;}

struct mat{
	LL a[66][66];
	LL *operator [] (int x){
		return a[x];
	}
	mat(){}
	mat(bool f){
		For(i,0,d)For(j,0,d)a[i][j]=i==j && f;
	}
	mat operator * (mat B){
		// matrix product
		mat C=mat(0);
		For(i,0,d)For(k,0,d)For(j,0,d)
			inc(C[i][j],a[i][k]*B[k][j]%mo);
		return C;
	}
	mat operator ^ (LL y){
		// matrix power
		mat z=mat(1),x=*this;
		for(;y;y>>=1,x=x*x)if(y&1)z=z*x;
		return z;
	}
}A,mm[66];

LL Main(){
	for(LL j=1;j<=n;j*=p,++m)pp[m]=j;--m;
	mm[0][0][0]=1;
	For(i,1,d)For(j,i,d)mm[0][i][j]=1;
	For(i,1,m){
		mm[i]=mm[i-1]^p;
		For(j,1,d)inc(mm[i][0][j]);// =_=
	}
	A=mat(1);
	dto(i,m,0){
		LL t=n/pp[i];
		if(t)A=A*(mm[i]^t);// p-based power
		n%=pp[i];
	}
	return A[0][d];
}

struct MegaFactorial{
	int countTrailingZeros(int N,int K,int B){
		mo=1e9+9;
		p=VI{0,0,2,3,2,5,3,7,2,3,5}[B];
		int c=VI{0,0,1,1,2,1,1,1,3,2,1}[B];
		mo*=c;
		d=K;
		n=N;
		return Main()/c;
	}
};