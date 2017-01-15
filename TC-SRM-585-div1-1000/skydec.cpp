#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int N=250000;
struct po{
    int x,y;
    inline po(int _x=0,int _y=0){x=_x;y=_y;}
}b[25],a[N];
inline po operator +(const po &a,const po &b){return po(a.x+b.x,a.y+b.y);}
inline po operator -(const po &a,const po &b){return po(a.x-b.x,a.y-b.y);}
inline LL operator *(const po &a,const po &b){return a.x*1ll*b.y-a.y*1ll*b.x;}
int n,m;
int f[N],g[N];
bool check(po x,po y){
    rep(i,1,m)if(((y-x)*(b[i]-x))<0)return 0;
    return 1;
}
LL sum1[N],sum2[N];
inline void add(LL *A,int x,LL v){
    for(;x<=n;x+=(x&(-x)))A[x]+=v;
}
inline LL ask(LL *A,int x){
    LL ans=0;
    for(;x;x-=(x&(-x)))ans+=A[x];
    return ans;
}
LL Main(){
    rep(i,1,n){
        f[i]=max(f[i-1],i);
        while(f[i]<n&&check(a[i],a[f[i]+1]))f[i]++;
        //printf("f[%d]=%d\n",i,f[i]);
    }
    int d=n+1;
    while(d>1&&check(a[d-1],a[1]))d--;

    int pre=0;
    LL ans=0;
    rep(i,1,n){
        while(d<=n&&(!check(a[d],a[i])))d++;

        while(pre<f[i]){
            ++pre;
            add(sum1,f[pre],f[pre]+1);
            add(sum2,f[pre],1);
        }

        if(d<=n){
            ans+=ask(sum1,n)-ask(sum1,d-1)-d*(ask(sum2,n)-ask(sum2,d-1));
            if(d==f[i])ans-=2;
        }
    }
    return ans;
}
class EnclosingTriangle{
public:
    LL getNumber(int m, vector <int> x, vector <int> y){
        ::m=x.size();
        rep(i,1,::m)b[i]=po(x[i-1],y[i-1]);

        per(i,m,0)a[++n]=po(i,m);
        per(i,m-1,0)a[++n]=po(0,i);
        rep(i,1,m)a[++n]=po(i,0);
        rep(i,1,m-1)a[++n]=po(m,i);
        
        return Main();
    }
 };