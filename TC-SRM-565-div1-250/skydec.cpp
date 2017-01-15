#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=55;
LL f[N][N<<1];
int a[N];
LL b[N];
int n;
int Main(){
    //f[i][j]表示前i只怪，受到伤害为j，最少要多少智商值
    rep(i,0,n)rep(j,0,n*2)f[i][j]=-(LL)(1e17);
    f[0][0]=0;
    rep(i,0,n-1)rep(j,0,n*2){
        //转移，要么吃要么不吃
        if(f[i][j]>=b[i+1])f[i+1][j]=max(f[i+1][j],f[i][j]);
        f[i+1][j+a[i+1]]=max(f[i+1][j+a[i+1]],f[i][j]+b[i+1]);
    }
    int ans=1e9;
    //取个最小的返回答案
    rep(j,0,2*n)if(f[n][j]>=0)ans=min(ans,j);
    return ans;
}
class MonstersValley{
public:
    int minimumPrice(vector<long long> dread, vector <int> price){
        //预处理
        n=dread.size();
        rep(i,1,n){
            a[i]=price[i-1];
            b[i]=dread[i-1];
        }
        return Main();
    }
};


