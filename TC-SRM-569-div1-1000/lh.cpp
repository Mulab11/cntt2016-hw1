#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

struct matrix{
	static const int maxn=18;
	static long long use[maxn][maxn];
	long long a[maxn][maxn];
	int mod;
	void setmod(int x){mod=x;}
	void mul(matrix &x,int mod){
		memset(use,0,sizeof(use));
		for (int i=1;i<=16;++i){
			use[i][0]=a[i][0];
			for (int j=1;j<=i;++j)
			for (int k=0;k<=j;++k) use[i][k]=(use[i][k]+a[i][j]*x.a[j][k])%mod;
		}
		memcpy(a,use,sizeof(a));
	}
	void calc(matrix &x,int mod){
		memset(use[0],0,sizeof(use[0]));
		for (int i=1;i<=16;++i){
			use[0][i]=x.a[i][0];
			for (int j=1;j<=i;++j) use[0][i]=(use[0][i]+x.a[i][j]*a[0][j])%mod;
		}
		memcpy(a[0],use[0],sizeof(a[0]));
		return;
	}
//	void print(int lim){
//		for (int i=1;i<=lim;++i){
//			printf("%d:",i);
//			for (int j=0;j<=i;++j) printf(" a[%d]=%lld",j,a[i][j]);
//			puts("");
//		}
//	}
};
long long matrix::use[maxn][maxn];

class MegaFactorial{
	long long power(long long a,int b,int mod){
		long long ret=1;
		while(b){
			if (b&1) ret=ret*a%mod;
			a=a*a%mod;
			b>>=1;
		}
		return ret;
	}
	
	matrix power(matrix a,int b,int mod){
		matrix ret=a;
		for (int i=1;i<b;++i) ret.mul(a,mod);
		return ret;
	}
	
	matrix A,C,sav[30];
	long long pw[30];
	
	long long ask(int n,int k,int p,int mod){
//		printf("ask %d,%d,%d,%d\n",n,k,p,mod);
		memset(A.a,0,sizeof(A.a));
		memset(C.a,0,sizeof(C.a));
		for (int i=1;i<=16;++i)
		for (int j=1;j<=i;++j) C.a[i][j]=1;
		sav[0]=C;
		pw[0]=1;
		int i;
		for (i=1;i<30;++i){
			pw[i]=pw[i-1]*p;
			if (pw[i]>n) break;
			C=power(C,p,mod);
			for (int j=1;j<=16;++j) C.a[j][0]=(C.a[j][0]+1)%mod;
//			printf("2^%d:\n",i);
//			C.print(2);
			sav[i]=C;
		}
		for (i=i-1;i>=0;--i){
//			printf("n=%d,pw[%d]=%lld\n",n,i,pw[i]);
			while (n>=pw[i]){
				A.calc(sav[i],mod);
				n-=pw[i];
			}
		}
		return A.a[0][k];
	}
	
	int solve(int N,int K,int p,int c){
		if (c==1) return ask(N,K,p,1000000009);
		else
		return (ask(N,K,p,1000000009)-ask(N,K,p,c)+1000000009)*power(c,1000000007,1000000009)%1000000009;
	}
	
	public:
		int countTrailingZeros(int N, int K, int B){
			if (B%7==0) return solve(N,K,7,1);
			else if (B%5==0) return solve(N,K,5,1);
			else if (B==9) return solve(N,K,3,2);
			else if (B%3==0) return solve(N,K,3,1);
			else{
				int cnt=0;
				while(B%2==0){
					B/=2;
					++cnt;
				}
				return solve(N,K,2,cnt);
			}
		}
};
