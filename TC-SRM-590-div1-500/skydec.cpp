#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#include<bitset>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double db;
const int N=66;
bitset<N> f[N];int g[N],m;
int n;
LL a[N];
LL up;
bool wu;
int last[N];
void gao(bitset<N> now,int val){
    rep(i,1,n)if(last[i]&&now[i]){
        now^=f[last[i]];
        val^=g[last[i]];
    }
    int high=0;
    rep(i,1,n)if(now[i]){
        high=i;break;
    }
    if(!high){
        if(!val)return;
        wu=1;return;
    }
    last[high]=++m;
    f[m]=now;g[m]=val;
    rep(i,1,high-1)if(f[last[i]][high]){
        f[last[i]]^=now;g[last[i]]^=val;
    }
}
LL work(LL goal,int wei){
    m=0;wu=0;memset(last,0,sizeof last);
    rep(i,wei,60){
        if(wu)return 0;
        bitset<N> h;
        rep(j,1,n)h[j]=((a[j]&(1ll<<i))>0);
        gao(h,(goal&(1ll<<i))>0);
    }
    if(wu)return 0;
    return 1ll<<(n-m);
}
LL Main(){
    LL ans=0;
    LL now=0;
    per(i,60,0){
        if(up&(1ll<<i)){
            ans+=work(now,i);
            now+=1ll<<i;
        }
    }
    ans+=work(up,0);
    return ans;
}
class XorCards{
    public:
    LL numberOfWays(vector<LL> number, LL limit){
        n=number.size();up=limit;
        rep(i,1,n)a[i]=number[i-1];
        return Main();
    }
}gt;