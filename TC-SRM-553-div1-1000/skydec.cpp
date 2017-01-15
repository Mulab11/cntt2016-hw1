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
const int N=55;
struct way{
    int s,t,w;
}da[N],xiao[N];
int n,m1,m2;
struct mes{
    bool ok;
    LL need;
    inline mes(bool _ok=0,LL _need=0){
        ok=_ok;need=_need;
    }
};
#define pll pair<LL,LL>
int head[N],p[N<<4],np[N<<4],tot;
pll w[N<<4];
inline void add(int a,int b,pll gt){
    ++tot;p[tot]=b;np[tot]=head[a];head[a]=tot;w[tot]=gt;
}
inline pll operator +(const pll &a,const pll &b){return pll(a.fi+b.fi,a.se+b.se);}
pll dis[N];
mes check(LL len){
    rep(i,1,tot){
        p[i]=np[i]=0;
    }
    tot=0;
    rep(i,1,n+1)head[i]=0;
    
    //在知道总环长后，这就是个典型的差分约束模型
    //通过足够多的连边，有解的条件等价于没有负环
    
    //为了给下面的二分更多的信息，我们在连边时记录下这个边权中环长的系数
    rep(i,1,n)add(i,i+1,pll(1,0));
    rep(i,1,m1){
        if(da[i].s<da[i].t){
            add(da[i].s,da[i].t,pll(da[i].w,0));
        }
        else{
            //边长是w-len，所以系数是-1
            add(da[i].s,da[i].t,pll(da[i].w-len,-1));
        }
    }
    rep(i,1,m2){
        if(xiao[i].s<xiao[i].t){
            add(xiao[i].t,xiao[i].s,pll(-xiao[i].w,0));
        }
        else{
            //边长是len-w，所以系数是1
            add(xiao[i].t,xiao[i].s,pll(len-xiao[i].w,1));
        }
    }
    
    //边长是-len，所以系数是-1
    add(n+1,1,pll(-len,-1));
    //边长是len，所以系数是1
    add(1,n+1,pll(len,1));
    
    bool upd=0;
    rep(i,1,n+1){
        dis[i].fi=-(LL)1e16;
    }
    dis[1].fi=0;
    dis[1].se=0;
    pll last;
    //为了找负环，这里用无限迭代的方法，迭代n*n轮
    rep(lun,1,(n+1)*(n+1)){
        upd=0;
        rep(x,1,n+1)for(int u=head[x];u;u=np[u])
        if((dis[x]+w[u]).fi>dis[p[u]].fi){
            dis[p[u]]=dis[x]+w[u];
            upd=1;
            last=dis[p[u]];
        }
        if(!upd)break;
    }
    //没有负环的话，直接返回在区间内
    if(!upd)return mes(1,0);
    else{
        //根据len的系数和，如果系数和<0，则len肯定要变小，因为变大的话负环不可能消失
        //如果系数和>0，则len必须变大，变小的话负环不会消失
        //不可能出现系数和=0的情况
        return mes(0,last.se);
    }
}
LL Main(){
    LL least,most;
    least=most=-1;
    //考虑二分总的环长的下限
    LL l=n;LL r=10000000000000ll;
    while(l<r){
        LL mid=(l+r)>>1;
        mes info=check(mid);
        //这个二分和传统的二分不一样
        //传统的二分的答案都是[x,+oo]或者[-oo,x]，而这个的答案是一个区间[l,r]
        //所以我们得根据差分约束返回的信息来确定当前是在[-oo,l-1]还是在[l,r]还是在[r+1,+oo]
        if(info.need>=0){
            r=mid;
            if(info.ok)least=mid;
        }
        else l=mid+1;
    }
    mes info=check(l);
    if(info.ok)least=l;
    
    if(least==-1)return 0;
    
    //同理，我们可以二分出环长的上限
    l=n;r=10000000000000ll;
    while(l<r){
        LL mid=(l+r)>>1;
        mes info=check(mid);
        if(info.need<=0){
            l=mid+1;
            if(info.ok)most=mid;
        }
        else r=mid;
    }
    info=check(l);
    if(info.ok)most=l;
    //返回答案
    if(most+100>=10000000000000ll)return -1;
    return most-least+1;
}
class YamanoteLine{
    public:
    LL howMany(int n,vector<int> s1,vector<int> t1,vector<int> l1,vector<int> s2,vector<int> t2,vector<int> l2){
        //预处理
        ::n=n;
        m1=s1.size();
        m2=s2.size();
        rep(i,1,m1){
            da[i].s=s1[i-1]+1;
            da[i].t=t1[i-1]+1;
            da[i].w=l1[i-1];
        }
        rep(i,1,m2){
            xiao[i].s=s2[i-1]+1;
            xiao[i].t=t2[i-1]+1;
            xiao[i].w=l2[i-1];
        }
        return Main();
    }
}gt;






