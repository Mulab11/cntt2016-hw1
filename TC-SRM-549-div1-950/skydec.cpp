#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<set>
#include<map>
#include<vector>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define SZ(x) ((int)((x).size()))
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double DB;
const DB pi=acos(-1.0);
const int N=10;
int n,cnt[N],L,R;
int go[N];
int ans=0;
namespace fl{
    int head[N<<1],np[N*N*N],p[N*N*N],flow[N*N*N],tot;
    int S,T;
    void init(){
        rep(i,1,T)head[i]=0;
        rep(i,1,tot)np[i]=p[i]=flow[i]=0;
        tot=1;
        S=2*n+3;
        T=S+1;
    }
    void add(int a,int b,int c){
        ++tot;p[tot]=b;np[tot]=head[a];head[a]=tot;flow[tot]=c;
        ++tot;p[tot]=a;np[tot]=head[b];head[b]=tot;flow[tot]=0;
    }
    int q[N<<1],dis[N<<1];
    int bfs(){
        memset(dis,-1,sizeof dis);
        q[q[0]=1]=S;dis[S]=0;
        rep(i,1,q[0]){
            int x=q[i];
            for(int u=head[x];u;u=np[u])if(flow[u]>0)if(dis[p[u]]==-1){
                dis[p[u]]=dis[x]+1;
                q[++q[0]]=p[u];
            }
        }
        return dis[T];
    }
    int dinic(int x,int ff){
        int ret=0;
        if(!ff)return 0;
        if(x==T)return ff;
        for(int u=head[x];u;u=np[u])if(flow[u])if(dis[p[u]]==dis[x]+1){
            int tmp=dinic(p[u],min(ff,flow[u]));
            ret+=tmp;ff-=tmp;
            flow[u]-=tmp;flow[u^1]+=tmp;
        }
        if(!ret)dis[x]=-1;
        return ret;
    }
    int getans(){
        int ans=0;
        while(bfs()!=-1){
            ans+=dinic(S,1e9);
        }
        return ans;
    }
};
int f[1<<6];
void check(int top){
    //一个答案合法的条件有两个，首先的按顺序拿的方案数要在L到R之间
    //这个我们可以通过简单的2^n*n的状压dp来解决
    memset(f,0,sizeof f);
    f[0]=1;
    rep(i,0,(1<<n)-1){
        rep(j,0,n-1)if(!(i&(1<<j)))if((go[j]&i)==go[j])
        f[i+(1<<j)]+=f[i];
    }
    if(f[(1<<n)-1]>R)return;
    if(f[(1<<n)-1]<L)return;
    //其次虽然我们给出了边的关系，但他不一定对应了一副图
    //用上下界网络流来判断是否合法，规定一个流从S流到一个柱子顶端流到了底端再流到T
    fl::init();
    rep(i,1,n){
        fl::add(2*n+1,2*i-1,1e9);
        if(!go[i-1]){
            fl::add(2*i,2*n+2,1e9);
        }
    }
    int all=0;
    fl::add(2*n+2,2*n+1,1e9);
    rep(i,0,n-1)rep(j,0,n-1)if(go[i]&(1<<j)){
        fl::add(2*i+2,2*j-1+2,1e9);
        fl::add(2*i+2,fl::T,1);
        fl::add(fl::S,2*j-1+2,1);
        ++all;
    }
    rep(i,1,n){
        fl::add(fl::S,2*i,cnt[i]);
        fl::add(2*i-1,fl::T,cnt[i]);
        all+=cnt[i];
    }
    int ret=fl::getans();
    if(ret==all)ans++;
}
void dfs(int S,int T);
void soubian(int S1,int S2,int x,int T){
    //表示S1是已经用过的点，S2是当前层的点，x是当前层还未分配边的点，T是上一层的点
    //如果已经分配完边，进行下一次搜索，点集是S1，上一层的点是S2
    if(!x){dfs(S1,S2);return;}
    int dd=0;
    //找到x的最低位进行搜索
    rep(i,0,n-1)if((1<<i)&x){dd=i;break;}
    
    //边必须是T的一个非空子集
    for(int D=T;D;D=(D-1)&T){
        go[dd]=D;
        soubian(S1,S2,x-(1<<dd),T);
    }
    //T=0表示S2是第一层，不需要连边
    if(!T){
        go[dd]=0;
        soubian(S1,S2,x-(1<<dd),T);
    }
}
void dfs(int S,int T){
    //大力出奇迹！
    //S表示已经用过的点是哪些
    //T表示上一层的点是哪些
    if(S==(1<<n)-1){
        check(T);
        return;
    }
    //每次搜索枚举~S的一个子集作为下一层
    //于是还要枚举下相邻两层的边
    int all=(1<<n)-1-S;
    for(int x=all;x;x=(x-1)&all){
        soubian(S+x,x,x,T);
    }
}
int Main(){
    dfs(0,0);
    return ans;
}
class CosmicBlocks{
    public:
    int getNumOrders(vector<int> blockTypes,int minWays,int maxWays){
        //预处理
        n=blockTypes.size();
        rep(i,1,n)cnt[i]=blockTypes[i-1];
        L=minWays;
        R=maxWays;
        return Main();
    }
}gt;



