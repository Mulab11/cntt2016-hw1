#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<set>
#include<string>
#include<map>
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
LL t;
LL dj(LL x){
    //返回x的阶乘中质因子2的幂次
    if(x==0)return 0;
    return x/2+dj(x/2);
}
string calc(LL x,LL y){
    if((x+y)&1)return ".";
    //每次x+y的值都是+2，所以奇数肯定是空格
    //重新设坐标是(x+y,y)，于是每次转移就跟(x+y-2,y)和(x+y-2,y-1)有关
    //将第一项除2，就变成了(nx-1,y)和(nx-1,y-1)
    //观察下他转移的条件，其实就是a[nx-1][y]^a[nx-1][y-1]，等价于求组合数mod 2
    
    //y>nx，组合数必定=0
    if(y>(x+y)/2)return ".";
    LL d1=(x+y)/2;
    //注意时间超过t也要特判
    if(d1>t)return ".";
    LL d2=y;
    LL two=dj(d1)-dj(d2)-dj(d1-d2);
    //统计下组合数mod 2是否等于0，再根据nx的奇偶性确定答案即可
    if(two>0)return ".";
    if(d1&1)return "B";
    else return "A";
}
class CheckerExpansion{
    public:
    vector<string> resultAfter(LL t,LL x0,LL y0,int w,int h){
        //预处理
        vector<string> res;
        ::t=t-1;
        res.clear();
        rep(i,0,h-1){
            res.pb("");
            rep(j,0,w-1){
                res[i]=res[i]+calc(j+x0,y0+h-i-1);
            }
        }
        return res;
    }
};


