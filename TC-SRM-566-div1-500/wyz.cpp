// BEGIN CUT HERE

// END CUT HERE
#line 5 "PenguinEmperor.cpp"
#include <bits/stdc++.h>
#define ll long long
#define P 1000000007

using namespace std;

const int maxn=400;

class PenguinEmperor{
	int n;
	void trans(int *f,int *g){
		int res[maxn];
		memset(res,0,sizeof(res));
		for (int i=0;i<n;++i)
			for (int j=0;j<n;++j)
				res[(i+j)%n]=(1LL*f[i]*g[j]+res[(i+j)%n])%P;
		memcpy(f,res,sizeof(res));
	}
	void fast_pow(int *res,int *x,ll y){
		while (y){
			if (y&1) trans(res,x);
			trans(x,x);
			y>>=1;
		}
	}
	int res[maxn];
	int dp[maxn];
	int dpx[maxn],tmp[maxn];
	public:
	int countJourneys(int numCities, long long daysPassed){
		n=numCities;
		int x=daysPassed%n;
		ll t=daysPassed/n;
		if (x==n-1) x=0,++t;
		memset(dp,0,sizeof(dp));dp[0]=1;
		for (int i=1;i<n;++i){
			if (i-1==x) memcpy(dpx,dp,sizeof(dp));
			memset(tmp,0,sizeof(tmp));
			tmp[i]=tmp[n-i]=1;
//			for (int i=0;i<n;++i) printf("%d ",tmp[i]);puts("");
			trans(dp,tmp);
//			for (int i=0;i<n;++i) printf("%d ",dp[i]);puts("");
		}
		memset(res,0,sizeof(res));res[0]=1;
		printf("%lld\n",t);
		fast_pow(res,dp,t);
//		for (int i=0;i<n;++i) printf("%d ",res[i]);puts("");
		trans(res,dpx);
//		for (int i=0;i<n;++i) printf("%d ",res[i]);puts("");
		return res[0];
	}
};
