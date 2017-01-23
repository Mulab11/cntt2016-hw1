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

int n,m,dp[55][55];
vector<ll> a,b,ta,tb;

inline int solve(vector<ll> a,vector<ll> b){
	int n=a.size(),m=b.size();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			dp[i][j]=0; 
			if(a[i-1]==b[j-1]) dp[i][j]=dp[i-1][j-1]+1;
			dp[i][j]=max(dp[i][j],max(dp[i-1][j],dp[i][j-1]));
		}
	return dp[n][m];
}

class AstronomicalRecords{
public:
	int minimalPlanets(vector <int> A, vector <int> B){
		n=A.size();m=B.size();
		a.clear();b.clear();
		for(int i=0;i<n;i++) a.pb(A[i]);
		for(int i=0;i<m;i++) b.pb(B[i]);
		int ans=n+m;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++){
				int tmp=n+m-1;
				ta.clear();tb.clear();
				for(int k=0;k<i;k++) ta.pb(a[k]*b[j]);
				for(int k=0;k<j;k++) tb.pb(b[k]*a[i]);
				tmp-=solve(ta,tb);
				ta.clear();tb.clear();
				for(int k=i+1;k<n;k++) ta.pb(a[k]*b[j]);
				for(int k=j+1;k<m;k++) tb.pb(b[k]*a[i]);
				ans=min(ans,tmp-solve(ta,tb));
			}
		return ans;
	}
};
