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

const int N=355,mod=1e9+7;
int n,dp[N][N],a[N],s[N],tmp[N];

inline void mul(int *a,int *x){
	memset(tmp,0,sizeof(tmp));
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			tmp[(i+j)%n]=(tmp[(i+j)%n]+(ll)a[i]*x[j]%mod)%mod;
	for(int i=0;i<n;i++) a[i]=tmp[i];
}

inline void exp(int *a,int *x,ll y){
	for(int i=0;i<n;i++) a[i]=0;a[0]=1;
	while(y){
		if(y&1) mul(a,x);
		mul(x,x);y>>=1;
	}
}

class PenguinEmperor{
public:
	int countJourneys(int n, long long m){
		::n=n;
		for(int i=0;i<n;i++) dp[0][i]=0; dp[0][0]=1;
		for(int i=1;i<=n;i++)
			for(int j=0;j<n;j++)
				if(i*2%n) dp[i][j]=(dp[i-1][(j+n-i)%n]+dp[i-1][(j+i)%n])%mod; else dp[i][j]=dp[i-1][(j+i)%n];
//		return dp[m%n][0];
		for(int i=0;i<n;i++) s[i]=dp[n][i];
		exp(a,s,m/n);
		for(int i=0;i<n;i++) dp[0][i]=a[i];
		for(int i=1;i<=n;i++)
			for(int j=0;j<n;j++)
				if(i*2!=n) dp[i][j]=(dp[i-1][(j+n-i)%n]+dp[i-1][(j+i)%n])%mod; else dp[i][j]=dp[i-1][(j+i)%n];
		return dp[m%n][0];
	}
};
