// BEGIN CUT HERE

// END CUT HERE
#line 5 "MegaFactorial.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
int fast_pow(int x,int y,int P){
	int ret=1;
	while (y){
		if (y&1) ret=1LL*ret*x%P;
		x=1LL*x*x%P;
		y>>=1;
	}
	return ret;
}

int P;

struct matrix{
	int x,y,a[20][20];
	matrix(){}
	matrix(int _x,int _y):x(_x),y(_y){
		memset(a,0,sizeof(a));
	}
	matrix(int _sz):x(_sz),y(_sz){
		memset(a,0,sizeof(a));
		for (int i=0;i<_sz;++i) a[i][i]=1;
	}
	void print(){
		printf("x:%d y:%d\n",x,y);
		for (int i=0;i<x;++i,puts(""))
			for (int j=0;j<y;++j)
				printf("%d ",a[i][j]);
	}
};
inline matrix operator *(const matrix &u,const matrix &v){
	matrix ret=matrix(u.x,v.y);
	int z=u.y;
	for (int i=0;i<ret.x;++i)
		for (int j=0;j<ret.y;++j)
			for (int k=0;k<z;++k)
				(ret.a[i][j]+=(ll)u.a[i][k]*v.a[k][j]%P)%=P;
	return ret;
}

matrix fast_pow(matrix x,int y){
	matrix ret=matrix(x.x);
	while (y){
		if (y&1) ret=ret*x;
		x=x*x;
		y=y>>1;
	}
	return ret;
}


class MegaFactorial{
	matrix A[50],B[50],T;
	int solve(int n,int k,int b,int mod){
		P=mod;
		T=matrix(k+1,k+1);
		for (int i=0;i<k;++i)for (int j=0;j<=i;++j)
			T.a[i][j]=1;
		T.a[k][k]=1;
		A[0]=T;
		B[0]=matrix(k+1);
		ll bin=b;
		int i=1;
		for (;bin<=n;++i,bin*=b){
			B[i]=B[i-1];
			for (int j=1;j<b;++j) B[i]=B[i]*A[i-1];
			for (int j=0;j<k;++j) T.a[j][k]=i;
			A[i]=T*B[i];
//			A[i].print();
//			printf("%d %d %lld\n",n,b,bin);
		}
		T=matrix(k+1);
		for (;n;bin/=b,--i)
			for (;bin<=n;n-=bin) T=A[i]*T;
		return T.a[k-1][k];
	}
	public:
	int countTrailingZeros(int N, int K, int B){
		const int mod=1000000009;
		if (B==10) B=5;
		if (B==6) B=3;
		int t=1;
		if (B==9) t=2,B=3;
		if (B==8) t=3,B=2;
		if (B==4) t=2,B=2;
//		return solve(N,K,B,mod);
		return 1LL*(solve(N,K,B,mod)-solve(N,K,B,t)+mod)*fast_pow(t,mod-2,mod)%mod;
	}
};
