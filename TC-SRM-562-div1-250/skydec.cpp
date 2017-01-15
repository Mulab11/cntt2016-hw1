#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=55;
int a[N][N];
int n,m,T;
vector<LL> ans;
vector<LL> Main(){
    rep(i,0,2)ans.push_back(0);
    rep(i,1,n)rep(j,1,m)if(a[i][j]){
        //枚举格子
        int d=-1;
        for(int k=1;k<min(i,j);k++)if(a[i-k][j-k]){
            //找到上一个可以覆盖他的
            d=k;break;
        }
        if(d==-1){
            //没有找到的话这个格子的颜色的贡献就是T
            ans[a[i][j]-1]+=T;
        }
        else{
            //否则贡献最多只有d，因为除了[T-d+1,T]以外，其他格子都会被覆盖
            ans[a[i][j]-1]+=min(d,T);
        }
    }
    //返回答案
    return ans;
}   
class PastingPaintingDivOne{
public:
    vector<LL> countColors(vector<string> c, int T){
        //预处理
        ::T=T;
        n=c.size();
        m=c[0].size();
        rep(i,1,n)rep(j,1,m)
        if(c[i-1][j-1]=='R')a[i][j]=1;
        else if(c[i-1][j-1]=='G')a[i][j]=2;
        else if(c[i-1][j-1]=='B')a[i][j]=3;
        return Main();
    }
}gt;

