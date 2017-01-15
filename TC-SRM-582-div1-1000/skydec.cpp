#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<assert.h>
#include<map>
#include<cmath>
#define pb push_back
#include<vector>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double db;
#define div _div
LL sqrt2(LL n){
    LL x=(LL)sqrt(n);
    while((x+1)*(x+1)<=n)x++;
    while(x*x>n)x--;
    return x;
}
LL sqrt3(LL n){
    LL x=(LL)pow(n,1./3);
    while((x+1)*1ll*(x+1)*(x+1)<=n)x++;
    while(x*x*x>n)x--;
    return x;
}
bool P2[510000];
bool P3[30100];
int gcd(int a,int b){
    if(!a||!b)return a+b;
    return gcd(b,a%b);
}
vector<int> f[21000];
int miu[21000];
LL Main(LL n){
    if(n<=1)return 0;
    LL ans=0;
    rep(a,1,sqrt3(n))if(P2[a]){
        LL v=sqrt2(n/a)-a;
        if(v>0)ans+=v;
    }
    rep(b,1,sqrt2(sqrt2(n)))if(P3[b]){
        rep(k,1,sqrt3(b)){
            int dd=gcd(k*k,b);
            int _b=b/dd;
            int _k=(k*k)/dd;
            if(!P2[_b])continue;
            for(int _d=1;_d*_d<=_b;_d++)if(_b%_d==0){
                int d=_d;
                LL up=sqrt3(n/b)/_k;
                LL down=b/_k;
                up-=(up%d);
                down-=(down%d);
                if(up>down){
                    ans+=1ll*miu[d]*(f[d][up/d]-f[d][down/d]);
                }
                if(d*d==_b)continue;
                
                d=_b/d;
                up=sqrt3(n/b)/_k;
                down=b/_k;
                up-=(up%d);
                down-=(down%d);
                if(up<=down)continue;
                ans+=1ll*miu[d]*(f[d][up/d]-f[d][down/d]);
            }
        }
    }
    return ans;
}
int pr[21000];
class SemiPerfectPower{
    public:
    LL count(LL L,LL R){
        int N=500000;
        rep(i,1,N)P2[i]=1;
        for(int i=2;i*i<=N;i++)
        for(int j=i*i;j<=N;j+=i*i)
        P2[j]=0;
    
        rep(i,1,20000)P3[i]=1;
        for(int i=2;i*i*i<=20000;i++)
        for(int j=i*i*i;j<=20000;j+=i*i*i)
        P3[j]=0;
    
        rep(d,1,20000){
            int ret=0;f[d].pb(0);
            rep(j,1,N/d){
                ret+=P2[j*d];
                f[d].pb(ret);
            }
        }
        N=20000;
        rep(i,2,N)if(!pr[i]){
            rep(j,1,N/i)if(!pr[i*j])pr[i*j]=i;
        }
        miu[1]=1;
        rep(i,2,N)if((i/pr[i])%pr[i]==0)miu[i]=0;
        else miu[i]=-miu[i/pr[i]];
        
        
        return Main(R)-Main(L-1);
    }
}gt;