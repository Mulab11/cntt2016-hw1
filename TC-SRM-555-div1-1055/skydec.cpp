#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<set>
#include<map>
#include<string>
#include<vector>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define SZ(x) ((int)((x).size()))
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double DB;
const DB pi=acos(-1.0);
const int N=555;
bool goal[N];
char code[N];
pii a[N];
int n,m;
int ma=0;
void init(){
    int x=0;
    int t=0;
    int dj=0;
    map<int,int>h;h.clear();
    //预处理这个操作的信息，把左右边界平移到非负整数
    //然后把修改化成一堆修改操作序列的形式
    rep(i,1,m){
        if(code[i]=='<')x--;
        else if(code[i]=='>')x++;
        else if(code[i]=='1'){
            if(h.count(x))if(h[x])continue;
            a[++t]=pii(x,1);
            h[x]=1;
        }
        else{
            if(h.count(x))if(!h[x])continue;
            a[++t]=pii(x,0);
            h[x]=0;
        }
        dj=min(dj,x);
        ma=max(ma,x);
    }
    //dj表示最小值，ma表示最大值，所有位置向左平移dj-1，保证最左端是1
    m=t;
    ma=ma-dj+1;
    //不要忘了操作序列也要平移
    rep(i,1,m)a[i].fi=a[i].fi-dj+1;
}
LL gao(int p){
    LL ans=0;
    LL now=0;
    int wa=0;
    //用一个二进制数表示一个位置为起始点有多少点是满足的
    rep(i,1,m){
        if(now&(1ll<<(p+a[i].fi))){
            if(goal[p+a[i].fi]!=a[i].se)wa++;
            else wa--;
        }
        else{
            now|=(1ll<<(p+a[i].fi));
            if(goal[p+a[i].fi]!=a[i].se)wa++;
        }
        if(!wa)ans=max(ans,now);
    }
    return ans;
}
LL db[N];
int cnt[1<<20];
int getcnt(LL x){
    //求x的二进制表示中有几个1
    return cnt[x&((1<<20)-1)]+cnt[x>>20];
}
LL Main(){
    //预处理二进制位信息
    rep(i,1,(1<<20)-1)cnt[i]=cnt[i/2]+(i&1);
    init();
    if(ma>n)return 0;
    rep(i,0,n-ma){
        db[i]=gao(i);
    }
    LL ans=0;
    //考虑分类讨论，将复杂度降下来
    if(ma<=18){
        //暴力枚举一段，进行检验
        rep(i,1,n){
            int len=min(n-i+1,ma);
            for(int j=1;j<(1<<len);j+=2){
                bool ok=0;
                rep(k,0,n-ma)if((((j*1ll)<<i)&db[k])==((j*1ll)<<i)){
                    ok=1;break;
                }
                if(ok){ans++;}
            }
        }
        ++ans;
    }
    else{
        //考虑容斥
        printf("mode 2\n");
        rep(i,1,(1<<(n-ma+1))-1){
            int v=-1;
            LL all=(1ll<<(n+1))-2;
            rep(j,0,n-ma)if(i&(1<<j))v=-v,all&=db[j];
            ans+=v*(1ll<<getcnt(all));
        }
    }
    return ans;
}
class MapGuessing{
    public:
    LL countPatterns(string goal, vector<string>code){
        //预处理
        n=goal.size();
        rep(i,1,n)::goal[i]=goal[i-1]-'0';
        rep(i,0,code.size()-1)
        rep(j,0,code[i].size()-1)
        ::code[++m]=code[i][j];
        return Main();
    }
}gt;


