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
int a[N][N];
int n;
namespace fl{
    int S,T;
    int head[N*N],np[N*N*10],p[N*N*10],flow[N*N*10],tot;
    void init(int n){
        S=n+1;T=S+1;
        rep(i,1,T)head[i]=0;
        rep(i,1,tot)p[i]=np[i]=flow[i]=0;
        tot=1;
    }
    void add(int a,int b,int c){
        ++tot;p[tot]=b;np[tot]=head[a];head[a]=tot;flow[tot]=c;
        ++tot;p[tot]=a;np[tot]=head[b];head[b]=tot;flow[tot]=0;
    }
    int q[N*N],dis[N*N];
    int bfs(){
        memset(dis,-1,sizeof dis);
        dis[S]=0;q[q[0]=1]=S;
        rep(i,1,q[0]){
            int x=q[i];
            for(int u=head[x];u;u=np[u])if(flow[u])if(dis[p[u]]==-1){
                dis[p[u]]=dis[x]+1;
                q[++q[0]]=p[u];
            }
        }
        return dis[T];
    }
    int dinic(int x,int ff){
        if(x==T)return ff;
        int ret=0;
        for(int u=head[x];u;u=np[u])if(flow[u])if(dis[p[u]]==dis[x]+1){
            int tmp=dinic(p[u],min(ff,flow[u]));
            ret+=tmp;ff-=tmp;
            flow[u]-=tmp;flow[u^1]+=tmp;
        }
        if(!ret)dis[x]=-1;
        return ret;
    }
    int getmax(){
        int ans=0;
        while(bfs()!=-1)ans+=dinic(S,1e9);
        return ans;
    }
};
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
int Main(){
    fl::init(n*n);
    rep(i,1,n)rep(j,1,n){
        if(a[i][j]==0){
            fl::add(fl::S,(i-1)*n+j,1);
        }
        else
        if(a[i][j]==1){
        }
        else{
            fl::add((i-1)*n+j,fl::T,1);
        }
        rep(k,0,3)if(i+dx[k]>=1&&i+dx[k]<=n)if(j+dy[k]>=1&&j+dy[k]<=n){
            if(a[i][j]==0){
                if(a[i+dx[k]][j+dy[k]]==2)
                fl::add((i-1)*n+j,(i+dx[k]-1)*n+j+dy[k],1e9);
            }       
        }
    }
    int ans=0;
    rep(i,1,n)rep(j,1,n)if(a[i][j]==0)ans++;
    else if(a[i][j]==2)ans++;
    return ans-fl::getmax();
}
class FoxAndGo3{
public:
    int maxEmptyCells(vector<string> board){
        n=board.size();
        rep(i,1,n)rep(j,1,n){
            if(board[i-1][j-1]=='.')a[i][j]=0;
            else if(board[i-1][j-1]=='x')a[i][j]=1;
            else if(board[i-1][j-1]=='o')a[i][j]=2;
        }
        return Main();
    }
};