#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<set>
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
const int N=55;
int a[N],n;
bool check(int ss){
    //因为b[i-1]<b[i]，所以我们可以贪心，让前面的b尽量小
    //这个贪心非常直观，b[i-1]越小，b[i]的选择越多，就越优
    int pre=0;
    //注意b[i]是正整数，所以令b[0]=0
    rep(i,1,n){
        //显然b[i]至少也是pre+1，所以如果a[i]+k<pre+1的话，说明已经不可能合法了，直接退出
        if(a[i]+ss<=pre)return 0;
        //a[i]比pre小的话，b[i]肯定直接等于pre+1最优
        if(a[i]<=pre){
            pre++;
        }
        else{
            //否则b[i]至少要取的值是a[i]-k，和pre+1取个max就好了
            pre=max(pre+1,a[i]-ss);
        }
    }
    //注意最后要返回1。。没开-Wall老是被坑
    return 1;
}
int Main(){
    //显然答案具有单调性，所以这里二分一发
    int l=0;int r=1001000000;
    int ans=0;
    while(l<r){
        int mid=(l+r)>>1;
        if(check(mid))ans=mid,r=mid;
        else l=mid+1;
    }
    if(check(l))ans=l;
    return ans;
}
class KingdomAndTrees{
    public:
    int minLevel(vector <int> heights){
        //初始化
        n=heights.size();
        rep(i,1,n)a[i]=heights[i-1];
        return Main();
    }
};
