#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=110000;
int sum[N];
int Main(int n,int m){
    //等价于A*B是完全平方数
    //预处理[1..x]内完全平方数的个数
    rep(i,1,m)if(i*1ll*i<=m)sum[i*1ll*i]++;
    rep(i,1,m)sum[i]+=sum[i-1];
    int ans=0;
    rep(i,1,n){
        int x=i;
        int up=m;
        //枚举A，分解质因数
        //对于指数是奇数的他一定要有，于是up/=x
        //剩下的就是累加[1..up]的完全平方数个数了
        for(int j=2;j*j<=x;j++)if(x%j==0){
            int xx=0;
            while(x%j==0){x/=j;xx^=1;}
            if(xx)up/=j;
        }
        if(x>1)up/=x;
        ans+=sum[up];
    }
    //返回答案
    return ans;
}
class TheSquareRootDilemma{
public:
    int countPairs(int N, int M){
        return Main(N,M);
    }
};



