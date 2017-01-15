#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
const int N=55;
int a[N],n;
int b[N*N],m;
int Main(){
    if(m<n)return -1;
    //排序
    sort(a+1,a+1+n);
    sort(b+1,b+1+m);
    reverse(a+1,a+1+n);
    int ans=0;
    //从小到大一一对应贪心匹配
    rep(i,1,n)ans+=a[i]*b[i];
    return ans;
}
class TomekPhone{
public:
    int minKeystrokes(vector<int> a,vector<int> key){
        n=a.size();
        rep(i,1,n)::a[i]=a[i-1];
        //预处理，因为每个key[i]代表区间[1,key[i]]，所以把所有数都放到队列里
        rep(i,0,key.size()-1)rep(j,1,key[i])b[++m]=j;
        return Main();
    }
};