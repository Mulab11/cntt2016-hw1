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
LL w1,w2;
bool check(LL R,LL G,LL B,LL s){
    //先减去必须的面积/3的球数，再考虑多出来的
    R-=w1*s;
    G-=w1*s;
    B-=w1*s;
    if(R<0)return 0;
    if(B<0)return 0;
    if(G<0)return 0;
    //多出来的需要的球必须不超过(R+G+B)
    if((R+G+B)>=s*w2)return 1;
    return 0;
}
class FoxPaintingBalls{
    public:
    LL theMax(LL R,LL G,LL B,LL N){
        //显然只要确定了顶上的那个三角形的颜色就可以确定整个三角形
        //具体证明：第三行开始非边缘的球都和上面一行两个颜色不同的球相邻，于是可以直接确定
        //而非边缘的球确定完后，边缘的也可以确定
        N=N*(N+1)/2;
        w1=N/3;
        w2=N%3;
        //通过观察可以发现，当面积是3的倍数时，所有球出现次数一样
        //而面积还有可能是3的倍数+1，多出来的球的颜色是顶上的球的颜色
        LL l=0;
        LL r=R+G+B;
        if(w1)r=min(R/w1,min(G/w1,B/w1));
        LL ans=0;
        //考虑二分能排列出多少个三角形
        while(l<r){
            LL mid=(l+r)/2;
            if(check(R,G,B,mid))ans=mid,l=mid+1;
            else r=mid;
        }
        if(check(R,G,B,l))ans=l;
        return ans;
    }
};