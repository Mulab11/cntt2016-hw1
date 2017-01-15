#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef double db;
const int N=65;
namespace __{
    //费用流模板
    int head[N*3],p[N*N*55],np[N*N*55],tot;
    int cost[N*3][N*3],flow[N*3][N*3],node;
    int S,T;
    void init(){
        rep(i,1,node){
            head[i]=0;
            rep(j,1,node)cost[i][j]=flow[i][j]=0;
        }
        rep(i,1,tot)p[i]=np[i]=0;
        tot=1;node=2;S=1;T=2;
    }
    inline void add(int a,int b,int c,int d){
        ++tot;p[tot]=b;np[tot]=head[a];head[a]=tot;
        ++tot;p[tot]=a;np[tot]=head[b];head[b]=tot;
        flow[a][b]+=c;cost[a][b]-=d;cost[b][a]+=d;
    }
    int pre[N*3],q[N*N*3],dis[N*3];bool inq[N*3];
    int newnode(){return ++node;}
    int spfa(){
        rep(i,1,node){
            dis[i]=1e9;
            inq[i]=0;
            pre[i]=-1;
        }
        q[q[0]=1]=S;inq[S]=1;dis[S]=0;
        rep(i,1,q[0]){
            int x=q[i];
            for(int u=head[x];u;u=np[u]){
                int y=p[u];if(!flow[x][y])continue;
                if(cost[x][y]+dis[x]<dis[y]){
                    dis[y]=dis[x]+cost[x][y];
                    pre[y]=x;
                    if(!inq[y]){
                        q[++q[0]]=y;inq[y]=1;
                    }
                }
            }
            inq[x]=0;
        }
        return pre[T];
    }
    int get(){
        int ans=0;
        while(spfa()!=-1){
            if(dis[T]>=0)break;
            int Mi=1e9;
            for(int x=T;x!=S;x=pre[x])
            if(flow[pre[x]][x]<Mi)Mi=flow[pre[x]][x];
            ans+=Mi*dis[T];
            for(int x=T;x!=S;x=pre[x]){
                flow[pre[x]][x]-=Mi;
                flow[x][pre[x]]+=Mi;
            }
        }
        return -ans;
    }
};
int n;
vector<int>p[N];
int from[N],to[N];
bool ban[N];
bool vis[N];
int ans;
int sz[N];
int f[N][3][N][3];
//0:父亲是from
//1:父亲是to
//2:并没什么父亲
int belong[N];
int edge[N];
void dfssz(int x,int bel){
    sz[x]=1;vis[x]=1;belong[x]=bel;
    rep(i,0,p[x].size()-1)if(!ban[p[x][i]]){
        int v=from[p[x][i]]^to[p[x][i]]^x;
        edge[p[x][i]]=bel;
        if(vis[v])continue;
        dfssz(v,bel);
        sz[x]+=sz[v];
    }
}
int root[2];
vector<pii>son[N][3];
int With(int x1,int y1,int x2,int y2){
    //With(x1,y1,x2,y2)表示匹配状态(x1,y1)和(x2,y2)
    pii A=pii(x1,y1);
    pii B=pii(x2,y2);
    vector<int>id1,id2;
    __::init();
    
    //建立二分图匹配模型，边权为dp的值
    //跑一发最大费用流计算答案
    rep(i,0,son[A.fi][A.se].size()-1)
    id1.pb(__::newnode());
    rep(i,0,son[B.fi][B.se].size()-1)
    id2.pb(__::newnode());
    
    rep(i,0,son[A.fi][A.se].size()-1)
    rep(j,0,son[B.fi][B.se].size()-1){
        int val=f[son[B.fi][B.se][j].fi][son[B.fi][B.se][j].se][son[A.fi][A.se][i].fi][son[A.fi][A.se][i].se];
        __::add(id1[i],id2[j],1,val);
    }
    rep(i,0,son[A.fi][A.se].size()-1)__::add(__::S,id1[i],1,0);
    rep(i,0,son[B.fi][B.se].size()-1)__::add(id2[i],__::T,1,0);
    return __::get();
}
void dfs(int x,int zt){
    //dp
    //f[x][v1][y][v2]表示状态(x,v1)匹配(x,v2)的答案
    if(f[x][zt][root[1]][2]!=0)return;
    //状态(x,w)表示，当w<=1时，(x,0)和(x,1)分别表示边x的两个方向
    //w=2时，表示点x
    rep(i,1,n-1)if(edge[i]==1){
        f[x][zt][i][0]=f[x][zt][i][1]=1;
    }
    rep(i,1,n)if(belong[i]==1)
    f[x][zt][i][2]=1;
    
    //进行答案计算
    rep(i,0,son[x][zt].size()-1){
        dfs(son[x][zt][i].fi,son[x][zt][i].se);
    }
    
    
    rep(ano,1,n)if(belong[ano]==1){
        f[x][zt][ano][2]=With(ano,2,x,zt)+1;
    }
    rep(ano,1,n-1)if(edge[ano]==1){
        f[x][zt][ano][0]=With(ano,0,x,zt)+1;
        f[x][zt][ano][1]=With(ano,1,x,zt)+1;
    }
}
void work(){
    //初始化数组
    memset(vis,0,sizeof vis);
    memset(sz,0,sizeof sz);
    memset(f,0,sizeof f);
    memset(edge,0,sizeof edge);
    memset(belong,0,sizeof belong);
    rep(i,1,n)rep(j,0,2)son[i][j].clear();
    
    //son[i][j]表示预处理状态(i,j)的后继状态

    rep(i,1,n){
        rep(j,0,p[i].size()-1)if(!ban[p[i][j]]){
            int id=p[i][j];
            if(from[id]==i)son[i][2].pb(pii(id,0));
            else son[i][2].pb(pii(id,1));
        }
    }
    
    rep(i,1,n-1)rep(j,0,1)if(!ban[i]){
        int x;if(!j)x=to[i];else x=from[i];
        rep(k,0,p[x].size()-1)if(!ban[p[x][k]])if(p[x][k]^i){
            int id=p[x][k];
            if(from[id]==x)son[i][j].pb(pii(id,0));
            else son[i][j].pb(pii(id,1));
        }
    }
    
    
    //找到联通的两个根
    //计算出size，fa等信息
    int gt=-1;
    rep(i,1,n)if(!vis[i]){
        root[++gt]=i;
        dfssz(i,gt);
        if(sz[i]<ans)return;
    }
    //dp
    rep(i,1,n)
    if(belong[i]==0)
    if(f[i][2][root[1]][2]==0)dfs(i,2);
    rep(i,1,n)rep(j,0,2)rep(k,1,n)rep(v,0,2)if(f[i][j][k][v]>ans)ans=f[i][j][k][v];
}
int Main(){
    ans=0;
    rep(i,1,n-1){
        //因为两个连通块要求没有共同点
        //所以枚举一条边，划分成两个连通块，答案就是这两个连通块里分别有一个
        //ban[x]表示第x条边是否被ban
        ban[i]=1;
        work();
        ban[i]=0;
    }
    return ans;
}
class DeerInZooDivOne{
    public:
    int getmax(vector<int>a, vector<int>b){
        //预处理边表
        n=a.size()+1;
        rep(i,1,n-1){
            from[i]=a[i-1]+1;
            to[i]=b[i-1]+1;
            p[from[i]].pb(i);
            p[to[i]].pb(i);
        }
        return Main();
    }
}gt;


