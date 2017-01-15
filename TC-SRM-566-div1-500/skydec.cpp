#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int P=1000000007;
const int N=360;
inline int Pow(int a,int b){
    int c=1;
    for(;b;b>>=1,a=a*1ll*a%P)if(b&1)c=c*1ll*a%P;
    return c;
}
inline void add(int &a,int b){a+=b;if(a>=P)a-=P;}
inline void dec(int &a,int b){a-=b;if(a<0)a+=P;}
int n;LL m;
int f[N],g[N],c[N],a[N],d[N];
void do1(){
    //倍增循环卷积
    memset(d,0,sizeof d);
    rep(i,0,n-1)rep(j,0,n-1)add(d[(i+j)%n],a[i]*1ll*a[j]%P);
    rep(i,0,n-1)a[i]=d[i];
}
void do2(){
    //倍增循环卷积
    memset(d,0,sizeof d);
    rep(i,0,n-1)rep(j,0,n-1)add(d[(i+j)%n],c[i]*1ll*a[j]%P);
    rep(i,0,n-1)c[i]=d[i];
}
int Main(){
    f[0]=1;
    //dp一下前n步走的情况，构造出一个矩阵
    rep(i,1,n){
        memset(g,0,sizeof g);
        rep(j,0,n-1){
            add(g[(j+i)%n],f[j]);
            if(((j+n-i)%n)!=((j+i)%n))add(g[(j+n-i)%n],f[j]);
        }
        rep(j,0,n-1)f[j]=g[j];
    }
    rep(i,0,n-1)a[i]=f[i];
    c[0]=1;
    //每次n步都是一样的，所以一起倍增一下
    for(LL b=m/n;b;b>>=1,do1())if(b&1)do2();
    rep(i,0,n-1)f[i]=c[i];
    //剩下m%n步暴力
    rep(i,1,(m%n)){
        memset(g,0,sizeof g);
        rep(j,0,n-1){
            add(g[(j+i)%n],f[j]);
            if(((j+n-i)%n)!=((j+i)%n))add(g[(j+n-i)%n],f[j]);
        }
        rep(j,0,n-1)f[j]=g[j];
    }
    return f[0];
}
class PenguinEmperor{
public:
    int countJourneys(int n,LL m){
        //预处理
        ::n=n;::m=m;
        return Main();
    }
};



