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
const int P=1000000007;
inline void add(int &a,int b){a+=b;if(a>=P)a-=P;}
inline void dec(int &a,int b){a-=b;if(a<0)a+=P;}
int n,m;
char a[N][N];
int f[N];
int g[N];
bool ok(int x,int y){
    //返回第x行是否可以变成以下形式：
    //y个W，然后剩下的m-y+1个B
    rep(i,1,y)if(a[x][i]=='W')return 0;
    rep(i,y+1,m)if(a[x][i]=='B')return 0;
    return 1;
}
int Main(){
    //对于最后答案，黑白的分界点肯定单调不增或者单调不减
    memset(f,0,sizeof f);
    int ans=0;
    //add
    //先预处理好第一行的情况
    rep(i,0,m){
        if(ok(1,i)){
            f[i]++;
        }
    }
    rep(i,2,n){
        //先对上一行的答案求个前缀和，优化复杂度
        rep(j,1,m)add(f[j],f[j-1]);
        //将这一行的答案存储到g里
        memset(g,0,sizeof g);
        //由于要不递减，所以g[j]=f[j]即可(如果ok(i,j)的话)
        rep(j,0,m){
            if(ok(i,j))add(g[j],f[j]);
        }
        rep(j,0,m)f[j]=g[j];
    }
    rep(j,0,m)add(ans,f[j]);
    //dec
    //接下来的流程和上一个部分差不多一样
    //只是把不递增改成了不递减
    memset(f,0,sizeof f);
    rep(i,0,m)if(ok(1,i))f[i]++;
    rep(i,2,n){
        per(j,m-1,0)add(f[j],f[j+1]);
        memset(g,0,sizeof g);
        rep(j,0,m)if(ok(i,j))add(g[j],f[j]);
        rep(j,0,m)f[j]=g[j];
    }
    rep(i,0,m)add(ans,f[i]);
    
    //chongfu
    //这样算的话会出现大量的重复
    //想象一下，某个分界点全都是i的情况，肯定在递减被算了一遍，在递增也被算了一遍
    rep(i,0,m){
        bool ook=1;
        //枚举分界点全是i的情况，在方案中减掉
        rep(j,1,n)ook&=ok(j,i);
        if(ook)dec(ans,1);
    }
    
    //刚刚考虑的是前面白后面黑的情况，为了考虑前面黑后面白的情况，列翻转一下再做一遍
    rep(i,1,n)rep(j,1,m/2)swap(a[i][j],a[i][m+1-j]);

    //add
    memset(f,0,sizeof f);
    rep(i,0,m){
        if(ok(1,i))f[i]++;  
    }
    rep(i,2,n){
        rep(j,1,m)add(f[j],f[j-1]);
        memset(g,0,sizeof g);
        rep(j,0,m){
            if(ok(i,j))add(g[j],f[j]);
        }
        rep(j,0,m)f[j]=g[j];
    }
    rep(j,0,m)add(ans,f[j]);
    //dec
    memset(f,0,sizeof f);
    rep(i,0,m)if(ok(1,i))f[i]++;
    rep(i,2,n){
        per(j,m-1,0)add(f[j],f[j+1]);
        memset(g,0,sizeof g);
        rep(j,0,m)if(ok(i,j))add(g[j],f[j]);
        rep(j,0,m)f[j]=g[j];
    }
    rep(i,0,m)add(ans,f[i]);
    
    //chongfu
    rep(i,0,m){
        bool ook=1;
        rep(j,1,n)ook&=ok(j,i);
        if(ook)dec(ans,1);
    }
    

    //然而这样做完后还不对，为什么呢？
    //考虑一种非常极端的情况，每一行都是全黑或者全白色
    //那么在翻转前这种方案会被计算一遍，翻转后还是会被计算一遍
    rep(i,0,n-1){
        //枚举前i行全黑，后面n-i行全白，check并减去答案
        bool flag=1;
        rep(j,1,i)flag&=ok(j,m);
        rep(j,i+1,n)flag&=ok(j,0);
        if(flag)dec(ans,1);
    }
    rep(i,1,n){
        //枚举前i行全白，后面n-i行全黑，check并减去答案
        bool flag=1;
        rep(j,i,n)flag&=ok(j,m);
        rep(j,1,i-1)flag&=ok(j,0);
        if(flag)dec(ans,1);
    }
    //由于这样算的话，整个图是同种颜色会被算2次，所以第二次计算i是从1到n的，第一次是从0到n-1
    return ans;
}
class TwoConvexShapes{
    public:
    int countWays(vector<string> a){
        //预处理
        n=a.size();
        m=a[0].size();
        rep(i,1,n)rep(j,1,m)
        ::a[i][j]=a[i-1][j-1];
        return Main();
    }
}gt;