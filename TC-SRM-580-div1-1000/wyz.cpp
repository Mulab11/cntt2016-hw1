// BEGIN CUT HERE

// END CUT HERE
#line 5 "WallGameDiv1.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn=55;


class WallGameDiv1{
	int dp[maxn][maxn][maxn];
	int n,m,cost[maxn][maxn][maxn];
	int solve(int x,int y,int z){
		if (dp[x][y][z]>=0) return dp[x][y][z];
		if (y<1||y>m) return 1e8;
		dp[x][y][z]=cost[x][y][y];
		if (x==n) return dp[x][y][z];
		int pre=min(y,z),nxt=max(y,z);
		int tmp=min(solve(x,pre-1,nxt)+cost[x][pre][y-1],solve(x,nxt+1,pre)+cost[x][y+1][nxt]);
		if (tmp>=(1e8)) tmp=-tmp;
		dp[x][y][z]+=max(solve(x+1,y,y),tmp);
		
		return dp[x][y][z];
	}
	public:
	int play(vector <string> costs){
		n=costs.size();m=costs[0].size();
		memset(cost,0,sizeof(cost));
		for (int i=1;i<=n;++i)
			for (int j=1;j<=m;++j)for (int k=j;k<=m;++k)
				cost[i][j][k]=cost[i][j][k-1]+costs[i-1][k-1]-48;
		int ret=1e9;
		memset(dp,-1,sizeof(dp));
		for (int i=1;i<=m;++i) ret=min(ret,solve(1,i,i));
		return ret;
	}
};
