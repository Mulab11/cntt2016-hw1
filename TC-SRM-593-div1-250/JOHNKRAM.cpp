#include<bits/stdc++.h>
using namespace std;
const int dx[]={-1,-1,0,0,1,1},dy[]={1,0,-1,1,0,-1};
int ans,n,m,i,j,a[55][55];
char s[55][55];
void dfs(int x,int y,int c)
{
    if(a[x][y])
    {
        if(a[x][y]!=c)ans=3;
        return;
    }
    a[x][y]=c;
    for(int i=0;i<6;i++)if(x+dx[i]>=0&&x+dx[i]<n&&y+dy[i]>=0&&y+dy[i]<m&&s[x+dx[i]][y+dy[i]]=='X')
    {
        ans=max(ans,2);
        dfs(x+dx[i],y+dy[i],c^3);
    }
}
class HexagonalBoard
{
    public:
        int minColors(vector <string> board)
        {
            n=board.size();
            m=board[0].size();
            for(i=0;i<n;i++)for(j=0;j<m;j++)s[i][j]=board[i][j];
            for(i=0;i<n;i++)for(j=0;j<m;j++)if(s[i][j]=='X'&&!a[i][j])
            {
                ans=max(ans,1);
                dfs(i,j,1);
            }
            return ans;
        }
};
