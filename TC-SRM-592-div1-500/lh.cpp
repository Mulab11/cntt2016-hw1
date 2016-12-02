#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class LittleElephantAndPermutationDiv1{
	static const int maxn=52,maxm=1275+10,mod=1000000007;
	int dp[maxn][maxn][maxm<<1];
	int zero;
	
	int &f(int a,int b,int c){
		if (a<b) return zero=0;
		if (b<0) return zero=0;
		if (c<-1275||c>1275) return zero=0;
		return dp[a][b][c+1280];
	}
	
	void MOD(int &a){
		if (a>=mod) a-=mod;
		return;
	}
	
	long long frac(int n){
		long long ret=1;
		for (int i=2;i<=n;++i) ret=ret*i%mod;
		return ret;
	}
	
	public:
		int getNumber(int N, int K){
			memset(dp,0,sizeof(dp));
			f(1,0,-1)=f(1,1,0)=1;
			for (int i=2;i<=N;++i)
			for (int j=0;j<=i;++j)
			for (int k=-1275;k<=1275;++k){
				f(i,j,k)=f(i-1,j-1,k);
				MOD(f(i,j,k)+=(long long)f(i-1,j-2,k-i)*(i-j+1)*(i-j+1)%mod);
				MOD(f(i,j,k)+=(long long)f(i-1,j-1,k)*(i-j)%mod);
				MOD(f(i,j,k)+=(long long)f(i-1,j-1,k)*(i-j)%mod);
				MOD(f(i,j,k)+=f(i-1,j,k+i));
//				if (f(i,j,k)) printf("f(%d,%d,%d)=%d\n",i,j,k,f(i,j,k));
			}
			int ret=0;
			int tmp=(1+N)*N/2;
			for (int i=K-tmp;i<=1275;++i) MOD(ret+=f(N,N,i));
			return ret*frac(N)%mod;
		}
};
