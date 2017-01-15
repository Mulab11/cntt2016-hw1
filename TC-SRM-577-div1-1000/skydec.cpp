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
namespace __{
    //dinic模板
    int S,T;
    const int N=2600;
    int head[N],np[N*15],p[N*15],flow[N*15];
    int tot=1;
    void init(){
        S=N-5;T=S+1;
    }
    void add(int a,int b,int c){
        ++tot;p[tot]=b;np[tot]=head[a];head[a]=tot;flow[tot]=c;
        ++tot;p[tot]=a;np[tot]=head[b];head[b]=tot;flow[tot]=0;
    }
    int q[N],dis[N];
    int BFS(){
        memset(dis,-1,sizeof dis);
        dis[S]=0;q[q[0]=1]=S;
        rep(i,1,q[0]){
            int x=q[i];
            for(int u=head[x];u;u=np[u])if(dis[p[u]]==-1)if(flow[u]){
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
        if(dis[p[u]]==dis[x]+1)if(flow[u]){
            int tmp=dinic(p[u],min(f,flow[u]));
            ret+=tmp;f-=tmp;
            flow[u]-=tmp;flow[u^1]+=tmp;
            if(!f)break;
        }
        if(!ret)dis[x]=-1;
        return ret;
    }
    int get(){int ans=0;while(BFS()!=-1)ans+=dinic(S,1e9);return ans;}
};
const int N=55;
int id[N][N];
int n,m;int jabby;
class BoardPainting{
    public:
    int minimalSteps(vector<string> a){
        //预处理
        n=a.size();m=a[0].size();__::init();
        //对每个#建一个点
        rep(i,0,n-1)rep(j,0,m-1)
        if(a[i][j]=='#')id[i+1][j+1]=++jabby;
        rep(i,1,n)rep(j,1,m)if(id[i][j]){
            //一个横的如果右边是竖的则需要答案+1
            if(!id[i+1][j]){
                __::add(id[i][j],__::T,1);
            }
            else __::add(id[i][j],id[i+1][j],1);
            //一个竖的如果下面是横的则需要答案+1
            if(!id[i][j+1]){
                __::add(__::S,id[i][j],1);
            }
            else __::add(id[i][j+1],id[i][j],1);
        }
        return __::get();
    }
}gt;





