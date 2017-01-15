#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
LL P;
inline void add(LL &a,LL b){a+=b;if(a>=P)a-=P;}
int n,K,b,ji;
LL ans=0;
//矩阵乘法
struct mat{
    LL a[18][18];
    inline void unit(){
        memset(a,0,sizeof a);
        rep(i,0,K)a[i][i]=1;
    }
    inline void clear(){
        memset(a,0,sizeof a);
    }
};
inline mat operator *(const mat &a,const mat &b){
    mat c;c.clear();
    rep(i,0,K)rep(j,0,K)rep(k,0,K){
        add(c.a[i][j],a.a[i][k]*1ll*b.a[k][j]%P);
    }
    return c;
}
inline mat operator +(const mat &a,const mat &b){
    mat c;c.clear();
    rep(i,0,K)rep(j,0,K){
        c.a[i][j]=a.a[i][j];
        add(c.a[i][j],b.a[i][j]);
    }
    return c;
}
mat base;
mat get_comb(int l){
    //求组合数
    mat c;c.unit();
    mat dj=base;
    for(;l;l>>=1,dj=dj*dj)if(l&1)c=c*dj;
    return c;
}
mat get_pow_sum(mat A,int l){
    //A^0+A^1+...A^{l-1}
    //求\sum_{i=0}^{l-1}A**i
    mat Sc;Sc.clear();
    mat Pc;Pc.unit();
    mat Sa;Sa.unit();
    mat Pa;Pa=A;
    //Sc表示当前答案
    //Sa表示当前倍增的和
    //Pa表示当前倍增的幂
    for(;l;){
        if(l&1){
            Sc=Sc+Sa*Pc;
            Pc=Pc*Pa;
        }
        Sa=Sa+Sa*Pa;
        Pa=Pa*Pa;
        l>>=1;
    }
    return Sc;
}
int Main(){
    P*=ji;
    base.clear();
    //初始化矩阵
    rep(i,0,K){
        add(base.a[i][i],1);
        if(i<K)add(base.a[i][i+1],1);
    }

    //倍增
    for(LL step=b;step<=n;step*=b){
        LL l=n-step*(n/step)+K-1;
        LL r=n-step+K-1;
        mat gtw=get_comb(l);
        mat A=get_comb(step);
        mat ss=get_pow_sum(A,(r-l)/step+1);
        ss=gtw*ss;
        add(ans,ss.a[0][K-1]);
    }
    //因为P是ji的倍数，所以可以直接取模后除达到下取整的效果
    ans=(ans-(ans%ji))/ji;
    return (int)ans;
}
class MegaFactorial{
public:
    int countTrailingZeros(int N,int K,int B){
        P=1000000009;
        //考虑B的值
        //当B=2*3时，由于是取min,直觉来看3肯定比2少
        //B=2*5时同理，只做5
        if(B==6)B=3;
        else if(B==10)B=5;
        n=N;::K=K;ji=1;
        b=B;
        //剩下的是a^p，求出a的个数再除p即可
        //这里采用了把模数乘p再做的方法
        if(B==4){
            b=2;
            ji=2;
        }
        else
        if(B==8){
            b=2;
            ji=3;
        }
        else
        if(B==9){
            b=3;
            ji=2;
        }
        return Main();
    }
}gt;