#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<assert.h>
#include<ctime>
#include<set>
#include<map>
#include<string>
#include<vector>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define SZ(x) ((int)((x).size()))
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double DB;
const DB pi=acos(-1.0);
const int P=1234567891;
const int N=205;
inline int Pow(int a,int b){
    int c=1;
    for(;b;b>>=1,a=a*1ll*a%P)if(b&1)c=c*1ll*a%P;
    return c;
}
inline void add(int &a,int b){
    a=(a*1ll+b)%P;
}
int st[N][4];
int m=0;
int tmp[4];
map<int,int>rp;
void dfs(int x,int col){
    //搜索最小表示法的状态
    if(x==4){
        ++m;
        rep(i,0,3)st[m][i]=tmp[i];
        rp[st[m][0]+st[m][1]*10+st[m][2]*100+st[m][3]*1000]=m;
        //用一个map记录下最小表示法的hash值，实际上并不需要map，因为st[m][3]实际上小于等于4
        return;
    }
    tmp[x]=col+1;
    //新建颜色时颜色定义为col+1
    dfs(x+1,col+1);
    rep(i,1,col){
        tmp[x]=i;
        dfs(x+1,col);
    }
}
int a[N][N];
int c[N][N];
int l;
int t[N][N];
void gao(){
    //矩阵乘法
    rep(i,0,l-1)rep(j,0,l-1){
        t[i][j]=0;
        rep(k,0,l-1)add(t[i][j],a[i][k]*1ll*a[k][j]%P);
    }
    rep(i,0,l-1)rep(j,0,l-1)a[i][j]=t[i][j];
}
void cao(){
    rep(i,0,l-1)rep(j,0,l-1){
    //矩阵乘法
        t[i][j]=0;
        rep(k,0,l-1)add(t[i][j],c[i][k]*1ll*a[k][j]%P);
    }
    rep(i,0,l-1)rep(j,0,l-1)c[i][j]=t[i][j];
}
int choose(int x,int y){
    //P(x,y)，即从x个东西里选y个出来构成一个数组，这个数组不同方案的个数
    if(x<0)return 0;
    if(y>x)return 0;
    int ret=1;
    rep(i,x-y+1,x)ret=ret*1ll*i%P;
    return ret;
}
int remix(int *d){
    //对于一个颜色数组d，返回他的最小表示法的id
    int g[4];
    int hav[10];
    memset(hav,0,sizeof hav);
    //hav表示该颜色已有的编号
    int m=0;
    rep(i,0,3)if(!hav[d[i]]){
        //根据最小表示法的定义，没编号就自动分配一个最小的
        hav[d[i]]=++m;
        g[i]=m;
    }
    else g[i]=hav[d[i]];
    //根据之前dfs预处理的编号与hash值的映射，返回答案
    int tt=rp[g[0]+g[1]*10+g[2]*100+g[3]*1000];
    if(!tt){rep(i,0,3)printf("%d ",g[i]);printf("\n");}
    return tt;
}
class TheBrickTowerHardDivOne{
    public:
    int find(int C,int K,LL H){
        tmp[0]=1;
        //dfs编号和hash值的映射
        dfs(1,1);
        //初始化矩阵
        l=m*(K+1);
        rep(i,0,l+1)c[i][i]=1;
        a[l+1][l+1]=1;
        rep(i,0,l-1){
            int s=i%m+1;
            int use=i/m;
            //枚举状态，每个状态实际上是两维的(s,use)表示最小表示法的编号为s，之前一共有use对不合法的
            int p[4];
            rep(j,0,3)p[j]=st[s][j];
            int d[4];
            int up=0;
            rep(j,0,3)up=max(up,p[j]);
            
            //sa表示顶层自己对自己的不合法对的贡献
            //01
            //23
            int sa=(p[0]==p[1])+(p[0]==p[2])+(p[1]==p[3])+(p[2]==p[3]);
            
            //如果当前状态合法，l用于给初始局面赋值，那么这个局面可以作为第一层来用，累加上
            if(sa<=K)
            a[l][s-1+sa*m]=choose(C,up);
            
            //l+1是答案累加器，最后答案是[l,l+1]
            a[i][l+1]=1;
            
            //备份原来的up
            int reup=up;

            for(d[0]=1;d[0]<=up+1;d[0]++){
                bool ff=0;
                if(d[0]==up+1){ff=1;up++;}
                for(d[1]=1;d[1]<=up+1;d[1]++){
                    bool ff=0;
                    if(d[1]==up+1){ff=1;up++;}
                    for(d[2]=1;d[2]<=up+1;d[2]++){
                        bool ff=0;
                        if(d[2]==up+1){ff=1;up++;}
                        for(d[3]=1;d[3]<=up+1;d[3]++){
                            bool ff=0;
                            if(d[3]==up+1){ff=1;up++;}
                            
                            //暴力枚举d[0],d[1],d[2],d[3]的值，中途要遵守最小表示

                            int same=0;
                            rep(j,0,3)same+=(p[j]==d[j]);
                            same+=(d[0]==d[1])+(d[0]==d[2])+(d[1]==d[3])+(d[2]==d[3]);
                            //累加颜色一样的相邻格子的对数
                            if(use+same<=K){
                                int xx=remix(d);
                                assert(xx>=1&&xx<=m);
                                //如果不超过限制的话最小表示法一下，然后乘上P(C-reup,up-reup)，即从没用过的颜色里选出新的颜色的方案数
                                //更新转移矩阵
                                add(a[i][xx-1+(use+same)*m],choose(C-reup,up-reup));
                            }
                            
                            
                            //做完后记得把up还原
                            if(ff)up--;
                        }   
                        if(ff)up--;
                    }
                    if(ff)up--;
                }
                if(ff)up--;
            }
            assert(reup==up);
        }
        
        l+=2;
        for(H++;H;H>>=1,gao())if(H&1)cao();
        return c[l-2][l-1];
    }
}gt;



