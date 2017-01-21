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
int n,m,dp[N][N];
bool vis[N];
char b[N][N];
void ch(int &x,int y){
	x+=y;
	if(x>=mod)x-=mod;
}
void upt(vector<string> a){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			b[i][j]=a[i-1][j-1];
}
int solve(vector<string> a){
	memset(dp,0,sizeof(dp));
	upt(a);
	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		int L=0,R=m;
		for(int j=1;j<=m;j++){
			if(b[i][j]=='W') R=min(R,j-1);
			else if(b[i][j]=='B') L=j;
		}
		if(L>R) return 0;
		for(int j=0;j<=L;j++) ch(dp[i][L],dp[i-1][j]);
		for(int j=L+1;j<=R;j++)
			ch(dp[i][j],(j>0?dp[i][j-1]:0)+dp[i-1][j]);
//		for(int j=0;j<=m;j++) printf("%d ",dp[i][j]);
//		printf("%d %d\n",L,R);
	}
	int ans=0;
	for(int i=0;i<=m;i++) ch(ans,dp[n][i]);
	return ans;
}
int s1(vector<string> a){
	upt(a);vis[0]=1;
	for(int j=1;j<=m;j++){
		vis[j]=vis[j-1];
		for(int i=1;i<=n;i++)
			if(b[i][j]=='W') vis[j]=0;
	}
	bool isok=1;int ans=0;
	for(int j=m;j>=0;j--){
		if(!isok) break;
		if(vis[j]) ans++;
		for(int i=1;i<=n;i++)
			if(b[i][j]=='B') isok=0;
	}
//	if(ans) puts("A");
	return ans;
}
int s2(vector<string> a){
	upt(a);vis[0]=1;
	for(int i=1;i<=n;i++){
		vis[i]=vis[i-1];
		for(int j=1;j<=m;j++)
			if(b[i][j]=='W') vis[i]=0;
	}
	bool isok=1;int ans=0;
	for(int i=n;i>=0;i--){
		if(!isok) break;
		if(vis[i]) ans++;
		for(int j=1;j<=m;j++)
			if(b[i][j]=='B') isok=0;
	}
	return ans;
}


class TwoConvexShapes{
public:
	int countWays(vector <string> grid){
		int ans=0;
		n=grid.size();m=grid[0].size();
		ch(ans,solve(grid));
		reverse(grid.begin(),grid.end());
		ch(ans,solve(grid));
		for(int i=0;i<n;i++)
			reverse(grid[i].begin(),grid[i].end());
		ch(ans,solve(grid));
		reverse(grid.begin(),grid.end());
		ch(ans,solve(grid));
//		return ans;
//		-------------------plus-----------------------
		ch(ans,mod-s1(grid));
		for(int i=0;i<n;i++)
			reverse(grid[i].begin(),grid[i].end());
		ch(ans,mod-s1(grid));
		ch(ans,mod-s2(grid));
		reverse(grid.begin(),grid.end());
//		debug(ans);
		ch(ans,mod-s2(grid));
		bool vb=0,vw=0;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(grid[i][j]=='B') vb=1; else if(grid[i][j]=='W') vw=1;
		ch(ans,1-vb);ch(ans,1-vw);
		return ans;
	}
};
