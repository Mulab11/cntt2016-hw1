#include<bits/stdc++.h>
using namespace std;
int dx[6]={1,0,-1,-1,0,1},dy[6]={0,1,1,0,-1,-1},c[55][55],s=1,i,j,n;
void dfs(int x,int y,int f)
{
	int i=0,u,v;
	if(c[x][y])s=max(s,2*(c[x][y]!=f));
	else for(;i<6;i++)if(u=x+dx[i],v=y+dy[i],~u&&~v&&u<n&&v<n)dfs(u,v,f^1);
}
class HexagonalBoard
{
	public:
		int minColors(vector<string> a)
		{
			n=a.size();
			for(i=0;i<n;i++)for(j=0;j<n;j++)if(a[i][j]=='X'&&!c[i][j])dfs(i,j,2);
			return s;
		}
};
