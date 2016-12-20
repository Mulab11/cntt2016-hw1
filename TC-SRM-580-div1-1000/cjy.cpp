#include <bits/stdc++.h>
using namespace std;
int f[55][55][55][2],v[55][55][55][2],a[55][55],n,m,s[55][55],i,j,O=1<<30,ans=O;
int dfs(int x,int l,int r,int t)//搜索
{
	if(x==n-1)return a[x][l];
	if(v[x][l][r][t])return f[x][l][r][t];
	int y=t?r:l,S=a[x][y]+dfs(x+1,y,y,0),g=O;
	if(l)g=min(g,dfs(x,l-1,r,0)+s[x][y+1]-s[x][l]);
	if(r<m-1)g=min(g,dfs(x,l,r+1,1)+s[x][r+1]-s[x][y]);
	if(g!=O)S=max(S,g);
	return v[x][l][r][t]=1,f[x][l][r][t]=S;
}
class WallGameDiv1
{
	public:
		int play(vector<string> S)
		{
			for(n=S.size(),m=S[0].size();i<n;i++)for(j=0;j<m;j++)s[i][j+1]=s[i][j]+(a[i][j]=S[i][j]-48);
			for(i=0;i<m;i++)ans=min(ans,dfs(0,i,i,0));
			return ans;
		}
};
