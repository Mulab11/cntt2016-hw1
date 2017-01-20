#include<bits/stdc++.h>
using namespace std;
int dx[6]={1,0,-1,-1,0,1},dy[6]={0,1,1,0,-1,-1},c[55][55],s,i,j,n;
vector<string> a;
void dfs(int x,int y,int f)
{
	int i=0,u,v;
	if(c[x][y])s=max(s,3*(c[x][y]!=f));
	else for(c[x][y]=f;i<6;i++)if(u=x+dx[i],v=y+dy[i],~u&&~v&&u<n&&v<n&&a[u][v]=='X')s=max(s,2),dfs(u,v,f^1);
}
class HexagonalBoard
{
	public:
		int minColors(vector<string> A)
		{
			a=A;n=a.size();
			for(i=0;i<n;i++)for(j=0;j<n;j++)if(a[i][j]=='X'&&!c[i][j])s=max(s,1),dfs(i,j,2);
			return s;
		}
};
