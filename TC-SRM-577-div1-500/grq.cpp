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

int dp[20][20][20][20];
vector<string> a;

int solve(int l,int r,int p,int q){
	if(l==r&&p==q) return 0;
	if(l>r||p>q) return 0;
	int &ans=dp[l][r][p+7][q+7];
	if(~ans) return ans;
	ans=1e9;
	
	int tmp=solve(l+1,r,p,q);
	for(int i=0;i<8;i++){
		int x=i,y=l-i;
		if(x<0||y<0||x>7||y>7||x-y<p||x-y>q) continue;
		if(a[x][y]=='#') tmp+=max(r-l,max(x-y-p,q-x+y));
	}
	ans=min(ans,tmp);
	
	tmp=solve(l,r-1,p,q);
	for(int i=0;i<8;i++){
		int x=i,y=r-i;
		if(x<0||y<0||x>7||y>7||x-y<p||x-y>q) continue;
		if(a[x][y]=='#') tmp+=max(r-l,max(x-y-p,q-x+y));
	}
	ans=min(ans,tmp);
	
	tmp=solve(l,r,p+1,q);
	for(int i=0;i<8;i++){
		int x=i,y=i-p;
		if(x<0||y<0||x>7||y>7||x+y<l||x+y>r) continue;
		if(a[x][y]=='#') tmp+=max(q-p,max(x+y-l,r-x-y));
	}
	ans=min(ans,tmp);
	
	tmp=solve(l,r,p,q-1);
	for(int i=0;i<8;i++){
		int x=i,y=i-q;
		if(x<0||y<0||x>7||y>7||x+y<l||x+y>r) continue;
		if(a[x][y]=='#') tmp+=max(q-p,max(x+y-l,r-x-y));
	}
	ans=min(ans,tmp);
	return ans;	
}

class EllysChessboard{
public:
	int minCost(vector<string> board){
		a=board;
		memset(dp,-1,sizeof(dp));
		solve(0,7,0,7);
//		printf("%d\n",dp[2][3][1][3]);
		return solve(0,14,-7,7);
	}
};

