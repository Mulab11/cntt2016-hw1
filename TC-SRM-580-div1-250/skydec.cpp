#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int N=55;
int x[N],y[N];
int n;
int Main(){
    int ans=0;
    rep(i,1,n)rep(j,1,n){
        //考虑暴力，因为只能抓2次鱼，暴力枚举抓两条鱼的位置
        int ret=0;
        //统计下有多少鱼被抓了
        rep(k,1,n)if((x[k]<=x[i]&&x[i]<=y[k])||(x[k]<=x[j]&&x[j]<=y[k]))ret++;
        ans=max(ans,ret);
    }
    return ans;
}
class EelAndRabbit{
public:
    int getmax(vector <int> l, vector <int> t){
        //预处理
        n=l.size();
        rep(i,1,n){
            //将每条鱼转化成一个区间
            x[i]=t[i-1];
            y[i]=l[i-1]+t[i-1];
        }
        return Main();
    }
};





