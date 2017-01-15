#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=110000;
LL f[N];
class AlternateColors2{
public:
    LL countWays(int n, int k){
        LL ans=0;
        rep(i,0,n/3){
            //特判全都一样的情况
            if(k<=min(n-i,i)*3)continue;
            if(n-i<i)continue;
            ans++;
        }
        rep(i,0,n){
            //枚举最早用完的是i个
            int rest=k-3*i;
            //剩下的是k-3*i个，分配给两个颜色
            if(rest<0)continue;
            if(rest&1){
                //R,G都没用完
                if(n-3*i-(rest+1)>=0)ans+=2*(n-3*i-(rest+1)+1);
                //G用完
                ans+=2*(rest/2);
            }
            else{
                //G用完
                if(rest/2>0)
                ans+=2*(rest/2-1);
            }
        }
        if(k%3==1){
            //考虑剩下的全都没用完的情况
            rep(i,0,n)if(3*i<=n)if(3*i>=k){
                int d=n-3*i;
                ans+=(d+2)*1ll*(d+1)/2;
                break;
            }
        }
        return ans;
    }
}gt;



