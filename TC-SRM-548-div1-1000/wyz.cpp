// BEGIN CUT HERE

// END CUT HERE
#line 5 "KingdomAndCities.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
#define P 1000000007
int fast_pow(int x,int y){
	int ret=1;
	while (y){
		if (y&1) ret=1LL*ret*x%P;
		x=1LL*x*x%P;
		y>>=1;
	}
	return ret;
}

#define inc(x,y) if(((x)+=(y))>=P)(x)-=P;
#define dec(x,y) if(((x)-=(y))<0)(x)+=P;

const int maxn2=1250;
const int maxn=55;
int c[maxn2+5][maxn2+5];
int e[maxn];
int dp[maxn][maxn];
void init(int n,int m){
	memset(c,0,sizeof(c));
	for (int i=0;i<=maxn2;++i){
		c[i][0]=1;
		for (int j=1;j<=i;++j)
			if ((c[i][j]=c[i-1][j]+c[i-1][j-1])>=P) c[i][j]-=P;
	}
	for (int i=0;i<=50;++i) e[i]=c[i][2];
	
	memset(dp,0,sizeof(dp));
//	dp[0][0]=1;
	for (int i=1;i<=n;++i)for (int j=i-1;j<=m;++j){
		dp[i][j]=c[e[i]][j];
		for (int x=1;x<i;++x)for (int y=x-1;y<=j;++y){
			int tmp=1LL*c[i-1][x-1]*dp[x][y]%P*c[e[i-x]][j-y]%P;
			dec(dp[i][j],tmp);
		}
	}
}

const int inv2=(P+1)/2;

class KingdomAndCities{
	public:
	int howMany(int N, int M, int K){
		if (K<N-1) return 0;
		if (N==M) return 0;
		init(N,K);
		if (M==0) return dp[N][K];
		if (M==1){
			int ret=1LL*dp[N-1][K-2]*c[N-1][2]%P,tmp,ret2=0;
			for (int i=1;i<N-1;++i)for (int j=0;j<=K-2;++j){
//				if (i==N-1-i&&j>K-2-j) continue;
				tmp=1LL*dp[i][j]*dp[N-1-i][K-2-j]%P*c[N-1][i]%P*i*(N-1-i)%P;
//				tmp=1LL*tmp*(i<N-1-i||j<K-2-j?c[N-1][i]:c[N-2][i-1])%P;
				inc(ret2,tmp);
			}
			ret2=1LL*ret2*inv2%P;
			inc(ret,ret2);
			return ret;
		}
		int ret=1LL*dp[N-2][K-3]*(N-2)*(N-2)%P,tmp,ret2=0;
		for (int i=1;i<N-2;++i)for (int j=0;j<=K-3;++j){
			tmp=1LL*dp[i][j]*dp[N-2-i][K-3-j]%P*c[N-2][i]%P*i*(N-2-i)%P;
			inc(ret,tmp);
		}
		tmp=1LL*dp[N-2][K-4]*c[N-2][2]*c[N-2][2]%P;
		inc(ret,tmp);
		for (int i=1;i<N-2;++i)for (int j=0;j<=K-4;++j){
			tmp=2LL*dp[i][j]*dp[N-2-i][K-4-j]%P*c[N-2][i]%P*i*(N-2-i)*c[i][2]%P;
			inc(ret,tmp);
		}
		for (int i=1;i<N-2;++i)for (int j=0;j<=K-4;++j){
//			if (i==N-2-i&&j>K-4-j) continue;
			tmp=1LL*dp[i][j]*dp[N-2-i][K-4-j]%P*c[N-2][i]%P*i*i*(N-2-i)*(N-2-i)%P;
//			tmp=1LL*tmp*(i<N-2-i||j<K-4-j?c[N-2][i]:c[N-3][i-1])%P;
			inc(ret2,tmp);
		}
		ret2=1LL*ret2*inv2%P;
		inc(ret,ret2);
		for (int i0=1;i0<N-2;++i0)for (int j0=0;j0<=K-4;++j0)
			for (int i1=1;i0+i1<N-2;++i1)for (int j1=0;j0+j1<=K-4;++j1){
				tmp=1LL*dp[i0][j0]*dp[i1][j1]%P*dp[N-2-i0-i1][K-4-j0-j1]%P;
				tmp=1LL*tmp*c[N-2][i0]%P*c[N-2-i0][i1]%P*i0*i1*(N-2-i0-i1)*(N-2-i0-i1)%P;
				inc(ret,tmp);
			}
		return ret;
	}
};
