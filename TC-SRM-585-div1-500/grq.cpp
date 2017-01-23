#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

const int mod=1e9+7;
int n,m,k,dp[2][1505],c[1505][1505];

inline void ch(int &x,int y){
	x+=y;if(x>=mod) x-=mod;
}

class LISNumber{
public:
	int count(vector<int> cardsnum, int K){
		K=-K;
		for(int i=0;i<cardsnum.size();i++) K+=cardsnum[i];
		if(K<0) return 0;
		for(int i=0;i<=1505;i++){
			c[i][0]=c[i][i]=1;
			for(int j=1;j<i;j++) c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
		}
		m=0;k=0;
		memset(dp[k],0,sizeof(dp[k]));
		dp[k][0]=1;
		for(int i=0;i<cardsnum.size();i++){
			k^=1;memset(dp[k],0,sizeof(dp[k]));
			for(int j=0;j<=m;j++)
				for(int a=0;a<=cardsnum[i];a++)
					ch(dp[k][j+a],(ll)dp[k^1][j]*c[m-j][a]%mod*c[cardsnum[i]+j][cardsnum[i]-a]%mod);
			m+=cardsnum[i];
//			for(int j=0;j<=m;j++) printf("%d ",dp[k][j]);puts("");
		}
		return dp[k][K];
	}
};
