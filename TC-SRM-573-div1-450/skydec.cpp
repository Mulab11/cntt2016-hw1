#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=55;
int h[N];
int hp[N];
bool go[N][N];
int n;
LL dis[N][N];
pii q[N*N*N*10];
int t;
bool inq[N][N];
inline void check(pii x,LL v){
    //用值v更新点x
    if(v<dis[x.fi][x.se]){
        dis[x.fi][x.se]=v;
        if(!inq[x.fi][x.se]){
            inq[x.fi][x.se]=1;
            q[++t]=x;
        }
    }
}
LL Main(){
    rep(i,1,n)hp[i]=h[i];
    sort(hp+1,hp+1+n);
    //状态(i,j)表示点i的值是j，最短路径
    rep(i,1,n)rep(j,1,n)dis[i][j]=(LL)(1e17);
    t=0;
    rep(i,1,n){
        check(pii(1,i),abs(hp[i]-h[1]));
    }
    rep(i,1,t){
        //每次枚举一个点去更新
        //不需要枚举下一个点的值，因为我们可以再连一些可以降低点的值的边
        //这样边的数量就是O(n^3)了
        int x=q[i].fi;
        int y=q[i].se;
        if(y>1)check(pii(x,y-1),dis[x][y]);
        rep(j,1,n)if(go[x][j]){
            check(pii(j,y),dis[x][y]+abs(hp[y]-h[j]));
        }
        inq[x][y]=0;
    }
    LL ans=-1;
    //返回答案
    rep(i,1,n)if(dis[n][i]<(LL)(1e16)){
        if(ans==-1)ans=dis[n][i];
        else if(dis[n][i]<ans)ans=dis[n][i];
    }
    return ans;
}
class SkiResorts{
public:
    LL minCost(vector <string> road, vector <int> altitude){
        //预处理
        n=altitude.size();
        rep(i,1,n)h[i]=altitude[i-1];
        rep(i,1,n)rep(j,1,n)go[i][j]=(road[i-1][j-1]=='Y');
        return Main();
    }
}gt;


