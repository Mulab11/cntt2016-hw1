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
int col[N];
int n;
int ff[3];
namespace fl{
    int S,T;
    int head[N],np[N*N*4],p[N*N*4],flow[N*N*4],tot;
    void init(){
        S=n+1;T=S+1;
        rep(i,1,T)head[i]=0;
        rep(i,1,tot){
            p[i]=np[i]=flow[i]=0;
        }
        tot=1;
    }
    void add(int a,int b,int c){
        ++tot;p[tot]=b;np[tot]=head[a];head[a]=tot;flow[tot]=c;
        ++tot;p[tot]=a;np[tot]=head[b];head[b]=tot;flow[tot]=0;
    }
    int dis[N],q[N];
    int dinic(int x,int ff){
        if(x==T)return ff;
        int ret=0;
        for(int u=head[x];u;u=np[u])if(dis[p[u]]==dis[x]+1)if(flow[u]){
            int tmp=dinic(p[u],min(ff,flow[u]));
            ret+=tmp;ff-=tmp;
            flow[u]-=tmp;flow[u^1]+=tmp;
        }
        if(!ret)dis[x]=-1;
        return ret;
    }
    int bfs(){
        memset(dis,-1,sizeof dis);
        q[q[0]=1]=S;dis[S]=0;
        rep(i,1,q[0]){
            int x=q[i];
            for(int u=head[x];u;u=np[u])if(dis[p[u]]==-1)if(flow[u]){
                dis[p[u]]=dis[x]+1;
                q[++q[0]]=p[u];
            }
        }
        return dis[T];
    }
    int getmax(){
        int ans=0;
        while(bfs()!=-1){
            ans+=dinic(S,1e9);
        }
        return ans;
    }
};
int Main(){
    int ans=1e9;
    rep(St,0,2){
        fl::init();
        int ds=0;
        if(St==0)ds=1;
        int dt=2;
        if(St==2)dt=1;
        int res=0;
        rep(i,1,n)if(col[i]==ds){
            fl::add(fl::S,i,1);
            ++res;
        }
        else if(col[i]==dt){
            fl::add(i,fl::T,1);
            ++res;
        }

        rep(i,1,n)rep(j,1,n)if(col[i]==ds)if(col[j]==dt)if(a[i][j])fl::add(i,j,1);

        res=fl::getmax();
        if(res<ans)ans=res;
    }
    return ans;
}
class GearsDiv1{
public:
    int getmin(string color, vector <string> graph){
        n=color.size();
        rep(i,1,n){
            if(color[i-1]=='R')col[i]=0;
            else if(color[i-1]=='G')col[i]=1;
            else col[i]=2;
        }
        rep(i,1,n)rep(j,1,n){
            a[i][j]=(graph[i-1][j-1]=='Y');
        }
        return Main();
    }
}gt;