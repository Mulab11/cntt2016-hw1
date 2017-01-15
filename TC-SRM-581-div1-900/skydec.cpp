#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<map>
#include<string>
#include<vector>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double db;
const int N=16;
int n,m;
bool a[N][N];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
int ZT;
int ans=1e9;
void put(int x,int y,int kd){
    //对(x,y)进行类型为kd的操作
    rep(k,0,3)a[x+dx[k]][y+dy[k]]^=1;
    if(kd)a[x][y]^=1;
}
void dfs(int x,int cost,int lie){
    if(cost>1e7)return;
    if(x==1){
        //第一列特殊处理
        rep(kd,0,1){
            int fang=0;
            int tmp=lie;
            int co=cost;
            rep(i,1,m)if((1<<(i-1))&ZT){
                fang|=(1<<i);
                co++;put(x,i,kd);
                tmp|=(1<<(kd*m+i));
                if((tmp&(1<<(m+i)))&&(tmp&(1<<i)))co=1e9;
            }
            dfs(x+1,co,tmp);
            rep(i,1,m)if(fang&(1<<i))put(x,i,kd);
        }
        return;
    }
    if(x==n+1){
        //最后一行，check后返回
        rep(i,1,m)if(a[n][i])return;
        if(cost<ans)ans=cost;
        return;
    }
    rep(kd,0,1){
        int tmp=lie;
        int co=cost;
        int fang=0;
        //枚举是否要放
        //要放的话方案显然是唯一的
        rep(i,1,m)if(a[x-1][i]){
            fang|=(1<<i);
            co++;put(x,i,kd);
            tmp|=(1<<(kd*m+i));
            if((tmp&(1<<(m+i)))&&(tmp&(1<<i)))co=1e9;
        }
        dfs(x+1,co,tmp);
        rep(i,1,m)if(fang&(1<<i))put(x,i,kd);
    }
}
int Main(){
    rep(use,0,(1<<m)-1){
        //枚举每列进行的操作的类型
        ZT=use;
        //搜索
        dfs(1,0,0);
    }
    if(ans>1e7)ans=-1;
    return ans;
}
class YetAnotherBoardGame{
    public:
    int minimumMoves(vector<string> _a){
        //预处理
        n=_a.size();m=_a[0].size();
        rep(i,1,n)rep(j,1,m)a[i][j]=(_a[i-1][j-1]=='W');
        return Main();
    }
}gt;



