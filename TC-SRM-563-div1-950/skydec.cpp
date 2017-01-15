#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
const int N=55;
const int P=1000000009;
inline int Pow(int a,int b){
    int c=1;
    for(;b;b>>=1,a=a*1ll*a%P)if(b&1)c=c*1ll*a%P;
    return c;
}
int ST;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
bool a[N][N];int n,m;
bool over(int x,int y){
    //是否是外界
    return (x<1)||(x>n)||(y<1)||(y>m);
}
bool border(int x,int y){
    //是否在边界
    return (x==1)||(x==n)||(y==1)||(y==m);
}
bool zhang(int x,int y){
    //是否是障碍
    if(over(x,y))return 0;
    return !a[x][y];
}
bool kong(int x,int y){
    //是否是空格子
    if(over(x,y))return 0;
    return a[x][y];
}
bool vis[N][N][N][N];
char q[N*N*N*N][4];
int t;
void input(int x,int y,int j,int k){
    //加入到队列里
    if(vis[x][y][j][k])return;
    vis[x][y][j][k]=1;
    ++t;
    q[t][0]=x;q[t][1]=y;q[t][2]=j;q[t][3]=k;
}
int id[N][N],tot;
int fa[N*N];
int get(int x){
    if(x==fa[x])return x;
    return fa[x]=get(fa[x]);
}
void Union(int x,int y){
    fa[get(x)]=get(y);
}
bool hav[N*N];
bool can[N][N];
int rex[N*N],rey[N*N];
int ED;
int Main(){
    rep(i,1,n)rep(j,1,m)if(a[i][j]){
        id[i][j]=++tot;
        rex[tot]=i;
        rey[tot]=j;
    }
    rep(i,1,tot)fa[i]=i;

    //采取bfs的方法
    rep(i,1,n)rep(j,1,m)if(a[i][j])rep(k,0,3)if(kong(i+dx[k],j+dy[k])){
        Union(id[i][j],id[i+dx[k]][j+dy[k]]);
    }
    int ue=0;
    //预处理一些东西
    rep(i,1,n)rep(j,1,m)if(a[i][j])if(border(i,j))hav[get(id[i][j])]=1;
    rep(i,1,n)rep(j,1,m)if(a[i][j]){
        can[i][j]=hav[get(id[i][j])];
        if(!can[i][j])ue++;
    }

    rep(i,1,n)rep(j,1,m)if(border(i,j))if(a[i][j])
    rep(k,1,n)rep(l,1,m)if(a[k][l])
    rep(d,0,3)if(over(i+dx[d],j+dy[d])){
        //考虑计算本质不同的对有哪些
        //那么我们一开始一个点在边界外，另外一个在任意的地方
        //这样bfs下去，如果能经过某2个点，则他们本质不同
        if(zhang(k+dx[d],l+dy[d])){
            input(i,j,k,l);
        }
        if(kong(k+dx[d^2],l+dy[d^2])){
            input(i,j,k+dx[d^2],l+dy[d^2]);
        }
    }
    rep(i,1,t){
        int x=q[i][0];
        int y=q[i][1];
        int k=q[i][2];
        int l=q[i][3];
        //bfs
        rep(d,0,3){
            //枚举一个方向
            //如果这个方向2个位置都是空的，则可以走过去
            if(kong(x+dx[d^2],y+dy[d^2])&&kong(k+dx[d^2],l+dy[d^2]))input(x+dx[d^2],y+dy[d^2],k+dx[d^2],l+dy[d^2]);
            //一个是空的，一个是障碍，则只走一个
            if(zhang(x+dx[d],y+dy[d])&&kong(k+dx[d^2],l+dy[d^2]))input(x,y,k+dx[d^2],l+dy[d^2]);
            if(kong(x+dx[d^2],y+dy[d^2])&&zhang(k+dx[d],l+dy[d]))input(x+dx[d^2],y+dy[d^2],k,l);
        }
    }
    rep(i,1,tot)fa[i]=i;
    rep(i,1,n)rep(j,1,m)if(a[i][j])if(can[i][j])
    rep(k,1,n)rep(l,1,m)if(a[k][l])if(can[k][l])
    if((!vis[i][j][k][l])&&(!vis[k][l][i][j])){
        //如果两个点本质一样，用并查集连起来
        Union(id[i][j],id[k][l]);
    }
    int ans=0;
    //考虑补集转化，计算都被移出去的方案
    rep(i,1,tot)if(can[rex[get(i)]][rey[get(i)]])if(get(i)==i){
        //那么选的点都是本质相同的，考虑每个联通块，计算答案
        int sz=0;
        rep(j,1,tot)sz+=(get(j)==i);
        ans=(ans+(Pow(2,sz)-1))%P;
    }
    ans=(Pow(2,tot)-1+P-ans)%P;
    //注意，只要选了任何不和外界联通的点就一定满足答案
    ans=(ans+P-(Pow(2,ue)-1))%P;
    return ans;
}
class CoinsGame{
public:
    int ways(vector <string> board){
        //预处理
        n=board.size();
        m=board[0].size();
        rep(i,1,n)rep(j,1,m)a[i][j]=(board[i-1][j-1]=='.');
        return Main();
    }
}gt;



