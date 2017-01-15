#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
const int N=55;
int f[N][4];
int n;
int a[N];
bool ok(int l,int r,int x){
    //判断l到r内是否可以染颜色x
    rep(i,l,r)if(a[i])if(a[i]!=x)return 0;
    return 1;
}
int Main(int A,int B){
    int ans=1e9;
    rep(L,1,n){
        //枚举L的值
        memset(f,63,sizeof f);
        int ret=1e9;
        //f[i][j]表示染了前i个，末尾的颜色是j的最小代价
        rep(i,1,3)if(ok(1,L,i))f[L][i]=B;

        rep(i,L+1,n)rep(j,i-L,i-1){
            //枚举前一块染色的结尾和颜色
            rep(d,1,3)rep(t,1,3){
                if((d^t)&&(j+L!=i))continue;
                if(d^t)if(ok(j+1,j+L,d))f[i][d]=min(f[i][d],f[j][t]+B);
                if(d==t)if(ok(j+1,i,d))f[i][d]=min(f[i][d],f[j][t]+B);
            }
        }
        //统计答案
        rep(i,1,3)ret=min(ret,f[n][i]);
        ans=min(ans,ret+A*L);
    }
    return ans;
}
class Stamp{
public:
    int getMinimumCost(string a, int A, int B){
        //预处理
        n=a.size();
        rep(i,1,n)if(a[i-1]=='G')::a[i]=1;
        else if(a[i-1]=='B')::a[i]=2;
        else if(a[i-1]=='R')::a[i]=3;
        return Main(A,B);
    }
};



