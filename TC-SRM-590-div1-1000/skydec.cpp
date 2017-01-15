#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<set>
#include<map>
#include<vector>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double db;
namespace __{
    const int N=200005;
    int head[N],np[N],p[N],flow[N],tot;
    int S,T;int node;
    int newnode(){return ++node;}
    void init(){
        node=2;S=1;T=2;tot=1;
    }
    inline void add(int a,int b,int c){
        ++tot;p[tot]=b;np[tot]=head[a];head[a]=tot;flow[tot]=c;
        ++tot;p[tot]=a;np[tot]=head[b];head[b]=tot;flow[tot]=0;
    }
    int q[N],dis[N];
    int BFS(){
        rep(i,1,node)dis[i]=-1;
        dis[S]=0;q[q[0]=1]=S;
        rep(i,1,q[0]){
            int x=q[i];
            for(int u=head[x];u;u=np[u])if(flow[u])if(dis[p[u]]==-1){
                q[++q[0]]=p[u];dis[p[u]]=dis[x]+1;
            }
        }
        return dis[T];
    }
    int dinic(int x,int fl){
        if(x==T)return fl;
        int ret=0;
        for(int u=head[x];u;u=np[u])if(dis[p[u]]==dis[x]+1)if(flow[u]){
            int tmp=dinic(p[u],min(fl,flow[u]));
            fl-=tmp;ret+=tmp;flow[u]-=tmp;flow[u^1]+=tmp;
            if(!fl)break;
        }
        if(!ret)dis[x]=-1;
        return ret;
    }
    int maxflow(){
        int ret=0;
        while(BFS()!=-1)ret+=dinic(S,1e9);
        return ret;
    }
};
const int N=45;
vector<int>p[N];
int want[N],n;
int dis[N];
int q[N];
int id[N][N];
int Main(){
    rep(i,2,n)dis[i]=-1;
    q[q[0]=1]=1;
    rep(i,1,q[0]){
        int x=q[i];
        rep(j,0,p[x].size()-1)if(dis[p[x][j]]==-1){
            dis[p[x][j]]=dis[x]+1;
            q[++q[0]]=p[x][j];
        }
    }
    __::init();
    rep(i,2,n)
    rep(j,0,n)id[i][j]=__::newnode();
    rep(i,2,n){
        rep(j,0,n-1){
            if(j+1<=dis[i])__::add(id[i][j],id[i][j+1],(j+1-want[i])*(j+1-want[i]));
            else __::add(id[i][j],id[i][j+1],1e9);
        }
        __::add(__::S,id[i][0],1e9);
        __::add(id[i][n],__::T,1e9);
    }
    rep(i,2,n)rep(j,0,p[i].size()-1){
        int v=p[i][j];if(v==1)continue;
        rep(j,1,n)__::add(id[i][j],id[v][j-1],1e9);
    }
    return __::maxflow()+want[1]*want[1];
}
class FoxAndCity{
    public:
    int minimalCost(vector <string> linked, vector <int> wan){
        n=linked.size();
        rep(i,1,n)want[i]=wan[i-1];
        rep(i,1,n){
            rep(j,1,n)if(linked[i-1][j-1]=='Y')
            p[i].push_back(j);
        }
        return Main();
    }
};