#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=55;
bool a[N][N];
int n;
LL Main(){
    LL ans=1;
    //每条边会被算到2次，所以提前减掉
    rep(i,1,n)rep(j,i+1,n)if(a[i][j])ans--;
    //枚举三角形
    rep(i,1,n)rep(j,i+1,n)rep(k,j+1,n)if(j^k)if(a[i][j]&&a[j][k]&&a[i][k])ans++;

    rep(i,1,n){
        //枚举以点i为中心的菊花树
        int w=0;
        //计算答案
        rep(j,1,n)if(a[i][j])w++;
        ans+=((1ll<<w)-1);
    }
    return ans;
}
class PenguinSledding{
public:
    LL countDesigns(int n, vector <int> a, vector <int> b){
        //预处理
        ::n=n;
        rep(i,0,a.size()-1){
            ::a[a[i]][b[i]]=::a[b[i]][a[i]]=1;
        }
        return Main();
    }
};




