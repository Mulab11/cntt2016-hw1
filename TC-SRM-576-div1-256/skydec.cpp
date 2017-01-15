#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int N=55;
bool a[N][N];
int n,m;
int sx,sy;
pii q[N*N*N];
int t;
int dis[N][N];
bool inq[N][N];
int Main(){
    rep(i,1,n)rep(j,1,m)dis[i][j]=1e9;
    rep(i,1,m){
        q[++t]=pii(n,i);
        dis[n][i]=0;
        inq[n][i]=1;
    }
    //考虑最短路
    rep(i,1,t){
        int x=q[i].fi;
        int y=q[i].se;
        //每次枚举往哪走，然后答案max上相应的梯子长度
        //往右走
        if(y+1<=m&&a[x][y+1]){
            if(dis[x][y+1]>dis[x][y]){
                dis[x][y+1]=dis[x][y];
                if(!inq[x][y+1]){
                    inq[x][y+1]=1;
                    q[++t]=pii(x,y+1);
                }
            }
        }
        //往左走
        if(y-1>=1&&a[x][y-1]){
            if(dis[x][y-1]>dis[x][y]){
                dis[x][y-1]=dis[x][y];
                if(!inq[x][y-1]){
                    inq[x][y-1]=1;
                    q[++t]=pii(x,y-1);
                }
            }
        }
        rep(j,-n,n)if(x+j>=1&&x+j<=n)if(a[x+j][y]){
            //枚举往上跳或者往下跳多少
            int w=max(dis[x][y],abs(j));
            //最短路里更新
            if(w<dis[x+j][y]){
                dis[x+j][y]=w;
                if(!inq[x+j][y]){
                    inq[x+j][y]=1;
                    q[++t]=pii(x+j,y);
                }
            }
        }
        inq[x][y]=0;
    }
    //返回答案
    return dis[sx][sy];
}
class ArcadeManao{
public:
    int shortestLadder(vector<string> level, int coinRow, int coinColumn){
        //预处理
        n=level.size();
        m=level[0].size();
        rep(i,1,n)rep(j,1,m)a[i][j]=(level[i-1][j-1]=='X');
        sx=coinRow;
        sy=coinColumn;
        return Main();
    }
};




