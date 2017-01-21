// BEGIN CUT HERE

// END CUT HERE
#line 5 "ArcadeManao.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn=55;

class ArcadeManao{
	int a[maxn][maxn],r,c;
	bool vis[maxn][maxn];
	int ans;
	void dfs(int x,int y,bool type){
		if (type&&vis[x][y]) return;
//		printf("%d %d %d %d\n",ans,x,y,type);
		vis[x][y]=1;
		if (a[x][y-1]) dfs(x,y-1,1);
		if (a[x][y+1]) dfs(x,y+1,1);
		for (int i=1;i<=ans&&x+i<=r;++i)
			if (a[x+i][y]) dfs(x+i,y,1);
		for (int i=1;i<=ans&&x-i>=1;++i)
			if (a[x-i][y]) dfs(x-i,y,1);
	}
	public:
	int shortestLadder(vector <string> level, int coinRow, int coinColumn){
		r=level.size();c=level[0].size();
		memset(a,0,sizeof(a));
		for (int i=0;i<r;++i)for (int j=0;j<c;++j)
			a[i+1][j+1]=level[i][j]=='X';
		memset(vis,0,sizeof(vis));
		for (int i=1;i<=c;++i) vis[r][i]=1;
		for (ans=1;!vis[coinRow][coinColumn];++ans)
			for (int i=1;i<=r;++i)for (int j=1;j<=c;++j)if (vis[i][j])dfs(i,j,0);
		return ans-1;
	}
};
