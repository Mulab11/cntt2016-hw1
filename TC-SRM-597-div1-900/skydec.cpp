#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int N=2010000;
const int P=1000000007;
inline int Pow(int a,int b){
    int c=1;
    for(;b;b>>=1,a=a*1ll*a%P)if(b&1)c=c*1ll*a%P;
    return c;
}
inline void add(int &a,int b){a+=b;if(a>=P)a-=P;}
inline void dec(int &a,int b){a-=b;if(a<0)a+=P;}
int fac[N],inv[N];
int f[N];
inline int C(int a,int b){
    return (fac[a]*1ll*inv[b]%P)*1ll*inv[a-b]%P;
}
int n;
int calc(int n,int a,int b){
    int ans=0;

    rep(x0,0,n){
        if(n-x0+a-b<0)continue;
        if((n-x0+a-b)&1)continue;
        int x1=(n-x0+a-b)/2;

        int x2=n-x0-x1;

        if(x2<0)continue;

        assert(a-x1==b-x2);

        int val=C(a-x1-x0+n-1,n-1);
        val=val*1ll*fac[n]%P;
        val=val*1ll*inv[x0]%P;
        val=val*1ll*inv[x1]%P;
        val=val*1ll*inv[x2]%P;
        val=val*1ll*Pow(2,x0)%P;
        add(ans,val);
    }
    return ans;
}
int Main(int a,int b,int c){
    n=2*(a+b+c);
    fac[0]=1;rep(i,1,n)fac[i]=fac[i-1]*1ll*i%P;
    inv[n]=Pow(fac[n],P-2);
    per(i,n-1,0)inv[i]=inv[i+1]*1ll*(i+1)%P;

    n/=2;
    int ans=0;
    
    ans=calc(a,b,c)*2%P;
    add(ans,calc(a-1,b,c));
    add(ans,calc(a+1,b,c));

    return ans*2%P;
}
class LittleElephantAndBoard{
public:
    int getNumber(int M, int R, int G, int B){
        if(R>M)return 0;
        if(G>M)return 0;
        if(B>M)return 0;
        return Main(M-R,M-G,M-B);
    }
}gt;