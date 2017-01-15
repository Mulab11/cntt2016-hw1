#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=55;
int a[N][N];
int n,m;
int Main(){
    int ret=0;
    rep(i,1,m){
        //显然每一位都是独立的，枚举每一位计算答案
        int cnt1=0;
        int cnt0=0;
        rep(j,1,n)if(a[j][i])cnt1++;else cnt0++;
        //首先至少要2个1才能区分or和xor
        //至少要1个0
        ret=max(ret,max(2-cnt1,0)+max(1-cnt0,0));
    }
    return ret;
}
class TheDevice{
public:
    int minimumAdditional(vector<string> plates){
        //预处理
        n=plates.size();
        m=plates[0].size();
        rep(i,1,n)rep(j,1,m)a[i][j]=plates[i-1][j-1]-'0';
        return Main();
    }
};
