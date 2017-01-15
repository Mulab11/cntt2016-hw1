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
bool a[N][N];int n;
int dx[6]={-1,-1,0,0,1,1};
int dy[6]={0,1,1,-1,0,-1};
bool hf(int x,int y){
    if(x<1)return 0;
    if(x>n)return 0;
    if(y<1)return 0;
    if(y>n)return 0;
    return a[x][y];
}
bool vis[N][N];
bool col[N][N];
bool flag2=0;
void dfs(int x,int y){
    vis[x][y]=1;
    rep(k,0,5)if(hf(x+dx[k],y+dy[k])){
        if(!vis[x+dx[k]][y+dy[k]]){
            col[x+dx[k]][y+dy[k]]=(col[x][y]^1);
            dfs(x+dx[k],y+dy[k]);
        }
        else{
            flag2&=(col[x][y]^col[x+dx[k]][y+dy[k]]);
        }
    }
}
int Main(){
    bool flag1=1;
    bool flag0=1;
    rep(i,1,n)rep(j,1,n)if(a[i][j]){
        flag0=0;
        rep(k,0,5)if(hf(i+dx[k],j+dy[k]))flag1=0;
    }
    if(flag0)return 0;
    if(flag1)return 1;

    flag2=1;
    rep(i,1,n)rep(j,1,n)if(a[i][j])if(!vis[i][j]){
        col[i][j]=0;
        dfs(i,j);
    }

    if(flag2)return 2;
    return 3;
}
class HexagonalBoard{
public:
    int minColors(vector <string> board){
        n=board.size();
        rep(i,1,n)rep(j,1,n)a[i][j]=(board[i-1][j-1]=='X');
        return Main();
    }
};