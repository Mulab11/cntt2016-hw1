#include<bits/stdc++.h>
using namespace std;
#define P 1000000007
int n,m,i,j,k,ans,f[55][55];
char c[55][55];
bool b[55][55];
void F()//计算黑色在左侧且单调不增的情况 
{
    memset(f,0,sizeof(f));
    fill(f[0],f[0]+m+1,1);
    for(i=1;i<=n;i++)for(j=m;~j;j--)
    {
        f[i][j]=f[i][j+1];
        if(b[i][j])f[i][j]=(f[i][j]+f[i-1][j])%P;
    }
    ans=(ans+f[n][0])%P;
    for(i=1;i<=n;i++)reverse(b[i],b[i]+m+1);
}
void work()
{
    for(i=1;i<=n;i++)for(j=0;j<=m;j++)for(k=b[i][j]=1;k<=m;k++)if(k<=j&&c[i][k]=='W'||k>j&&c[i][k]=='B')b[i][j]=0;
    F();//计算黑色在左侧且单调不增的情况 
    F();//计算白色在左侧且单调不减的情况 
    for(i=0;i<=n;i++)//计算每列均相同的情况 
    {
        for(j=k=1;j<=n;j++)if(j<=i&&!b[j][m]||j>i&&!b[j][0])k=0;
        ans-=k;
    }
    for(i=0;i<=m;i++)//计算每行均相同的情况 
    {
        for(j=k=1;j<=n;j++)k&=b[j][i];
        ans-=k;
    }
    for(i=k=1;i<=n;i++)for(j=1;j<=m;j++)if(c[i][j]=='W')k=0;//计算所有格子均相同的情况 
    ans+=k;
}
class TwoConvexShapes
{
    public:
        int countWays(vector <string> grid)
        {
            n=grid.size();
            m=grid[0].size();
            for(i=0;i<n;i++)for(j=0;j<m;j++)c[i+1][j+1]=grid[i][j];
            work();//处理5种情况 
            for(i=1;i<=n;i++)for(j=1;j<=m;j++)if(c[i][j]!='?')c[i][j]^=21;//黑白反转 
            work();//处理剩下5种情况 
            return (ans+P)%P;
        }
};