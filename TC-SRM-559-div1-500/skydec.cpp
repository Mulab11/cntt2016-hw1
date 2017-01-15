#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=55;
int n,dep;
int head[N],np[N<<1],p[N<<1],tot;
inline void add(int a,int b){
    ++tot;p[tot]=b;np[tot]=head[a];head[a]=tot;
    ++tot;p[tot]=a;np[tot]=head[b];head[b]=tot;
}
int q[N],fa[N],sz[N];
vector<int>son[N];
inline bool cmp(const int &x,const int &y){return sz[x]>sz[y];}
LL ret=1;
int dfs(int x,int dp){
    //儿子数大于2则方案数为0
    if(son[x].size()>2)return 0;
    //判断是否递归到了底层
    if(dp==dep)return sz[x]==1;

    if(son[x].size()==1){
        //当只有一个儿子的时候，判断是否在倒数第二层
        if(sz[x]==2&&dp+1==dep)return 1;
        return 0;
    }

    
    //rest表示当前层满二叉子树应有的大小
    int rest=(1<<(dep-dp));
    int ok=0;
    int ok2=0;
    bool xx=0;
    rep(i,0,son[x].size()-1)if(rest-1==sz[son[x][i]]){
        //如果是满二叉树，则直接递归
        if(!dfs(son[x][i],dp+1))return 0;
        ok++;
    }
    else{
        if(!xx){
            //这个二叉树的儿子的结构应该是中间有一个不满，剩下的都是满的
            //xx表示前面是否有不满的
            if(!dfs(son[x][i],dp+1))return 0;
            xx=1;
        }
        else{
            //判断是否是缺一层的满的
            if(sz[son[x][i]]!=rest/2-1)return 0;
            if(!dfs(son[x][i],dp+1))return 0;
            ok2++;
        }
    }
    //如果两个子树同构，则答案*2
    if(son[x].size()==2&&sz[son[x][0]]==sz[son[x][1]])ret=ret*2;
    return 1;
}
LL work(int rt){
    memset(fa,0,sizeof fa);
    //先进行bfs，求出每个子树的大小和每个点的父亲
    q[q[0]=1]=rt;
    rep(i,1,q[0]){
        int x=q[i];
        for(int u=head[x];u;u=np[u])if(p[u]^fa[x]){
            fa[p[u]]=x;q[++q[0]]=p[u];
        }
    }
    per(i,q[0],1){
        int x=q[i];
        sz[x]=1;
        for(int u=head[x];u;u=np[u])if(fa[p[u]]==x)sz[x]+=sz[p[u]];
    }
    //将每个点的儿子按size大小sort
    rep(i,1,n)son[i].clear();
    rep(i,1,n)if(fa[i])son[fa[i]].push_back(i);
    rep(i,1,n)if(son[i].size())sort(son[i].begin(),son[i].end(),cmp);
    //因为题目的树实际上是一颗完全二叉树，所以儿子多于2个可以直接ban掉
    rep(i,1,n)if(son[i].size()>2)return 0;
    ret=1;
    int flag=dfs(rt,1);
    if(!flag)return 0;
    return ret;
}
LL Main(){
    LL ans=0;
    //枚举root为i，计算答案
    rep(i,1,n)ans+=work(i);
    return ans;
}
class HatRack{
public:
    LL countWays(vector<int> a,vector<int> b){
        //预处理
        n=a.size()+1;
        while((1<<dep)-1<n)dep++;
        rep(i,0,a.size()-1){
            add(a[i],b[i]);
        }
        return Main();
    }
}gt;



