#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<map>
#include<assert.h>
#include<vector>
#define pb push_back
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double db;
const int P=1000000007;
const int N=42;
inline int Pow(int a,int b){
    int c=1;
    for(;b;b>>=1,a=a*1ll*a%P)if(b&1)c=c*1ll*a%P;
    return c;
}
int n;
int a[N];int limit;
int fu;
vector<int>pre[22];
vector<int>suf[22];
int bit[1<<20];
int f[N];
void getf(){
    //求有多少种选择甜糖果的方法使得甜度不超过限制
    //由于n<=40，采用meet-in-the-middle算法
    
    //预处理位运算信息
    rep(i,1,(1<<20)-1)bit[i]=bit[i>>1]+(i&1);
    if(n==1){
        pre[0].pb(0);
        suf[1].pb(a[1]);
        suf[0].pb(0);
    }
    else{
        //暴力枚举一半的信息，添加到相应个数的vector里
        int M=n/2;
        rep(i,0,(1<<M)-1){
            int sum=0;
            rep(j,1,M)if((1<<(j-1))&i)sum+=a[j];
            pre[bit[i]].pb(sum);
        }
        M=(n+1)/2;
        rep(i,0,(1<<M)-1){
            int sum=0;
            rep(j,1,M)if((1<<(j-1))&i)sum+=a[j+(n/2)];
            suf[bit[i]].pb(sum);
        }
    }
    //对每个后一半的vector暴力排序
    rep(i,0,(n+1)/2)sort(suf[i].begin(),suf[i].end());
    rep(i,0,n/2)if(pre[i].size())
    for(vector<int>::iterator it=pre[i].begin();it!=pre[i].end();it++){
        //枚举前一半选的糖果的集合
        //这里pre不需要排序，优化一下常数
        //其实连pre这个vector都不用开
        int v=*it;
        if(v>limit)continue;
        v=limit-v;
        rep(j,0,(n+1)/2)if(suf[j][0]<=v){
            //枚举后一半的个数，通过二分求出有多少种方法使得不超过限制
            int l=0;int r=suf[j].size()-1;
            int rp=-1;
            while(l<r){
                int mid=(l+r)>>1;
                if(suf[j][mid]<=v)rp=mid,l=mid+1;
                else r=mid;
            }
            if(suf[j][l]<=v)rp=l;
            //直接统计
            f[i+j]=(f[i+j]+rp+1)%P;
        }
    }
}
int g[N];
int comb[N][N];
int b[N][N];int M;
int gauss(){
    //用高斯消元求矩阵行列式
    int ret=1;
    if(M==0)return 1;
    rep(i,1,M){
        int ha=0;
        rep(j,i,M)if(b[j][i]!=0)ha=j;
        if(ha==0)return 0;
        rep(j,1,M)swap(b[ha][j],b[i][j]);
        if(ha!=i)ret=P-ret;
        rep(j,i+1,M)if(b[j][i]!=0){
            int v=b[i][i]*1ll*Pow(b[j][i],P-2)%P;
            rep(k,1,M)b[j][k]=b[j][k]*1ll*v%P;
            ret=ret*1ll*Pow(v,P-2)%P;
            rep(k,1,M){
                b[j][k]=(b[j][k]+P-b[i][k])%P;
            }
        }
    }
    rep(i,1,M)ret=ret*1ll*b[i][i]%P;
    ret=(ret+P)%P;
    return ret;
}
void getg(){
    rep(i,0,n){
        //预处理组合数
        comb[i][0]=comb[i][i]=1;
        rep(j,1,i-1)comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%P;
    }
    //g[i]表示i个甜糖果的生成树方案
    rep(i,0,n){
        memset(b,0,sizeof b);
        rep(k,1,n+fu)rep(j,1,n+fu)if(k^j){
            if((k<=i&&j<=i)||(k>n)||(j>n)){
                //令需要甜的糖果和所有点连边
                //不需要甜的糖果，如果他本来是甜的，那就只和普通糖果连边
                //普通糖果和所有糖果连边
                b[k][j]=P-1;b[k][k]++;
            }
        }
        //跑一发基尔霍夫矩阵求生成树个数
        M=n+fu-1;
        g[i]=gauss();
        //注意这样子求出来，其实有些需要甜的糖果仍然是不甜的，于是需要容斥一下
        rep(j,0,i-1)g[i]=(g[i]-comb[i][j]*1ll*g[j])%P;
        g[i]=(g[i]+P)%P;
    }
}
int Main(){
    //由于点与点之间只有甜度有区别，所以我们只关心点的个数
    //令f[i]表示选i个点，甜度之和不超过限制的方案数
    getf();
    //令g[i]表示i个甜的点的生成树的个数
    getg();
    int ans=0;
    //答案就是\sum_{i=0}^{n}f[i]*g[i]
    rep(i,0,n)ans=(ans+f[i]*1ll*g[i])%P;
    return ans;
}
class SweetFruits{
    public:
    int countTrees(vector<int> sw,int _limit){
        //预处理
        rep(i,0,sw.size()-1)if(sw[i]==-1)fu++;
        else a[++n]=sw[i];
        limit=_limit;
        return Main();
    }
}gt;


