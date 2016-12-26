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

const db pi=acos(-1);

int n,a[33],b[33];
VI c;
cpx A[33],B[33],w[33],tmp[33];

// 离散傅里叶变换与其逆变换
void DFT(cpx* A){
	rep(i,0,n){
		cpx x=1;
		tmp[i]=0;
		rep(j,0,n)tmp[i]+=x*A[j],x*=w[i];
	}
	rep(i,0,n)A[i]=tmp[i];
}
void IDFT(cpx* A){
	rep(i,0,n){
		cpx x=1;
		tmp[i]=0;
		rep(j,0,n)tmp[i]+=x*A[j],x*=w[n-i];
		tmp[i]/=n;
	}
	rep(i,0,n)A[i]=tmp[i];
}

VI Main(){
	// 单位复根
	For(i,0,n)w[i]=cpx(cos(2*pi/n*i),sin(2*pi/n*i));
	rep(i,0,n)A[i]=a[i];
	DFT(A);
	rep(i,0,n)A[i]=sqrt(A[i]);
	int m=n/2+1;
	rep(mask,0,1<<m){
		// 枚举根的正负号
		rep(i,0,n)if(i<m)
			B[i]=mask>>i&1?A[i]:-A[i];
		else B[i]=B[n-i];
		// 进行逆变换还原B
		IDFT(B);
		rep(i,0,n)b[i]=int(B[i].real()+0.5);
		rep(i,0,n){
			int xx=a[i];
			rep(j,0,n)xx-=b[j]*b[(i-j+n)%n];
			if(xx)goto loop;
		}
		rep(i,0,n)if(b[i]!=b[(n-i)%n])goto loop;
		// 找到一组解，更新答案
		if(!SZ(c)){
			c=VI(b,b+n);
		}else{
			if(lexicographical_compare(b,b+n,ALL(c))){
				c=VI(b,b+n);
			}
		}
		loop:;
	}
	return SZ(c)?c:VI{-1};
}

struct SplittingFoxes2{
	VI getPattern(VI a){
		n=SZ(a);
		rep(i,0,n)::a[i]=a[i];
		return Main();
	}
};