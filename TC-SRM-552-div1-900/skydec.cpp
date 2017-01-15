#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double db;
const int N=1010000;
bool f[N];int p[N],n;
int ans;
LL dfs(LL now,int me){
    //dfs(now,me)表示当前的上限是now，当前考虑了[1,me]个质数
    if(me>n)return 1;
    //如果上限没有当前的质数大，直接返回即可
    if(now<p[me])return 1;
    if(p[me]*1ll*p[me]>now){
        //后面的所有质数都只能贡献给now一个幂次
        //那么我们找出有几个质数满足条件，直接返回即可
        //这里采用二分查找的方法
        int l=me;int r=n;
        int ret=0;
        while(l<r){
            int mid=(l+r)>>1;
            if(p[mid]<=now)l=mid+1,ret=mid;
            else r=mid;
        }
        if(p[l]<=now)ret=l;
        return ret-me+2;
    }
    //枚举幂次，继续搜索
    LL sum=dfs(now,me+1);
    for(LL x=p[me];x<=now;x*=(p[me]*1ll*p[me])){
        sum+=dfs(now/x,me+1);
    }
    //经实测，这个搜索非常快，根本不需要加记忆化
    return sum;
}
class HolyNumbers{
    public:
    LL count(LL up,int maxpr){
        //预处理出[1,maxpr]中的所有质数
        rep(i,2,maxpr)if(!f[i]){
            p[++n]=i;
            for(int j=i*2;j<=maxpr;j+=i)f[j]=1;
        }
        return dfs(up,1);
    }
};



