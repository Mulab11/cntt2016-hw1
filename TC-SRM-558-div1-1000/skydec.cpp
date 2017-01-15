#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
const int N=25;
int cost[N][N];
int goal[N][N];
int n,m;
int gs(char x){
    if((x<='9')&&(x>='0'))return x-'0';
    if((x<='z')&&(x>='a'))return (x-'a')+10;
    return (x-'A')+36;
}
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
namespace fl{
    //最大流模板
    int head[N*N*10],np[N*N*10],p[N*N*10],flow[N*N*10],tot;
    int S,T;
    inline void init(){
        S=2*n*m+1;
        T=S+1;
        tot=1;
    }
    inline void add(int a,int b,int c){
        ++tot;p[tot]=b;np[tot]=head[a];head[a]=tot;flow[tot]=c;
        ++tot;p[tot]=a;np[tot]=head[b];head[b]=tot;flow[tot]=0;
    }
    int q[N*N*10],dis[N*N*10];
    int bfs(){
        rep(i,1,T)dis[i]=-1;
        q[q[0]=1]=S;
        dis[S]=0;
        rep(i,1,q[0]){
            int x=q[i];
            for(int u=head[x];u;u=np[u])if(flow[u])if(dis[p[u]]==-1){
                dis[p[u]]=dis[x]+1;q[++q[0]]=p[u];
            }
        }
        return dis[T];
    }
    int dinic(int x,int ff){
        if(x==T)return ff;
        if(!ff)return 0;
        int ret=0;
        for(int u=head[x];u;u=np[u])if(flow[u])if(dis[p[u]]==dis[x]+1){
            int tmp=dinic(p[u],min(ff,flow[u]));
            ret+=tmp;ff-=tmp;
            flow[u]-=tmp;flow[u^1]+=tmp;
            if(!ff)break;
        }
        if(!ret)dis[x]=-1;
        return ret;
    }
    int maxflow(){
        int ans=0;
        while(bfs()!=-1)ans+=dinic(S,1e9);
        return ans;
    }
};
int Main(){
    int ans=0;
    fl::init();
    rep(i,1,n)rep(j,1,m)ans+=goal[i][j];

    //对每个点建两个点
    //根据奇偶染色建类似二分图
    rep(i,1,n)rep(j,1,m)if((i+j)&1){
        fl::add(fl::S,((i-1)*m+j)*2-1,cost[i][j]);
        rep(k,0,3)if(i+dx[k]<=n&&i+dx[k]>=1&&j+dy[k]<=m&&j+dy[k]>=1){
            //连一些边，用来表示题目中的限制
            fl::add(2*((i-1)*m+j),2*((i+dx[k]-1)*m+j+dy[k]),1e9);
            fl::add(2*((i-1)*m+j)-1,2*((i+dx[k]-1)*m+j+dy[k])-1,1e9);
        }
    }
    else fl::add(((i-1)*m+j)*2,fl::T,cost[i][j]);

    //每个点拆成两个点，连一条边表示是否得到目标
    rep(i,1,n)rep(j,1,m)fl::add(2*((i-1)*m+j)-1,2*((i-1)*m+j),goal[i][j]);

    return ans-fl::maxflow();
}
class SurroundingGame{
public:
    int maxScore(vector<string> cost,vector<string> benefit){
        //预处理
        n=cost.size();
        m=cost[0].size();
        rep(i,1,n)rep(j,1,m){
            ::cost[i][j]=gs(cost[i-1][j-1]);
            ::goal[i][j]=gs(benefit[i-1][j-1]);
        }
        return Main();
    }
};
