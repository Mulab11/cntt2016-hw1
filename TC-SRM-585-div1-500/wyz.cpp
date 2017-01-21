// BEGIN CUT HERE

// END CUT HERE
#line 5 "LISNumber.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
#define P 1000000007

const int maxn=38;

class LISNumber{
	int c[maxn*maxn][maxn*maxn];
	int n;
	int dp[maxn][maxn*maxn];
	public:
	int count(vector <int> cardsnum, int K){
		n=cardsnum.size();

		memset(c,0,sizeof(c));
		c[0][0]=1;
		for (int i=1;i<=36*36;++i){
			c[i][0]=1;
			for (int j=1;j<=i;++j) c[i][j]=(c[i-1][j]+c[i-1][j-1])%P;
		}
		
		memset(dp,0,sizeof(dp));
		dp[1][cardsnum[0]]=1;
		for (int i=1,s=cardsnum[0];i<n;s+=cardsnum[i++])
			for (int j=1;j<=K;++j)if (dp[i][j])
				for (int u=1;u<=cardsnum[i]&&u<=s+1;++u){//u->divide (i+1)s to u*(i+1)s
					ll now=1LL*dp[i][j]*c[cardsnum[i]-1][u-1]%P;
					int toj=j+cardsnum[i]-u;
					for (int v=max(u-j,0);v<=s+1-j&&v<=u;++v)//v->v postions let LISNumber plus one
						dp[i+1][toj+v]=(now*c[j][u-v]%P*c[s+1-j][v]+dp[i+1][toj+v])%P;
				}
		return dp[n][K];
	}
};
