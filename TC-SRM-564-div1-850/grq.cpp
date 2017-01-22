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
int dp[2][2];
int solve(vi a,int n){
	int m=a.size(),t=1,k,ans;
	bool isok=1;
	for(int i=0;i<m;i++)
		if(a[i]) isok=0;
	if(isok){if(n) return 0; return 1;}
	while(t<=a[m-1]) t<<=1;
	if(t<=n) return 0;
	t>>=1;
//	debug(t);
	memset(dp,0,sizeof(dp));
	k=0;dp[k][0]=1;
	for(int i=0;i<m-1;i++){
		k^=1;
		for(int j=0;j<2;j++)
			if(a[i]<t) dp[k][j]=(ll)dp[k^1][j]*(a[i]+1)%mod;
			else dp[k][j]=((ll)dp[k^1][j^1]*(a[i]-t+1)%mod+(ll)dp[k^1][j]*t%mod)%mod;
	}
	if(n&t) ans=dp[k][1]; else ans=dp[k][0];
//	debug(ans);
	a[m-1]^=t;
		sort(a.begin(),a.end());
	return (ans+solve(a,n^t))%mod;
}

class DefectiveAddition{
public:
	int count(vector <int> cards, int n){
		sort(cards.begin(),cards.end());
		return solve(cards,n);
	}
};
