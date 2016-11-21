#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=51,inf=500000000;

namespace Solve{
	int dp[maxn][maxn][maxn][maxn][2],tmp[maxn][maxn];
	int n,m,sum[maxn][maxn];
	int ask(int y,int x,int l,int r,int w){
		if (~dp[y][x][l][r][w]) return dp[y][x][l][r][w];
		if (w==0){
			if (y==n) return 0;
			if (x<l||x>r) return dp[y][x][l][r][0]=ask(y+1,x,0,0,1)+tmp[y+1][x];
			else{
				return dp[y][x][l][r][0]=min((l>1)?ask(y,l-1,l,r,1)+sum[y][x-1]-sum[y][l-2]:inf,
											(r<m)?ask(y,r+1,l,r,1)+sum[y][r+1]-sum[y][x]:inf);
			}
		}
		else{
			if (l==0)
				return dp[y][x][l][r][1]=max(ask(y,x,l,r,0),(m>1)?ask(y,x,x,x,0):0);
			else if (x<l)
				return dp[y][x][l][r][1]=max(ask(y,x,l,r,0),(x>1||r<m)?ask(y,x,x,r,0):0);
			else
				return dp[y][x][l][r][1]=max(ask(y,x,l,r,0),(l>1||x<m)?ask(y,x,l,x,0):0);
		}
	}
}

class WallGameDiv1{
	
	public:
		int play(vector<string> costs){
			
			using namespace Solve;
			n=costs.size();
			m=costs[0].length();
			memset(sum,0,sizeof(sum));
			for (int i=0;i<n;++i)
			for (int j=0;j<m;++j) tmp[i+1][j+1]=costs[i][j]-'0';
			memset(dp,-1,sizeof(dp));
			for (int i=1;i<=n;++i)
			for (int j=1;j<=m;++j) sum[i][j]=sum[i][j-1]+tmp[i][j];
			
			int ans=inf;
			for (int i=1;i<=m;++i) ans=min(ans,ask(1,i,0,0,1)+tmp[1][i]);
			return ans;
			
			return 100;
		}
};
