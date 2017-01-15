#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=55;
int head[N],np[N<<1],p[N<<1],tot,n;
inline void add(int a,int b){
    //连树边
    ++tot;p[tot]=b;np[tot]=head[a];head[a]=tot;
    ++tot;p[tot]=a;np[tot]=head[b];head[b]=tot;
}
const int S=50;
double f[N][N*3][2];
double g[N*3][2];
int sz[N];
void dfs(int x,int ff){
    sz[x]=1;
    //初始化背包
    f[x][S-1][1]=1;
    f[x][S][0]=1;
    for(int u=head[x];u;u=np[u])if(p[u]^ff){
        dfs(p[u],x);
        sz[x]+=sz[p[u]];
        memset(g,0,sizeof g);
        //背包方程转移，要注意负数
        rep(i,-50,100)rep(j,-50,100)if(i+j>=-50)if(i+j<=100)
        rep(v1,0,1)rep(v2,0,1){
            int d=i+j;
            if(v1==0&&v2==1)d+=2;
            g[d+S][v1]+=f[x][i+S][v1]*f[p[u]][j+S][v2];
        }
        rep(i,-50,100)rep(v,0,1)f[x][i+S][v]=g[i+S][v];
    }
}
double Main(){
    //考虑dp背包
    dfs(1,0);
    double ans=0;
    rep(y,-40,100)rep(v,0,1){
        //要注意y-2+v*2可能是负数，这样的话是不能算到贡献里的
        ans+=f[1][y+S][v]*max(y-2+v*2,0);
    }
    rep(i,1,n-1)ans/=2.;
    return ans;
}
class CentaurCompany{
public:
    double getvalue(vector<int> a, vector<int> b){
        //预处理
        n=a.size()+1;
        rep(i,0,n-2){
            add(a[i],b[i]);
        }
        return Main();
    }
}gt;