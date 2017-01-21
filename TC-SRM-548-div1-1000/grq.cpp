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
#define pq priority_queue
#define rf random_shuffle
#define np next_permutation
#define lb lower_bound
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

const int mod=1e9+7;
int c[2505][2505],dp[55][55],dp1[55][55];

inline void ch(int &x,int y){
	x+=y;if(x>=mod) x-=mod;
}

class KingdomAndCities{
public:
	int howMany(int n, int m, int k){
		for(int i=0;i<=2500;i++){
			c[i][0]=c[i][i]=1;
			for(int j=1;j<i;j++)
				c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
		}
		for(int i=1;i<=n;i++)
			for(int j=0;j<=k;j++){
				dp[i][j]=c[i*(i-1)/2][j];
				for(int ip=1;ip<i;ip++)
					for(int jp=0;jp<=j;jp++)
						ch(dp[i][j],mod-(ll)dp[ip][jp]*c[i-1][ip-1]%mod*c[(i-ip)*(i-ip-1)/2][j-jp]%mod);
			}
		for(int i=3;i<=n;i++)
			for(int j=2;j<=k;j++){
				dp1[i][j]=0;
				ch(dp1[i][j],(ll)dp[i-1][j-2]*c[i-1][2]%mod);
				for(int ip=1;ip<i-1;ip++)
					for(int jp=0;jp<=j-2;jp++)
						ch(dp1[i][j],(ll)dp[ip][jp]*dp[i-1-ip][j-2-jp]%mod*c[i-2][ip-1]%mod*ip%mod*(i-1-ip)%mod);
			}

		if(!m) return dp[n][k];
		if(m==1) return dp1[n][k];
		int ans=0;
		
		if(k<3) return 0;
		ch(ans,(ll)dp[n-2][k-3]*(n-2)%mod*(n-2)%mod);
		for(int ip=1;ip<=n-2;ip++)
			for(int jp=0;jp<=k-3;jp++)
				ch(ans,(ll)dp[ip][jp]*dp[n-2-ip][k-3-jp]%mod*c[n-3][ip-1]%mod*ip%mod*(n-2-ip)%mod*2%mod);
		ch(ans,(ll)dp1[n-1][k-2]*c[n-2][2]%mod);
		for(int ip=1;ip<=n-1;ip++)
			for(int jp=0;jp<=k-2;jp++)
				ch(ans,(ll)dp1[ip][jp]*dp[n-1-ip][k-2-jp]%mod*c[n-2][ip-1]%mod*(ip-1)%mod*(n-1-ip)%mod);
		return ans;
	}
};
