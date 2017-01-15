#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<set>
#include<map>
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
const int N=55;
const DB pi=acos(-1.0);
int gcd(int a,int b){
    if(!a||!b)return a+b;
    return gcd(b,a%b);
}
//两个帽子能配对，当且仅当h1/r1>h2/r2，且r1<r2
//于是我们需要写一个分数类来维护h1/r1的值，防止爆精度
struct fen{
    int u,d;
    fen(int x=1,int y=1){
        u=x;d=y;
        //保证分母和分子互质
        int c=gcd(u,d);
        u/=c;d/=c;
    }
};
inline bool operator <(const fen &a,const fen &b){
    return a.u*b.d<a.d*b.u;
}
multiset<fen> a;
int n,m;
struct hi{
    int r;
    fen d;
}top[N],but[N];
inline bool operator <(const hi &a,const hi &b){
    if(a.r!=b.r)return a.r<b.r;
    return a.d<b.d;
}
int Main(){
    //将所有帽子按照r的大小排序
    sort(top+1,top+1+n);
    sort(but+1,but+1+m);
    int s=1;
    int ans=0;
    rep(i,1,m){
        //每个底部帽子所能匹配的是r小于他，且h/r大于他的，每次枚举底层帽子，然后加入对应的高层帽子
        while(s<=n&&top[s].r<but[i].r){
            a.insert(top[s].d);
            ++s;
        }
        //考虑贪心，找到h/r大于他的里面最小的那个，用set的lower_bound可以很轻易地实现
        if(a.lower_bound(but[i].d)!=a.begin()){
            ++ans;
            a.erase(--a.lower_bound(but[i].d));
        }
    }
    return ans;
}
class PointyWizardHats{
    public:
    int getNumHats(vector<int> h1, vector <int> r1, vector <int> h2, vector<int> r2){
        //初始化
        n=h1.size();
        m=h2.size();
        rep(i,1,n){
            top[i].r=r1[i-1];
            top[i].d=fen(r1[i-1],h1[i-1]);
        }
        rep(i,1,m){
            but[i].r=r2[i-1];
            but[i].d=fen(r2[i-1],h2[i-1]);
        }
        return Main();
    }
};
