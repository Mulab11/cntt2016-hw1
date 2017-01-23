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

const int inf=1e7,N=55;

int n,m,dp[N][N][N][2],a[N][N],s[N][N];
int sum(int x,int l,int r){
	if(l<0||r>=m) return inf;
	return s[x][r]-(l?s[x][l-1]:0);
}
int solve(int x,int l,int r,int s){
	if(l<0||r>=m) return inf;
	if(x==n-1) return a[x][r];
	int &ans=dp[x][l][r][s];
	if(~ans) return ans;
	ans=0;
	if(!s){
		ans=max(ans,solve(x+1,l,l,0));
		if(r-l+1<m) ans=max(ans,min(solve(x,l-1,r,0),solve(x,l,r+1,1)+sum(x,l+1,r)));
		ans+=a[x][l];
	}
	else{
		ans=max(ans,solve(x+1,r,r,0));
		if(r-l+1<m) ans=max(ans,min(solve(x,l-1,r,0)+sum(x,l,r-1),solve(x,l,r+1,1)));
		ans+=a[x][r];
	}
	return ans;
}

class WallGameDiv1{
public:
	int play(vector<string> costs){
		n=costs.size();m=costs[0].size();
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				a[i][j]=costs[i][j]-'0',s[i][j]=(j?s[i][j-1]:0)+a[i][j];
		memset(dp,-1,sizeof(dp));
		int ans=inf;
		for(int i=0;i<m;i++)
			ans=min(ans,solve(0,i,i,0));
		return ans;
	}
};
