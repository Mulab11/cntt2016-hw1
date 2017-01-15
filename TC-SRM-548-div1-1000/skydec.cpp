#include<assert.h>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double db;
const int P=1000000007;
inline int Pow(int a,int b){
    int c=1;
    for(;b;b>>=1,a=a*1ll*a%P)if(b&1)c=c*1ll*a%P;
    return c;
}
const int N=55;
int fac[N*N],inv[N*N];
inline int comb(int n,int m){
    if(n<m)return 0;
    int ret=fac[n];ret=ret*1ll*inv[m]%P;
    ret=ret*1ll*inv[n-m]%P;
    return ret;
}
void init(int n){
    fac[0]=1;
    rep(i,1,n)fac[i]=fac[i-1]*1ll*i%P;
    inv[n]=Pow(fac[n],P-2);
    per(i,n-1,0)inv[i]=inv[i+1]*1ll*(i+1)%P;
}
//-------------------------------------------
//以上是预处理阶乘，逆元和组合数
//------------------------------------------
//鬼畜大讨论
namespace work0{
    int n,k;
    int f[N][N];
    int Main(int _n,int _k){
        n=_n;k=_k;
        //当m=0时，答案就是n个点，k条边的连通图个数
        //我们可以用经典的容斥dp来计算
        f[0][0]=1;
        rep(i,1,n)rep(j,0,k){
            if(j*2>i*(i-1))continue;
            //初值为i个点j条边的图的个数=C(C(i,2),j)
            f[i][j]=comb(i*(i-1)/2,j);
            rep(v,1,i-1)rep(u,0,j){
                //减去不是联通图的方案，枚举标号最小的点所在的联通块的点数为v，边数为u
                int ret=comb(i-1,v-1);
                //注意是最小标号，所以选点的方案是C(i-1,v-1)不是C(i,v)
                ret=ret*1ll*f[v][u]%P;
                ret=ret*1ll*comb((i-v)*(i-v-1)/2,j-u)%P;
                //于是剩下的边都是在剩下i-v个点的完全图的子图里
                f[i][j]=(f[i][j]+P-ret)%P;
            }
        }
        return f[n][k];
    }
};
namespace work1{
    int n,k;
    int f[N][N];
    int Main(int _n,int _k){
        if(_k<2)return 0;
        n=_n;k=_k;
        f[0][0]=1;
        //度数为1的点由恰好一个的情况
        //先dp出n个点m条边的连通图个数
        rep(i,1,n)rep(j,0,k){
            if(j*2>i*(i-1))continue;
            f[i][j]=comb(i*(i-1)/2,j);
            rep(v,1,i-1)rep(u,0,j){
                int ret=comb(i-1,v-1);
                ret=ret*1ll*f[v][u]%P;
                ret=ret*1ll*comb((i-v)*(i-v-1)/2,j-u)%P;
                f[i][j]=(f[i][j]+P-ret)%P;
            }
        }
        //情况一，这个特殊点不是割点
        //那么这个特殊点肯定是随便选两个点连边，然后剩下n个点必须是一个连通图
        //于是答案是C(n,2)*f[n][k-2]
        int ans=comb(n,2)*1ll*f[n][k-2]%P;
        //情况二，这个特殊点是割点
        //那么他的两条边连接了2个联通块
        //枚举这两个联通块的大小，统计贡献即可。
        rep(i,1,n-1)rep(j,1,n-i)if(i+j==n)
        rep(u,0,k-2)rep(v,0,k-2-u)if(u+v==k-2){
            int ret=comb(n-1,i-1);
            //为了避免算重，第一个联通块一定要包含标号最小的点
            //于是要乘上组合数C(n-1,i-1)，而不是C(n,i)
            ret=ret*1ll*f[i][u]%P;
            ret=ret*1ll*f[j][v]%P;
            //注意要乘上2条边的方案数
            ret=ret*1ll*i%P;
            ret=ret*1ll*j%P;
            ans=(ans+ret)%P;
        }
        return ans;
    }
}
inline void add(int &x,int y){x=(x+y)%P;}
namespace work2{
    int n,k;
    int f[N][N];
    int g[N][N][3][3][2];
    //点数，边数，度数情况，连通性
    int Main(int _n,int _k){
        //大讨论之恰好有2个点的情况
        n=_n;k=_k;
        if(k<3)return 0;
        f[0][0]=1;
        //先dp出n个点m条边的联通图个数
        rep(i,1,n)rep(j,0,k){
            if(j*2>i*(i-1))continue;
            f[i][j]=comb(i*(i-1)/2,j);
            rep(v,1,i-1)rep(u,0,j){
                int ret=comb(i-1,v-1);
                ret=ret*1ll*f[v][u]%P;
                ret=ret*1ll*comb((i-v)*(i-v-1)/2,j-u)%P;
                f[i][j]=(f[i][j]+P-ret)%P;
            }
            assert(f[i][j]>=0);
        }
        //考虑去掉这两个点，剩下的图被划分成若干个联通块，考虑每次背包加入包含最小标号点的联通块
        //g[i][j][d1][d2][p]表示，当前有i个点，j条边，p表示第一个点特殊点和第二个特殊点是否联通，d1,d2分别表示两个特殊点的度数
        g[0][0][0][0][0]=1;
        //有一种初始情况别漏掉，就是第一个特殊点和第二个特殊点有边
        g[0][1][1][1][1]=1;
        rep(i,0,n-1)rep(j,0,k)rep(d1,0,2)rep(d2,0,2)rep(con,0,1){
            int v=g[i][j][d1][d2][con];
            assert(v>=0);
            rep(u,1,n-i)rep(w,0,k-j)if(f[u][w]!=0){
                int ret=comb(n-i-1,u-1);
                //选择标号最小的点所在的联通块，所以是C(n-i-1,u-1)
                ret=ret*1ll*f[u][w]%P;
                rep(v1,0,2-d1)rep(v2,0,2-d2){
                    //枚举该联通块和第一个特殊点的边的个数，和第二个特殊点的边的个数
                    if(v1==0&&v2==0)continue;
                    //都为0的话，不是联通图，直接continue
                    int tmp=ret;
                    tmp=tmp*1ll*comb(u,v1)%P;
                    tmp=tmp*1ll*comb(u,v2)%P;
                    tmp=tmp*1ll*v%P;
                    //注意，如果一个联通块和两个特殊点都有边，则要更新两个特殊点的联通情况
                    add(g[i+u][j+w+v1+v2][v1+d1][v2+d2][con|(v1&&v2)],tmp);
                }
            }
        }
        //统计答案
        int ans=0;
        add(ans,g[n][k][2][2][1]);
        return ans;
    }
}
class KingdomAndCities{
    public:
    int howMany(int n,int m,int k){
        init(50*50+8);
        //讨论m的值，根据m的值来算
        if(m==0)return work0::Main(n,k);
        else if(m==1)return work1::Main(n-1,k);
        else return work2::Main(n-2,k);
    }
}gt;



