#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
const int N=55;
const int P=1000000009;
inline int Pow(int a,int b){
    int c=1;
    for(;b;b>>=1,a=a*1ll*a%P)if(b&1)c=c*1ll*a%P;
    return c;
}
inline void add(int &a,int b){a+=b;if(a>=P)a-=P;}
inline void dec(int &a,int b){a-=b;if(a<0)a+=P;}
int head[N],np[N<<1],p[N<<1],tot,fa[N],size[N];
int fac[N],inv[N];
int ans=0;
int C(int a,int b){
    int ret=fac[a]*1ll*inv[b]%P;
    return ret*1ll*inv[a-b]%P;
}
int n,k;
inline void addedge(int a,int b){
    ++tot;p[tot]=b;np[tot]=head[a];head[a]=tot;
    ++tot;p[tot]=a;np[tot]=head[b];head[b]=tot;
}
int dfn[N],ed[N],dftot,idx[N];
void dfs(int x){
    //计算子树大小和dfs序
    //dfs序用来判断祖先关系
    size[x]=1;
    dfn[x]=++dftot;
    idx[dftot]=x;
    for(int u=head[x];u;u=np[u])if(p[u]^fa[x]){
        fa[p[u]]=x;dfs(p[u]);size[x]+=size[p[u]];
    }
    ed[x]=dftot;
}
int du[N];
int f[N];
int tmp[N];
void dp(int x,int cant=0){
    //给一个子树的点标号的方案
    //cant表示这个子树里不能有分支cant
    f[x]=1;
    int tt=0;
    for(int u=head[x];u;u=np[u])if(p[u]^cant)if(p[u]^fa[x]){
        dp(p[u]);
        f[x]=f[x]*1ll*f[p[u]]%P;
        f[x]=f[x]*1ll*inv[size[p[u]]]%P;
        //因为是组合数，所以用inv[size[p[u]]]
        tt+=size[p[u]];
    }
    f[x]=f[x]*1ll*fac[tt]%P;
}
int calc(int S,int T,int zhi){
    memset(f,0,sizeof f);
    //计算两端子树的方案数
    dp(T);
    dp(S,zhi);
    return f[T]*1ll*f[S]%P;
}
int gao1(){
    //2*k<=n的情况，图像是中间一条链，两端都是大小为k的子树
    
    //统计度数  
    rep(i,1,n)for(int u=head[i];u;u=np[u])du[i]++;
    rep(i,1,n){
        //枚举左端子树的根为i
        memset(fa,0,sizeof fa);
        memset(size,0,sizeof size);
        dfs(i);
        for(int u=head[i];u;u=np[u])if(size[p[u]]==n-k){
            //枚举一个大小为n-k的儿子，其实最多也就1个
            int y=p[u];
            bool ok=1;
            rep(t,1,n-2*k){
                //中间的链的长度是n-2*k
                //顺着链一步步走下去
                if(du[y]!=2){
                    //中途度数必须是2，不然不是链
                    ok=0;break;
                }
                for(int v=head[y];v;v=np[v])if(p[v]!=fa[y]){y=p[v];break;}
            }
            if(!ok)continue;
            if(size[y]!=k)continue;
            //计算答案
            add(ans,calc(i,y,p[u]));
        }
    }
    return ans;
}
int g[N][N][N];
int gao2(){
    //k*2>n的情况，是中间一个2*k-n的联通块，剩下是两个n-k的树
    rep(i,1,n){
        //枚举根
        int mid=2*k-n;
        //初始化，清空一些该清空的数组
        memset(fa,0,sizeof fa);
        memset(size,0,sizeof size);
        memset(dfn,0,sizeof dfn);
        memset(idx,0,sizeof idx);
        dftot=0;
        dfs(i);
        memset(g,0,sizeof g);
        memset(f,0,sizeof f);
        //因为前n-k个点和后n-k个点不能在同一子树内，所以背包时记录两维l,r
        dp(i);
        g[1][0][0]=1;
        rep(j,1,dftot)rep(l,0,k-mid)rep(r,0,k-mid)if(g[j][l][r]){
            int x=idx[j];
            int v=g[j][l][r];
            //放到第一段
            if(l+size[x]<=k-mid)add(g[ed[x]+1][l+size[x]][r],(v*1ll*inv[size[x]]%P)*1ll*f[x]%P);
            //放到第二段
            if(r+size[x]<=k-mid)add(g[ed[x]+1][l][r+size[x]],(v*1ll*inv[size[x]]%P)*1ll*f[x]%P);
            add(g[j+1][l][r],v);
        }
        add(ans,(g[n+1][k-mid][k-mid]*1ll*fac[k-mid]%P)*fac[k-mid]%P);
    }
    //还要算下中间的2*k-n个点的方案
    return (ans*1ll*Pow(2*k-n,P-2)%P)*1ll*fac[2*k-n]%P;
}
int Main(){
    //预处理阶乘和阶乘的逆元来快速求组合数
    fac[0]=1;rep(i,1,n)fac[i]=fac[i-1]*1ll*i%P;
    inv[n]=Pow(fac[n],P-2);per(i,n-1,0)inv[i]=inv[i+1]*1ll*(i+1)%P;

    //判断边界情况，k=1和k=n相当于没限制，直接返回n!
    if(k==1||k==n)return fac[n];

    //分k<=n/2和k>n/2来讨论
    if(2*k<=n)return gao1();
    else return gao2();
}
class InducedSubgraphs{
public:
    int getCount(vector <int> edge1, vector <int> edge2, int k){
        //预处理
        n=edge1.size()+1;
        rep(i,0,n-2){
            addedge(edge1[i]+1,edge2[i]+1);
        }
        ::k=k;
        return Main();
    }
}gt;

