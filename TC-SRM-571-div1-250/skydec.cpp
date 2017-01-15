#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
int n;
//存储答案
//在size=50后就不再加入
vector<string> ans;
string d[10]={"0","1","2","3","4","5","6","7","8","9"};
string trans(int x){
    string gt="";
    while(x){
        gt=d[x%10]+gt;
        x/=10;
    }
    return gt+".mp3";
}
void dfs(int x){
    //搜索
    if(ans.size()==50)return;
    ans.push_back(trans(x));
    rep(i,0,9)if(x*10ll+i<=n)dfs(x*10+i);
}
vector<string> Main(){
    //枚举第一位的值
    rep(i,1,9)if(i<=n)dfs(i);
    return ans;
}
class FoxAndMp3{
public:
    vector<string> playList(int n){
        //预处理
        ::n=n;
        return Main();
    }
}gt;


