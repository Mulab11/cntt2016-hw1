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

const int N=55,mod=1e9+7;
void ch(int &x,int y){
	x+=y;if(x>=mod) x-=mod;
}

class LittleElephantAndPermutationDiv1 {
public:
	int dp[2][N][N*N],n;
	int getNumber(int N, int K) {
		memset(dp,0,sizeof(dp));
		int k=0;dp[k][0][0]=1;n=N;
		for(int i=n;i>=1;i--){
			k^=1;memset(dp[k],0,sizeof(dp[k]));
			for(int j=0;j<=n;j++){
				for(int s=0;s<=n*n;s++){
					if(!dp[k^1][j][s]) continue;
					if(j>=2) ch(dp[k][j-2][s],(ll)dp[k^1][j][s]*(j/2)%mod*(j/2)%mod);
					if(i>j/2) ch(dp[k][j][s+i],(ll)dp[k^1][j][s]*(i-j/2)%mod*(j+1)%mod);
					if(i>j/2) ch(dp[k][j+2][s+i*2],(ll)dp[k^1][j][s]*(i-j/2)%mod*(i-j/2-1)%mod);
				}
			}	
		}
		int ans=0;
		for(int i=K;i<=n*n;i++) ch(ans,dp[k][0][i]);
		return ans;
	}
};

