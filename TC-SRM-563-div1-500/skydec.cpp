#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
const int N=55;
pii a[N];int n;
int f[N];
int Main(){
    rep(i,0,n)f[i]=-(1e9);
    f[0]=0;
    //可以只要总的level不超过n，就一定能构造出一种方案来删除
    //于是背包即可
    rep(i,1,n){
        //01背包
        per(j,n,a[i].fi)f[j]=max(f[j],f[j-a[i].fi]+a[i].se);
    }
    int ans=0;
    rep(i,1,n)ans=max(ans,f[i]);
    return ans;
}
class SpellCards{
public:
    int maxDamage(vector <int> level, vector <int> damage){
        //预处理
        n=level.size();
        rep(i,1,n)a[i]=pii(level[i-1],damage[i-1]);
        return Main();
    }
};


