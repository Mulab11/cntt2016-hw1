#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int N=3505;
const int P=1000000007;
inline int Pow(int a,int b){
    int c=1;
    for(;b;b>>=1,a=a*1ll*a%P)if(b&1)c=c*1ll*a%P;
    return c;
}
inline void add(int &a,int b){a+=b;if(a>=P)a-=P;}
inline void dec(int &a,int b){a-=b;if(a<0)a+=P;}
int n,k;
int fac[N],inv[N];
int cnt[N];
int C(int a,int b){
    if(b>a)return 0;
    int ret=fac[a]*1ll*inv[b]%P;
    return ret*1ll*inv[a-b]%P;
}
int f[N];
int Main(){
    int n=3000;
    fac[0]=1;
    rep(i,1,n)fac[i]=fac[i-1]*1ll*i%P;
    inv[n]=Pow(fac[n],P-2);
    per(i,n-1,0)inv[i]=inv[i+1]*1ll*(i+1)%P;

    int sum=0;
    rep(i,1,36)sum+=cnt[i];
    rep(i,1,k){
        f[i]=1;
        rep(j,1,36)f[i]=f[i]*1ll*C(i,cnt[j])%P;

        rep(j,1,i-1){
            dec(f[i],f[j]*1ll*C(sum+i-j,i-j)%P);
        }
    }
    return f[k];
}
class LISNumber{
public:
    int count(vector<int> cardsnum, int K){
        rep(i,0,cardsnum.size()-1)cnt[i+1]=cardsnum[i];
        k=K;
        return Main();
    }
}gt;