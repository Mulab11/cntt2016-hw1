#include<stdio.h>
#include<string>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cstdlib>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
const int N=55;
int n;
bool love[N][N];
int mat[N];
bool vis[N];
int dfs(int x){
    //匈牙利算法
    if(vis[x])return 0;
    vis[x]=1;
    rep(i,1,n)if(!love[i][i])if(love[x][i]){
        if((!mat[i])||(dfs(mat[i]))){
            mat[i]=x;
            return 1;
        }
    }
    return 0;
}
int Main(){
    //floyd传递闭包计算出所有点之间的可达关系
    rep(k,1,n)rep(i,1,n)rep(j,1,n)love[i][j]|=(love[i][k]&love[k][j]);
    memset(mat,0,sizeof mat);
    int ans=0;
    rep(i,1,n)if(!love[i][i]){
        //利用匈牙利算法计算二分图最大匹配
        ans++;
        memset(vis,0,sizeof vis);
        ans-=dfs(i);
    }
    return ans;
}
class Incubator{
public:
    int maxMagicalGirls(vector<string> love){
        //预处理
        n=love.size();
        rep(i,1,n)rep(j,1,n)::love[i][j]=(love[i-1][j-1]=='Y');
        return Main();
    }
};





