#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=105;
int n,a[N];
int m=0;int M;
bool ok=0;
namespace xiao{
    bool d[N][N];
    int l[N],r[N];
    int col[N];
    int q[N];
    void check(){
        memset(l,0,sizeof l);
        memset(r,0,sizeof r);
        rep(i,1,n*2){
            //l[i]表示颜色i的左边
            //r[i]表示颜色i的右边
            if(l[a[i]])r[a[i]]=i;
            else l[a[i]]=i;
        }

        memset(d,0,sizeof d);
        //如果有相交关系，则连一条边
        rep(i,1,n)rep(j,1,n)if(i^j)
        if(l[i]<=l[j]&&l[j]<=r[i]&&r[i]<=r[j])d[i][j]=d[j][i]=1;
        memset(col,-1,sizeof col);
        //二分图染色
        while(1){
            q[0]=0;
            rep(i,1,n)if(col[i]==-1){q[++q[0]]=i;col[i]=0;break;}
            if(!q[0])break;
            rep(i,1,q[0]){
                int x=q[i];
                rep(j,1,n)if(col[j]==-1)if(d[x][j]){
                    q[++q[0]]=j;
                    col[j]=col[x]^1;
                }
            }
        }
        //染色正确则返回答案
        rep(i,1,n)rep(j,1,n)if((d[i][j])&&(col[i]==col[j]))return;
        ok=1;
    }
    void dfs(int x,int col){
        if(ok)return;
        //dfs枚举连边
        if(x==n*2+1){
            check();
        }
        if(a[x]>0){
            //已配对，跳过
            dfs(x+1,col);
            return;
        }
        //给每个未配对点强行连边
        rep(i,x+1,n*2)if(a[i]==-1){
            a[x]=a[i]=col+1;
            dfs(x+1,col+1);
            a[x]=a[i]=-1;
        }
    }
    int Main(){
        ok=0;
        //爆搜
        dfs(1,M);
        return ok;
    }
};
namespace da{
    int fx[N];
    int l[N],r[N];
    int col[N];
    int LFT[N];
    int bb[N][N];
    int q[N];
    //0:no
    //1:same
    //2:diff
    bool dj=1;
    inline void Link(int x,int y,int v){
        if(x==y){
            if(v==1)dj=0;
            return;
        }
        if(x==0){
            if(col[y]==-1)col[y]=v;
            else if(col[y]!=v){dj=0;return;}
            return;
        }
        if(bb[x][y]==-1){
            bb[x][y]=bb[y][x]=v+1;
            return;
        }
        if(bb[x][y]!=v+1){dj=0;return;}
    }
    bool check(){
        //如果方向相同且相交则直接返回
        rep(i,1,M)rep(j,1,M)if(i^j)if(fx[i]==fx[j])
        if(l[i]<=l[j]&&l[j]<=r[i]&&r[i]<=r[j])return 0;
        dj=1;
        int d=0;
        memset(col,-1,sizeof col);
        memset(bb,-1,sizeof bb);
        //接下来是解一个类似异或方程的东西
        //由于形式特殊，都是一个区间的异或等于某个数的形势，所以直接变成二分图染色
        rep(i,1,2*n){
            if(a[i]==-1)++d;
            else{
                if(l[a[i]]==i)LFT[a[i]]=d;
                else{
                    if(fx[a[i]]==1)Link(LFT[a[i]],d,0);
                    else Link(LFT[a[i]],d,(d-LFT[a[i]])&1);
                }
            }
        }
        if(!dj)return 0;
        if(col[d]==1)return 0;
        col[d]=0;
        q[0]=0;
        rep(i,1,d)if(col[i]>=0)q[++q[0]]=i;
        //二分图染色
        while(1){
            rep(i,1,d)if(col[i]==-1){
                if(q[0])break;
                q[++q[0]]=i;
                col[i]=1;
                break;
            }
            if(!q[0])break;
            rep(i,1,q[0]){
                int x=q[i];
                rep(j,1,d)if(col[j]==-1)if(bb[x][j]>0){
                    q[++q[0]]=j;
                    col[j]=col[x]^(bb[x][j]-1);
                }
            }
            q[0]=0;
        }
        rep(i,1,d)rep(j,1,d)if(bb[i][j]>0)
        if((col[i]^col[j])!=(bb[i][j]-1))return 0;
        return 1;
    }
    int Main(){
        rep(i,1,2*n)if(a[i]!=-1){
            //l[i]表示颜色i的左边
            //r[i]表示颜色i的右边
            if(l[a[i]])r[a[i]]=i;
            else l[a[i]]=i;
        }
        rep(i,0,(1<<M)-1){
            //强行枚举已经配对的圆弧的方向是在上面还是下面
            rep(j,1,M)if(i&(1<<(j-1)))fx[j]=1;
            else fx[j]=0;
            if(check())return 1;
        }
        return 0;
    }
}
int num_[N];
void relabel(){
    //离散重标号
    rep(i,1,2*n)if(a[i]!=-1){
        if(num_[a[i]])a[i]=num_[a[i]];
        else {num_[a[i]]=++M;a[i]=M;}
    }
}
int Main(){
    //离散重标号
    relabel();
    rep(i,1,n*2)if(a[i]==-1)++m;
    //讨论m的大小，分别用2种暴力
    if(m<=12)return xiao::Main();
    else return da::Main();
}
class DisjointSemicircles{
public:
    string getPossibility(vector <int> labels){
        //预处理
        n=labels.size()/2;
        rep(i,1,2*n)a[i]=labels[i-1];
        return Main()?"POSSIBLE":"IMPOSSIBLE";
    }
}gt;



