#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
const int N=2505;
int head[N],np[N<<1],p[N<<1],tot;
int dis[N][N];
int idx[55][55],n,K;
bool key[N];
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
inline void add(int a,int b){
    ++tot;p[tot]=b;np[tot]=head[a];head[a]=tot;
}
void dfs(int x,int ff,int S,int v){
    //x表示当前点，ff表示上一个点，S表示根，v是当前深度
    dis[S][x]=v;
    for(int u=head[x];u;u=np[u])if(p[u]^ff)
    dfs(p[u],x,S,v+1);
}
int m;
int q[N];
int fa[N];
int sz[N];
double ans=0;
double C[305][305];
void pre(int x,int ff){
    //计算虚树边的长度*2的期望
    //考虑枚举一条边，他不在贡献内，当前仅当k个点都在他的一侧
    //直接组合数计算即可
    for(int u=head[x];u;u=np[u])if(p[u]^ff){
        pre(p[u],x);
        sz[x]+=sz[p[u]];
        ans+=2*(1-(C[m-sz[p[u]]][K]+C[sz[p[u]]][K])/C[m][K]);
    }
    sz[x]+=(key[x]==1);
}
double Main(){
    //计算每两个点之间的距离
    rep(i,1,n)dfs(i,0,i,0);
    rep(i,1,n)if(key[i]){
        q[++m]=i;
    }
    rep(i,0,m){
        //预处理组合数
        C[i][0]=C[i][i]=1;
        rep(j,1,i-1)C[i][j]=C[i-1][j-1]+C[i-1][j];
    }
    pre(1,0);
    rep(i,1,m)rep(j,i+1,m){
        //枚举直径为px,py，答案是所有边的长度*2-直径D
        //所有边的长度*2已经在pre里计算了
        //于是现在只要算直径的期望
        int px=q[i];int py=q[j];
        int D=dis[px][py];
        int cnt=0;
        rep(l,1,m)if(l!=i&&l!=j){
            int x=q[l];
            //计算有多少个点选了后不会影响直径长度
            //注意标号，避免算重
            if(dis[x][px]<D || (dis[x][px]==D&&x>py))
            if(dis[x][py]<D || (dis[x][py]==D&&x>px))
            ++cnt;
        }
        //组合数算一下
        ans-=(D*C[cnt][K-2])/C[m][K];
    }
    return ans;
}
class Orienteering{
public:
    double expectedLength(vector <string> w, int K){
        //预处理
        ::K=K;
        rep(i,0,w.size()-1)rep(j,0,w[0].size()-1)if(w[i][j]!='#'){
            idx[i][j]=++n;
            if(w[i][j]=='*')key[n]=1;
        }
        //将网格图转化成树
        rep(i,0,w.size()-1)rep(j,0,w[0].size()-1)if(w[i][j]!='#')
        rep(k,0,3)if(i+dx[k]>=0)if(i+dx[k]<w.size())if(j+dy[k]>=0)if(j+dy[k]<w[0].size())
        if(w[i+dx[k]][j+dy[k]]!='#')add(idx[i][j],idx[i+dx[k]][j+dy[k]]);
        return Main();
    }
};



