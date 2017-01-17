#include <bits/stdc++.h>
using namespace std;

const int N = 60,inf = 0x3f3f3f3f;

class WallGameDiv1 {
  public:
  	int n,m;
  	int f[N][N][N][2],ans;
  	int a[N][N],b[N][N];
	int play(vector <string> costs){
		ans = inf;
		n = costs.size();m = costs[0].size();
		memset(f,0x3f,sizeof(f));
		for (int i = 0;i < n;i++)
			for (int j = 0;j < m;j++)
				a[i+1][j+1] = costs[i][j]-'0';
		for (int i = 1;i <= n;i++)	
			for (int j = 1;j <= m;j++)
				b[i][j] = a[i][j]+b[i][j-1];
	
		for (int i = 1;i <= m;i++){
			dfs(1,i,i,0);
			ans = min(ans,f[1][i][i][0]);
		}
		return ans;
	}
	void dfs(int p,int l,int r,int t){
		if (f[p][l][r][t] < inf) return;
		if (p == n) {f[p][l][r][t] = a[p][l];return;}
		if (l == r){
			if (l > 1) dfs(p,l-1,r,0);
			if (r < m) dfs(p,l,r+1,1);
			dfs(p+1,l,r,0);
			int u = f[p+1][l][r][0]+a[p][l],v = f[p][l-1][r][0]+a[p][l],w = f[p][l][r+1][1]+a[p][l];
			if (l > 1 && r < m) f[p][l][r][t] = max(u,min(v,w));
			else if (l > 1) f[p][l][r][t] = max(u,v);
			else if (r < m) f[p][l][r][t] = max(u,w);
			else f[p][l][r][t] = u;
		}
		else if (t == 0){
			if (l > 1) dfs(p,l-1,r,0);
			if (r < m) dfs(p,l,r+1,1);
			dfs(p+1,l,l,0);
			int u = f[p+1][l][l][0]+a[p][l],v = f[p][l-1][r][0]+a[p][l],w = f[p][l][r+1][1]+b[p][r]-b[p][l-1];
			if (l > 1 && r < m) f[p][l][r][t] = max(u,min(v,w));
			else if (l > 1) f[p][l][r][t] = max(u,v);
			else if (r < m) f[p][l][r][t] = max(u,w);
			else f[p][l][r][t] = u;			
		}
		else {
			if (l > 1) dfs(p,l-1,r,0);
			if (r < m) dfs(p,l,r+1,1);
			dfs(p+1,r,r,0);
			int u = f[p+1][r][r][0]+a[p][r],v = f[p][l-1][r][0]+b[p][r]-b[p][l-1],w = f[p][l][r+1][1]+a[p][r];
			if (l > 1 && r < m) f[p][l][r][t] = max(u,min(v,w));
			else if (l > 1) f[p][l][r][t] = max(u,v);
			else if (r < m) f[p][l][r][t] = max(u,w);
			else f[p][l][r][t] = u;		
		}
		//printf("%d %d %d %d %d\n",p,l,r,t,f[p][l][r][t]);
	}
};
