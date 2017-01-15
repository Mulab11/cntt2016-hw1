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
const DB pi=acos(-1.0);
const int N=105;
int a[N],b[N],n,X;
bool f[N/2][N*N/4];
int dj[N];
DB Main(){
    memset(dj,0,sizeof dj);
    int m=0;
    rep(i,1,n){
        if(a[i])dj[++m]=a[i];
        if(b[i])dj[++m]=b[i];
    }
    sort(dj+1,dj+1+m);
    //考虑答案，概率是p=(a[i]>b[j]的对数)/(n*n)
    //于是我们只要算出是否存在一种填法使得(a[i]>b[j])=k即可
    dj[m+1]=X+1;
    //由于每个数只能用一次，我们把a和b的数放一起，每次只考虑一段
    int tt=0;
    //先计算初始的对数
    rep(i,1,n)if(a[i])rep(j,1,n)if(a[i]>b[j])++tt;
    f[0][tt]=1;
    rep(i,1,m+1){
        //每个数只能用一次，所以选的次数有限制
        int cnt=dj[i]-dj[i-1]-1;
        int w=0;
        rep(j,1,n)if(dj[i]-1>=b[j])++w;
        //显然这一段的所有数的贡献都可以提前算出来
        if(2*n-m<cnt)cnt=2*n-m;
        if(!cnt)continue;
        per(k,2*n-m,0)rep(d,0,n*n)if(f[k][d]){
            //因为是tc范围，所以就O(n^5)暴力实现背包了，实际上是可以优化到O(n^3)的
            int up=cnt;
            if(2*n-m-k<up)up=2*n-m-k;
            //注意w的值，因为有些段的贡献可以是0的，这里直接用除w估计上界的话会除0
            if(w)if((n*n-d)/w<up)up=(n*n-d)/w;
            rep(l,1,up)f[k+l][d+w*l]=1;
        }
    }
    int ans=-1000086;
    int rz=n*n;
    rep(j,0,n*n)rep(i,0,2*n-m)if(f[i][j]){
        //直接通过比较和中点的距离来比较|p-0.5|
        //如果直接用double可能会爆精度
        if(abs(rz-2*j)<abs(rz-2*ans))
        ans=j;
    }
    return ans*1./(n*n);
}
class KingdomAndDice{
    public:
    DB newFairness(vector<int> firstDie,vector<int> secondDie,int X){
        //初始化
        n=firstDie.size();
        ::X=X;
        rep(i,1,n){
            a[i]=firstDie[i-1];
            b[i]=secondDie[i-1];
        }
        return Main();
    }
};





