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
namespace fl{
    //dinic算法
    const int N=5500;
    int head[N],np[N*12],p[N*12],flow[N*12],tot;
    int S,T;
    inline void init(){
        S=5100;T=5101;tot=1;
    }
    inline void add(int a,int b,int c){
        ++tot;p[tot]=b;np[tot]=head[a];head[a]=tot;flow[tot]=c;
        ++tot;p[tot]=a;np[tot]=head[b];head[b]=tot;flow[tot]=0;
    }
    int q[N],dis[N];
    int BFS(){
        q[q[0]=1]=S;memset(dis,-1,sizeof dis);dis[S]=0;
        rep(i,1,q[0]){
            int x=q[i];
            for(int u=head[x];u;u=np[u])if(flow[u])if(dis[p[u]]==-1){
                dis[p[u]]=dis[x]+1;
                q[++q[0]]=p[u];
            }
        }
        return dis[T];
    }
    int dinic(int x,int f){
        if(x==T)return f;
        int ret=0;
        for(int u=head[x];u;u=np[u])
        if(flow[u])if(dis[p[u]]==dis[x]+1){
            int tmp=dinic(p[u],min(f,flow[u]));
            f-=tmp;flow[u]-=tmp;
            flow[u^1]+=tmp;ret+=tmp;
            if(!f)break;
        }
        if(!ret)dis[x]=-1;
        return ret;
    }
    int maxflow(){
        int ans=0;
        while(BFS()!=-1)ans+=dinic(S,1e9);
        return ans;
    }
};
int n,m;
int type(int x,int y){
    //返回一个格子的类型
    if(x<=0||x>n||y<=0||y>m)return 0;
    if((x+y)%2==0)return 2;
    if(x%2==1)return 1;
    return 3;
}
int in(int x,int y){return (x-1)*m+y;}
int out(int x,int y){return (x-1)*m+y+n*m;}
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
class TheTilesDivOne{
    public:
    int find(vector<string>a){
        n=a.size();m=a[0].size();
        fl::init();
        
        //类型1：白色的点中x是奇数的
        //类型2：黑色的点
        //类型3：白色的点中x是偶数的
        //任意一个方案是一个S->1->2->3->T的流
        rep(i,1,n)rep(j,1,m)
        if(a[i-1][j-1]!='X')fl::add(in(i,j),out(i,j),1);
        rep(i,1,n)rep(j,1,m)
        if(type(i,j)==1)fl::add(fl::S,in(i,j),1);
        else if(type(i,j)==3)fl::add(out(i,j),fl::T,1);
        
        rep(i,1,n)rep(j,1,m){
            //和相邻的等级比他高1的连边
            rep(k,0,3)if(type(i+dx[k],j+dy[k])==type(i,j)+1)
            fl::add(out(i,j),in(i+dx[k],j+dy[k]),1);
        }
        return fl::maxflow();
    }
};

