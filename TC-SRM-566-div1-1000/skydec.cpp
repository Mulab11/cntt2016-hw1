#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=250;
const double pi=acos(-1.0);
const int P=100007;
inline int Pow(int a,int b){
    int c=1;
    for(;b;b>>=1,a=a*1ll*a%P)if(b&1)c=c*1ll*a%P;
    return c;
}
inline void add(int &a,int b){a+=b;if(a>=P)a-=P;}
inline void dec(int &a,int b){a-=b;if(a<0)a+=P;}
//计算几何向量模板
struct po{
    double x,y;
    inline po(double _x=0.0,double _y=0.0){
        x=_x;y=_y;
    }
}a[N],b[N];
inline po operator +(const po &a,const po &b){return po(a.x+b.x,a.y+b.y);}
inline po operator -(const po &a,const po &b){return po(a.x-b.x,a.y-b.y);}
inline po operator *(const po &a,const double &b){return po(a.x*b,a.y*b);}
inline po operator /(const po &a,const double &b){return po(a.x/b,a.y/b);}
inline double operator ^(const po &a,const po &b){return a.x*b.y-a.y*b.x;}
inline double operator *(const po &a,const po &b){return a.x*b.x+a.y*b.y;}
int col[N],n,m;
double R;
bool canuse[N][N];
LL inter[N][N];
int cnt[1<<20];
int getcnt(LL x){
    //求一个二进制数x的1的个数
    return cnt[x&((1<<20)-1)]+cnt[(x>>20)&((1<<20)-1)]+cnt[x>>40];
}
int f[N][N];
int g[N][N][2];
int ff(int l,int r){
    //返回f[l+1][r-1]的值
    //因为一些边界合法性的问题，所以专门写个函数来返回
    if(l+1==r)return 1;
    if(!canuse[l][r])return 0;
    if(!canuse[l+1][r-1])return 0;
    if(!inter[l][r])return 1;
    if(inter[l][r]!=inter[l+1][r-1])return 0;
    return f[l+1][r-1];
}
LL all;
int trig(int l,int r,int x){
    //返回三角形(l,r,x)中有几种颜色
    //因为直线两侧直线颜色没有交集，所以可以直接减
    return getcnt(all)-getcnt(inter[l][r])-getcnt(inter[r][x])-getcnt(inter[x][l]);
}
int Main(){
    //预处理位运算
    rep(i,0,(1<<20)-1)cnt[i]=cnt[i>>1]+(i&1);
    all=0;
    //all表示所有color的集合
    rep(k,1,m)all|=(1ll<<col[k]);
    //canuse[i][j]表示(i,j)这条边是否能用
    rep(i,0,n+1)rep(j,0,n+1)canuse[i][j]=1;
    rep(i,1,n)rep(j,1,n)if(i^j){
        LL xiao=0;
        LL da=0;
        //xiao和da分别记录直线两侧有哪些颜色
        rep(k,1,m)if(((b[k]-a[i])^(a[j]-a[i]))<0)xiao|=(1ll<<col[k]);
        else if(((b[k]-a[i])^(a[j]-a[i]))>0)da|=(1ll<<col[k]);
        //如果颜色有交集，显然这条直线不能用
        if(xiao&da)canuse[i][j]=0;
        else canuse[i][j]=1;
    }
    rep(i,1,n)rep(j,1,n)if(i^j)if(canuse[i][j]){
        //inter[i][j]表示<i,j>内部的颜色的集合
        rep(k,1,m)if(((b[k]-a[i])^(a[j]-a[i]))>0)inter[i][j]|=(1ll<<col[k]);
    }
    rep(i,1,n){
        int j=(i%n)+1;
        rep(k,1,m)if(((b[k]-a[i])^(a[j]-a[i]))>0)return 0;
    }
    rep(i,1,n)f[i][i]=1;
    //f[i][j]表示现在的中间多边形的形状是i->j的方案数
    //为了避免算重，我们选的中间多边形的第一个端点要最小
    rep(len,2,n){
        rep(l,1,n-len+1){
            int r=l+len-1;
            //初始值
            if(canuse[l][r])add(g[l][r][0],ff(l,r));
            //考虑每次新增一条边，区域新增了一个三角形
            //所以用v2记当前中间区域是否有颜色
            rep(d,l,r-1)rep(v2,0,1)if(g[l][d][v2]){
                add(g[l][r][v2||(trig(l,d,r))],g[l][d][v2]*1ll*ff(d,r)%P);
            }
        }
        rep(l,1,n-len+1){
            int r=l+len-1;
            //转移一下f
            if(inter[l][r]==inter[l+1][r])add(f[l][r],f[l+1][r]);
            rep(k,l+1,r)if(canuse[l][k]&&(inter[l][k]==inter[l][r])){
                add(f[l][r],g[l][k][1]);
            }
        }
    }
    int ans=0;
    //统计答案
    rep(i,1,n)rep(j,i+1,n)if(g[i][j][1])if(canuse[j][i])if(inter[j][i]==inter[j+1][n]){
        if(j+1<=n)
        add(ans,g[i][j][1]*1ll*f[j+1][n]%P);
        else add(ans,g[i][j][1]);
    }
    return ans;
}
class FencingPenguins{
public:
    int countWays(int numPosts,int radius,vector<int> x,vector<int> y,string color){
        //预处理
        n=numPosts;
        m=x.size();
        R=radius;
        rep(i,0,m-1){
            b[i+1]=po(x[i],y[i]);
        }
        rep(i,1,m){
            if(color[i-1]>='a'&&color[i-1]<='z')
            col[i]=color[i-1]-'a'+1;
            else 
            col[i]=color[i-1]-'A'+27;
        }
        rep(i,0,n-1)a[i+1]=po(cos(2.*pi*i/n)*R,sin(2*pi*i/n)*R);
        return Main();
    }
}gt;




