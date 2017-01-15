#include<bits/stdc++.h>
#define pb push_back
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=55;
int x[N],y[N],r[N],n;
int fa[N];
bool hav(int s1,int s2){
    //检验s1是否包含s2
    if(r[s1]<=r[s2])return 0;
    LL dd=(r[s1]-r[s2])*1ll*(r[s1]-r[s2]);
    return dd>=(x[s1]-x[s2])*1ll*(x[s1]-x[s2])+(y[s1]-y[s2])*1ll*(y[s1]-y[s2]);
}
int head[N],np[N];
int sg[N];
int tmp[N*N*N],tt;
vector<int>tree[N];
int getsg(int x){
    if(sg[x]!=-1)return sg[x];

    vector<int>lb;lb.clear();
    rep(i,0,tree[x].size()-1){
        //枚举在子树哪个圆里加红点
        //之后就禁用了一条链，枚举这一条链的所有儿子，计算sg值即可
        int y=tree[x][i];

        int ret=0;
        for(int z=0;y!=fa[x];z=y,y=fa[y]){
            for(int u=head[y];u;u=np[u])if(u^z)ret^=getsg(u);
        }
        //sg值存到vector里，因为递归下去时还会用到数组sg
        lb.pb(ret);
    }
    ++tt;
    //计算mex
    rep(i,0,lb.size()-1)tmp[lb[i]]=tt;
    sg[x]=0;
    while(tmp[sg[x]]==tt)++sg[x];
    return sg[x];
}
void gettree(int x){
    //tree[x]存x的所有后代，方便求sg时枚举
    if(tree[x].size())return;
    tree[x].pb(x);
    for(int y=head[x];y;y=np[y]){
        gettree(y);
        rep(i,0,tree[y].size()-1)tree[x].pb(tree[y][i]);
    }
}
string Main(){
    //这些圆之间的关系只有包含和相离，显然构成了一个树形结构
    //我们先预处理出这棵树
    rep(i,1,n)rep(j,1,n)if(i!=j)
    if(hav(j,i)){
        //在包含他的圆里选一个半径最小的作为父亲
        if((!fa[i])||(r[j]<r[fa[i]]))fa[i]=j;
    }
    //建立边表
    rep(i,1,n)if(fa[i]){
        np[i]=head[fa[i]];
        head[fa[i]]=i;
    }
    //注意可能是森林，所以我们建树时需要都dfs一下
    rep(i,1,n)gettree(i);
    memset(sg,-1,sizeof sg);
    //计算sg
    rep(i,1,n)getsg(i);

    int ans=0;
    //将sg xor起来求总的sg值
    rep(i,1,n)if(!fa[i])ans^=sg[i];
    if(ans==0)return "Bob";
    else return "Alice";
}
class CirclesGame{
public:
    string whoCanWin(vector<int> x, vector<int> y, vector<int> r){
        //预处理
        n=x.size();
        rep(i,1,n){
            ::x[i]=x[i-1];
            ::y[i]=y[i-1];
            ::r[i]=r[i-1];
        }
        return Main();
    }
};




