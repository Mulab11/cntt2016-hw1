// BEGIN CUT HERE

// END CUT HERE
#line 5 "Tunnels.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

void Min(int &x,int y){if (y<x) x=y;}
void Max(int &x,int y){if (y>x) x=y;}

const int maxn=66;

const int dx[4]={1,0,-1,0};
const int dy[4]={0,1,0,-1};

class Tunnels{
	int a[maxn][maxn],n,m;
	int bl[maxn][maxn],sz[maxn*maxn],top[maxn*maxn],bot[maxn*maxn],stamp;
	int dgr[maxn][maxn];
	void dfs(int x,int y){
		if (bl[x][y]) return;
		bl[x][y]=stamp;
		++sz[stamp];
		Min(top[stamp],x);
		Max(bot[stamp],x);
		dgr[x][y]=4;
		for (int k=0;k<4;++k)
			if (!a[x+dx[k]][y+dy[k]]) --dgr[x][y];
			else dfs(x+dx[k],y+dy[k]);
	}
	int dp[maxn][maxn][maxn];
	public:
	int minimumTunnels(vector <string> frame){
		n=frame.size();
		m=frame[0].size();
		memset(a,0,sizeof(a));
		for (int i=1;i<=n;++i)for (int j=1;j<=m;++j)a[i][j]=frame[i-1][j-1]=='X';
		memset(bl,0,sizeof(bl));stamp=0;
		top[0]=bot[0]=-1;
		for (int i=1;i<=n;++i)for (int j=1;j<=m;++j)if (a[i][j]&&!bl[i][j]){
			sz[++stamp]=0;
			top[stamp]=bot[stamp]=i;
			dfs(i,j);
		}
		
		memset(dp,192,sizeof(dp));
		dp[0][0][0]=0;
		for (int i=1;i<=n;++i){
			int l=0,r=0;
			if (bot[bl[i][1]]==i&&(sz[bl[i][1]]!=2||i<3)) l=-1;
			if (top[bl[i][1]]==i&&i>1) l=1;
			if (bot[bl[i][m]]==i&&(sz[bl[i][m]]!=2||i<3)) r=-1;
			if (top[bl[i][m]]==i&&i>1) r=1;
			int tmp=(bot[bl[i][1]]-top[bl[i][1]]+1)*m-sz[bl[i][1]];
			if (bot[bl[i][1]]==i&&bl[i][1]==bl[i][m]&&tmp==0) l=r=0;
			if (top[bl[i][1]]==i&&bl[i][1]==bl[i][m]&&tmp==0) l=2;
			if (dgr[i][1]>1) l=0;
			if (dgr[i][m]>1) r=0;
			for (int j=0;j<i;++j)for (int k=0;k<i;++k)
				if (l==2){
					if (j) Max(dp[i][j-1][k+1],dp[i-1][j][k]+1);
					else Max(dp[i][j][k+1],dp[i-1][j][k]);
					if (k) Max(dp[i][j+1][k-1],dp[i-1][j][k]+1);
					else Max(dp[i][j+1][k],dp[i-1][j][k]);
				}
				else{
					int j0=j,k0=k,dlt=0;
					if (l==-1) ++j0;
					if (l==1&&j0) --j0,++dlt;
					if (r==-1) ++k0;
					if (r==1&&k0) --k0,++dlt;
					Max(dp[i][j0][k0],dp[i-1][j][k]+dlt);
				}
		}
		
		int res=0;
		for (int i=0;i<=n;++i)for (int j=0;j<=n;++j) Max(res,dp[n][i][j]);
		return stamp-res;
	}
};
