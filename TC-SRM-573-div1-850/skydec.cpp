#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=55;
const int P=1000000007;
inline int Pow(int a,int b){
    int c=1;
    for(;b;b>>=1,a=a*1ll*a%P)if(b&1)c=c*1ll*a%P;
    return c;
}
int fac[1010000];
int inv[1010000];
void init(int n){
    //预处理阶乘
    fac[0]=1;rep(i,1,n)fac[i]=fac[i-1]*1ll*i%P;
    inv[n]=Pow(fac[n],P-2);
    per(i,n-1,0)inv[i]=inv[i+1]*1ll*(i+1)%P;
}
inline int C(int a,int b){
    //组合数
    int ret=fac[a]*1ll*inv[b]%P;
    return ret*1ll*inv[a-b]%P;
}
inline void add(int &a,int b){a+=b;if(a>=P)a-=P;}
inline void dec(int &a,int b){a-=b;if(a<0)a+=P;}
int x[N],y[N],n,m;
int a[N];
int calc(int x,int y){
    //相当于有m次操作，每次+1或者-1，要求从x到y
    //可以计算出需要(m+abs(x-y))/2次+1
    //组合数排一下即可
    if((abs(x-y)&1)!=(m&1))return 0;
    if(abs(x-y)>m)return 0;
    return C(m,(m+abs(x-y))/2);
}
int work(){
    int ans=0;
    //枚举会面的点
    rep(i,-300000,300000){
        int ret=1;
        rep(j,1,n){
            //每条狼的方案数可以表达成一个组合数
            ret=ret*1ll*calc(a[j],i)%P;
            if(!ret)break;
        }
        add(ans,ret);
    }
    return ans;
}
int Main(){
    //预处理组合数
    init(500000);
    int ans=1;
    //坐标转化，(x,y)->(x+y,x-y)
    //这样每次(1,0)->(1,1)，(0,1)->(1,-1)
    //也就是说两维可以分开
    rep(i,1,n){
        a[i]=x[i]+y[i];
    }
    ans=ans*1ll*work()%P;
    rep(i,1,n){
        a[i]=x[i]-y[i];
    }
    ans=ans*1ll*work()%P;
    return ans;
}
class WolfPack{
public:
    int calc(vector <int> x, vector <int> y, int m){
        //预处理
        n=x.size();
        rep(i,1,n){
            ::x[i]=x[i-1];
            ::y[i]=y[i-1];
        }
        ::m=m;
        return Main();
    }
};





