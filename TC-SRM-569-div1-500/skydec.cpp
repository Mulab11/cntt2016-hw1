#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=25;
int a[N],n,k;
int ret;
void dfs(int x,int pre,int ans){
    if(x==n){
        //最后的贡献要算一下
        ans+=(a[x]+pre+k-1)/k;
        if(ans<ret)ret=ans;
        return;
    }
    //考虑每个空隙的符号
    //进行计算答案
    int d1=min((a[x]+pre)%k,min(a[x],a[x]+pre));
    dfs(x+1,d1,ans+((a[x]+pre-d1+k-1)/k));
    d1=min((k-((a[x]+pre)%k))%k,a[x+1]);
    dfs(x+1,-d1,ans+((a[x]+pre+d1+k-1)/k));
}
int Main(){
    ret=(int)((1ll<<31)-1);
    //搜索符号
    dfs(1,0,0);
    return ret;
}
class TheJediTest{
public:
    int minimumSupervisors(vector <int> students, int K){
        //预处理
        n=students.size();
        k=K;
        rep(i,1,n)a[i]=students[i-1];
        return Main();
    }
};
