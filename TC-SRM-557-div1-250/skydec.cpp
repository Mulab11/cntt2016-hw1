#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<string>
#include<cstdlib>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
class FoxAndMountainEasy{
public:
    string possible(int n, int h0, int hn, string a){
        //因为最后只要和达到hn即可，我们肯定尽量将U放到前面
        //我们可以预先算出有几个U，就可以check了
        
        //当奇偶性不同时直接返回NO
        if(((h0+hn)&1)!=(n&1))return "NO";
        int now=h0;
        int pre=0;
        int m=a.size();
        rep(i,0,m-1){
            //按位模拟
            if(a[i]=='U')now++;
            else{
                now--;
                if(now<0){
                    //当now<0时，我们就需要在开头放一个U了，pre记录放了几个U
                    now++;pre++;
                }
            }
        }
        //如果pre+m过大，则不行
        if(pre+m>n)return "NO";
        n-=pre+m;
        //因为奇偶性已经判断过了，所以只要判断距离是否不超过n-pre-m即可
        if(abs(hn-now)>n)return "NO";
        else return "YES";
    }
};





