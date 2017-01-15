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
int a[N],n;
int f[N];
bool ok(int l,int r){
    //判断a[l...r]是否是5的幂次
    if(!a[l])return 0;
    LL ans=0;
    rep(i,l,r){
        //直接转成一个二进制数
        (ans<<=1)|=(a[i]);
    }
    //每次除5直到是1为止，只要每次都是5的倍数就行
    while(ans>1){
        if(ans%5)return 0;
        ans/=5;
    }
    return 1;
}
int Main(){
    memset(f,63,sizeof f);
    f[0]=0;
    //暴力dp
    rep(i,1,n)rep(j,0,i-1)
    if(ok(j+1,i))
    f[i]=min(f[i],f[j]+1);
    //要注意特判无解的情况
    if(f[n]>10000)return -1;
    return f[n];
}
class CuttingBitString{
    public:
    int getmin(string S){
        //预处理
        n=S.size();
        rep(i,1,n)a[i]=S[i-1]-'0';
        return Main();
    }
};






