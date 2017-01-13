#include<bits/stdc++.h>
using namespace std;
int n,m,N,i,j,a[20],o[8192],ans=1000000000;
int dfs(int x,int b,int B,int d,int D)
{
    if(x==n)return b?1000000000:0;
    int y=b&d,s=1000000000;
    if(!(D&y))s=min(s,dfs(x+1,a[x]^B^(b>>1)^(b<<1&N),b,d|b,D));
    if(!(~D&y))s=min(s,dfs(x+1,a[x]^B^b^(b>>1)^(b<<1&N),b,d|b,D|b));
    return s+o[b];
}
class YetAnotherBoardGame
{
    public:
        int minimumMoves(vector <string> board)
        {
            n=board.size();
            m=board[0].size();
            for(i=0;i<n;i++)for(j=0;j<m;j++)a[i]|=(board[i][j]=='W')<<j;
            for(i=1;i<1<<m;i++)o[i]=o[i>>1]+(i&1);
            N=(1<<m)-1;
            for(i=0;i<1<<m;i++)for(j=0;j<2;j++)ans=min(ans,dfs(1,a[0]^(i>>1)^(i<<1&N)^i*j,i,i,i*j)+o[i]);
            if(ans==1000000000)ans=-1;
            return ans;
        }
};

