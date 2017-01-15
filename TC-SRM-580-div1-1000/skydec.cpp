#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int N=53;
const int inf=1000000000;
int a[N][N];
int n,m;
map<int,int>f[2][N][N][N];
int sum[N][N][N];
int dp(int who,int x,int y,int l,int r){
    //记忆化搜索，who表示现在是谁
    //x,y表示当前位置是(x,y)
    //l,r表示当前行的隔板是[l,r]
    if(f[who][x][y][l].find(r)!=f[who][x][y][l].end())
    return f[who][x][y][l][r];

    if(x==n)return 0;

    int ret=0;
    if(who)ret=-inf;
    else ret=inf;

    if(who){
        //不动
        ret=dp(who^1,x,y,l,r);
        //补好来阻碍他
        if(max(r,y)-min(l,y)!=m-1){
            ret=max(ret,dp(who^1,x,y,min(l,y),max(r,y)));
        }
    }
    else{
        //如果说有空隙，就直接走下去
        if(!(l<=y&&y<=r))
        ret=min(ret,dp(who^1,x+1,y,m+1,0)+a[x+1][y]);
        else{
            if(l>1){
                //走到l-1
                ret=min(ret,dp(who^1,x,l-1,l,r)+sum[x][l-1][y-1]);
            }   
            if(r<m){
                //走到r+1
                ret=min(ret,dp(who^1,x,r+1,l,r)+sum[x][y+1][r+1]);
            }
        }
    }

    return f[who][x][y][l][r]=ret;
}
int Main(){
    int ans=1e9;
    rep(i,1,n){
        //预处理行的区间和，sum[i][l][r]表示第i行[l,r]列的和
        rep(j,1,m)rep(k,j,m)sum[i][j][k]=sum[i][j][k-1]+a[i][k];
    }
    //枚举第一格dp
    rep(i,1,m)ans=min(ans,dp(1,1,i,m+1,0)+a[1][i]);
    return ans;
}
class WallGameDiv1{
public:
    int play(vector <string> costs){
        //预处理
        n=costs.size();
        m=costs[0].size();
        rep(i,1,n)rep(j,1,m)a[i][j]=costs[i-1][j-1]-'0';
        return Main();
    }
}gt;
