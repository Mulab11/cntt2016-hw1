#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=55;
int n;LL a[N];
LL w[N];
LL Main(){
    int free=0;
    //用高斯消元求出线性基和自由元的个数free
    rep(i,1,n){
        LL x=a[i];
        per(j,50,0)if(x&(1ll<<j)){
            if(!w[j]){
                w[j]=x;
                break;
            }
            else x^=w[j];
        }
        if(!x)free++;
    }
    //往回消方便求最大值
    rep(i,0,50)if(w[i])rep(j,i+1,50)if(w[j]&(1ll<<i))w[j]^=w[i];

    LL ma=0;
    rep(i,0,50)ma^=w[i];
    //对于所有自由元，肯定是选择所有基xor起来的值
    LL ans=ma*free;

    bool hh=0;
    //接下来除了第一个是所有基xor起来以外，都是基^最大值的形式
    //hh记录是否是第一个
    per(i,50,0)if(w[i]){
        if(!hh){hh=1;ans+=ma;continue;}
        ans+=(ma^w[i]);
    }
    return ans;
}
class XorAndSum{
public:
    LL maxSum(vector<LL> a){
        //预处理
        n=a.size();
        rep(i,1,n)::a[i]=a[i-1];
        return Main();
    }
};

