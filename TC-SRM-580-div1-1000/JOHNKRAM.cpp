#include<bits/stdc++.h>
using namespace std;
int a[55][55],n,m,i,j,ans=1000000000,f[55][55][55][2];
int work(int x,int l,int r,bool b)
{
    int y=b?r:l;
    if(x==n)return a[n][y]-a[n][y-1];
    if(~f[x][l][r][b])return f[x][l][r][b];
    f[x][l][r][b]=1000000000;
    if(l>1)f[x][l][r][b]=work(x,l-1,r,0)+a[x][y-1]-a[x][l-1];
    if(r<m)f[x][l][r][b]=min(f[x][l][r][b],work(x,l,r+1,1)+a[x][r]-a[x][y]);
    if(f[x][l][r][b]==1000000000)f[x][l][r][b]=0;
    f[x][l][r][b]=max(f[x][l][r][b],work(x+1,y,y,0));
    return f[x][l][r][b]+=a[x][y]-a[x][y-1];
}
class WallGameDiv1
{
    public:
        int play(vector <string> costs)
        {
            n=costs.size();
            m=costs[0].size();
            for(i=0;i<n;i++)for(j=0;j<m;j++)a[i+1][j+1]=a[i+1][j]+costs[i][j]-'0';
            memset(f,-1,sizeof(f));
            for(i=1;i<=m;i++)ans=min(ans,work(1,i,i,0));
            return ans;
        }
};

